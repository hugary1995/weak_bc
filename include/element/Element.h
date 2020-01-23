#pragma once

#include <vector>
#include <cmath>
#include "Node.h"

class Element
{
public:
  Element(std::vector<const Node *> nodes) : _id(count++), _nodes(nodes) {}
  virtual ~Element() {}
  size_t id() { return _id; }
  size_t id() const { return _id; }
  std::vector<const Node *> nodes() { return _nodes; }
  std::vector<const Node *> nodes() const { return _nodes; }
  std::vector<Point> qPoints() { return _q_points; }
  std::vector<Point> qPoints() const { return _q_points; }
  std::vector<Point> mappedQPoints() { return _mapped_q_points; }
  std::vector<Point> mappedQPoints() const { return _mapped_q_points; }
  std::vector<double> weights() { return _weights; }
  std::vector<double> weights() const { return _weights; }
  std::vector<double> JxW() { return _JxW; }
  std::vector<double> JxW() const { return _JxW; }
  std::vector<std::vector<double>> test() { return _test; }
  std::vector<std::vector<double>> test() const { return _test; }
  std::vector<std::vector<Point>> gradTest() { return _grad_test; }
  std::vector<std::vector<Point>> gradTest() const { return _grad_test; }

  friend std::ostream & operator<<(std::ostream & console, const Element & e);

protected:
  virtual void initQRule() = 0;
  virtual void initJxW() = 0;
  virtual void initTest() = 0;
  virtual void initGradTest() = 0;

  static size_t count;
  size_t _id;

  std::vector<const Node *> _nodes;
  std::vector<Point> _q_points;
  std::vector<Point> _mapped_q_points;
  std::vector<double> _weights;
  std::vector<double> _JxW;
  std::vector<std::vector<double>> _test;
  std::vector<std::vector<Point>> _grad_test;
};

inline std::ostream &
operator<<(std::ostream & os, const Element & e)
{
  os << "Element #" << e.id() << ": {";
  for (size_t i = 0; i < e.nodes().size() - 1; i++)
    os << *e.nodes()[i] << ", ";
  os << *e.nodes()[e.nodes().size() - 1] << "}";
  return os;
}
