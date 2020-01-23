#pragma once

#include "FEProblem.h"

class FEProblem;

class KernelBase
{
public:
  KernelBase(FEProblem * problem, std::string variable);
  virtual ~KernelBase() {}

  void reinitElem();
  void computeGradient();
  void computeHessian();

protected:
  virtual double computeQpGradient() = 0;
  virtual double computeQpHessian() = 0;

  FEProblem * _problem;
  std::string _variable;

  double * _objective;
  Eigen::VectorXd * _gradient;
  Eigen::MatrixXd * _hessian;

  size_t _i;
  size_t _j;
  size_t _qp;

  const Element * _current_elem;
  std::vector<const Node *> _current_nodes;
  std::vector<Point> _q_points;

  std::vector<double> _JxW;
  std::vector<std::vector<double>> _test;
  std::vector<std::vector<Point>> _grad_test;

  std::vector<double> _u;
  std::vector<Point> _grad_u;

  std::map<std::string, std::vector<double>> _coupled_variables;
  std::map<std::string, std::vector<Point>> _coupled_gradients;

private:
  std::vector<double> reinitCoupledValue(std::string var);
  std::vector<Point> reinitCoupledGradient(std::string var);
};
