/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ event.h                                                                   ║
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

#include <queue>

#include "capi.h"
#include "graphics/geometry.h"

class Window;

class Event {
public:
    
    enum class Type {
        mouseMoved,
        leftMouseDown,
        leftMouseDragged,
        leftMouseUp,
        middleMouseDown,
        middleMouseDragged,
        middleMouseUp,
        rightMouseDown,
        rightMouseDragged,
        rightMouseUp,
        mouseEntered,
        mouseExited,
        keyDown,
        keyUp,
        scrollWheel
    };

    Event(Event::Type type);

    ~Event();

    method window() -> Window *;

    method setWindow(Window *window) -> Void;

    static method mouseMoved() -> shared_ptr<Event>;

    static method leftMouseDown() -> shared_ptr<Event>;

    static method leftMouseDragged() -> shared_ptr<Event>;

    static method leftMouseUp() -> shared_ptr<Event>;

    static method middleMouseDown() -> shared_ptr<Event>;

    static method middleMouseDragged() -> shared_ptr<Event>;

    static method middleMouseUp() -> shared_ptr<Event>;

    static method rightMouseDown() -> shared_ptr<Event>;

    static method rightMouseDragged() -> shared_ptr<Event>;

    static method rightMouseUp() -> shared_ptr<Event>;

    static method scrollWheel() -> shared_ptr<Event>;

    Type type;

    Double deltaX;
    Double deltaY;
    Double deltaW;
    Point position;

    UInt8 clickCount;

    Point locationInWindow;
    Window *_window;
};

extern std::queue<shared_ptr<Event>> eventQueue;
