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
#include "event.h"

#define WINDOW_BORDER_WIDTH 4
#define WINDOW_TITLEBAR_HEIGHT 16

class Event;

class Window {
public:
    friend class Workspace;

    using WindowDrawCallback = function (*)(Window *) -> Void;

    Window();

    ~Window();

    static String defaultTitle;

    virtual method width() -> UInt64;

    virtual method height() -> UInt64;

    method origin() -> Point;

    method rect() -> Rect;

    method titlebarRect() -> Rect;

    method contentRect() -> Rect;

    method move(Point point) -> Void;

    method resize(Size size) -> Void;

    method title() -> String;

    method setTitle(String title) -> Void;

    method setDrawCallback(WindowDrawCallback callback) -> Void;

    method isVisible() -> Bool;

    method show() -> Void;

    method hide() -> Void;

    method isDecorated() -> Bool;

    method setIsDecorated(Bool decorated) -> Void;

    method hasCloseButton() -> Bool;

    method setHasCloseButton(Bool closeButton) -> Void;

    method hasRollUpButton() -> Bool;

    method setHasRollUpButton(Bool rollUpButton) -> Void;

    method opacity() -> UInt8;

    method setOpacity(UInt8 opacity) -> Void;

    method contentOrigin() -> Point;

    method acquire() -> Void;

    method release() -> Void;

    method drawText(String message, Point origin) -> Void;

    method drawSurface(shared_ptr<Surface> src, Point dest) -> Void;

    virtual method draw() -> Void;

    method handleEvent(shared_ptr<Event> event, shared_ptr<Window>sharedThis) -> Void;

private:

    method surface() -> shared_ptr<Surface>;

    virtual method drawWindowChrome() -> Void;

    virtual method drawWindowContent() -> Void;

    method translate(Rect rect) -> Rect;

    method translate(Point point) -> Point;

    String _title;
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
    Bool isBeingDragged;

    shared_ptr<Surface> windowSurface;
    shared_ptr<Surface> contentSurface;

    CSpinLock _lock;

    WindowDrawCallback drawCallback;
};
