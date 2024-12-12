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

UInt32 SystemPalette[] = {
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

    Double alpha_ratio = (1.0/255.0);

    Double background_alpha = alpha_ratio * ((background >> 24) & 0xFF);
    Double background_red = alpha_ratio * ((background >> 16) & 0xFF);
    Double background_green = alpha_ratio * ((background >> 8) & 0xFF);
    Double background_blue = alpha_ratio * (background & 0xFF);

    Double foreground_alpha = alpha_ratio * ((foreground >> 24) & 0xFF);
    Double foreground_red = alpha_ratio * ((foreground >> 16) & 0xFF);
    Double foreground_green = alpha_ratio * ((foreground >> 8) & 0xFF);
    Double foreground_blue = alpha_ratio * (foreground & 0xFF);
/*
r.A = 1 - (1 - fg.A) * (1 - bg.A);
if (r.A < 1.0e-6) return r; // Fully transparent -- R,G,B not important
r.R = fg.R * fg.A / r.A + bg.R * bg.A * (1 - fg.A) / r.A;
r.G = fg.G * fg.A / r.A + bg.G * bg.A * (1 - fg.A) / r.A;
r.B = fg.B * fg.A / r.A + bg.B * bg.A * (1 - fg.A) / r.A;
*/
    Double result_alpha = 1 - (1 - foreground_alpha) * (1 - background_alpha);
    Double result_red = foreground_red * foreground_alpha / result_alpha + background_red * background_alpha * (1 - foreground_alpha) / result_alpha;
    Double result_green = foreground_green * foreground_alpha / result_alpha + background_green * background_alpha * (1 - foreground_alpha) / result_alpha;
    Double result_blue = foreground_blue * foreground_alpha / result_alpha + background_blue * background_alpha * (1 - foreground_alpha) / result_alpha;

    UInt8 result_alpha_u8 = ceil(255.0 * result_alpha);
    UInt8 result_red_u8 = ceil(255.0 * result_red);
    UInt8 result_green_u8 = ceil(255.0 * result_green);
    UInt8 result_blue_u8 = ceil(255.0 * result_blue);

    return result_blue_u8 | (result_green_u8 << 8) | (result_red_u8 << 16) | (result_alpha_u8 << 24);
}
