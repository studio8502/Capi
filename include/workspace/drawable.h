// workspace/view.h
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

#include "graphics/geometry.h"
#include "graphics/palette.h"
#include "workspace/workspace.h"

#include "custom_types.h"

// An abstract class declaring an interface to the drawing API.
class Drawable {
public:

    virtual method scrollX() -> Int32 = 0;
    
    virtual method setScrollX(Int32 scroll) -> Void = 0;

    virtual method scrollY() -> Int32 = 0;
    
    virtual method setScrollY(Int32 scroll) -> Void = 0;

	virtual method clear(UInt8 palette, UInt8 color) -> Void = 0;

    virtual method drawRect(Rect rect, Bool fill, UInt8 palette, UInt8 color, UInt8 alpha = 255) -> Void = 0;

    virtual method drawCircle(Point origin, UInt32 radius, Bool fill, UInt8 palette, UInt8 color, UInt8 alpha = 255) -> Void = 0;

	virtual method drawLine(Point origin, Point end, UInt8 palette, UInt8 color, UInt8 alpha = 255) -> Void = 0;
	
	virtual method drawImage(Rect rect, Color *pixelBuffer, UInt8 alpha = 255) -> Void = 0;
	
	virtual method drawImageTransparent(Rect rect, Color *pixelBuffer, Color transparentColor, UInt8 alpha = 255) -> Void = 0;
	
	virtual method drawImageRect(Rect rect, Point sourceOrigin, Color *pixelBuffer, UInt8 alpha = 255) -> Void = 0;
	
	virtual method drawImageRectTransparent(Rect rect, Rect sourceRect, Color *pixelBuffer, Color transparentColor, UInt8 alpha = 255) -> Void = 0;

    virtual method draw()-> Void = 0;

};
