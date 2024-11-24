// workspace/window.h
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

#include <string>
#include <memory>

#include "fonts/fonts.h"
#include "graphics/geometry.h"
#include "graphics/palette.h"
#include "workspace/workspace.h"
#include "workspace/drawable.h"

#include "custom_types.h"

#define WINDOW_TITLEBAR_HEIGHT 18
#define WINDOW_BORDER_THICKNESS 3

using std::shared_ptr;

class Window: public Drawable {
public:
    friend class Kernel;
    friend class Workspace;
    friend class View;

    using WindowDrawCallback = void (*)(shared_ptr<Window>);
    using WindowCloseCallback = void (*)(shared_ptr<Window>);

    Window();
    
    ~Window();

    virtual method rect() -> Rect ;
    
    virtual method setRect(Rect rect) -> Void;
    
    virtual method move(Point point) -> Void;

    virtual method isDecorated() -> Bool;

    virtual method setIsDecorated(Bool decorated) -> Void;

    virtual method hasTitlebar() -> Bool;

    virtual method setHasTitlebar(Bool titlebar) -> Void;

    virtual method hasCloseButton() -> Bool;

    virtual method setHasCloseButton(Bool closeButton) -> Void;

    virtual method isResizable() -> Bool;

    virtual method setIsResisable(Bool resizable) -> Void;

    virtual method title() -> String;
    
    virtual method setTitle(String title) -> Void;

    virtual method scrollX() -> Int32 override;
    
    virtual method setScrollX(Int32 scroll) -> Void override;

    virtual method scrollY() -> Int32 override;
    
    virtual method setScrollY(Int32 scroll) -> Void override;

	virtual method clear(UInt8 palette, UInt8 color) -> Void override;

    virtual method drawRect(Rect rect, Bool fill, UInt8 palette, UInt8 color, UInt8 alpha = 255) -> Void override;

    virtual method drawCircle(Point origin, UInt32 radius, Bool fill, UInt8 palette, UInt8 color, UInt8 alpha = 255) -> Void override;

	virtual method drawLine(Point origin, Point end, UInt8 palette, UInt8 color, UInt8 alpha = 255) -> Void override;
	
	virtual method drawImage(Rect rect, Color *pixelBuffer, UInt8 alpha = 255) -> Void override;
	
	virtual method drawImageTransparent(Rect rect, Color *pixelBuffer, Color transparentColor, UInt8 alpha = 255) -> Void override;
	
	virtual method drawImageRect(Rect rect, Point sourceOrigin, Color *pixelBuffer, UInt8 alpha = 255) -> Void override;
	
	virtual method drawImageRectTransparent(Rect rect, Rect sourceRect, Color *pixelBuffer, Color transparentColor, UInt8 alpha = 255) -> Void override;

protected:

    Rect _rect;

    Bool _isDecorated;
    Bool _hasTitlebar;
    Bool _hasCloseButton;
    Bool _isResizable;
    String _title;

    Int32 _scrollX;
    Int32 _scrollY;

    // This method takes a point relative to the window's content area origin, and translates it into
    // screen coordinates based on the window's scrollX and scrollY variables.
    virtual method translate(Point origin) -> Point;

    virtual method translate(Rect rect) -> Rect;

    virtual method contentRect() -> Rect;

    virtual method clipRect() -> Rect;

    virtual method draw()-> Void override;

};
