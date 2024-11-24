// geometry/geometry.cpp
//
// Copyright © 2024 Kyle K Cardoza, Studio 8502 <Kyle.Cardoza@icloud.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "graphics/geometry.h"

Rect::Rect() {}

Rect::Rect(Point origin, Size size):
    x(origin.x), y(origin.y),
    width(size.width), height(size.height)
{}

Rect::Rect(Int32 x, Int32 y, Int32 width, Int32 height):
    x(x), y(y), width(width), height(height)
{}

Rect::~Rect() {}

method Rect::checkPoint(Point point) -> Bool {
    if (point.x < x || point.x > x + width ||
        point.y < y || point.y > y + height) {
        return false;
    } else {
        return true;
    }
}

method Rect::checkRect(Rect other) -> Bool {
    if (x < other.x + other.width &&
        x + height > other.x &&
        y < other.y + other.height &&
        y + height > other.y) {
        return true;
    } else {
        return false;
    }
}

method Rect::origin() -> Point {
    return Point(x, y);
}

method Rect::size() -> Size {
    return Size(width, height);
}

Point::Point(Int32 x, Int32 y):
    x(x), y(y)
{}

Size::Size(Int32 width, Int32 height):
    width(width), height(height)
{}