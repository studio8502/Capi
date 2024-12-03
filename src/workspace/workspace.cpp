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

#include "workspace/workspace.h"
#include "kernel.h"

unique_ptr<Workspace> workspace = nullptr;

Workspace::Workspace():
    buffer(nullptr),
    windowList(),
    _dirty(true),
    mouseCursor(make_shared<Surface>(8, 16)),
    menubar(make_shared<Surface>(screen->width(), MENUBAR_HEIGHT))
{
    guard (workspace == nullptr) else {
        throw std::runtime_error("There can be only a single Workspace instance!");
    }

    guard(mouseCursor != nullptr) else {
        throw(std::runtime_error("Failed to allocate surface for mouse cursor!"));
    }

    guard(menubar != nullptr) else {
        throw(std::runtime_error("Failed to allocate surface for menubar!"));
    }

    mouseCursor->clear(0);
}

Workspace::~Workspace(){}

method Workspace::setDirtyFlag() -> Void {
    _dirty = true;
}

method Workspace::resize (unsigned width, unsigned height) -> Void {
    var mouse = dynamic_cast<CMouseDevice *>(CDeviceNameService::Get()->GetDevice("mouse1", FALSE));

    if (mouse != nullptr) {
	    mouse->Release();
    }

    screen->acquire();
    screen->resize(width, height);
    screen->release();

    if (mouse != nullptr) {
        mouse->Setup(width, height);
        mouse->SetCursor(width/2, height/2);
        mouse->ShowCursor(false);
    }
}

char msg[256];

method Workspace::update(Int64 delta) -> Void {
    sprintf(msg, "%.2ffps", kernel->fps);
}

method Workspace::draw() -> Void {
    guard (_dirty == true) else {
    //   return;
    }

    screen->acquire();

    screen->clear();

    std::for_each(windowList.rbegin(), windowList.rend(), [this](shared_ptr<Window> win) {
        if (win->isVisible()) {
            win->draw();
            screen->drawSurface(win->surface(), win->origin());
        }
    });

    menubar->clear(SystemPalette[0][12]);

    menubar->drawText(msg, ParagraphStyle::DefaultStyle(), Point(3,3));
    
    screen->drawSurface(menubar, Point(0, 0));
    
    screen->drawSurface(mouseCursor, kernel->mousePosition);

    screen->release();

    _dirty = false;
}

method Workspace::createWindow() -> shared_ptr<Window> {

    windowList.push_back(make_shared<Window>());

    var win = windowList.back();

    _dirty = true;

    return win;
}

method Workspace::discardWindow(shared_ptr<Window> win) -> Void {
    std::erase(windowList, win);

    _dirty = true;
}

method Workspace::moveWindowToFront(shared_ptr<Window> win) -> Void {
    std::erase(windowList, win);
    windowList.insert(windowList.begin(), win);

    _dirty = true;
}

method Workspace::moveWindowToBack(shared_ptr<Window> win) -> Void {
    std::erase(windowList, win);
    windowList.push_back(win);

    _dirty = true;
}