/*
 * level.cpp
 *
 *  Created on: 14 dec. 2019
 *      Author: Mattias Larsson Sköld
 */


#include "level.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <memory>

using namespace std;
using namespace MatGui;


Level::Level(string filename): _texture(filename){
	IMG_Init(IMG_INIT_PNG);
	std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> surface(
			IMG_Load(filename.c_str()), SDL_FreeSurface);

	if (!surface) {
		throw runtime_error("could not load level");
	}

	_width = surface->w;
	_height = surface->h;
	auto *data = static_cast<char*>(surface->pixels);

	_data.resize(_width * _height);

	for (size_t y = 0; y < _height; ++y) {
		for (size_t x = 0; x < _width; ++x) {
			// Get the alpha value
			at(x, y) = data[(x * 4 + y * surface->pitch) + 3];
		}
	}
}



