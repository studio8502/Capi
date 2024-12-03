/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ graphics/font_notosans.cpp                                                ║
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
#include "graphics/font_notosans.h"

Font::NotoSans::NotoSans(Size size, Weight weight, Style style):
    _size(size),
    _weight(weight),
    _style(style)
{}

Font::NotoSans::~NotoSans() {}

method Font::NotoSans::size() -> Size {
    return _size;
}

method Font::NotoSans::setSize(Size newSize) -> Void {
    _size = newSize;
}

method Font::NotoSans::weight() -> Weight {
    return _weight;
}

method Font::NotoSans::setWeight(Weight newWeight) -> Void {
    _weight = newWeight;
}

method Font::NotoSans::style() -> Style {
    return _style;
}

method Font::NotoSans::setStyle(Style newStyle) -> Void {
    _style = newStyle;
}

method Font::NotoSans::data() -> const FontData * {

    var bold = _weight == Font::Weight::bold;
    var italic = _style == Font::Style::italic;

    switch (_size) {
    case Font::Size::xxSmall:
        if (bold && italic) {
            return &(mf_rlefont_NotoSans_BoldItalic8.font);
        } else if (bold) {
            return &(mf_rlefont_NotoSans_Bold8.font);
        } else if (italic) {
            return &(mf_rlefont_NotoSans_Italic8.font);
        } else {
            return &(mf_rlefont_NotoSans_Regular8.font);
        }
        break;
    case Font::Size::xSmall:
        if (bold && italic) {
            return &(mf_rlefont_NotoSans_BoldItalic10.font);
        } else if (bold) {
            return &(mf_rlefont_NotoSans_Bold10.font);
        } else if (italic) {
            return &(mf_rlefont_NotoSans_Italic10.font);
        } else {
            return &(mf_rlefont_NotoSans_Regular10.font);
        }
        break;
    case Font::Size::small:
        if (bold && italic) {
            return &(mf_rlefont_NotoSans_BoldItalic12.font);
        } else if (bold) {
            return &(mf_rlefont_NotoSans_Bold12.font);
        } else if (italic) {
            return &(mf_rlefont_NotoSans_Italic12.font);
        } else {
            return &(mf_rlefont_NotoSans_Regular12.font);
        }
        break;
    case Font::Size::medium:
        if (bold && italic) {
            return &(mf_rlefont_NotoSans_BoldItalic16.font);
        } else if (bold) {
            return &(mf_rlefont_NotoSans_Bold16.font);
        } else if (italic) {
            return &(mf_rlefont_NotoSans_Italic16.font);
        } else {
            return &(mf_rlefont_NotoSans_Regular16.font);
        }
        break;
    case Font::Size::large:
        if (bold && italic) {
            return &(mf_rlefont_NotoSansDisplay_BoldItalic20.font);
        } else if (bold) {
            return &(mf_rlefont_NotoSansDisplay_Bold20.font);
        } else if (italic) {
            return &(mf_rlefont_NotoSansDisplay_Italic20.font);
        } else {
            return &(mf_rlefont_NotoSansDisplay_Regular20.font);
        }
        break;
    case Font::Size::xLarge:
        if (bold && italic) {
            return &(mf_rlefont_NotoSansDisplay_BoldItalic32.font);
        } else if (bold) {
            return &(mf_rlefont_NotoSansDisplay_Bold32.font);
        } else if (italic) {
            return &(mf_rlefont_NotoSansDisplay_Italic32.font);
        } else {
            return &(mf_rlefont_NotoSansDisplay_Regular32.font);
        }
        break;
    case Font::Size::xxLarge:
        if (bold && italic) {
            return &(mf_rlefont_NotoSansDisplay_BoldItalic48.font);
        } else if (bold) {
            return &(mf_rlefont_NotoSansDisplay_Bold48.font);
        } else if (italic) {
            return &(mf_rlefont_NotoSansDisplay_Italic48.font);
        } else {
            return &(mf_rlefont_NotoSansDisplay_Regular48.font);
        }
        break;
    default:
        if (bold && italic) {
            return &(mf_rlefont_NotoSans_BoldItalic16.font);
        } else if (bold) {
            return &(mf_rlefont_NotoSans_Bold16.font);
        } else if (italic) {
            return &(mf_rlefont_NotoSans_Italic16.font);
        } else {
            return &(mf_rlefont_NotoSans_Regular16.font);
        }
        break;
    }
}
