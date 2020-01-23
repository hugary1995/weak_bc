#include "Tests.h"

void
testBAR2(std::vector<TestBase *> & tests)
{
  TEST(BAR2, constructor, {
    const Node * n1 = new Node(1.2, 3.5);
    const Node * n2 = new Node(-5.5, 17.1);
    Element * e = new BAR2({n1, n2});
    EXPECT_SAME(e->nodes()[0], n1);
    EXPECT_SAME(e->nodes()[1], n2);
    EXPECT_SAME(e->id(), 0);
    delete n1;
    delete n2;
    delete e;

    return true;
  });

  TEST(BAR2, quadrature_points, {
    const Node * n1 = new Node(1.2, 3.5);
    const Node * n2 = new Node(-5.5, 17.1);
    Element * e = new BAR2({n1, n2});
    EXPECT_NEAR(e->qPoints()[0].x(), -std::sqrt(3.0) / 3.0);
    EXPECT_NEAR(e->qPoints()[1].x(), std::sqrt(3.0) / 3.0);
    delete n1;
    delete n2;
    delete e;

    return true;
  });

  TEST(BAR2, weights, {
    const Node * n1 = new Node(1.2, 3.5);
    const Node * n2 = new Node(-5.5, 17.1);
    Element * e = new BAR2({n1, n2});
    EXPECT_NEAR(e->weights()[0], 1.0);
    EXPECT_NEAR(e->weights()[1], 1.0);
    delete n1;
    delete n2;
    delete e;

    return true;
  });

  TEST(BAR2, test_function, {
    const Node * n1 = new Node(1.2, 3.5);
    const Node * n2 = new Node(-5.5, 17.1);
    Element * e = new BAR2({n1, n2});
    EXPECT_NEAR(e->test()[0][0], (1.0 + std::sqrt(3.0) / 3.0) / 2.0);
    EXPECT_NEAR(e->test()[0][1], (1.0 - std::sqrt(3.0) / 3.0) / 2.0);
    EXPECT_NEAR(e->test()[1][0], (1.0 - std::sqrt(3.0) / 3.0) / 2.0);
    EXPECT_NEAR(e->test()[1][1], (1.0 + std::sqrt(3.0) / 3.0) / 2.0);
    delete n1;
    delete n2;
    delete e;

    return true;
  });

  TEST(BAR2, JxW, {
    const Node * n1 = new Node(1.2, 3.5);
    const Node * n2 = new Node(-5.5, 17.1);
    Element * e = new BAR2({n1, n2});
    EXPECT_NEAR(e->JxW()[0], -3.35);
    EXPECT_NEAR(e->JxW()[1], -3.35);
    delete n1;
    delete n2;
    delete e;

    return true;
  });

  TEST(BAR2, test_function_gradient, {
    const Node * n1 = new Node(1.2, 3.5);
    const Node * n2 = new Node(-5.5, 17.1);
    Element * e = new BAR2({n1, n2});
    EXPECT_NEAR(e->gradTest()[0][0].x(), 1.0 / 6.7);
    EXPECT_NEAR(e->gradTest()[0][1].x(), 1.0 / 6.7);
    EXPECT_NEAR(e->gradTest()[1][0].x(), -1.0 / 6.7);
    EXPECT_NEAR(e->gradTest()[1][1].x(), -1.0 / 6.7);
    delete n1;
    delete n2;
    delete e;

    return true;
  });

  TESTPRINT(BAR2, print, {
    const Node * n1 = new Node(1.2, 3.5);
    const Node * n2 = new Node(-5.5, 17.1);
    BAR2 e({n1, n2});
    std::cout << e;
    delete n1;
    delete n2;
  });
}
