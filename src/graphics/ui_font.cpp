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

#include "graphics/ui_font.h"
#include "fonts/fonts.h"


UIFont::UIFont(Font::Size size, Font::Weight weight)
{

    var bold = weight == Font::Weight::bold;

    switch (size) {
    case Font::Size::xxSmall:
        if (bold) {
            _fontData = &(mf_rlefont_Lexend_Bold8.font);
        } else {
            _fontData = &(mf_rlefont_Lexend_Regular8.font);
        }
        break;
    case Font::Size::xSmall:
        if (bold) {
            _fontData = &(mf_rlefont_Lexend_Bold10.font);
        } else {
            _fontData = &(mf_rlefont_Lexend_Regular10.font);
        }
        break;
    case Font::Size::small:
        if (bold) {
            _fontData = &(mf_rlefont_Lexend_Bold12.font);
        } else {
            _fontData = &(mf_rlefont_Lexend_Regular12.font);
        }
        break;
    case Font::Size::medium:
        if (bold) {
            _fontData = &(mf_rlefont_Lexend_Bold16.font);
        } else {
            _fontData = &(mf_rlefont_Lexend_Regular16.font);
        }
        break;
    case Font::Size::large:
        if (bold) {
            _fontData = &(mf_rlefont_Lexend_Bold20.font);
        } else {
            _fontData = &(mf_rlefont_Lexend_Regular20.font);
        }
        break;
    case Font::Size::xLarge:
        if (bold) {
            _fontData = &(mf_rlefont_Lexend_Bold32.font);
        } else {
            _fontData = &(mf_rlefont_Lexend_Regular32.font);
        }
        break;
    case Font::Size::xxLarge:
        if (bold) {
            _fontData = &(mf_rlefont_Lexend_Bold48.font);
        } else {
            _fontData = &(mf_rlefont_Lexend_Regular48.font);
        }
        break;
    default:
        if (bold) {
            _fontData = &(mf_rlefont_Lexend_Bold12.font);
        } else {
            _fontData = &(mf_rlefont_Lexend_Regular12.font);
        }
        break;
    }
}

UIFont::~UIFont() {}

method UIFont::data() -> const FontData * {
    return _fontData;
};
