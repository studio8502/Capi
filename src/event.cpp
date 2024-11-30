/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ event.cpp                                                                 ║
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

#include "event.h"

std::queue<shared_ptr<Event>> eventQueue = std::queue<shared_ptr<Event>>();

Event::Event(EventType type):
    type(type)
{}

method Event::mouseEvent(Event::MouseEventType mouseEventType, UInt32 x, UInt32 y) -> shared_ptr<Event> {
    return make_shared<Event::MouseEvent>(mouseEventType, x, y);
}

Event::MouseEvent::MouseEvent(Event::MouseEventType mouseEventType, UInt32 x, UInt32 y):
    Event(Event::EventType::mouse),
    mouseEventType(mouseEventType),
    _x(x),
    _y(y)
{}

method Event::MouseEvent::position() -> Point {
    return Point(_x, _y);
}

method Event::MouseEvent::setPosition(Point position) {
    _x = position.x;
    _y = position.y;
}
