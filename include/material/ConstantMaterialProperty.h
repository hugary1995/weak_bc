#pragma once

#include "MaterialProperty.h"

class ConstantMaterialProperty : public MaterialProperty
{
public:
  ConstantMaterialProperty(FEProblem * problem, double value)
    : MaterialProperty(problem), _value(value)
  {
  }

protected:
  virtual double computeQpProperty(const Point & q_point) { return _value; }

private:
  double _value;
};
