/*
 * level.h
 *
 *  Created on: 14 dec. 2019
 *      Author: Mattias Larsson Sköld
 */

#pragma once

#include "matgui/texture.h"
#include "vec.h"
#include <string>
#include <vector>

class Level {
public:
    struct Cell {
        char state = 0; // 0 = free, 1 = occupied

        Cell &operator=(char value) {
            state = static_cast<bool>(value);
            return *this;
        }

        operator bool() {
            return static_cast<bool>(state);
        }
    };

    Level(std::string filename);

    double traceRay(Vec origin, Vec direction);

    Cell &operator()(int x, int y) {
        return _data.at(x + y * _width);
    }

    Cell &at(int x, int y) {
        return (*this)(x, y);
    }

    auto width() {
        return _width;
    }
    auto height() {
        return _height;
    }
    const auto &texture() const {
        return _texture;
    }

private:
    std::vector<Cell> _data;
    MatGui::Texture _texture;
    size_t _width = 0, _height = 0;
};
