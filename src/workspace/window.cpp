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
    contentView(make_unique<View>()),
    trackingRectList()
{
    resize(Size(_width, _height));
}

Window::~Window() {}

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
    resize(Size(_width, _height));
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

    if (_isDecorated && _hasTitlebar) {
        contentView->setFrame(Rect(WINDOW_BORDER_WIDTH,
                                   WINDOW_TITLEBAR_HEIGHT + 2, 
                                   size.width - WINDOW_BORDER_WIDTH * 2, 
                                   size.height - WINDOW_BORDER_WIDTH - WINDOW_TITLEBAR_HEIGHT - 3));
    } else if (_isDecorated) {
        contentView->setFrame(Rect(WINDOW_BORDER_WIDTH,
                                   WINDOW_BORDER_WIDTH, 
                                   size.width - WINDOW_BORDER_WIDTH * 2, 
                                   size.height - WINDOW_BORDER_WIDTH * 2));
    } else {
        contentView->setFrame(Rect(0, 0, size.width, size.height));
    }
    draw();
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

    contentView->draw();
    drawWindowChrome();

    _dirty = false;
}

// Draw the window chrome to the window's main surface.
method Window::drawWindowChrome() -> Void {

}

method Window::becomeActive() -> Void {
    _isActive = true;

    _dirty = true;
}

method Window::resignActive() -> Void {
    _isActive = false;

    _dirty = true;
}

method Window::mouseDown(shared_ptr<Event> event) -> Void {
    if (_isActive == false) {
        workspace->moveWindowToFront(event->window());
        event->window()->becomeActive();
    }
    if (titlebarRect().checkPoint(event->position) && _hasTitlebar) {
        workspace->setDragContextForWindow(event->window(), event->position);
    }
    workspace->setDirtyFlag();              
}

method Window::mouseUp(shared_ptr<Event> event) -> Void {
    workspace->clearDragContext();
}