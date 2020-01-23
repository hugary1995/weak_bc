#include "Tests.h"

void
testNode(std::vector<TestBase *> & tests)
{
  TEST(Node, default_constructor, {
    Node n1;
    EXPECT_SAME(n1.id(), 0);
    EXPECT_NEAR(n1.x(), 0.0);
    EXPECT_NEAR(n1.y(), 0.0);

    Node * n2 = new Node();
    EXPECT_SAME(n2->id(), 1);
    EXPECT_NEAR(n2->x(), 0.0);
    EXPECT_NEAR(n2->y(), 0.0);
    delete n2;

    return true;
  });

  TEST(Node, initialization_constructor, {
    Node n1(5.6, -2.2);
    EXPECT_SAME(n1.id(), 2);
    EXPECT_NEAR(n1.x(), 5.6);
    EXPECT_NEAR(n1.y(), -2.2);

    Node * n2 = new Node(5.6, -2.2);
    EXPECT_SAME(n2->id(), 3);
    EXPECT_NEAR(n2->x(), 5.6);
    EXPECT_NEAR(n2->y(), -2.2);
    delete n2;

    return true;
  });

  TEST(Node, copy_constructor, {
    Node n(3.2, -1.0);
    Node n1(n);
    EXPECT_SAME(n1.id(), 5);
    EXPECT_NEAR(n1.x(), 3.2);
    EXPECT_NEAR(n1.y(), -1.0);

    Node * n2 = new Node(n);
    EXPECT_SAME(n2->id(), 6);
    EXPECT_NEAR(n2->x(), 3.2);
    EXPECT_NEAR(n2->y(), -1.0);
    delete n2;

    return true;
  });

  TEST(Node, assignment_operator, {
    Node n(1.2, 3.5);

    Node n1;
    n1 = n;
    EXPECT_SAME(n1.id(), 8);
    EXPECT_NEAR(n1.x(), 1.2);
    EXPECT_NEAR(n1.y(), 3.5);

    Node * n2 = new Node();
    *n2 = n;
    EXPECT_SAME(n2->id(), 9);
    EXPECT_NEAR(n2->x(), 1.2);
    EXPECT_NEAR(n2->y(), 3.5);
    delete n2;

    return true;
  });

  TESTPRINT(Node, print, {
    Node n(1.2, 3.5);
    std::cout << n;
  });
}
