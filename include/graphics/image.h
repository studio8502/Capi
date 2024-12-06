/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ graphics/image.h                                                          ║
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
#include "graphics/geometry.h"
#include "graphics/palette.h"

class Surface;

class Image {
public:
    Image(String filename);

    ~Image();

    static method imageFromFile(String filename) -> shared_ptr<Image>;

    static method imageSurfaceFromFile(String filename) -> shared_ptr<Surface>;

    static method imageFromURL(String url) -> shared_ptr<Image>;

    static method RGBAtoBGRA(Color pixel) -> Color;

    method rect() -> Rect;

    Color operator[](std::size_t idx);
    const Color operator[](std::size_t idx) const;

    Int32 _width;
    Int32 _height;
    Int32 _channels;
    Color *data;

private:
};
