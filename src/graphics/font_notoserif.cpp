/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ graphics/font_notoserif.cpp                                               ║
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
#include "graphics/font_notoserif.h"

Font::NotoSerif::NotoSerif(Size size, Weight weight,Style style):
    _size(size),
    _weight(weight),
    _style(style)
{}

Font::NotoSerif::~NotoSerif() {}

method Font::NotoSerif::size() -> Size {
    return _size;
}

method Font::NotoSerif::setSize(Size newSize) -> Void {
    _size = newSize;
}

method Font::NotoSerif::weight() -> Weight {
    return _weight;
}

method Font::NotoSerif::setWeight(Weight newWeight) -> Void {
    _weight = newWeight;
}

method Font::NotoSerif::style() -> Style {
    return _style;
}

method Font::NotoSerif::setStyle(Style newStyle) -> Void {
    _style = newStyle;
}

method Font::NotoSerif::data() -> const FontData * {

    var bold = _weight == Font::Weight::bold;
    var italic = _style == Font::Style::italic;

    switch (_size) {
    case Font::Size::xxSmall:
        if (bold && italic) {
            return &(mf_rlefont_NotoSerif_BoldItalic8.font);
        } else if (bold) {
            return &(mf_rlefont_NotoSerif_Bold8.font);
        } else if (italic) {
            return &(mf_rlefont_NotoSerif_Italic8.font);
        } else {
            return &(mf_rlefont_NotoSerif_Regular8.font);
        }
        break;
    case Font::Size::xSmall:
        if (bold && italic) {
            return &(mf_rlefont_NotoSerif_BoldItalic10.font);
        } else if (bold) {
            return &(mf_rlefont_NotoSerif_Bold10.font);
        } else if (italic) {
            return &(mf_rlefont_NotoSerif_Italic10.font);
        } else {
            return &(mf_rlefont_NotoSerif_Regular10.font);
        }
        break;
    case Font::Size::small:
        if (bold && italic) {
            return &(mf_rlefont_NotoSerif_BoldItalic12.font);
        } else if (bold) {
            return &(mf_rlefont_NotoSerif_Bold12.font);
        } else if (italic) {
            return &(mf_rlefont_NotoSerif_Italic12.font);
        } else {
            return &(mf_rlefont_NotoSerif_Regular12.font);
        }
        break;
    case Font::Size::medium:
        if (bold && italic) {
            return &(mf_rlefont_NotoSerif_BoldItalic16.font);
        } else if (bold) {
            return &(mf_rlefont_NotoSerif_Bold16.font);
        } else if (italic) {
            return &(mf_rlefont_NotoSerif_Italic16.font);
        } else {
            return &(mf_rlefont_NotoSerif_Regular16.font);
        }
        break;
    case Font::Size::large:
        if (bold && italic) {
            return &(mf_rlefont_NotoSerifDisplay_BoldItalic20.font);
        } else if (bold) {
            return &(mf_rlefont_NotoSerifDisplay_Bold20.font);
        } else if (italic) {
            return &(mf_rlefont_NotoSerifDisplay_Italic20.font);
        } else {
            return &(mf_rlefont_NotoSerifDisplay_Regular20.font);
        }
        break;
    case Font::Size::xLarge:
        if (bold && italic) {
            return &(mf_rlefont_NotoSerifDisplay_BoldItalic32.font);
        } else if (bold) {
            return &(mf_rlefont_NotoSerifDisplay_Bold32.font);
        } else if (italic) {
            return &(mf_rlefont_NotoSerifDisplay_Italic32.font);
        } else {
            return &(mf_rlefont_NotoSerifDisplay_Regular32.font);
        }
        break;
    case Font::Size::xxLarge:
        if (bold && italic) {
            return &(mf_rlefont_NotoSerifDisplay_BoldItalic48.font);
        } else if (bold) {
            return &(mf_rlefont_NotoSerifDisplay_Bold48.font);
        } else if (italic) {
            return &(mf_rlefont_NotoSerifDisplay_Italic48.font);
        } else {
            return &(mf_rlefont_NotoSerifDisplay_Regular48.font);
        }
        break;
    default:
        if (bold && italic) {
            return &(mf_rlefont_NotoSerif_BoldItalic16.font);
        } else if (bold) {
            return &(mf_rlefont_NotoSerif_Bold16.font);
        } else if (italic) {
            return &(mf_rlefont_NotoSerif_Italic16.font);
        } else {
            return &(mf_rlefont_NotoSerif_Regular16.font);
        }
        break;
    }
}
