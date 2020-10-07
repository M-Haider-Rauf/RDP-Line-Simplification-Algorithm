#ifndef MATHFUNC_HPP
#define MATHFUNC_HPP

#include "typedefs.hpp"

#include <functional>
#include <vector>

class MathFunc {
public:
	MathFunc();

	void set_func(const std::function<double(double)>& func);
	VecI get_xrange() const;
	VecI get_yrange() const;
	void set_xrange(double min, double max);

	void calc_points();
	const std::vector<VecD>& get_points() const;
	std::vector<VecI> to_screen_points(double min_y, double max_y) const;
	std::vector<VecI> to_screen_points() const;

private:
	static const unsigned POINT_TARGET = 200;

	std::function<double(double)> func;
	double min_x;
	double max_x;

	double min_y;
	double max_y;

	std::vector<VecD> points;
};

#endif // !MATHFUNC_HPP
