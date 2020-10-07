#ifndef UTIL_HPP
#define UTIL_HPP

#include "typedefs.hpp"

#include <raylib.h>

#include <vector>

class MathFunc;

double map(double val, double in_min, double in_max, double out_min, double out_max);
double dist_line2point(VecI point, const LineI& line);

void draw_polylines(const std::vector<VecI>& points, Color color, float thickness);

void rdp_linesimp(
    const std::vector<VecI>& points,
    std::vector<VecI>& out,
    double epsilon
    );

#endif // !UTIL_HPP
