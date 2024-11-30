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

#include "graphics/font.h"

class Font::Lexend: public Font {
public:
    Lexend(Size size = Size::medium, Weight weight = Weight::regular);

    ~Lexend();

    virtual method size() -> Size;

    virtual method setSize(Size newSize) -> Void;

    virtual method weight() -> Weight;

    virtual method setWeight(Weight newWeight) -> Void;

    virtual method style() -> Style;

    virtual method setStyle(Style newStyle) -> Void;

    virtual method data() -> const FontData *;

private:
    Size _size;
    Weight _weight;
    Style _style;
};
