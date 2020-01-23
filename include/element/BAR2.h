#pragma once

#include "Element.h"

// Forward Declarations
class BAR2;

class BAR2 : public Element
{
public:
  BAR2(std::vector<const Node *> nodes) : Element(nodes)
  {
    initQRule();
    initJxW();
    initTest();
    initGradTest();
  }

private:
  virtual void initQRule() override;
  virtual void initJxW() override;
  virtual void initTest() override;
  virtual void initGradTest() override;
};
