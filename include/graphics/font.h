/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ graphics/fonts.h                                                          ║
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

using FontData = unsigned char const *;

struct Font {
public:
    enum class Weight {
        regular,
        bold
    };

    enum class Style {
        roman,
        italic
    };

    Font(String path);

    ~Font();

    static method init() -> Void;

    static method DefaultUIFont() -> shared_ptr<Font>;

    static method DefaultWindowTitleFont() -> shared_ptr<Font>;

    static method NotoSans(Weight weight = Weight::regular, Style style = Style::roman) -> shared_ptr<Font>;

    static method NotoSerif(Weight weight = Weight::regular, Style style = Style::roman) -> shared_ptr<Font>;

    static method NotoSansMono(Weight weight) -> shared_ptr<Font>;

    method acquire() -> Void;

    method release() -> Void;

    UInt length;
    FontData data;

    CSpinLock fontLock;
};
