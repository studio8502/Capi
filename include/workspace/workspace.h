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

#include <vector>

#include "capi.h"
#include "graphics/surface.h"
#include "graphics/screen.h"
#include "workspace/window.h"
#include "kernel.h"

#define MENUBAR_HEIGHT 18

class Workspace {
public:
    friend class Kernel::WorkspaceMonitor;
    friend class Screen;

    struct DragContext {
        Bool active;
        Point previousLocation;
        Window *window;
    };

    DragContext dragContext;
    
    Workspace();

    ~Workspace();

    method resize(unsigned width, unsigned height) -> Void;

    method update(Int64 delta) -> Void;

    method draw() -> Void;

    method frontSurface() -> shared_ptr<Surface>;

    method backSurface() -> shared_ptr<Surface>;

    method createWindow() -> shared_ptr<Window>;

    method discardWindow(shared_ptr<Window> win) -> Void;

    method moveWindowToFront(shared_ptr<Window> win) -> Void;

    method moveWindowToBack(shared_ptr<Window> win) -> Void;

    method setDirtyFlag() -> Void;

    method dispatchEvent(shared_ptr<MouseEvent> event) -> Bool;

    method setDragContextForWindow(Window *window, Point dragOrigin) -> Void;

    method updateDragContext(Point newLocation) -> Void;

    method clearDragContext() -> Void;

private:

    std::vector<shared_ptr<Window>> windowList;

    bool _dirty;
    bool _screenFlag;

    shared_ptr<Surface> mouseCursor;

    shared_ptr<Surface> menubar;

    shared_ptr<Surface> surface1;

    shared_ptr<Surface> surface2;

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