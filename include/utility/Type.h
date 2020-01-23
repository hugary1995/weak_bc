#pragma once

#include <iostream>

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
