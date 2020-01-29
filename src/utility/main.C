#include "FEProblem.h"
#include "Diffusion.h"
#include "ConstantMaterialProperty.h"
#include "QPMaterialProperty.h"
#include "FunctionMaterialProperty.h"
#include "CopyMaterialProperty.h"
#include "ConstantDirichletBC.h"
#include "RegularizedNeumannBC.h"

int
main(int argc, char const * argv[])
{
  // define mesh
  const MeshBase * m = new Mesh1DBAR2(0.0, 1.0, 50);

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

  // create boundary conditions
  DirichletBC * left = new ConstantDirichletBC(problem, "T", "left", 0);
  DirichletBC * right = new ConstantDirichletBC(problem, "T", "right", 0);
  problem->addNodalBC(left);
  problem->addNodalBC(right);

  // allocate space
  problem->init();

  // solve
  problem->computeProperties();
  std::cout << problem->computeGradient() << std::endl;
  std::cout << problem->computeHessian() << std::endl;
  problem->enforceBCs();
  std::cout << "enforced BCs" << std::endl;
  std::cout << *problem->gradientPtr() << std::endl;
  std::cout << *problem->hessianPtr() << std::endl;

  // print problem information
  // problem->print();

  // define weak constraint
  FEProblem * constraint = new FEProblem(m);

  // create variables
  constraint->addVariable("T");

  // declare material properties
  MaterialProperty * gamma = new FunctionMaterialProperty(
      constraint,
      "if(x<0.4, 0, if(x<0.5, 1500*x^2-1200*x+240, if(x<0.6, 1500*x^2-1800*x+540, 0)))");
  constraint->addMaterialProperty("gamma", gamma);
  MaterialProperty * n =
      new FunctionMaterialProperty(constraint, "if(x<0.4, 0, if(x<0.5, 1, if(x<0.6, -1, 0)))");
  constraint->addMaterialProperty("n", n);

  // create kernels
  KernelBase * bc = new RegularizedNeumannBC(constraint, "T", "gamma", "n", 3.0);
  constraint->addKernel(bc);

  // allocate space
  constraint->init();

  // solve
  constraint->computeProperties();
  std::cout << constraint->computeGradient() << std::endl;
  std::cout << constraint->computeHessian() << std::endl;

  // print problem information
  // constraint->print();

  delete problem;
  delete constraint;
  delete m;

  return 0;
}
