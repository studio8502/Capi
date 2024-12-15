/*
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ event_responder.h                                                         ║
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
 */

#pragma once

#include "capi.h"
#include "kernel/event.h"

class Event;

// An event responder is any class which processes system events and partitipates
// in the responder chain.

class EventResponder {
public:

    EventResponder();

    virtual ~EventResponder();

    // Returns whether or not the instance is willing to accept first responder
    // status.
    virtual method acceptsFirstResponder() -> Bool;

    // Notify the instance that it is about to become the first responder in its
    // window. The default implementatin simply returns true -- subclasses can
    // override this to trigger other behaviour, and/or return false to refuse
    // first responder status.
    virtual method becomeFirstResponder() -> Bool;

    virtual method nextResponder() -> EventResponder *;

    virtual method setNextResponder(EventResponder *next) -> Void;

    virtual method mouseMoved(shared_ptr<Event> evt) -> Void;

    virtual method mouseEntered(shared_ptr<Event> evt) -> Void;

    virtual method mouseExited(shared_ptr<Event> evt) -> Void;

    virtual method mouseDown(shared_ptr<Event> evt) -> Void;

    virtual method mouseDragged(shared_ptr<Event> evt) -> Void;

    virtual method mouseUp(shared_ptr<Event> evt) -> Void;

    virtual method middleMouseDown(shared_ptr<Event> evt) -> Void;

    virtual method middleMouseDragged(shared_ptr<Event> evt) -> Void;

    virtual method middleMouseUp(shared_ptr<Event> evt) -> Void;

    virtual method rightMouseDown(shared_ptr<Event> evt) -> Void;

    virtual method rightMouseDragged(shared_ptr<Event> evt) -> Void;

    virtual method rightMouseUp(shared_ptr<Event> evt) -> Void;

    virtual method scrollWheel(shared_ptr<Event> evt) -> Void;

    virtual method keyDown(shared_ptr<Event> evt) -> Void;

    virtual method keyUp(shared_ptr<Event> evt) -> Void;

    virtual method gamepadButtonDown(shared_ptr<Event> evt) -> Void;

    virtual method gamepadButtonUp(shared_ptr<Event> evt) -> Void;

    virtual method gamepadAxisMoved(shared_ptr<Event> evt) -> Void;

private:
    EventResponder *_nextResponder;
};
