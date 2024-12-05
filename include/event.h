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

class MouseEvent {
public:
    enum class EventType {
        buttonUp,
        buttonDown,
        buttonClicked,
        scroll,
        move
    };

    enum class MouseButton {
        left = MOUSE_BUTTON_LEFT,
        right = MOUSE_BUTTON_RIGHT,
        middle = MOUSE_BUTTON_MIDDLE
    };

    MouseEvent(EventType type, UInt32 x, UInt32 y);

    MouseEvent(EventType type, MouseButton button, UInt32 x, UInt32 y);

    ~MouseEvent();

    static method Move(UInt32 x, UInt32 y) -> shared_ptr<MouseEvent>;

    static method ButtonUp(MouseButton button, UInt32 x, UInt32 y) -> shared_ptr<MouseEvent>;

    static method ButtonDown(MouseButton button, UInt32 x, UInt32 y) -> shared_ptr<MouseEvent>;

    static method Scroll(UInt32 x, UInt32 y) -> shared_ptr<MouseEvent>;

    method position() -> Point;

    MouseEvent::EventType type;
    MouseButton button;

private:
    UInt32 _x;
    UInt32 _y;
    MouseButton _button;
};

extern std::queue<shared_ptr<MouseEvent>> mouseEventQueue;