#include "DirichletBC.h"

DirichletBC::DirichletBC(FEProblem * problem, std::string var, std::string boundary_name)
  : _problem(problem),
    _variable(var),
    _node_set(*(problem->mesh()->getNodeSet(boundary_name))),
    _gradient(problem->gradientPtr()),
    _hessian(problem->hessianPtr())
{
}

void
DirichletBC::enforce()
{
  for (auto const & n : _node_set)
  {
    size_t dof = _problem->globalDoF(n, _variable);
    double dof_value = computeNodalValue();

    (*_gradient) -= dof_value * (*_hessian).col(dof);
    (*_gradient)(dof) = dof_value;

    (*_hessian).row(dof).setZero();
    (*_hessian).col(dof).setZero();
    (*_hessian)(dof, dof) = 1.0;
  }
}
