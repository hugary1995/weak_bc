#pragma once

#include <vector>
#include <map>
#include "Element.h"

class MeshBase
{
public:
  ~MeshBase()
  {
    for (const Node * n : _nodes)
      delete n;
    for (const Element * e : _elems)
      delete e;
  }
  const std::vector<const Node *> & nodes() const { return _nodes; }
  const std::vector<const Element *> & elems() const { return _elems; }
  const std::map<std::string, std::vector<const Node *>> & boundaries() const
  {
    return _boundaries;
  }
  void print() const
  {
    std::cout << "\n==============================MESH==============================\n";
    for (const Element * e : _elems)
      std::cout << *e << std::endl;
  }

protected:
  std::vector<const Node *> _nodes;
  std::vector<const Element *> _elems;
  std::map<std::string, std::vector<const Node *>> _boundaries;
};
