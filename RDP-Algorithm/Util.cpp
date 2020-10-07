#include "Util.hpp"

#include <cmath>

double map(double val, double in_min, double in_max, double out_min, double out_max)
{
	return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double dist_line2point(VecI point, const LineI& line)
{
    //calculate line segment vector
    double dx = (double)line[2] - line[0];
    double dy = (double)line[3] - line[1];

    //normalize line vector
    double norm = std::sqrt(dx * dx + dy * dy);
    dx /= norm;
    dy /= norm;

    //vector from point to one end of line
    double plx = (double)line[0] - point.first;
    double ply = (double)line[1] - point.second;

    //project 
    double dot = plx * dx + ply * dy;

    //scale line segment unit vector by dot product
    dx *= dot;
    dy *= dot;

    //drop perpendicular
    double perp_x = plx - dx;
    double perp_y = ply - dy;

    return std::sqrt(perp_x * perp_x + perp_y * perp_y);
}

void draw_polylines(const std::vector<VecI>& points, Color color, float thickness)
{
    for (size_t i = 0; i < points.size() - 1; ++i) {
        Vector2 start = { points[i].first, points[i].second };
        Vector2 end = { points[i + 1].first, points[i + 1].second };
        DrawLineEx(start, end, thickness, color);
    }
}

void rdp_linesimp(
    const std::vector<VecI>& points,
    std::vector<VecI>& out, double epsilon
    )
{
    double max_dist = 0.0;
    size_t max_idx = 0;
    LineI line = {
        points.front().first, points.front().second,
        points.back().first, points.back().second
    };

    for (size_t i = 1; i < points.size() - 1; ++i) {
        double dist = dist_line2point(points[i], line);
        if (dist > max_dist) {
            max_dist = dist;
            max_idx = i;
        }
    }

    if (max_dist > epsilon) {
        std::vector<VecI> result1;
        std::vector<VecI> result2;

        std::vector<VecI> points1(points.begin(), points.begin() + max_idx + 1);
        std::vector<VecI> points2(points.begin() + max_idx, points.end());

        rdp_linesimp(points1, result1, epsilon);
        rdp_linesimp(points2, result2, epsilon);

        out.assign(result1.begin(), result1.end() - 1);
        out.insert(out.end(), result2.begin(), result2.end());
    }
    else {
        out = { points.front(), points.back() };
    }
}
