#pragma once

#include <iostream>

typedef enum elemType
{
  B2,
  T3
} ElemType;

inline std::ostream &
operator<<(std::ostream & os, const ElemType & e)
{
  if (e == ElemType::B2)
    std::cout << "B2";
  if (e == ElemType::T3)
    std::cout << "T3";
  return os;
}

typedef enum terminalColor
{
  DEFAULT,
  BLACK,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE
} TerminalColor;

inline std::ostream &
operator<<(std::ostream & os, const TerminalColor & c)
{
  if (c == TerminalColor::DEFAULT)
    os << "\33[0m";
  if (c == TerminalColor::RED)
    os << "\33[31m";
  if (c == TerminalColor::GREEN)
    os << "\33[32m";
  return os;
}
