#include "MathFunc.hpp"

#include "Util.hpp"
#include "Constants.hpp"

MathFunc::MathFunc() 
	: func([] (auto x) { return 0.0; })
	, min_x(0.0), max_x(0.0)
	, min_y(0.0), max_y(0.0)
	, points()
{
}

void MathFunc::set_func(const std::function<double(double)>& func)
{
	this->func = func;
}

VecI MathFunc::get_xrange() const
{
	return { min_x, max_x };
}
VecI MathFunc::get_yrange() const
{
	return { min_y, max_y };
}

void MathFunc::set_xrange(double min, double max)
{
	this->min_x = min;
	this->max_x = max;
}

void MathFunc::calc_points()
{
	double range = std::abs(max_x - min_x);
	double increment = range / POINT_TARGET;

	min_y = +std::numeric_limits<double>::infinity();
	max_y = -std::numeric_limits<double>::infinity();

	points.clear();

	for (double x = min_x; x <= max_x; x += increment) {
		if (x > max_x) x = max_x;
		double y = func(x);

		if (y < min_y) min_y = y;
		if (y > max_y) max_y = y;

		points.push_back({ x, y });
	}
}

const std::vector<VecD>& MathFunc::get_points() const
{
	return points;
}

std::vector<VecI> MathFunc::to_screen_points(double min_y, double max_y) const
{
	std::vector<VecI> screen_points;

	for (auto p : points) {
		int x = 50 + std::round(map(p.first, min_x, max_x, 0, WIN_WIDTH - 100));
		int y = 90 + std::round(map(p.second, min_y, max_y, WIN_HEIGHT - 100, 0));

		screen_points.push_back({ x, y });
	}

	return screen_points;
}

std::vector<VecI> MathFunc::to_screen_points() const
{
	return to_screen_points(min_y, max_y);
}
