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

#include <memory>

#include "workspace/drawable.h"
#include "graphics/geometry.h"

class View: public Drawable {
public:

    virtual method rect() -> Rect ;
    
    virtual method setRect(Rect rect) -> Void;

    virtual method parent() -> std::weak_ptr<Drawable>;

    virtual method setParent(std::shared_ptr<Drawable> parent) -> Void;

    virtual method scrollX() -> Int32 override;
    
    virtual method setScrollX(Int32 scroll) -> Void override;

    virtual method scrollY() -> Int32 override;
    
    virtual method setScrollY(Int32 scroll) -> Void override;

    virtual method drawRect(Rect rect, Bool fill, UInt8 palette, UInt8 color, UInt8 alpha = 255) -> Void override;

    virtual method drawCircle(Point origin, UInt32 radius, Bool fill, UInt8 palette, UInt8 color, UInt8 alpha = 255) -> Void override;

    virtual method draw()-> Void override;

	virtual method drawLine(Point origin, Point end, UInt8 palette, UInt8 color, UInt8 alpha = 255) -> Void override;

	virtual method drawImage(Rect rect, Color *pixelBuffer, UInt8 alpha = 255) -> Void override;
	
	virtual method drawImageTransparent(Rect rect, Color *pixelBuffer, Color transparentColor, UInt8 alpha = 255) -> Void override;
	
	virtual method drawImageRect(Rect rect, Point sourceOrigin, Color *pixelBuffer, UInt8 alpha = 255) -> Void override;
	
	virtual method drawImageRectTransparent(Rect rect, Rect sourceRect, Color *pixelBuffer, Color transparentColor, UInt8 alpha = 255) -> Void override;

private:
    Rect _rect;

    Int32 _scrollX;
    Int32 _scrollY;

    std::weak_ptr<Drawable> _parent;

    virtual method translate(Point origin) -> Point;

    virtual method translate(Rect origin) -> Rect;
};
