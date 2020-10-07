#include "Engine.hpp"

#include <sstream>
#include <cmath>

#include "Constants.hpp"
#include "MathFunc.hpp"
#include "Util.hpp"

Engine::~Engine()
{
	UnloadFont(font);
}

Engine& Engine::get_instance()
{
	static Engine instance;
	return instance;
}

void Engine::main_loop()
{
	while (!WindowShouldClose()) {
		update();
		render();
	}
}

Engine::Engine() : epsilon(0.0), selected(0)
{
	InitWindow(WIN_WIDTH, WIN_HEIGHT, "RDP Line Simplification Algorithm");

#ifdef MODE_FULLSCREEN
	ToggleFullscreen();
#endif // MODE_FULLSCREEN

	SetTargetFPS(60);
	font = LoadFontEx("font.ttf", 18, nullptr, -1);

	MathFunc func1;
	func1.set_func([](auto x) {return std::exp(-x) * std::cos(2.0 * PI_ * x); });
	func1.set_xrange(0.0, 5.0);
	func1.calc_points();
	funcs.push_back({ "e^-x * cos(2* PI * x) [0, 5]", func1 });

	MathFunc func2;
	func2.set_func([](auto x) { return x * x * x  - std::exp(-x); });
	func2.set_xrange(-2.0, 4.0);
	func2.calc_points();
	funcs.push_back({ "x^3 - e^-x [-2, 4]", func2 });

	MathFunc func3;
	func3.set_func([](auto x) {return std::log(x) / (x * x); });
	func3.set_xrange(1, 5);
	func3.calc_points();
	funcs.push_back({ "ln(x) / x^2 [1, 5]", func3 });

	MathFunc func4;
	func4.set_func([](auto x) { return std::sin(x) * x  + std::cos(x); });
	func4.set_xrange(-4 * PI_, 4 * PI_);
	func4.calc_points();
	funcs.push_back({ "xsin(x) + cos(x) [-4pi, 4pi]", func4 });

	MathFunc func5;
	func5.set_func([](auto x) {  return x * std::sin(1.0 / x); });
	func5.set_xrange(0.05, 0.1);
	func5.calc_points();
	funcs.push_back({ "xsin(1 / x) [0.05, 0.1]", func5 });

	MathFunc func6;
	func6.set_func([](auto x) {
		const double x2 = x * x;
		return (5 * x2 + 8 * x - 3) / (3 * x2 + 2);
	});
	func6.set_xrange(-5.0, 10);
	func6.calc_points();
	funcs.push_back({ "(5x^2 + 8x - 3) / (3x^2 + 2) [-5, 10]", func6 });

	MathFunc func7;
	func7.set_func([](auto x) { return std::sin(x * x * std::sin(x)); });
	func7.set_xrange(-0.5, 2);
	func7.calc_points();
	funcs.push_back({ "sin (x^2 * sin(x)) [-0.5, 2]", func7 });

	MathFunc func8;
	func8.set_func([](auto x) { return std::sin(1.0 / x) * x; });
	func8.set_xrange(0.1, 0.5);
	func8.calc_points();
	funcs.push_back({ "xsin (1 / x) [0.1, 0.5]", func8 });

	MathFunc func9;
	func9.set_func([](auto x) { return (x * x * x) / 3 - x; });
	func9.set_xrange(-2, 3);
	func9.calc_points();
	funcs.push_back({ "x^3 - x [-2, 3]", func9 });

	rdp_linesimp(funcs[selected].second.to_screen_points(), simplified_points, epsilon);
}

void Engine::update()
{
	bool recalc = false;

	static constexpr double delta = MAX_EPSILON / 1200.0;

	if (IsKeyDown(KEY_UP)) {
		epsilon += delta;
		if (epsilon > MAX_EPSILON) epsilon = MAX_EPSILON;
		recalc = true;
	}
	else if (IsKeyDown(KEY_DOWN)) {
		epsilon -= delta;
		if (epsilon < 0.0) epsilon = 0.0;
		recalc = true;
	}
	else if (IsKeyPressed(KEY_R)) {
		epsilon = 0.0f;
		recalc = true;
	}
	else {
		for (int i = 0; i < 10; ++i) {
			auto key = static_cast<KeyboardKey>(KEY_ONE + i);
			if (IsKeyPressed(key) && i < funcs.size() && i != selected) {
				selected = i;
				recalc = true;
				break;
			}
		}
	}

	if (recalc) {
		simplified_points.clear();
		rdp_linesimp(funcs[selected].second.to_screen_points(), simplified_points, epsilon);
	}
}


void Engine::render() const
{
	std::ostringstream sout;
	sout << "Function: " << funcs[selected].first << "\n";
	sout << "Epsilon: " << epsilon << "\n";
	sout << "Points in Curve: " << simplified_points.size() << "\n";


	BeginDrawing();
	ClearBackground(BLACK);

	DrawTextEx(font, sout.str().c_str(), { 10, 5 }, 18.0f, 0.0f, GREEN);
	draw_polylines(simplified_points, WHITE, 3.0f);

	EndDrawing();
}
