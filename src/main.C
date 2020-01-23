#include "FEProblem.h"
#include "Diffusion.h"
#include "ConstantMaterialProperty.h"
#include "QPMaterialProperty.h"
#include "FunctionMaterialProperty.h"
#include "CopyMaterialProperty.h"

int
main(int argc, char const * argv[])
{
  // define mesh
  const MeshBase * m = new Mesh1DBAR2(0.0, 12.0, 3);

  // define problem
  FEProblem * problem = new FEProblem(m);

  // create variables
  problem->addVariable("T");

  // declare material properties
  MaterialProperty * k = new ConstantMaterialProperty(problem, 1.0);
  problem->addMaterialProperty("conductivity", k);
  MaterialProperty * x = new QPMaterialProperty(problem);
  problem->addMaterialProperty("x", x);
  MaterialProperty * f = new FunctionMaterialProperty(problem, "x+1");
  problem->addMaterialProperty("f", f);
  MaterialProperty * c = new CopyMaterialProperty(problem, "f");
  problem->addMaterialProperty("f_copied", c);

  // create kernels
  KernelBase * diff = new Diffusion(problem, "T");
  problem->addKernel(diff);

  // allocate space
  problem->init();

  // solve
  problem->computeProperties();
  std::cout << problem->computeGradient() << std::endl;
  std::cout << problem->computeHessian() << std::endl;

  // print problem information
  problem->print();

  delete problem;

  return 0;
}
