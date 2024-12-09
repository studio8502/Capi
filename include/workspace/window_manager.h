/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ workspace/window_manager.h                                                ║
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
#include "graphics/geometry.h"
#include "workspace/window.h"

class WindowManager {
public:
    struct DragContext {
        Bool active;
        Point previousLocation;
        Window *window;
    };
    
    WindowManager();

    virtual ~WindowManager();

    virtual method createWindow() -> Window *;

    virtual method discardWindow(Window *win) -> Void;

    virtual method moveWindowToFront(Window *win) -> Void;

    virtual method moveWindowToBack(Window *win) -> Void;

    virtual method setDragContextForWindow(Window *window, Point dragOrigin) -> Void;

    virtual method updateDragContext(Point newLocation) -> Void;

    virtual method clearDragContext() -> Void;

    virtual method activeWindow() -> Window *;

    DragContext dragContext;

    std::vector<Window *> windowList;
};
