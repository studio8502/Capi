/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ workspace/window.cpp                                                      ║
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

#include "workspace/window.h"
#include "workspace/workspace.h"

String Window::defaultTitle = "Default Title";

Window::Window():
    _title("Default Title"),
    _x(100),
    _y(100),
    _width(400),
    _height(300),
    _isDecorated(true),
    _hasTitlebar(true),
    _isVisible(false),
    _hasCloseButton(true),
    _hasRollUpButton(true),
    _hasIconifyButton(false),
    _isResizable(true),
    _opacity(255),
    _dirty(true),
    isBeingDragged(false),
    _isActive(false),
    windowSurface(nullptr),
    contentSurface(nullptr),
    drawCallback(nullptr)
{
    resize(Size(_width, _height));
}

Window::~Window() {}

method Window::surface() -> shared_ptr<Surface> {
    return windowSurface;
}

method Window::title() -> String {
    return _title;
}

method Window::setTitle(String title) -> Void {
    _title = title;
    _dirty = true;
}

method Window::isDecorated() -> Bool {
    return _isDecorated;
}

method Window::setIsDecorated(Bool decorated) -> Void {
    _isDecorated = decorated;
    _dirty = true;
    workspace->setDirtyFlag();
}

method Window::hasTitlebar() -> Bool {
    return _hasTitlebar;
}

method Window::setHasTitlebar(Bool hasTitlebar) -> Void {
    _hasTitlebar = hasTitlebar;
}

method Window::hasIconifyButton() -> Bool {
    return _hasIconifyButton;
}

method Window::setHasIconifyButton(Bool hasIconifyButton) -> Void {
    _hasIconifyButton = hasIconifyButton;
    _dirty = true;
    workspace->setDirtyFlag();
}

method Window::isResisable() -> Bool {
    return _isResizable;
}

method Window::setIsResizable(Bool resizable) -> Void {
    _isResizable = resizable;
}

method Window::width() -> UInt64 {
    return _width;
}

method Window::height() -> UInt64 {
    return _height;
}

method Window::origin() -> Point {
    return Point(_x, _y);
}

method Window::rect() -> Rect {
    return Rect(_x, _y, _width, _height);
}

method Window::titlebarRect() -> Rect {
    return Rect(_x, _y, _width, WINDOW_TITLEBAR_HEIGHT);
}

method Window::contentRect() -> Rect {
    var rect = Rect(0, 0, 0, 0);
    if (_isDecorated && _hasTitlebar) {
        rect.x = WINDOW_BORDER_WIDTH;
        rect.y = WINDOW_TITLEBAR_HEIGHT;
        rect.width = _width - WINDOW_BORDER_WIDTH * 2;
        rect.height = _height - WINDOW_BORDER_WIDTH - WINDOW_TITLEBAR_HEIGHT;
    } else if (_isDecorated) {
        rect.x = WINDOW_BORDER_WIDTH;
        rect.y = WINDOW_BORDER_WIDTH - 1;
        rect.width = _width - WINDOW_BORDER_WIDTH * 2;
        rect.height = _height - WINDOW_BORDER_WIDTH * 2 + 1;
    } else {
        rect.x = 0;
        rect.y = 0;
        rect.width = _width;
        rect.height = _height;
    }

    return rect;
}

method Window::move(Point point) -> Void {
    _x = point.x;
    _y = point.y;
    workspace->setDirtyFlag();
}

method Window::resize(Size size) -> Void {
    _width = size.width;
    _height = size.height;
    windowSurface.reset();
    contentSurface.reset();
    windowSurface = make_shared<Surface>(size);
    contentSurface = make_shared<Surface>(contentRect().size());
    _dirty = true;
    workspace->setDirtyFlag();
}

method Window::setDrawCallback(WindowDrawCallback callback) -> Void {
    drawCallback = callback;
    _dirty = true;
    workspace->setDirtyFlag();
}

method Window::isVisible() -> Bool {
    return _isVisible;
}

method Window::show() -> Void {
    _isVisible = true;
    _dirty = true;
    workspace->setDirtyFlag();
}

