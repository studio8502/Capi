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

static char msg[256];

Workspace::Workspace():
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
    fpsCounter(0.0),
    _nextResponder()
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
        CLogger::Get()->Write("Workspace", LogNotice, err.what());
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

method Workspace::update() -> Void {
    var freeMem = ((CMemorySystem::Get()->GetHeapFreeSpace(HEAP_ANY) * 1.0) / 1024.0 / 1024.0);
    var totalMem = (CMemorySystem::Get()->GetMemSize() * 1.0) / 1024.0 / 1024.0;
    sprintf(msg, "%.2f frames/sec, %.2f kupdates/sec, %.2f kdraws/sec, Mem: %.2fMB/%.2fMB (%.2fMB used)   %s", 
            kernel->fps, 
            ups / 1024.0, 
            fps / 1024.0,
            freeMem, totalMem, totalMem - freeMem,
            VersionString());

    // Consume queued events.
    dispatchEvents();

    upsCounter += 1.0;
}

method Workspace::draw() -> Void {
    guard (_dirty == true) else {   
        fpsCounter += 1.0;
        return;
    }

    var surface = backSurface();

    surface->drawSurface(wallpaper, Point(0,0));

    std::for_each(windowList.rbegin(), windowList.rend(), [this, surface](Window *win) {
        if (win->isVisible()) {
            win->draw();
            surface->drawSurface(win->surface(), win->origin());
        }
    });

    menubar->clear(0xFFCCCCCC);
    var menubarTextYPos = 13;
    menubar->setFont(Font::DefaultUIFont(), 12.0);
    menubar->setFillColor(0xFF000000);
    menubar->fillText(msg, Point(3, menubarTextYPos));
    
    if (leftButtonDown == true) {
        menubar->fillText("L", Point(920, menubarTextYPos));
    }
    
    if (middleButtonDown == true) {
        menubar->fillText("M", Point(930, menubarTextYPos));
    }
    
    if (rightButtonDown == true) {
        menubar->fillText("R", Point(945, menubarTextYPos));
    }

    menubar->render();

    surface->drawSurface(menubar, Point(0, 0));

    surface->drawSurface(mouseCursor, Point(mouseX - 1, mouseY - 1), true);

    _dirty = false;
    _surfaceFlipped = !_surfaceFlipped;

    fpsCounter += 1.0;
}

method Workspace::dispatchEvents() -> Bool {
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
            
            setDirtyFlag();

            break;

        case Event::Type::leftMouseDown:
            leftButtonDown = true;
            event->position = Point(mouseX, mouseY);
            
            for (var window : windowList) {
                if (window->isVisible() && window->rect().checkPoint(event->position)) {
                    event->setWindow(window);
                    window->mouseDown(event);
                    break;
                }
            }

            setDirtyFlag();

            break;

        case Event::Type::leftMouseUp:
            leftButtonDown = false;
            event->position = Point(mouseX, mouseY);
            
            for (var window : windowList) {
                if (window->isVisible() && window->rect().checkPoint(event->position)) {
                    event->setWindow(window);
                    window->mouseUp(event);
                    break;
                }
            }
            
            setDirtyFlag();
            break;
        default:
            break;
        }
    }

    return false;
}