/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ graphics/font_notomono.cpp                                                ║
 ╟───────────────────────────────────────────────────────────────────────────╢
 ║ Copyright © 2024 Kyle J Cardoza, Studio 8502 <Kyle.Cardoza@icloud.com>    ║
 ╟───────────────────────────────────────────────────────────────────────────╢
 ║ This program is free software: you can redistribute it and/or modify      ║
 ║ it under the terms of the GNU General Public License as published by      ║
 ║ the Free Software Foundation, either version 3 of the License, or         ║
 ║ (at your option) any later version.                                       ║
 ║                                                                           ║
 ║ This program is distributed in the hope that it will be useful,           ║
 ║ but WITHOUT ANY WARRANTY; without even the implied warranty of            ║
 ║ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             ║
 ║ GNU General Public License for more details.                              ║
 ║                                                                           ║
 ║ You should have received a copy of the GNU General Public License         ║
 ║ along with this program.  If not, see <http://www.gnu.org/licenses/>.     ║
 ╚═══════════════════════════════════════════════════════════════════════════╝
 ****************************************************************************/

#include "mcufont.h"
#include "fonts/fonts.h"
#include "graphics/font.h"
#include "graphics/font_notomono.h"

Font::NotoMono::NotoMono(Size size, Weight weight, Style style):
    _size(size),
    _weight(weight),
    _style(Font::Style::roman)
{}

Font::NotoMono::~NotoMono() {}

method Font::NotoMono::size() -> Size {
    return _size;
}

method Font::NotoMono::setSize(Size newSize) -> Void {
    _size = newSize;
}

method Font::NotoMono::weight() -> Weight {
    return _weight;
}

method Font::NotoMono::setWeight(Weight newWeight) -> Void {
    _weight = newWeight;
}

method Font::NotoMono::style() -> Style {
    return _style;
}

method Font::NotoMono::setStyle(Style newStyle) -> Void {
    _style = newStyle;
}

method Font::NotoMono::data() -> const FontData * {

    var bold = _weight == Font::Weight::bold;

    switch (_size) {
    case Font::Size::xxSmall:
        if (bold) {
            return &(mf_rlefont_NotoSansMono_Bold8.font);
        }else {
            return &(mf_rlefont_NotoSansMono_Regular8.font);
        }
        break;
    case Font::Size::xSmall:
        if (bold) {
            return &(mf_rlefont_NotoSansMono_Bold10.font);
        }else {
            return &(mf_rlefont_NotoSansMono_Regular10.font);
        }
        break;
    case Font::Size::small:
        if (bold) {
            return &(mf_rlefont_NotoSansMono_Bold12.font);
        }else {
            return &(mf_rlefont_NotoSansMono_Regular12.font);
        }
        break;
    case Font::Size::medium:
        if (bold) {
            return &(mf_rlefont_NotoSansMono_Bold16.font);
        }else {
            return &(mf_rlefont_NotoSansMono_Regular16.font);
        }
        break;
    case Font::Size::large:
        if (bold) {
            return &(mf_rlefont_NotoSansMono_Bold20.font);
        }else {
            return &(mf_rlefont_NotoSansMono_Regular20.font);
        }
        break;
    case Font::Size::xLarge:
        if (bold) {
            return &(mf_rlefont_NotoSansMono_Bold32.font);
        }else {
            return &(mf_rlefont_NotoSansMono_Regular32.font);
        }
        break;
    case Font::Size::xxLarge:
        if (bold) {
            return &(mf_rlefont_NotoSansMono_Bold48.font);
        }else {
            return &(mf_rlefont_NotoSansMono_Regular48.font);
        }
        break;
    default:
        if (bold) {
            return &(mf_rlefont_NotoSansMono_Bold16.font);
        }else {
            return &(mf_rlefont_NotoSansMono_Regular16.font);
        }
        break;
    }
}