method Window::hide() -> Void {
    _isVisible = false;
    workspace->setDirtyFlag();
}

method Window::hasCloseButton() -> Bool {
    return _hasCloseButton;
}

method Window::setHasCloseButton(Bool closeButton) -> Void {
    _hasCloseButton = closeButton;
    _dirty = true;
    workspace->setDirtyFlag();
}

method Window::hasRollUpButton() -> Bool {
    return _hasRollUpButton;
}

method Window::setHasRollUpButton(Bool rollUpButton) -> Void {
    _hasRollUpButton = rollUpButton;
    _dirty = true;
    workspace->setDirtyFlag();
}

method Window::opacity() -> UInt8 {
    return _opacity;
}

method Window::setOpacity(UInt8 opacity) -> Void {
    _opacity = opacity;
    _dirty = true;
    workspace->setDirtyFlag();
}

method Window::acquire() -> Void {
    _lock.Acquire();
}

method Window::release() -> Void {
    _lock.Release();
}

method Window::drawText(String message, Point origin) -> Void {
    contentSurface->fillText(message, origin);
    _dirty = true;
    workspace->setDirtyFlag();
}

method Window::drawSurface(shared_ptr<Surface> src, Point dest) -> Void {
    contentSurface->drawSurface(src, dest);
    _dirty = true;
    workspace->setDirtyFlag();
}

method Window::contentOrigin() -> Point {
    var origin = Point(WINDOW_BORDER_WIDTH,0);
    if (_isDecorated && _hasTitlebar) {
        origin.y = WINDOW_TITLEBAR_HEIGHT;
    } else if (_isDecorated) {
        origin.y = WINDOW_BORDER_WIDTH;
    } else {
        origin.x = 0;
    }
    return origin;
}

method Window::draw() -> Void{
    guard (_dirty == true) else {
        return;
    }

    drawWindowContent();
    windowSurface->drawSurface(contentSurface, contentOrigin());
    drawWindowChrome();

    _dirty = false;
}

