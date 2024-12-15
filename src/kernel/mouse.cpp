/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ mouse.cpp                                                                 ║
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

#include "kernel/mouse.h"

#include "kernel/event.h"
#include "workspace/workspace.h"

// The maximum amount of time in milliseconds from mouse down to mouse up to
// count as a click.
#define TIME_FOR_CLICK 100

// The maxium amount of time in milliseconds from one click to a second click,
// to count as a double click.
#define TIME_FOR_DOUBLE_CLICK 250

Mouse *mouse = new Mouse();
/*
// The timestamp when the left mouse button went down.
static UInt64 leftMouseButtonDownTime;

// The timestamp when the left mouse button went up.
static UInt64 leftMouseButtonUpTime;
*/
Mouse::Mouse():
    leftButtonDown(false),
    middleButtonDown(false),
    rightButtonDown(false)
{}

Mouse::~Mouse() {}

// Update the retained mouse state, then dispatch appropriate events to the Workspace.
method Mouse::statusHandler(UInt buttons, Int deltaX, Int deltaY, Int deltaW) -> Void {
    // Start by handling mouse movement.
    if (deltaX != 0 || deltaY != 0) {
        // issue a mouse moved event.
        var event = Event::mouseMoved();
        event->deltaX = deltaX;
        event->deltaY = deltaY;
        eventQueue.push(event);
    }

    // Is the left button down when it wasn't before?
    if ((buttons & MOUSE_BUTTON_LEFT) != 0 && mouse->leftButtonDown == false) {
        mouse->leftButtonDown = true;
        var event = Event::leftMouseDown();
        eventQueue.push(event);
    }

    // Is the left button up when it wasn't before?
    if ((buttons & MOUSE_BUTTON_LEFT) == 0 && mouse->leftButtonDown == true) {
        mouse->leftButtonDown = false;
        var event = Event::leftMouseUp();
        eventQueue.push(event);
    }

    // Is the middle button down when it wasn't before?
    if ((buttons & MOUSE_BUTTON_MIDDLE) != 0 && mouse->middleButtonDown == false) {
        mouse->middleButtonDown = true;
        var event = Event::middleMouseDown();
        eventQueue.push(event);
    }

    // Is the middle button up when it wasn't before?
    if ((buttons & MOUSE_BUTTON_MIDDLE) == 0 && mouse->middleButtonDown == true) {
        mouse->middleButtonDown = false;
        var event = Event::middleMouseUp();
        eventQueue.push(event);
    }

    // Is the right button down when it wasn't before?
    if ((buttons & MOUSE_BUTTON_RIGHT) != 0 && mouse->rightButtonDown == false) {
        mouse->rightButtonDown = true;
        var event = Event::rightMouseDown();
        eventQueue.push(event);
    }

    // Is the right button up when it wasn't before?
    if ((buttons & MOUSE_BUTTON_RIGHT) == 0 && mouse->rightButtonDown == true) {
        mouse->rightButtonDown = false;
        var event = Event::rightMouseUp();
        eventQueue.push(event);
    }

    // Is the scroll delta not zero?
    if (deltaW != 0) {
        var event = Event::scrollWheel();
        event->deltaW = deltaW;
        eventQueue.push(event);
    }
}
