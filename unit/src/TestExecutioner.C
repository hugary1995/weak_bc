#include "TestExecutioner.h"
#include "Type.h"

void
TestExecutioner::execute()
{
  // figure out the longest test name
  size_t max_name_length = 50;
  for (TestBase * t : _tests)
    if (t->nameLength() > max_name_length)
      max_name_length = t->nameLength();

  // run all tests
  for (TestBase * t : _tests)
  {
    std::cout << t->className << "." << t->testName;
    for (size_t i = 0; i < max_name_length + 1 - t->nameLength(); i++)
      std::cout << '.';

    if (!t->printTest)
    {
      if (t->run())
        std::cout << TerminalColor::GREEN << "SUCCESS" << TerminalColor::DEFAULT << std::endl;
      else
        std::cout << TerminalColor::RED << "FAIL" << TerminalColor::DEFAULT << std::endl;
    }

    if (t->printTest)
    {
      t->print();
      std::cout << std::endl;
    }
  }
}
