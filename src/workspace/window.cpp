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
#include "graphics/font_notosans.h"

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
    _opacity(255),
    _dirty(true),
    isBeingDragged(false),
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
        rect.y = WINDOW_BORDER_WIDTH;
        rect.width = _width - WINDOW_BORDER_WIDTH * 2;
        rect.height = _height - WINDOW_BORDER_WIDTH * 2;
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

method Window::drawText(String message, shared_ptr<ParagraphStyle> style, Point origin) -> Void {
    contentSurface->drawText(message, style, origin);
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

    windowSurface->rectangle(0, 0, _width - 1, _height - 1);

    windowSurface->setColor(BrushType::fill, 0xFFCCCCCC);
    windowSurface->fill();

    windowSurface->setColor(BrushType::fill, 0xFF000000);
    windowSurface->setLineWidth(1);
    windowSurface->stroke();

    if (_hasTitlebar) {
        var rect = contentRect();
        windowSurface->beginPath();
        windowSurface->rectangle(rect.x, rect.y, rect.width - 1, rect.height);
        windowSurface->setColor(BrushType::fill, 0xFFFFFFFF);
        windowSurface->fill();
        windowSurface->stroke();
    }

    if (_hasTitlebar && _hasCloseButton) {
        windowSurface->beginPath();
        windowSurface->rectangle(WINDOW_BORDER_WIDTH, WINDOW_BORDER_WIDTH, 9, 9);
        windowSurface->stroke();
    }

    windowSurface->render();

    if (_hasTitlebar) {
        var titleFont = make_shared<Font::NotoSans>(Font::Size::small, Font::Weight::bold);
        var titleStyle = make_shared<ParagraphStyle>(titleFont, 0, ParagraphStyle::Align::center);
        var titleWidth = titleStyle->font()->widthForString(_title);
        if (titleWidth != 0) {
            var centerX = _width / 2;
            var titleX = centerX - titleWidth / 2;
            var titleBGRect = Rect(titleX - 6, 1, titleWidth + 12, WINDOW_TITLEBAR_HEIGHT - 2);
            windowSurface->drawText(_title, titleStyle, Point(centerX, 1));
        }
    }

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

method Window::handleEvent(shared_ptr<Event> event, shared_ptr<Window>sharedThis) -> Void {

    switch (event->type) {
    case Event::Type::mouseMoved:
        if (isBeingDragged == true) {
            _x += event->deltaX;
            _y += event->deltaY;
        }
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

/*
    switch (event->type) {
    case MouseEvent::EventType::buttonDown:
        switch (event->button) {
        case MouseEvent::MouseButton::left: {
            workspace->moveWindowToFront(sharedThis);
            workspace->clearDragContext();

            if (titlebarRect().checkPoint(event->position())) {
                workspace->setDragContextForWindow(this, event->position());
            }

            break;
        }
        case MouseEvent::MouseButton::right: {
            break;
        }
        case MouseEvent::MouseButton::middle: {
            break;
        }
        default:
            break;
        }
        break;
    case MouseEvent::EventType::buttonUp:
        switch (event->button) {
        case MouseEvent::MouseButton::left: {
            workspace->clearDragContext();
            break;
        }
        case MouseEvent::MouseButton::right: {
            break;
        }
        case MouseEvent::MouseButton::middle: {
            break;
        }
        default:
            break;
        }
        break;
    case MouseEvent::EventType::scroll:
        break;
    default:
        break;
    }
    */
}