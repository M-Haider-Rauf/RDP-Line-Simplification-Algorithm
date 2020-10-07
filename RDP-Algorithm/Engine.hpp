#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "MathFunc.hpp"

#include <raylib.h>

class Engine {
public:
	~Engine();
	static Engine& get_instance();

	void main_loop();

private:
	constexpr static double MAX_EPSILON = 50.0;

	Engine();

	void update();
	void render() const;

	std::vector<std::pair<std::string, MathFunc>> funcs;
	int selected = 0;

	double epsilon;
	std::vector<VecI> simplified_points;

	Font font;
};

#endif // !ENGINE_HPP
