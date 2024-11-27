/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ graphics/palette.cpp                                                      ║
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

#include <cmath>

#include "graphics/palette.h"
#include "capi.h"

Palette SystemPalette[] = {{{
#include "graphics/aurora.hex"
}}};

auto RGB(UInt32 RGB) -> Color {
    UInt8 RED = (RGB >> 16) & 0xFF;
    UInt8 GREEN = (RGB >> 8) & 0xFF;
    UInt8 BLUE = RGB & 0xFF;

    return COLOR32(RED, GREEN, BLUE, 0xFF);
}

Color& Palette::operator[] (int index) {
    return color[index];
}

// Given two colours and an alpha level, return the result of alpha blending
// the second over the first with the supplied alpha level.
auto alpha_blend(Color background, Color foreground, UInt8 alpha) -> Color {

    if (alpha == 255) {
        return foreground;
    }

    Double alpha_ratio = (1.0/255.0) * alpha;

    Double background_red = 1.0 * ((background >> 16) & 0xFF);
    Double background_green = 1.0 * ((background >> 8) & 0xFF);
    Double background_blue = 1.0 * (background & 0xFF);

    Double foreground_red = 1.0 * ((foreground >> 16) & 0xFF);
    Double foreground_green = 1.0 * ((foreground >> 8) & 0xFF);
    Double foreground_blue = 1.0 * (foreground & 0xFF);

    UInt8 result_red = ceil(background_red + (foreground_red - background_red) * alpha_ratio);
    UInt8 result_green = ceil(background_green + (foreground_green - background_green) * alpha_ratio);
    UInt8 result_blue = ceil(background_blue + (foreground_blue - background_blue) * alpha_ratio);

    return COLOR32(result_red, result_green, result_blue, 255);
}