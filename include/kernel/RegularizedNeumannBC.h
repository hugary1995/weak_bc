#pragma once

#include "KernelBase.h"

class RegularizedNeumannBC;

class RegularizedNeumannBC : public KernelBase
{
public:
  RegularizedNeumannBC(FEProblem * problem, std::string variable, std::string gamma, double q)
    : KernelBase(problem, variable), _gamma(problem->getMaterialProperty(gamma)->data()), _q(q)
  {
  }

protected:
  double computeQpGradient()
  {
    double gamma = _gamma[_current_elem->id()][_qp];
    double n = _n[_current_elem->id()][_qp];
    return gamma * _test[_i][_qp] * _q;
  }
  double computeQpHessian()
  {
    double gamma = _gamma[_current_elem->id()][_qp];
    double n = _n[_current_elem->id()][_qp];
    return gamma * _test[_i][_qp] * _grad_test[_j][_qp].x() * n;
  }

private:
  const std::vector<std::vector<double>> & _gamma;
  const std::vector<std::vector<double>> & _n;
  double _q;
};
