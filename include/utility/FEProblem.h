#pragma once

#include <utility>

#include <Eigen/Dense>
using Eigen::MatrixXd;
using Eigen::VectorXd;

#include "Mesh.h"
#include "KernelBase.h"
#include "MaterialProperty.h"

class KernelBase;
class MaterialProperty;

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

  const Element * currentElem() { return _current_elem; }

  void init();

  void addVariable(std::string var);

  void addMaterialProperty(std::string name, MaterialProperty *);

  MaterialProperty * getMaterialProperty(std::string name);

  size_t globalDoF(size_t node_id, std::string var)
  {
    return node_id * _variable_ids.size() + _variable_ids[var];
  }

  void addKernel(KernelBase * k) { _kernels.push_back(k); }

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
  Eigen::VectorXd _solution;

  double _objective;
  Eigen::VectorXd _gradient;
  Eigen::MatrixXd _hessian;

  const Element * _current_elem;
};
