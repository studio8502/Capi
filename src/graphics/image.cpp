/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ graphics/image.cpp                                                        ║
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

#include "graphics/image.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#define STBI_ONLY_JPEG
#include "graphics/stb_image.h"

static UInt8 desired_channels = 4;
static char exceptionMessage[256];

Image::Image(String filename) {
    data = (Color *) stbi_load(filename.c_str(), &_width, &_height, &_channels, desired_channels);
    if (data == nullptr) {
        sprintf(exceptionMessage, "Failed to load file \"%s\"", filename.c_str());
        throw(std::runtime_error(exceptionMessage));
    }
}

Image::~Image() {
    stbi_image_free(data);
}

method Image::imageFromFile(String filename) -> shared_ptr<Image> {
    return make_shared<Image>(filename);
}

method Image::rect() -> Rect {
    return Rect(0, 0, _width, _height);
}