// Draw the window chrome to the window's main surface.
method Window::drawWindowChrome() -> Void {

    windowSurface->acquire();

    windowSurface->setFillColor(0xFFCCCCCC);
    if (_isActive) {
        windowSurface->setStrokeColor(0xFF333333);
    } else {
        windowSurface->setStrokeColor(0xFF666666);
    }
    windowSurface->setLineWidth(1);
    windowSurface->beginPath();

    windowSurface->rectangle(Rect(0, 0, _width - 1, _height - 1));
    
    // Content border
    if (_isDecorated) {
        var rect = contentRect();
        windowSurface->rectangle(Rect(rect.x - 1, rect.y, rect.width + 1, rect.height));
    }

    // Close button
    if (_isActive && _hasTitlebar && _hasCloseButton) {
        windowSurface->rectangle(Rect(WINDOW_BORDER_WIDTH - 1, WINDOW_BORDER_WIDTH - 1, 10, 10));
    }

    // Roll Up button
    if (_isActive && _hasTitlebar) {
        var rect = Rect(_width - WINDOW_BORDER_WIDTH - 10, WINDOW_BORDER_WIDTH - 1, 10, 10);
        windowSurface->rectangle(rect);
        windowSurface->moveTo(rect.x, rect.y + 3);
        windowSurface->lineTo(rect.x + rect.width, rect.y + 3);
        windowSurface->moveTo(rect.x, rect.y + 6);
        windowSurface->lineTo(rect.x + rect.width, rect.y + 6);
    }

    // Iconify button
    if (_isActive && _hasTitlebar && _hasIconifyButton) {
        var rect = Rect(_width - WINDOW_BORDER_WIDTH - 23, WINDOW_BORDER_WIDTH - 1, 10, 10);
        windowSurface->rectangle(rect);
        windowSurface->moveTo(rect.x, rect.y + 6);
        windowSurface->lineTo(rect.x + 5, rect.y + 6);
        windowSurface->lineTo(rect.x + 5, rect.y);
    }

    windowSurface->fill();
    windowSurface->stroke();

    // Titlebar text and texture lines
    if (_isActive && _hasTitlebar) {
        windowSurface->beginPath();

        var textureLineStartX = 0;
        textureLineStartX += _hasCloseButton ? WINDOW_BORDER_WIDTH + 12 : WINDOW_BORDER_WIDTH;

        var textureLineEndX = _width - WINDOW_BORDER_WIDTH - 13;
        textureLineEndX -= _hasIconifyButton ?  13 : 0;

        windowSurface->moveTo(textureLineStartX, 3);
        windowSurface->lineTo(textureLineEndX, 3);

        windowSurface->moveTo(textureLineStartX, 5);
        windowSurface->lineTo(textureLineEndX, 5);

        windowSurface->moveTo(textureLineStartX, 7);
        windowSurface->lineTo(textureLineEndX, 7);

        windowSurface->moveTo(textureLineStartX, 9);
        windowSurface->lineTo(textureLineEndX, 9);

        windowSurface->moveTo(textureLineStartX, 11);
        windowSurface->lineTo(textureLineEndX, 11);

        windowSurface->moveTo(textureLineStartX, 13);
        windowSurface->lineTo(textureLineEndX, 13);

        windowSurface->setStrokeColor(0xFF444444);
        windowSurface->stroke();

        windowSurface->setFont(Font::DefaultWindowTitleFont(), 13.0);

        var titleWidth = windowSurface->measureText(_title);
        var centerX = _width / 2;
        var titleX = centerX - titleWidth / 2;
        windowSurface->setFillColor(0xFFCCCCCC);
        windowSurface->fillRect(Rect(titleX - 5, 1, titleWidth + 10, WINDOW_TITLEBAR_HEIGHT - 2));
        windowSurface->setFillColor(0xFF000000);
        windowSurface->fillText(_title, Point(titleX, WINDOW_TITLEBAR_HEIGHT - 4));
    } else if (_hasTitlebar) {
        windowSurface->setFont(Font::DefaultWindowTitleFont(), 13.0);

        var titleWidth = windowSurface->measureText(_title);
        var centerX = _width / 2;
        var titleX = centerX - titleWidth / 2;
        windowSurface->setFillColor(0xFFCCCCCC);
        windowSurface->fillRect(Rect(titleX - 5, 1, titleWidth + 10, WINDOW_TITLEBAR_HEIGHT - 2));
        windowSurface->setFillColor(0xFF888888);
        windowSurface->fillText(_title, Point(titleX, WINDOW_TITLEBAR_HEIGHT - 4));
    }

    windowSurface->render();
    windowSurface->release();

}

// Draw the window content to the window's content surface.
method Window::drawWindowContent() -> Void {
    contentSurface->acquire();
    if (drawCallback != nullptr) {
        drawCallback(this);
    }
    contentSurface->release();
}

method Window::becomeActive() -> Void {
    _isActive = true;

    _dirty = true;
}

method Window::resignActive() -> Void {
    _isActive = false;

    _dirty = true;
}

/*
method Window::handleEvent(shared_ptr<Event> event, shared_ptr<Window>sharedThis) -> Void {

    switch (event->type) {
    case Event::Type::mouseMoved:
        break;
    case Event::Type::leftMouseDown:
        workspace->moveWindowToFront(sharedThis);
        if (titlebarRect().checkPoint(event->position)) {
            workspace->setDragContextForWindow(this, event->position);
        }
        break;
    case Event::Type::leftMouseUp:
        workspace->clearDragContext();
        break;
    default:
        break;
    }
}
*/

method Window::mouseDown(shared_ptr<Event> event) -> Void {
    if (_isActive == false) {
        workspace->moveWindowToFront(event->window());
    }
    if (titlebarRect().checkPoint(event->position)) {
        workspace->setDragContextForWindow(this, event->position);
    }
    workspace->setDirtyFlag();              
}

method Window::mouseUp(shared_ptr<Event> event) -> Void {
    workspace->clearDragContext();
}