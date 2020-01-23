#include "Tests.h"

void
testMesh(std::vector<TestBase *> & tests)
{
  TEST(Mesh, 1D_BAR2, {
    const MeshBase * m = new Mesh1DBAR2(0.0, 1.0, 10);
    EXPECT_SAME(m->nodes().size(), 11);
    EXPECT_SAME(m->elems().size(), 10);
    delete m;

    return true;
  });

  TESTPRINT(Mesh, 1D_BAR2_print, {
    const MeshBase * m = new Mesh1DBAR2(0.0, 1.0, 10);
    m->print();
    delete m;
  });
}
