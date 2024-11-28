/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ workspace/window.h                                                        ║
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
#include "graphics/surface.h"

#define WINDOW_BORDER_WIDTH 4
#define WINDOW_TITLEBAR_HEIGHT 16

class Window {
public:

    using WindowDrawCallback = function (*)(Window *) -> Void;

    Window(Point origin, Size size, Bool hasTitlebar = true, Bool isDecorated = true);

    ~Window();

    virtual method width() -> UInt64;

    virtual method height() -> UInt64;

    method rect() -> Rect;

    method contentRect() -> Rect;

    method resize(Size size) -> Void;

    method setDrawCallback(WindowDrawCallback callback) -> Void;

    method isVisible() -> Bool;

    method show() -> Void;

    method hide() -> Void;

    method hasCloseButton() -> Bool;

    method setHasCloseButton(Bool closeButton) -> Void ;

    method hasRollUpButton() -> Bool;

    method setHasRollUpButton(Bool rollUpButton) -> Void ;

    method opacity() -> UInt8;

    method setOpacity(UInt8 opacity) -> Void;

    method acquire() -> Void;

    method release() -> Void;

	method clear(UInt8 palette, UInt8 color) -> Void;

    method drawLine(Point begin, Point end, UInt8 palette, UInt8 color, UInt8 alpha = 255) -> Void;

    method drawRect(Rect rect, Bool fill, UInt8 palette, UInt8 color, UInt8 alpha = 255) -> Void;

    method drawCircle(Point origin, UInt32 radius, Bool fill, UInt8 palette, UInt8 color, UInt8 alpha = 255) -> Void;

    method drawImageRect(Rect rect, Rect sourceRect, Color *pixelBuffer, UInt8 alpha = 255) -> Void;

    method drawImageRectTransparent(Rect rect, Rect sourceRect, Color *pixelBuffer, Color transparentColor, UInt8 alpha = 255) -> Void;

    method drawSurface(shared_ptr<Surface> src, Point dest, UInt8 alpha = 255) -> Void;

    virtual method draw() -> Void;

private:

    virtual method drawWindowChrome() -> Void;

    virtual method drawWindowContent() -> Void;

    method translate(Rect rect) -> Rect;

    method translate(Point point) -> Point;

    Int64 _x;
    Int64 _y;
    UInt64 _width;
    UInt64 _height;
    Bool _isDecorated;
    Bool _hasTitlebar;
    Bool _isVisible;
    Bool _hasCloseButton;
    Bool _hasRollUpButton;
    UInt8 _opacity;
    Bool _dirty;

    shared_ptr<Surface> windowSurface;
    shared_ptr<Surface> contentSurface;

    CSpinLock _lock;

    WindowDrawCallback drawCallback;
};
