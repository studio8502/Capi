/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ graphics/fonts.h                                                          ║
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

#pragma once

#include "capi.h"

#include "mcufont.h"

using FontData = mf_font_s;

class Font {
public:
    enum class Size {
        xxSmall = 8,
        xSmall = 10,
        small = 12,
        medium = 16,
        large = 20,
        xLarge = 32,
        xxLarge = 48
    };

    enum class Weight {
        regular,
        bold
    };

    enum class Style {
        roman,
        italic
    };

    virtual method size() -> Size = 0;

    virtual method setSize(Size newSize) -> Void = 0;

    virtual method weight() -> Weight = 0;

    virtual method setWeight(Weight newWeight) -> Void = 0;

    virtual method style() -> Style = 0;

    virtual method setStyle(Style newStyle) -> Void = 0;

    virtual method data() -> const FontData * = 0;

    virtual method widthForString(String str, UInt16 count = 0) -> Int16;

    static method UIFont(Font::Size size = Font::Size::medium, Font::Weight weight = Font::Weight::regular) -> shared_ptr<Font>;

    class NotoSans;
    class NotoSerif;
    class NotoMono;


};