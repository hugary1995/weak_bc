#pragma once

#include "FEProblem.h"

class FEProblem;

class MaterialProperty
{
public:
  MaterialProperty(FEProblem * problem);
  virtual ~MaterialProperty() {}

  void resize(size_t nelems);
  void reinitElem();
  virtual void computeProperty();
  const std::vector<std::vector<double>> & data() { return _data; }
  void print();

protected:
  virtual double computeQpProperty(const Point & q_point) = 0;

  FEProblem * _problem;

  size_t _i;
  size_t _qp;
  const Element * _current_elem;
  std::vector<const Node *> _current_nodes;
  std::vector<Point> _mapped_q_points;

  std::map<std::string, std::vector<double>> _coupled_variables;
  std::map<std::string, std::vector<Point>> _coupled_gradients;

private:
  std::vector<double> reinitCoupledValue(std::string var);
  std::vector<Point> reinitCoupledGradient(std::string var);

  std::vector<std::vector<double>> _test;
  std::vector<std::vector<Point>> _grad_test;

  std::vector<std::vector<double>> _data;
};
