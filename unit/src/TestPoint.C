#include "Tests.h"

void
testPoint(std::vector<TestBase *> & tests)
{
  TEST(Point, default_constructor, {
    Point p1;
    EXPECT_NEAR(p1.x(), 0.0);
    EXPECT_NEAR(p1.y(), 0.0);

    Point * p2 = new Point();
    EXPECT_NEAR(p2->x(), 0.0);
    EXPECT_NEAR(p2->y(), 0.0);
    delete p2;

    return true;
  });

  TEST(Point, initialization_constructor, {
    Point p1(1.2, 3.5);
    EXPECT_NEAR(p1.x(), 1.2);
    EXPECT_NEAR(p1.y(), 3.5);

    Point * p2 = new Point(1.2, 3.5);
    EXPECT_NEAR(p2->x(), 1.2);
    EXPECT_NEAR(p2->y(), 3.5);
    delete p2;

    return true;
  });

  TEST(Point, copy_constructor, {
    Point p(1.2, 3.5);

    Point p1(p);
    EXPECT_NEAR(p1.x(), 1.2);
    EXPECT_NEAR(p1.y(), 3.5);

    Point * p2 = new Point(p);
    EXPECT_NEAR(p2->x(), 1.2);
    EXPECT_NEAR(p2->y(), 3.5);
    delete p2;

    return true;
  });

  TEST(Point, assignment_operator, {
    Point p(1.2, 3.5);

    Point p1;
    p1 = p;
    EXPECT_NEAR(p1.x(), 1.2);
    EXPECT_NEAR(p1.y(), 3.5);

    Point * p2 = new Point();
    *p2 = p;
    EXPECT_NEAR(p2->x(), 1.2);
    EXPECT_NEAR(p2->y(), 3.5);
    delete p2;

    return true;
  });

  TESTPRINT(Point, print, {
    Point p(1.2, 3.5);
    std::cout << p;
  });
}
