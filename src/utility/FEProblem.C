#include "FEProblem.h"

FEProblem::~FEProblem()
{
  delete _mesh;
  for (auto & k : _kernels)
    delete k;
  for (auto & m : _material_property_warehouse)
    delete m.second;
}

void
FEProblem::computeProperties()
{
  for (auto const & e : _mesh->elems())
  {
    _current_elem = e;
    for (auto p = _material_property_warehouse.begin(); p != _material_property_warehouse.end();
         p++)
    {
      p->second->reinitElem();
      p->second->computeProperty();
    }
  }
}

const Eigen::VectorXd &
FEProblem::computeGradient()
{
  _gradient.setZero();
  for (auto const & e : _mesh->elems())
  {
    _current_elem = e;
    for (auto const & k : _kernels)
    {
      k->reinitElem();
      k->computeGradient();
    }
  }

  return _gradient;
}

const Eigen::MatrixXd &
FEProblem::computeHessian()
{
  _hessian.setZero();
  for (auto const & e : _mesh->elems())
  {
    _current_elem = e;
    for (auto const & k : _kernels)
    {
      k->reinitElem();
      k->computeHessian();
    }
  }

  return _hessian;
}

void
FEProblem::init()
{
  size_t nNodes = _mesh->nodes().size();
  size_t nVars = _variable_ids.size();
  _solution.setZero(nNodes * nVars);
  _gradient.setZero(nNodes * nVars);
  _hessian.setZero(nNodes * nVars, nNodes * nVars);

  // find maximum element id
  size_t max_elem_id = 0;
  for (auto const & e : _mesh->elems())
    if (e->id() > max_elem_id)
      max_elem_id = e->id();
  for (auto const & p : _material_property_warehouse)
    p.second->resize(max_elem_id + 1);
}

void
FEProblem::addVariable(std::string var)
{
  auto it = _variable_ids.find(var);
  if (it != _variable_ids.end())
    return;
  size_t n = _variable_ids.size();
  _variable_ids[var] = n;
}

void
FEProblem::addMaterialProperty(std::string name, MaterialProperty * prop)
{
  for (auto it = _material_property_warehouse.begin(); it != _material_property_warehouse.end();
       it++)
    if (it->first == name)
      return;

  std::pair<std::string, MaterialProperty *> tmp(name, prop);
  _material_property_warehouse.push_back(tmp);
}

MaterialProperty *
FEProblem::getMaterialProperty(std::string name)
{
  for (auto it = _material_property_warehouse.begin(); it != _material_property_warehouse.end();
       it++)
    if (it->first == name)
      return it->second;

  return nullptr;
}

void
FEProblem::printVariables()
{
  std::cout << "\n============================VARIABLES===========================\n";
  for (auto const & v : _variable_ids)
    std::cout << v.first << ": " << v.second << std::endl;
}

void
FEProblem::printMaterials()
{
  std::cout << "\n============================MATERIALS===========================\n";
  for (auto const & m : _material_property_warehouse)
  {
    std::cout << "Material '" << m.first << "':" << std::endl;
    m.second->print();
  }
}
