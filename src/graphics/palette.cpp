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

#include "graphics/palette.h"

Color SystemPalette[] = {
#include "graphics/aurora.hex"
};

auto RGBA(UInt32 RGBA) -> Color {
    UInt8 ALPHA = (RGBA >> 24) & 0xFF;
    UInt8 RED = (RGBA >> 16) & 0xFF;
    UInt8 GREEN = (RGBA >> 8) & 0xFF;
    UInt8 BLUE = RGBA & 0xFF;

    return BLUE | (GREEN << 8) | (RED << 16) | (ALPHA < 24);
}

auto alpha_blend(Color background, Color foreground) -> Color {

    UInt8 alpha = (foreground >> 24) & 0xFF;

    if (alpha == 255) {
        return foreground;
    }

    Double alpha_ratio = (1.0/255.0) * alpha;

    Double background_alpha = 1.0 * ((background >> 24) & 0xFF);
    Double background_red = 1.0 * ((background >> 16) & 0xFF);
    Double background_green = 1.0 * ((background >> 8) & 0xFF);
    Double background_blue = 1.0 * (background & 0xFF);

    Double foreground_alpha = 1.0 * ((foreground >> 24) & 0xFF);
    Double foreground_red = 1.0 * ((foreground >> 16) & 0xFF);
    Double foreground_green = 1.0 * ((foreground >> 8) & 0xFF);
    Double foreground_blue = 1.0 * (foreground & 0xFF);

    UInt8 result_alpha = ceil(255.0 * (1.0 - (1.0 - foreground_alpha) * (1.0 - background_alpha)));
    UInt8 result_red = ceil(background_red + (foreground_red - background_red) * alpha_ratio);
    UInt8 result_green = ceil(background_green + (foreground_green - background_green) * alpha_ratio);
    UInt8 result_blue = ceil(background_blue + (foreground_blue - background_blue) * alpha_ratio);


    return result_blue | (result_green << 8) | (result_red << 16) | (255 << 24);
}

auto alpha_blend_override(Color background, Color foreground, UInt8 alpha) -> Color {

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

    return result_blue | (result_green << 8) | (result_red << 16) | (0xFF << 24);
}
