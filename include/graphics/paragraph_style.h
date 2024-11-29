/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ graphics/paragraph_style.h                                                ║
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
#include "graphics/font.h"
#include "graphics/palette.h"

using std::shared_ptr;

class ParagraphStyle {
public:

    enum class Align {
        left,
        center,
        centre = center,
        right,
        justify
    };

    ParagraphStyle(shared_ptr<Font> font, UInt8 palette, UInt8 color, Align align = Align::left);

    ~ParagraphStyle();

    static method DefaultStyle() -> shared_ptr<ParagraphStyle>;

    method color() -> Color;

    method setColor(Color newColor) -> Void;
    
    method align() -> Align;

    method setAlign(Align newAlign) -> Void;

    method font() -> shared_ptr<Font>;

    method setFont(shared_ptr<Font> newFont) -> Void;

private:

    Color _color;

    Align _align;

    shared_ptr<Font> _font;
};
