#include <vector>
#include "TestBase.h"

// classes to test
#include "Type.h"
#include "Point.h"

// register tests here
#define REGISTER_TESTS()                                                                           \
  std::vector<TestBase *> tests;                                                                   \
  REGISTER_TEST(point_default_constructor)                                                         \
  REGISTER_TEST(point_copy_constructor)

// define tests here
TEST(point_default_constructor, { return true; });

int
main(int argc, char const * argv[])
{
  REGISTER_TESTS();

  // figure out the longest test name
  size_t max_name_length = 50;
  for (TestBase * t : tests)
    if (t->name.length() > max_name_length)
      max_name_length = t->name.length();

  // run all tests
  for (TestBase * t : tests)
  {
    std::cout << t->name;
    for (size_t i = 0; i < max_name_length + 1 - t->name.length(); i++)
      std::cout << '.';
    if (t->run())
      std::cout << TerminalColor::GREEN << "SUCCESS" << TerminalColor::DEFAULT << std::endl;
    else
      std::cout << TerminalColor::RED << "FAIL" << TerminalColor::DEFAULT << std::endl;
  }

  return 0;
}
