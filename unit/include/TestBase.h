#include <iostream>

class TestBase
{
public:
  TestBase() { name = ""; }
  TestBase(std::string n) { name = n; }
  std::string name;
  virtual bool run() = 0;
};

#define TEST(name, code)                                                                           \
  class name : public TestBase                                                                     \
  {                                                                                                \
  public:                                                                                          \
    name() : TestBase(#name) {}                                                                    \
    virtual bool run() override { code }                                                           \
  };

#define REGISTER_TEST(name)                                                                        \
  TestBase * _name = new name();                                                                   \
  tests.push_back(_name);
