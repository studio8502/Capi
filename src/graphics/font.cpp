// graphics/font.cpp
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

#include "graphics/font.h"
#include "fonts/fonts.h"

using std::make_shared;

Font::Font(const mf_rlefont_s *fontData):
    _fontData(fontData)
{}

Font::~Font() {}

method Font::fullName() -> String {
    if (_fontData != nullptr) {
        return _fontData->font.full_name;
    } else {
        return "";
    }
}

method Font::shortName() -> String {
    if (_fontData != nullptr) {
        return _fontData->font.short_name;
    } else {
        return "";
    }
}

method Font::fontData() -> const mf_font_s * {
    return &(_fontData->font);
}

method Font::DejaVuSans(UInt8 size, Bool bold, Bool italic) -> shared_ptr<Font> {
    switch (size) {
    case 8 ... 9:
        return make_shared<Font>(&mf_rlefont_DejaVuSans8);
    case 10 ... 11:
        return make_shared<Font>(&mf_rlefont_DejaVuSans10);
    case 12 ... 13:
        return make_shared<Font>(&mf_rlefont_DejaVuSans12);
    case 14 ... 15:
        return make_shared<Font>(&mf_rlefont_DejaVuSans14);
    default:
        return nullptr;
    }
}
