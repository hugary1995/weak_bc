#pragma once

#include "DirichletBC.h"

class ConstantDirichletBC : public DirichletBC
{
public:
  ConstantDirichletBC(FEProblem * problem, std::string var, std::string boundary, double value)
    : DirichletBC(problem, var, boundary), _value(value)
  {
  }

protected:
  virtual double computeNodalValue() { return _value; }

  double _value;
};
