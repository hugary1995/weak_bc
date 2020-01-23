#include "MaterialProperty.h"

MaterialProperty::MaterialProperty(FEProblem * problem) : _problem(problem) {}

void
MaterialProperty::resize(size_t nelems)
{
  _data.resize(nelems);
}

void
MaterialProperty::reinitElem()
{
  _current_elem = _problem->currentElem();
  _current_nodes = _current_elem->nodes();
  _mapped_q_points = _current_elem->mappedQPoints();
  _test = _current_elem->test();
  _grad_test = _current_elem->gradTest();

  // calculate couple values
  for (auto & v : _coupled_variables)
    v.second = reinitCoupledValue(v.first);

  // calculate couple gradients
  for (auto & v : _coupled_gradients)
    v.second = reinitCoupledGradient(v.first);
}

std::vector<double>
MaterialProperty::reinitCoupledValue(std::string var)
{
  std::vector<double> v(_mapped_q_points.size());
  const Eigen::VectorXd solution = _problem->solution();
  for (_i = 0; _i < _current_nodes.size(); _i++)
  {
    size_t dof = _problem->globalDoF(_current_nodes[_i]->id(), var);
    double dof_value = solution(dof);
    for (_qp = 0; _qp < _mapped_q_points.size(); _qp++)
      v[_qp] += _test[_i][_qp] * dof_value;
  }
  return v;
}

std::vector<Point>
MaterialProperty::reinitCoupledGradient(std::string var)
{
  std::vector<Point> v(_mapped_q_points.size());
  const Eigen::VectorXd solution = _problem->solution();
  for (_i = 0; _i < _current_nodes.size(); _i++)
  {
    size_t dof = _problem->globalDoF(_current_nodes[_i]->id(), var);
    double dof_value = solution(dof);
    for (_qp = 0; _qp < _mapped_q_points.size(); _qp++)
      v[_qp] += _grad_test[_i][_qp] * dof_value;
  }
  return v;
}

void
MaterialProperty::computeProperty()
{
  std::vector<double> props(_mapped_q_points.size());
  for (_qp = 0; _qp < _mapped_q_points.size(); _qp++)
    props[_qp] = computeQpProperty(_mapped_q_points[_qp]);
  _data[_current_elem->id()] = props;
}

void
MaterialProperty::print()
{
  for (size_t i = 0; i < _data.size(); i++)
  {
    std::cout << "Element #" << i << ": ";
    for (size_t j = 0; j < _data[i].size(); j++)
      std::cout << "(qp #" << j << ", " << _data[i][j] << ") ";
    std::cout << std::endl;
  }
}
