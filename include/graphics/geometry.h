// geometry.h
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

#pragma once

#include "custom_types.h"

struct Point {
    Int32 x;
    Int32 y;

    Point(Int32 x, Int32 y);
};

struct Size {
    Int32 width;
    Int32 height;

    Size(Int32 width, Int32 height);
};

struct Rect {
public:
    Int32 x;
    Int32 y;
    Int32 width;
    Int32 height;


    Rect(Point origin, Size size);

    Rect(Int32 x, Int32 y, Int32 width, Int32 height);

    Rect();
    
    ~Rect();

    method origin() -> Point;

    method size() -> Size;

    // Returns true if the specified point is within the area
    // defined by the rect.
    method checkPoint(Point point) -> Bool;

    // Returns true if the specified rect overlaps the rect.
    method checkRect(Rect other) -> Bool;
};
