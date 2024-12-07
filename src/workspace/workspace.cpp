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
#include "event.h"

unique_ptr<Workspace> workspace = nullptr;

Workspace::Workspace():
    dragContext(false, Point(0,0), nullptr),
    windowList(),
    _dirty(true),
    _screenFlag(true),
    wallpaper(Image::imageSurfaceFromFile("SD:/wallpaper.jpg")),
    mouseCursor(Image::imageSurfaceFromFile("SD:/cursor_arrow.png")),
    menubar(make_shared<Surface>(screen->width(), MENUBAR_HEIGHT)),
    surface1(make_shared<Surface>(screen->width(), screen->height())),
    surface2(make_shared<Surface>(screen->width(), screen->height())),
    _surfaceFlipped(false),
    leftButtonDown(false),
    rightButtonDown(false),
    middleButtonDown(false),
    ups(0.0),
    upsCounter(0.0),
    fps(0.0),
    fpsCounter(0.0)
{
    
    try {
        guard (workspace == nullptr) else {
            throw std::runtime_error("There can be only a single Workspace instance!");
        }

        guard (wallpaper != nullptr) else {
            throw std::runtime_error("Failed to allocate surface for wallpaper!");
        }

        guard(surface1 != nullptr) else {
            throw(std::runtime_error("Failed to allocate surface for workspace!"));
        }

        guard(surface2 != nullptr) else {
            throw(std::runtime_error("Failed to allocate surface for workspace!"));
        }

        guard(mouseCursor != nullptr) else {
            throw(std::runtime_error("Failed to allocate surface for mouse cursor!"));
        }

        guard(menubar != nullptr) else {
            throw(std::runtime_error("Failed to allocate surface for menubar!"));
        }

    } catch (const std::runtime_error& err) {
        CLogger::Get()->Write("Image", LogNotice, err.what());
    }

    Font::init();
}

Workspace::~Workspace(){}

method Workspace::setDirtyFlag() -> Void {
    _dirty = true;
}

method Workspace::frontSurface() -> shared_ptr<Surface> {
    return _surfaceFlipped ? surface2 : surface1;
}

method Workspace::backSurface() -> shared_ptr<Surface> {
    return _surfaceFlipped ? surface1 : surface2;
}

method Workspace::resize(unsigned width, unsigned height) -> Void {
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

static char msg[256];
static char msg2[256];
static char msg3[256];

method Workspace::update() -> Void {
    sprintf(msg, "%.2f frames/sec", kernel->fps);
    sprintf(msg2, "%.2f updates/sec", ups);
    sprintf(msg3, "%.2f draws/sec", fps);

    // Consume queued events.
    while (eventQueue.empty() == false) {
        var event = eventQueue.front();
        eventQueue.pop();

        switch (event->type) {
        case Event::Type::mouseMoved:
            mouseX += ceil(event->deltaX);
            mouseY += ceil(event->deltaY);
            mouseX = std::min(mouseX, screen->width() - 1);
            mouseY = std::min(mouseY, screen->height() - 1);
            event->position = Point(mouseX, mouseY);

            if (dragContext.active == true) {
                updateDragContext(event->position);
            }
            
            _dirty = true;

            break;

        case Event::Type::leftMouseDown:
            leftButtonDown = true;
            event->position = Point(mouseX, mouseY);
            dispatchEvent(event);
            
            _dirty = true;
            break;

        case Event::Type::leftMouseUp:
            leftButtonDown = false;
            event->position = Point(mouseX, mouseY);
            dispatchEvent(event);
            
            _dirty = true;
            break;

        case Event::Type::middleMouseDown:
            middleButtonDown = true;
            event->position = Point(mouseX, mouseY);
            dispatchEvent(event);
            
            _dirty = true;
            break;

        case Event::Type::middleMouseUp:
            middleButtonDown = false;
            event->position = Point(mouseX, mouseY);
            dispatchEvent(event);
            
            _dirty = true;
            break;

        case Event::Type::rightMouseDown:
            rightButtonDown = true;
            event->position = Point(mouseX, mouseY);
            dispatchEvent(event);
            
            _dirty = true;
            break;

        case Event::Type::rightMouseUp:
            rightButtonDown = false;
            event->position = Point(mouseX, mouseY);
            dispatchEvent(event);
            
            _dirty = true;
            break;

        case Event::Type::scrollWheel:
            dispatchEvent(event);
            
            _dirty = true;
            break;

        default:
            break;
        }
    }

    upsCounter += 1.0;
}

method Workspace::draw() -> Void {
    guard (_dirty == true) else {
        goto done;
    }

    backSurface()->drawSurface(wallpaper, Point(0,0));

    std::for_each(windowList.rbegin(), windowList.rend(), [this](shared_ptr<Window> win) {
        if (win->isVisible()) {
            win->draw();
            backSurface()->drawSurface(win->surface(), win->origin());
        }
    });

    menubar->clear(0xFFCCCCCC);
    
    menubar->setFont(Font::DefaultUIFont(), 16.0);
    menubar->setFillColor(0xFF000000);
    menubar->fillText(msg, Point(3,15));
    menubar->fillText(msg2, Point(150,15));
    menubar->fillText(msg3, Point(350,15));
    menubar->fillText(VersionString(), Point(650, 15));
    
    if (leftButtonDown == true) {
        menubar->fillText("L", Point(920,15));
    }
    
    if (middleButtonDown == true) {
        menubar->fillText("M", Point(930,15));
    }
    
    if (rightButtonDown == true) {
        menubar->fillText("R", Point(945,15));
    }

    menubar->render();

    backSurface()->drawSurface(menubar, Point(0, 0));

    backSurface()->drawSurface(mouseCursor, Point(mouseX - 1, mouseY - 1), true);

    _dirty = false;
    _surfaceFlipped = !_surfaceFlipped;
done:
    fpsCounter += 1.0;
}

method Workspace::createWindow() -> shared_ptr<Window> {

    windowList.insert(windowList.begin(), make_shared<Window>());

    var win = windowList.front();

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

method Workspace::dispatchEvent(shared_ptr<Event> event) -> Bool {
    // Compare event->mousePosition for each window's rect, starting at the top.

    for (var win : windowList) {
        if (win->isVisible() && win->rect().checkPoint(event->position)) {
            win->handleEvent(event, win);
            return true;
        }
    }

    return false;
}
method Workspace::setDragContextForWindow(Window *window, Point dragOrigin) -> Void {
    dragContext.active = true;
    dragContext.window = window;
    dragContext.previousLocation = dragOrigin;
}

method Workspace::updateDragContext(Point newLocation) -> Void {
    guard (dragContext.window != nullptr) else {
        return;
    }
    Int deltaX = dragContext.previousLocation.x - newLocation.x;
    Int deltaY = dragContext.previousLocation.y - newLocation.y;
    dragContext.previousLocation = newLocation;
    var newWindowOrigin = Point(dragContext.window->_x + -deltaX, dragContext.window->_y + -deltaY);
    dragContext.window->move(newWindowOrigin);
}

method Workspace::clearDragContext() -> Void {
    dragContext.active = false;
    dragContext.window = nullptr;
}