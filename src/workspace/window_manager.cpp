/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ workspace/window_manager.cpp                                              ║
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

#include "workspace/window_manager.h"
#include "workspace/workspace.h"

WindowManager::WindowManager():
    dragContext(false, Point(0,0), nullptr),
    windowList()
{}

WindowManager::~WindowManager() {}

method WindowManager::createWindow() -> shared_ptr<Window> {

    var win = make_shared<Window>();

    windowList.insert(windowList.begin(), win);

    workspace->setDirtyFlag();

    return win;
}

method WindowManager::discardWindow(shared_ptr<Window> win) -> Void {

    std::erase_if(windowList, [win](var window){
        return win.get() == window.get();
    });
    
    workspace->setDirtyFlag();
}

method WindowManager::moveWindowToFront(shared_ptr<Window> win) -> Void {

    activeWindow()->resignActive();

    std::erase_if(windowList, [win](var window){
        return win.get() == window.get();
    });

    windowList.insert(windowList.begin(), win);
    
    workspace->setDirtyFlag();
}

method WindowManager::moveWindowToBack(shared_ptr<Window> win) -> Void {
    std::erase_if(windowList, [win](var window){
        return win.get() == window.get();
    });

    windowList.push_back(win);

    workspace->setDirtyFlag();
}

method WindowManager::setDragContextForWindow(shared_ptr<Window> window, Point dragOrigin) -> Void {
    dragContext.active = true;
    dragContext.window = window;
    dragContext.previousLocation = dragOrigin;
}

method WindowManager::updateDragContext(Point newLocation) -> Void {
    guard (dragContext.window != nullptr) else {
        return;
    }
    Int deltaX = dragContext.previousLocation.x - newLocation.x;
    Int deltaY = dragContext.previousLocation.y - newLocation.y;
    dragContext.previousLocation = newLocation;
    var newWindowOrigin = Point(dragContext.window->_x + -deltaX, dragContext.window->_y + -deltaY);
    dragContext.window->move(newWindowOrigin);

    workspace->setDirtyFlag();
}

method WindowManager::clearDragContext() -> Void {
    dragContext.active = false;
    dragContext.window.reset();
}

method WindowManager::activeWindow() -> shared_ptr<Window>  {
    return windowList.front();
}