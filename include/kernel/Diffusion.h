#pragma once

#include "KernelBase.h"

class Diffusion;

class Diffusion : public KernelBase
{
public:
  Diffusion(FEProblem * problem, std::string variable) : KernelBase(problem, variable) {}

protected:
  double computeQpGradient() { return _grad_test[_i][_qp] * _grad_u[_qp]; }
  double computeQpHessian() { return _grad_test[_i][_qp] * _grad_test[_j][_qp]; }
};
