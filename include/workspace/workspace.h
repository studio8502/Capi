/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ workspace/workspace.h                                                     ║
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

#include "capi.h"
#include "graphics/screen.h"
#include "workspace/window.h"
#include "kernel/kernel.h"
#include "event_responder.h"
#include "window_manager.h"

#define MENUBAR_HEIGHT 18

class Workspace: public EventResponder, public WindowManager {
public:
    friend class Kernel;
    friend class Screen;
    
    Workspace();

    ~Workspace();

    method resize(unsigned width, unsigned height) -> Void;

    method update() -> Void;

    method draw() -> Void;

    method setDirtyFlag() -> Void;

    method dispatchEvents() -> Bool;

private:

    bool _dirty;
    bool _screenFlag;

    bool _surfaceFlipped;

    UInt32 mouseX;
    UInt32 mouseY;

    Bool leftButtonDown;
    Bool rightButtonDown;
    Bool middleButtonDown;

    Double ups;
    Double upsCounter;

    Double fps;
    Double fpsCounter;
};

extern unique_ptr<Workspace> workspace;