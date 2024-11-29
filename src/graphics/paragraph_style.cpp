/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ graphics/paragraph_style.cpp                                              ║
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

#include "graphics/paragraph_style.h"
#include "graphics/font.h"

ParagraphStyle::ParagraphStyle(shared_ptr<Font> font, UInt8 palette, UInt8 color, ParagraphStyle::Align align):
    _color(SystemPalette[palette][color]),
    _align(align),
    _font(font)
{}

ParagraphStyle::~ParagraphStyle() {}

method ParagraphStyle::DefaultStyle() -> shared_ptr<ParagraphStyle> {
    var font = Font::UIFont();
    var align = Align::left;
    return make_shared<ParagraphStyle>(font, 0, 0, align);
}

method ParagraphStyle::color() -> Color {
    return _color;
}

method ParagraphStyle::align() -> ParagraphStyle::Align {
    return _align;
}

method ParagraphStyle::font() -> shared_ptr<Font> {
    return _font;
}
