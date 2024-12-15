/*
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ graphics/font.cpp                                                         ║
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
*/

#include "graphics/font.h"
#include "fonts.h"
 
Font::Font(Family family, Style style, Weight weight, Size size):
    family(family),
    style(style),
    weight(weight),
    size(size)
{}

Font::~Font() {}

method Font::Helvetica(Size size) -> Font {
    var font = Font(Family::Helvetica, Style::Roman, Weight::Regular, size);

    switch (size) {
    case Size::xSmall:
        font.data = (&mf_rlefont_Helvetica_8.font);
        break;
    case Size::small:
        font.data = (&mf_rlefont_Helvetica_10.font);
        break;
    case Size::medium:
        font.data = (&mf_rlefont_Helvetica_12.font);
        break;
    case Size::large:
        font.data = (&mf_rlefont_Helvetica_14.font);
        break;
    case Size::xLarge:
        font.data = (&mf_rlefont_Helvetica_18.font);
        break;
    case Size::xxLarge:
        font.data = (&mf_rlefont_Helvetica_24.font);
        break;
    }

    return font;
}

method Font::HelveticaBold(Size size) -> Font {
    var font = Font(Family::Helvetica, Style::Roman, Weight::Regular, size);

    switch (size) {
    case Size::xSmall:
        font.data = (&mf_rlefont_HelveticaBold_8.font);
        break;
    case Size::small:
        font.data = (&mf_rlefont_HelveticaBold_10.font);
        break;
    case Size::medium:
        font.data = (&mf_rlefont_HelveticaBold_12.font);
        break;
    case Size::large:
        font.data = (&mf_rlefont_HelveticaBold_14.font);
        break;
    case Size::xLarge:
        font.data = (&mf_rlefont_HelveticaBold_18.font);
        break;
    case Size::xxLarge:
        font.data = (&mf_rlefont_HelveticaBold_24.font);
        break;
    }

    return font;
}

method Font::HelveticaItalic(Size size) -> Font {
    var font = Font(Family::Helvetica, Style::Roman, Weight::Regular, size);

    switch (size) {
    case Size::xSmall:
        font.data = (&mf_rlefont_HelveticaItalic_8.font);
        break;
    case Size::small:
        font.data = (&mf_rlefont_HelveticaItalic_10.font);
        break;
    case Size::medium:
        font.data = (&mf_rlefont_HelveticaItalic_12.font);
        break;
    case Size::large:
        font.data = (&mf_rlefont_HelveticaItalic_14.font);
        break;
    case Size::xLarge:
        font.data = (&mf_rlefont_HelveticaItalic_18.font);
        break;
    case Size::xxLarge:
        font.data = (&mf_rlefont_HelveticaItalic_24.font);
        break;
    }

    return font;
}

method Font::HelveticaBoldItalic(Size size) -> Font {
    var font = Font(Family::Helvetica, Style::Roman, Weight::Regular, size);

    switch (size) {
    case Size::xSmall:
        font.data = (&mf_rlefont_HelveticaBoldItalic_8.font);
        break;
    case Size::small:
        font.data = (&mf_rlefont_HelveticaBoldItalic_10.font);
        break;
    case Size::medium:
        font.data = (&mf_rlefont_HelveticaBoldItalic_12.font);
        break;
    case Size::large:
        font.data = (&mf_rlefont_HelveticaBoldItalic_14.font);
        break;
    case Size::xLarge:
        font.data = (&mf_rlefont_HelveticaBoldItalic_18.font);
        break;
    case Size::xxLarge:
        font.data = (&mf_rlefont_HelveticaBoldItalic_24.font);
        break;
    }

    return font;
}