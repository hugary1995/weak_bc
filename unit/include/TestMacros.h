#define COMMA ,

#define TEST(c, n, code)                                                                           \
  class c##n : public TestBase                                                                     \
  {                                                                                                \
  public:                                                                                          \
    c##n() : TestBase(#c, #n) {}                                                                   \
    virtual bool run() override { code }                                                           \
  };                                                                                               \
  TestBase * _c##n = new c##n();                                                                   \
  tests.push_back(_c##n)

#define TESTPRINT(c, n, code)                                                                      \
  class c##_##n : public TestBase                                                                  \
  {                                                                                                \
  public:                                                                                          \
    c##_##n() : TestBase(#c, #n) { printTest = true; }                                             \
    virtual bool run() override { return false; }                                                  \
    virtual void print() override { code }                                                         \
  };                                                                                               \
  TestBase * _c##_##n = new c##_##n();                                                             \
  tests.push_back(_c##_##n)

#define EXPECT_NEAR(a, b)                                                                          \
  if (std::abs(a - b) > 1e-16)                                                                     \
  return false

#define EXPECT_SAME(a, b)                                                                          \
  if (a != b)                                                                                      \
  return false
