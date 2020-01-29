#pragma once

#include <utility>

#include <Eigen/Dense>
using Eigen::MatrixXd;
using Eigen::VectorXd;

#include "Mesh.h"
#include "KernelBase.h"
#include "MaterialProperty.h"
#include "DirichletBC.h"

class KernelBase;
class MaterialProperty;
class DirichletBC;

class FEProblem
{
public:
  FEProblem(const MeshBase * mesh) : _mesh(mesh) {}
  ~FEProblem();

  const MeshBase * mesh() { return _mesh; }

  const Eigen::VectorXd & solution() { return _solution; }

  double * objectivePtr() { return &_objective; }
  Eigen::VectorXd * gradientPtr() { return &_gradient; }
  Eigen::MatrixXd * hessianPtr() { return &_hessian; }

  void computeProperties();
  const Eigen::VectorXd & computeGradient();
  const Eigen::MatrixXd & computeHessian();
  void enforceBCs();

  const Element * currentElem() { return _current_elem; }

  void init();

  void addVariable(std::string var);

  void addKernel(KernelBase * k) { _kernels.push_back(k); }

  void addMaterialProperty(std::string name, MaterialProperty *);

  void addNodalBC(DirichletBC * b) { _nodal_bcs.push_back(b); }

  MaterialProperty * getMaterialProperty(std::string name);

  size_t globalDoF(const Node * node, std::string var)
  {
    return node->id() * _variable_ids.size() + _variable_ids[var];
  }

  void printVariables();

  void printMaterials();

  void print()
  {
    _mesh->print();
    printVariables();
    printMaterials();
  }

private:
  const MeshBase * _mesh;
  std::map<std::string, size_t> _variable_ids;
  std::vector<std::pair<std::string, MaterialProperty *>> _material_property_warehouse;
  std::vector<KernelBase *> _kernels;
  std::vector<DirichletBC *> _nodal_bcs;

  Eigen::VectorXd _solution;
  double _objective;
  Eigen::VectorXd _gradient;
  Eigen::MatrixXd _hessian;

  const Element * _current_elem;
};
