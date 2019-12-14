
#include <iostream>
#include "matgui/application.h"
#include "matgui/window.h"
#include "matgui/texture.h"
#include "matgui/draw.h"
#include "vec.h"
#include "matrix.h"
#include "input.h"
#include "matgui/keys.h"

#include "level.h"

using namespace std;
using namespace MatGui;
using namespace Engine;

class Car {
public:
	Car(Level &level): level(level), texture("car.png") {
		pos = {100, 100};
		rayPaint.line.color(1,1,1);
	}
	void update(double t){
		if (Input::getKey(Keys::Up)) {
			throttle += .3;
		}
		if (Input::getKey(Keys::Down)) {
			throttle += -.3;
		}

		throttle *= .9;


		if (Input::getKey(Keys::Left)) {
			angle += .03 * throttle;
		}
		if (Input::getKey(Keys::Right)) {
			angle -= .03 * throttle;
		}
		location = Matrixf::RotationZ(angle);

		dir = location.row(1) * throttle;
		pos += dir;

		location.setTranslation(pos);
	}

	void draw() {
		drawTextureRect(pos, angle, 20, -30, texture, DrawStyle::CenterOrigo);

		int numRays = 20;
		for (int i = -numRays; i <= numRays; ++i) {
			double a = MatGui::pi / 2. / numRays * i;
			Vec d(sin(a), cos(a));
			Vec l = d * 100;

			Vec p2 = location * l;

			auto dist = level.traceRay(pos, p2 - pos);

			p2 = location * (d * dist);

			rayPaint.drawLine(pos, p2);
		}
	}

	Vec pos;
	Vec vel;
	Vec dir;
	Matrixf location;
	double throttle = 0;
	double angle = MatGui::pi;
	Level &level;
	Texture texture;
	Paint rayPaint;
};

int main(int argc, char **argv) {
	Application app(argc, argv);

	Window window("auto-driving", 1000, 800);

	window.style.fill.color(1, 0, 0);
	window.updateStyle();

	Paint paint;


	Level level("levels/1.png");
	Car car(level);

	window.frameUpdate.connect([&](double t) {

		drawTextureRect(0,0, 0, level.width(), level.height(), level.texture(), DrawStyle::OrigoTopLeft);
		car.update(t);
		car.draw();
	});

	window.keyDown.connect([](View::KeyArgument arg) {
		Input::setKeyDown(arg.scanCode);
	});

	window.keyUp.connect([](View::KeyArgument arg) {
		Input::setKeyUp(arg.scanCode);
	});

	app.mainLoop();

	return 0;
}

