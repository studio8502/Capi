// graphics/text.cpp
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

#include "graphics/text.h"
#include "fonts/fonts.h"
#include "mcufont.h"

using std::make_shared;

// A class representing a string as a graphical object which Drawable
// objects can use to draw text on screen.

Text::Text(String value, shared_ptr<Font> font, Int32 width, Alignment align):
    _string(value),
    _width(width),
    _align(align),
    _font(font)
{}
  
method Text::font() -> shared_ptr<Font> {
    return _font;
}

method Text::setFont(shared_ptr<Font> newValue) -> Void {
    _font.reset();
    _font = newValue;
}

method Text::widthForLength(UInt16 length) -> Int16 {

    return mf_get_string_width(font()->fontData(), _string.c_str(), length, true);
}

method Text::width() -> Int32 {
    return _width;
}

method Text::setWidth(Int32 newValue) -> Void {
    _width = newValue;
}

method Text::align() -> Alignment {
    return _align;
}

method Text::setAlign(Alignment newValue) -> Void {
    _align = newValue;
}
