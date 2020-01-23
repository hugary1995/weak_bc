#pragma once

#include "MeshBase.h"
#include "BAR2.h"

class Mesh1DBAR2;

class Mesh1DBAR2 : public MeshBase
{
public:
  Mesh1DBAR2(double xmin, double xmax, size_t nx);
};
