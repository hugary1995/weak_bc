#pragma once

#include "MaterialProperty.h"

class CopyMaterialProperty : public MaterialProperty
{
public:
  CopyMaterialProperty(FEProblem * problem, std::string from)
    : MaterialProperty(problem), _from(problem->getMaterialProperty(from)->data())
  {
  }

protected:
  virtual double computeQpProperty(const Point & q_point)
  {
    return _from[_current_elem->id()][_qp];
  }

private:
  const std::vector<std::vector<double>> & _from;
};
