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

std::queue<shared_ptr<MouseEvent>> mouseEventQueue = std::queue<shared_ptr<MouseEvent>>();

MouseEvent::~MouseEvent() {}

method MouseEvent::Move(UInt32 x, UInt32 y) -> shared_ptr<MouseEvent> {
    return make_shared<MouseEvent>(EventType::move, x, y);
}

method MouseEvent::ButtonUp(MouseButton button, UInt32 x, UInt32 y) -> shared_ptr<MouseEvent> {
    return make_shared<MouseEvent>(EventType::buttonUp, button, x, y);
}

method MouseEvent::ButtonDown(MouseButton button, UInt32 x, UInt32 y) -> shared_ptr<MouseEvent> {
    return make_shared<MouseEvent>(EventType::buttonDown, button, x, y);
}

method MouseEvent::Scroll(UInt32 x, UInt32 y) -> shared_ptr<MouseEvent> {
    return make_shared<MouseEvent>(EventType::scroll, x, y);
}

MouseEvent::MouseEvent(EventType type, UInt32 x, UInt32 y):
    type(type),
    _x(x),
    _y(y)
{}

MouseEvent::MouseEvent(EventType type, MouseButton button, UInt32 x, UInt32 y):
    type(type),
    button(button),
    _x(x),
    _y(y)
{}

method MouseEvent::position() -> Point {
    return Point(_x, _y);
}
