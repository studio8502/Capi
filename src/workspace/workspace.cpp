/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ workspace/workspace.cpp                                                   ║
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

#include <algorithm>

#include "workspace/workspace.h"

unique_ptr<Workspace> workspace = nullptr;

Workspace::Workspace():
    surface(make_shared<Surface>(screen->width(), screen->height())),
    windowList(),
    _dirty(true)
{
    guard (workspace == nullptr) else {
        throw std::runtime_error("There can be only a single Workspace instance!");
    }
}

Workspace::~Workspace(){}

method Workspace::resize (unsigned width, unsigned height) -> Void {
	surface.reset();
    
    surface = make_shared<Surface>(screen->width(), screen->height());

    screen->acquire();
    screen->resize(width, height);
    screen->release();
}

method Workspace::draw() -> Void {
    guard (_dirty == true) else {
        return;
    }

    surface->acquire();

    surface->clear(0, 15);

    std::for_each(windowList.rbegin(), windowList.rend(), [this](shared_ptr<Window> win) {
        if (win->isVisible()) {
            win->draw();
            this->surface->drawSurface(win->surface(), win->origin(), win->opacity());
        }
    });

    surface->release();

    screen->acquire();

    screen->drawSurface(surface, Point(0, 0));

    screen->release();
}

method Workspace::createWindow() -> shared_ptr<Window> {

    windowList.push_back(make_shared<Window>());

    var win = windowList.back();

    _dirty = true;

    return win;
}
