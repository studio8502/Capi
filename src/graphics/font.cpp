/*****************************************************************************
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
 ****************************************************************************/

#include "graphics/font.h"
#include "filesystem.h"

static shared_ptr<Font> _NotoSansRegular;
static shared_ptr<Font> _NotoSansBold;
static shared_ptr<Font> _NotoSansItalic;
static shared_ptr<Font> _NotoSansBoldItalic;

Font::Font(String path):
    fontLock()
{
    data = Filesystem::readFile(path, &length);
}

Font::~Font() {
    free((void *)data);
}

method Font::init() -> Void {
    _NotoSansRegular = make_shared<Font>("SD:/NotoSans-Regular.ttf");
    _NotoSansBold = make_shared<Font>("SD:/NotoSans-Bold.ttf");
    _NotoSansItalic = make_shared<Font>("SD:/NotoSans-Italic.ttf");
    _NotoSansBoldItalic = make_shared<Font>("SD:/NotoSans-BoldItalic.ttf");
}

method Font::acquire() -> Void {
    fontLock.Acquire();
}

method Font::release() -> Void {
    fontLock.Release();
}

method Font::DefaultUIFont() -> shared_ptr<Font> {
    return NotoSans();
}

method Font::DefaultWindowTitleFont() -> shared_ptr<Font> {
    return NotoSans(Weight::bold);
}

method Font::NotoSans(Weight weight, Style style) -> shared_ptr<Font> {
    if (weight == Weight::regular && style == Style::roman ) {
        return _NotoSansRegular; 
    } else if (weight == Weight::bold && style == Style::roman ) {
        return _NotoSansBold; 
    } else if (weight == Weight::regular && style == Style::italic ) {
        return _NotoSansItalic; 
    } else {
        return _NotoSansBoldItalic; 
    }
}
