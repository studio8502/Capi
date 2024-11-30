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

class Event {
public:
    enum class EventType {
        mouse,
        keyboard,
        gamepad
    };

    enum class MouseEventType {
        buttonUp,
        buttonDown,
        buttonClicked,
        scroll,
        move
    };

    static method mouseEvent(MouseEventType mouseEventType, UInt32 x, UInt32 y) -> shared_ptr<Event>;

    Event(EventType type);

    virtual ~Event(){}

    EventType type;
private:
    class MouseEvent;
};

class Event::MouseEvent: public Event {
public:
    MouseEvent(Event::MouseEventType mouseEventType, UInt32 x, UInt32 y);

    virtual ~MouseEvent() {}

    method position() -> Point;

    method setPosition(Point position);

private:
    Event::MouseEventType mouseEventType;
    UInt32 _x;
    UInt32 _y;
};

extern std::queue<shared_ptr<Event>> eventQueue;