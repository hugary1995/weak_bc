#pragma once

#include "TestBase.h"

class TestExecutioner
{
public:
  TestExecutioner(std::vector<TestBase *> tests) : _tests(tests) {}
  void execute();

private:
  std::vector<TestBase *> _tests;
};
