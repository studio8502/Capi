// graphics/text.h
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

#include <memory>

#include "graphics/font.h"
#include "custom_types.h"

using std::shared_ptr;

// A class representing a string as a graphical object which can be rendered
// to a Drawable class's bitmap.

class Text {
public:

    enum class Alignment {
        left,
        center,
        centre = center,
        right,
        justify
    };

    Text(String value, shared_ptr<Font> font, Int32 width, Alignment align = Alignment::left);
    
    ~Text();

    // Get the width of the Text in pixels, based on a maximum character
    // length of `length` characters (0 to consider the full length of the string)
    method widthForLength(UInt16 length) -> Int16;

    // Get the rendering width of the string.
    method width() -> Int32;

    // Set the rendering width of the string.
    method setWidth(Int32 newValue) -> Void;

    method align() -> Alignment;

    method setAlign(Alignment newValue) -> Void;

    // Get the font for the text.
    method font() -> shared_ptr<Font>;

    // Set the font for the text.
    method setFont(shared_ptr<Font> newValue) -> Void;

private:

    String _string;
    
    Int32 _width;

    Alignment _align;

    shared_ptr<Font> _font;

};
