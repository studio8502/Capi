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

#include "kernel/event.h"

std::queue<shared_ptr<Event>> eventQueue = std::queue<shared_ptr<Event>>();

Event::Event(Event::Type type):
    type(type),
    deltaX(0.0),
    deltaY(0.0),
    position(Point(0,0)),
    clickCount(0),
    locationInWindow(Point(0,0)),
    _window(nullptr)
{}

Event::~Event() {}

method Event::window() -> shared_ptr<Window>  {
    return _window;
}

method Event::setWindow(shared_ptr<Window> window) -> Void {
    _window = window;
}

method Event::mouseMoved() -> shared_ptr<Event> {
    return make_shared<Event>(Type::mouseMoved);
}

method Event::leftMouseDown() -> shared_ptr<Event> {
    return make_shared<Event>(Type::leftMouseDown);
}

method Event::leftMouseDragged() -> shared_ptr<Event> {
    return make_shared<Event>(Type::leftMouseDragged);
}

method Event::leftMouseUp() -> shared_ptr<Event> {
    return make_shared<Event>(Type::leftMouseUp);
}

method Event::middleMouseDown() -> shared_ptr<Event> {
    return make_shared<Event>(Type::middleMouseDown);
}

method Event::middleMouseDragged() -> shared_ptr<Event> {
    return make_shared<Event>(Type::middleMouseDragged);
}

method Event::middleMouseUp() -> shared_ptr<Event> {
    return make_shared<Event>(Type::middleMouseUp);
}

method Event::rightMouseDown() -> shared_ptr<Event> {
    return make_shared<Event>(Type::rightMouseDown);
}

method Event::rightMouseDragged() -> shared_ptr<Event> {
    return make_shared<Event>(Type::rightMouseDragged);
}

method Event::rightMouseUp() -> shared_ptr<Event> {
    return make_shared<Event>(Type::rightMouseUp);
}

method Event::scrollWheel() -> shared_ptr<Event> {
    return make_shared<Event>(Type::scrollWheel);
}
