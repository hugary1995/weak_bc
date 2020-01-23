#pragma once

#include "fparser.hh"

#include "MaterialProperty.h"

class FunctionMaterialProperty : public MaterialProperty
{
public:
  FunctionMaterialProperty(FEProblem * problem, std::string function) : MaterialProperty(problem)
  {
    _fparser.Parse(function, "x,y");
  }

protected:
  virtual double computeQpProperty(const Point & q_point)
  {
    double vals[] = {q_point.x(), q_point.y()};
    return _fparser.Eval(vals);
  }

private:
  FunctionParser _fparser;
};
