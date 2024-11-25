// workspace/paragraph_style.h
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


#pragma once

#include "mf_font.h"
#include "graphics/font.h"
#include "custom_types.h"

using FontData = mf_font_s;

class Font {
public:

    enum class Size {
        xxSmall = 8,
        xSmall = 10,
        small = 12,
        medium = 16,
        large = 20,
        xLarge = 32,
        xxLarge = 48
    };

    enum class Weight {
        regular,
        bold
    };

    enum class Style {
        roman,
        italic
    };

    virtual method data() -> const FontData * = 0;
};
