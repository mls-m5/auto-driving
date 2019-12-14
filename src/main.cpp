
#include <iostream>
#include "matgui/application.h"
#include "matgui/window.h"
#include "matgui/texture.h"
#include "matgui/draw.h"
#include "vec.h"

#include "level.h"

using namespace std;
using namespace MatGui;

class Car {
public:
	Car(Level &level): level(level), texture("car.png") {
		pos = {100, 100};
	}
	void update(double t){

	}

	void draw() {
		drawTextureRect(pos, 0, 20, 30, texture, DrawStyle::CenterOrigo);
	}

	Vec pos;
	Vec vel;
	double angle = 0;
	Level &level;
	Texture texture;
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
		car.draw();
	});

	app.mainLoop();

	return 0;
}

