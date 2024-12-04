/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ graphics/palette.h                                                        ║
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

#ifndef DefaultPalette
#define DefaultPalette ((UInt8)0)
#endif

using Color = TScreenColor;

#define ALPHA(C, A) ({ \
    ((((C)) & 0x00FFFFFF) | ((((A) & 0xFF)) << 24)); \
})

// Take an RGB value in the form 0xAABBCC and turn it into a screen colour.
auto RGB(UInt32 RGB) -> Color;

auto RGBA(UInt32 RGBA) -> Color;

extern Color SystemPalette[256];

// Given two colours return the result of alpha blending the second over the
// first.
auto alpha_blend(Color background, Color foreground) -> Color;

auto alpha_blend_override(Color background, Color foreground, UInt8 alpha) -> Color;
