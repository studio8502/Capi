// workspace/event.h
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

class Event {
public:

    enum class Type {
        mouse,
        key,
        gamepad;
    };

    Type type;

    Event(Type type);
    
    ~Event();

};

class MouseEvent: public Event {
public:
    
    enum class Subtype {
        mouseMoved,
        mouseButtonDown,
        mouseButtonUp,
        mouseButtonClicked,
        mouseButtonDoubleClicked,
        mouseScrolled
    };

    Subtype subtype;
}

class KeyEvent: public Event {
public:
    enum class Subtype {
        keyUp,
        keyDown
    };

    UInt8 scancode;
    Bool ctrl;
    Bool alt;
    Bool shift;
    Bool super;
}

class GamepadEvent: public Event {
public:
    UInt8 pad;
    Bool Up;
    Bool Down;
    Bool Left;
    Bool Right;
    Bool A;
    Bool B;
    Bool X;
    Bool Y;
    Bool L;
    Bool R;
    Bool Select;
    Bool Start
}