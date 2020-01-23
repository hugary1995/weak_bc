#include "BAR2.h"

void
BAR2::initQRule()
{
  Point qp1(-std::sqrt(3) / 3.0, 0.0);
  Point qp2(std::sqrt(3) / 3.0, 0.0);

  _q_points.resize(2);
  _q_points[0] = qp1;
  _q_points[1] = qp2;

  _weights.resize(2);
  _weights[0] = _weights[1] = 1.0;
}

void
BAR2::initJxW()
{
  _JxW.resize(2);
  _JxW[0] = _JxW[1] = 0.5 * (_nodes[1]->x() - _nodes[0]->x());
}

void
BAR2::initTest()
{
  _test.resize(2);
  _test[0].resize(2);
  _test[1].resize(2);
  _test[0][0] = _test[1][1] = 0.5 * (1.0 + std::sqrt(3.0) / 3.0);
  _test[0][1] = _test[1][0] = 0.5 * (1.0 - std::sqrt(3.0) / 3.0);

  _mapped_q_points.resize(2);
  Point qp1(_test[0][0] * _nodes[0]->x() + _test[1][0] * _nodes[1]->x(),
            _test[0][0] * _nodes[0]->y() + _test[1][0] * _nodes[1]->y());
  Point qp2(_test[0][1] * _nodes[0]->x() + _test[1][1] * _nodes[1]->x(),
            _test[0][1] * _nodes[0]->y() + _test[1][1] * _nodes[1]->y());
  _mapped_q_points[0] = qp1;
  _mapped_q_points[1] = qp2;
}

void
BAR2::initGradTest()
{
  Point dN1_qp1(-0.5 / _JxW[0], 0.0);
  Point dN1_qp2(-0.5 / _JxW[1], 0.0);
  Point dN2_qp1(0.5 / _JxW[0], 0.0);
  Point dN2_qp2(0.5 / _JxW[1], 0.0);

  _grad_test.resize(2);
  _grad_test[0].resize(2);
  _grad_test[1].resize(2);
  _grad_test[0][0] = dN1_qp1;
  _grad_test[0][1] = dN1_qp2;
  _grad_test[1][0] = dN2_qp1;
  _grad_test[1][1] = dN2_qp2;
}
