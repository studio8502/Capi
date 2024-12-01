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

#define MENUBAR_HEIGHT 18

class Workspace {
public:
    Workspace();

    ~Workspace();

    method resize(unsigned width, unsigned height) -> Void;

    method draw() -> Void;

    method createWindow() -> shared_ptr<Window>;

    method discardWindow(shared_ptr<Window> win) -> Void;

    method moveWindowToFront(shared_ptr<Window> win) -> Void;

    method moveWindowToBack(shared_ptr<Window> win) -> Void;

    method setDirtyFlag() -> Void;

private:
    shared_ptr<Surface> surface;

    std::vector<shared_ptr<Window>> windowList;

    bool _dirty;

    shared_ptr<Surface> mouseCursor;

    shared_ptr<Surface> menubar;
};

extern unique_ptr<Workspace> workspace;