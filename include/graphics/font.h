/*
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ graphics/font.h                                                           ║
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

#pragma once

#include "capi.h"
#include "mcufont.h"

struct Font {

    enum class Family {
        Courier,
        Helvetica,
        Lucida,
        LucidaBright,
        LucidaTypewriter,
        OpenDyslexic,
        NewCenturySchoolbook,
        Terminus,
        Times,
        Utopia
    };

    enum class Style {
        Roman,
        Italic
    };

    enum class Weight {
        Regular,
        Bold
    };

    enum class Size {
        xSmall = 8,
        small = 10,
        medium = 12,
        large = 14,
        xLarge = 18,
        xxLarge = 24
    };

    Family family;
    Style style;
    Weight weight;
    Size size;

    String name;

    const mf_font_s *data;

    ~Font();

    static method Helvetica(Size size) -> Font;

    static method HelveticaBold(Size size) -> Font;

    static method HelveticaItalic(Size size) -> Font;

    static method HelveticaBoldItalic(Size size) -> Font;

private:

    Font(Family family, Style style, Weight weight, Size size);
};
