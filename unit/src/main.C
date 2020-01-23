#include "TestExecutioner.h"
#include "TestMacros.h"

// include tests
#include "Tests.h"

// global vector containing all tests
std::vector<TestBase *> tests;

int
main(int argc, char const * argv[])
{
  testPoint(tests);
  testNode(tests);
  testBAR2(tests);
  testMesh(tests);

  TestExecutioner e(tests);
  e.execute();
  for (TestBase * t : tests)
    delete t;

  return 0;
}
