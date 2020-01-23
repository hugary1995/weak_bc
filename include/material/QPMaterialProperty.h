#pragma once

#include "MaterialProperty.h"

class QPMaterialProperty : public MaterialProperty
{
public:
  QPMaterialProperty(FEProblem * problem) : MaterialProperty(problem) {}

protected:
  virtual double computeQpProperty(const Point & q_point) { return q_point.x(); }
};
