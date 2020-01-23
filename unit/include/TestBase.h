#pragma once

#include <iostream>
#include <vector>

// forward declaration
class TestBase;

class TestBase
{
public:
  TestBase() : className(""), testName("") {}
  TestBase(std::string c, std::string n) : className(c), testName(n) {}
  virtual ~TestBase() {}
  size_t nameLength() { return className.length() + testName.length(); }
  virtual bool run() = 0;
  virtual void print() {}

  std::string className;
  std::string testName;
  bool printTest = false;
};
