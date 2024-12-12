/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ event_responder.cpp                                                       ║
 ╟───────────────────────────────────────────────────────────────────────────╢
 ║ Copyright © 2024 Kyle J Cardoza, Studio 8502 <Kyle.Cardoza@icloud.com>    ║
 ╟───────────────────────────────────────────────────────────────────────────╢
 ║ This program is free software: you can redistribute it and/or modify      ║
 ║ it under the terms of the GNU General Public License as published by      ║
 ║ the Free Software Foundation, either version 3 of the License, or         ║
 ║ (at your option) any later version.                                       ║
 ║                                                                           ║
 ║ This program is distributed in the hope that it will be useful,           ║
 ║ but WITHOUT ANY WARRANTY  without even the implied warranty of            ║
 ║ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             ║
 ║ GNU General Public License for more details.                              ║
 ║                                                                           ║
 ║ You should have received a copy of the GNU General Public License         ║
 ║ along with this program.  If not, see <http://www.gnu.org/licenses/>.     ║
 ╚═══════════════════════════════════════════════════════════════════════════╝
 ****************************************************************************/

#include "workspace/event_responder.h"

EventResponder::EventResponder():
    _nextResponder(nullptr)
{}

EventResponder::~EventResponder() {}

method EventResponder::nextResponder() -> EventResponder * {
    return _nextResponder;
}

method EventResponder::setNextResponder(EventResponder *next) -> Void {
    _nextResponder = next;
}

method EventResponder::acceptsFirstResponder() -> Bool {
    return true;
}

method EventResponder::becomeFirstResponder() -> Bool {
    return true;
}

method EventResponder::mouseMoved(shared_ptr<Event> evt) -> Void {
    if (EventResponder *next = nextResponder()) {
        next->mouseMoved(evt);
    }
}

method EventResponder::mouseEntered(shared_ptr<Event> evt) -> Void {
    if (EventResponder *next = nextResponder()) {
        next->mouseEntered(evt);
    }
}

method EventResponder::mouseExited(shared_ptr<Event> evt) -> Void {
    if (EventResponder *next = nextResponder()) {
        next->mouseExited(evt);
    }
}

method EventResponder::mouseDown(shared_ptr<Event> evt) -> Void {
    if (EventResponder *next = nextResponder()) {
        next->mouseDown(evt);
    }
}

method EventResponder::mouseDragged(shared_ptr<Event> evt) -> Void {
    if (EventResponder *next = nextResponder()) {
        next->mouseDragged(evt);
    }
}

method EventResponder::mouseUp(shared_ptr<Event> evt) -> Void {
    if (EventResponder *next = nextResponder()) {
        next->mouseUp(evt);
    }
}

method EventResponder::middleMouseDown(shared_ptr<Event> evt) -> Void {
    if (EventResponder *next = nextResponder()) {
        next->middleMouseDown(evt);
    }
}

method EventResponder::middleMouseDragged(shared_ptr<Event> evt) -> Void {
    if (EventResponder *next = nextResponder()) {
        next->middleMouseDragged(evt);
    }
}

method EventResponder::middleMouseUp(shared_ptr<Event> evt) -> Void {
    if (EventResponder *next = nextResponder()) {
        next->middleMouseUp(evt);
    }
}

method EventResponder::rightMouseDown(shared_ptr<Event> evt) -> Void {
    if (EventResponder *next = nextResponder()) {
        next->rightMouseDown(evt);
    }
}

method EventResponder::rightMouseDragged(shared_ptr<Event> evt) -> Void {
    if (EventResponder *next = nextResponder()) {
        next->rightMouseDragged(evt);
    }
}

method EventResponder::rightMouseUp(shared_ptr<Event> evt) -> Void {
    if (EventResponder *next = nextResponder()) {
        next->rightMouseUp(evt);
    }
}

method EventResponder::scrollWheel(shared_ptr<Event> evt) -> Void {
    if (EventResponder *next = nextResponder()) {
        next->scrollWheel(evt);
    }
}

method EventResponder::keyDown(shared_ptr<Event> evt) -> Void {
    if (EventResponder *next = nextResponder()) {
        next->keyDown(evt);
    }
}

method EventResponder::keyUp(shared_ptr<Event> evt) -> Void {
    if (EventResponder *next = nextResponder()) {
        next->keyUp(evt);
    }
}

method EventResponder::gamepadButtonDown(shared_ptr<Event> evt) -> Void {
    if (EventResponder *next = nextResponder()) {
        next->gamepadButtonDown(evt);
    }
}

method EventResponder::gamepadButtonUp(shared_ptr<Event> evt) -> Void {
    if (EventResponder *next = nextResponder()) {
        next->gamepadButtonUp(evt);
    }
}

method EventResponder::gamepadAxisMoved(shared_ptr<Event> evt) -> Void {
    if (EventResponder *next = nextResponder()) {
        next->gamepadAxisMoved(evt);
    }
}
