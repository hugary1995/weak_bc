#pragma once

#include "Point.h"

// Forward Declarations
class Node;

class Node : public Point
{
public:
  Node() : Point(), _id(count++) {}
  Node(double x, double y) : Point(x, y), _id(count++) {}
  Node(const Node & other) : Point(other), _id(count++) {}

  Node & operator=(const Node & other)
  {
    // check for self-assignment
    if (&other == this)
      return *this;
    _x = other._x;
    _y = other._y;
    return *this;
  }

  size_t id() { return _id; }
  size_t id() const { return _id; }

  friend std::ostream & operator<<(std::ostream & console, const Node & p);

private:
  static size_t count;
  size_t _id;
};

inline std::ostream &
operator<<(std::ostream & os, const Node & n)
{
  os << "Node #" << n.id() << ": ";
  os << '(' << n.x() << ", " << n.y() << ')';
  return os;
}
