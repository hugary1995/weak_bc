#pragma once

#include "FEProblem.h"

class FEProblem;

class DirichletBC
{
public:
  DirichletBC(FEProblem * problem, std::string var, std::string boundary);
  virtual ~DirichletBC() {}

  void enforce();

protected:
  virtual double computeNodalValue() = 0;

  FEProblem * _problem;
  const std::string _variable;
  const std::vector<const Node *> & _node_set;

  Eigen::VectorXd * _gradient;
  Eigen::MatrixXd * _hessian;
};
