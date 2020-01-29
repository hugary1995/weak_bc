#include "Mesh.h"

Mesh1DBAR2::Mesh1DBAR2(double xmin, double xmax, size_t nx)
{
  // create nodes
  double s = (xmax - xmin) / nx;
  for (size_t i = 0; i < nx; i++)
  {
    const Node * n = new Node(xmin + i * s, 0.0);
    _nodes.push_back(n);
  }
  const Node * n = new Node(xmax, 0.0);
  _nodes.push_back(n);

  // create elements (connectivity)
  for (size_t i = 0; i < nx; i++)
  {
    const BAR2 * e = new BAR2({_nodes[i], _nodes[i + 1]});
    _elems.push_back(e);
  }

  // boundaries
  _node_sets["left"] = {_nodes[0]};
  _node_sets["right"] = {_nodes[nx]};
}
