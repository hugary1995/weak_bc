#include "KernelBase.h"

KernelBase::KernelBase(FEProblem * problem, std::string variable)
  : _problem(problem),
    _variable(variable),
    _objective(problem->objectivePtr()),
    _gradient(problem->gradientPtr()),
    _hessian(problem->hessianPtr())
{
}

void
KernelBase::reinitElem()
{
  _current_elem = _problem->currentElem();
  _current_nodes = _current_elem->nodes();
  _q_points = _current_elem->qPoints();
  _JxW = _current_elem->JxW();
  _test = _current_elem->test();
  _grad_test = _current_elem->gradTest();

  // calculate couple values
  _u = reinitCoupledValue(_variable);
  for (auto & v : _coupled_variables)
    v.second = reinitCoupledValue(v.first);

  // calculate couple gradients
  _grad_u = reinitCoupledGradient(_variable);
  for (auto & v : _coupled_gradients)
    v.second = reinitCoupledGradient(v.first);
}

std::vector<double>
KernelBase::reinitCoupledValue(std::string var)
{
  std::vector<double> v(_q_points.size());
  const Eigen::VectorXd solution = _problem->solution();
  for (_i = 0; _i < _current_nodes.size(); _i++)
  {
    size_t dof = _problem->globalDoF(_current_nodes[_i], var);
    double dof_value = solution(dof);
    for (_qp = 0; _qp < _q_points.size(); _qp++)
      v[_qp] += _test[_i][_qp] * dof_value;
  }
  return v;
}

std::vector<Point>
KernelBase::reinitCoupledGradient(std::string var)
{
  std::vector<Point> v(_q_points.size());
  const Eigen::VectorXd solution = _problem->solution();
  for (_i = 0; _i < _current_nodes.size(); _i++)
  {
    size_t dof = _problem->globalDoF(_current_nodes[_i], var);
    double dof_value = solution(dof);
    for (_qp = 0; _qp < _q_points.size(); _qp++)
      v[_qp] += _grad_test[_i][_qp] * dof_value;
  }
  return v;
}

void
KernelBase::computeGradient()
{
  for (_qp = 0; _qp < _q_points.size(); _qp++)
    for (_i = 0; _i < _current_nodes.size(); _i++)
    {
      size_t dof_i = _problem->globalDoF(_current_nodes[_i], _variable);
      (*_gradient)(dof_i) += _JxW[_qp] * computeQpGradient();
    }
}

void
KernelBase::computeHessian()
{
  for (_qp = 0; _qp < _q_points.size(); _qp++)
    for (_i = 0; _i < _current_nodes.size(); _i++)
      for (_j = 0; _j < _current_nodes.size(); _j++)
      {
        size_t dof_i = _problem->globalDoF(_current_nodes[_i], _variable);
        size_t dof_j = _problem->globalDoF(_current_nodes[_j], _variable);
        (*_hessian)(dof_i, dof_j) += _JxW[_qp] * computeQpHessian();
      }
}
