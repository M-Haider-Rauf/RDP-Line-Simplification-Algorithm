#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// #define MODE_FULLSCREEN

#include <cmath>

#ifdef MODE_FULLSCREEN
constexpr unsigned WIN_WIDTH =	1366;
constexpr unsigned WIN_HEIGHT = 768;

#else
constexpr unsigned WIN_WIDTH = 1100;
constexpr unsigned WIN_HEIGHT = 651;

#endif

const double PI_ = std::acos(-1.0);

#endif // !CONSTANTS_HPP
