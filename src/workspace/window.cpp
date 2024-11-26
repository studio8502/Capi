// workspace/window.cpp
//
// Copyright © 2024 Kyle K Cardoza, Studio 8502 <Kyle.Cardoza@icloud.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <memory>

#include "workspace/window.h"
#include "workspace/workspace.h"

Window::Window():
    _rect(Rect(200, 200, 400, 300)),
    _isDecorated(true),
    _hasTitlebar(true),
    _hasCloseButton(true),
    _isResizable(true),
    _title("Window Title"),
    _scrollX(0),
    _scrollY(0)
{}

Window::~Window() {}

method Window::rect() -> Rect {
    return _rect;
}

method Window::setRect(Rect rect) -> Void {
    _rect = rect;
}
    
method Window::move(Point point) -> Void {
    Rect rect = this->rect();
    rect.x = point.x;
    rect.y = point.y;
    setRect(rect);
}

method Window::isDecorated() -> Bool {
    return _isDecorated;
}

method Window::setIsDecorated(Bool decorated) -> Void {
    _isDecorated = decorated;
}

method Window::hasTitlebar() -> Bool {
    return _hasTitlebar;
}

method Window::setHasTitlebar(Bool titlebar) -> Void {
    _hasTitlebar = titlebar;
}

method Window::hasCloseButton() -> Bool {
    return _hasCloseButton;
}

method Window::setHasCloseButton(Bool closeButton) -> Void {
    _hasCloseButton = closeButton;
}

method Window::isResizable() -> Bool {
    return _isResizable;
}

method Window::setIsResisable(Bool resizable) -> Void {
    _isResizable = resizable;
}

method Window::title() -> String {
    return _title;
}

method Window::setTitle(String title) -> Void {
    _title = title;
}

method Window::scrollX() -> Int32 {
    return _scrollX;
}
    
method Window::setScrollX(Int32 scroll) -> Void {
    _scrollX = scroll;
}

method Window::scrollY() -> Int32 {
    return _scrollY;
}
    
method Window::setScrollY(Int32 scroll) -> Void {
    _scrollY = scroll;
}

method Window::contentRect() -> Rect {

    var content = Rect(0, 0, 0, 0);

    if (isDecorated() && hasTitlebar()) {
        content.x = rect().x + WINDOW_BORDER_THICKNESS;
        content.y = rect().y + WINDOW_TITLEBAR_HEIGHT;
        content.width = rect().width - WINDOW_BORDER_THICKNESS * 2;
        content.height = rect().height - WINDOW_BORDER_THICKNESS - WINDOW_TITLEBAR_HEIGHT;
    } else if (isDecorated()) {
        content.x = rect().x + WINDOW_BORDER_THICKNESS;
        content.y = rect().y + WINDOW_BORDER_THICKNESS;
        content.width = rect().width - WINDOW_BORDER_THICKNESS * 2;
        content.height = rect().height - WINDOW_BORDER_THICKNESS * 2;
    } else {
        return rect();
    }

    return content;
}

method Window::clipRect() -> Rect {

    var clip = contentRect();
    clip.x += 1;
    clip.y += 1;
    clip.width -= 2;
    clip.height -= 2;

    return clip;
}

method Window::translate(Point origin) -> Point {
    
    var result = origin;
    var clip = clipRect();
    result.x += (clip.x + -scrollX());
    result.y += (clip.y + -scrollY());

    return result;
}

method Window::translate(Rect rect) -> Rect {
    
    var result = rect;
    var clip = clipRect();
    result.x += (clip.x + -scrollX());
    result.y += (clip.y + -scrollY());

    return result;
}

method Window::clear(UInt8 palette, UInt8 color) -> Void {

    workspace->drawRect(clipRect(), clipRect(), true, palette, color);
}

method Window::drawRect(Rect rect, Bool fill, UInt8 palette, UInt8 color, UInt8 alpha) -> Void {

    workspace->drawRect(translate(rect), clipRect(), fill, palette, color, alpha);
}

method Window::drawCircle(Point origin, UInt32 radius, Bool fill, UInt8 palette, UInt8 color, UInt8 alpha) -> Void {
    workspace->drawCircle(translate(origin), radius, clipRect(), fill, palette, color, alpha);
}

method Window::drawLine(Point origin, Point end, UInt8 palette, UInt8 color, UInt8 alpha) -> Void {

	workspace->drawLine(translate(origin), translate(end), clipRect(), palette, color, alpha);
}

method Window::drawImage(Rect rect, Color *pixelBuffer, UInt8 alpha) -> Void {

	workspace->drawImage(translate(rect), clipRect(), pixelBuffer, alpha);
}

method Window::drawImageTransparent(Rect rect, Color *pixelBuffer, Color transparentColor, UInt8 alpha) -> Void {

	workspace->drawImageTransparent(translate(rect), clipRect(), pixelBuffer, transparentColor, alpha);
}

method Window::drawImageRect(Rect rect, Point sourceOrigin, Color *pixelBuffer, UInt8 alpha) -> Void {

	workspace->drawImageRect(translate(rect), sourceOrigin, clipRect(), pixelBuffer, alpha);
}
	
method Window::drawImageRectTransparent(Rect rect, Rect sourceRect, Color *pixelBuffer, Color transparentColor, UInt8 alpha) -> Void {

	workspace->drawImageRectTransparent(translate(rect), sourceRect, clipRect(), pixelBuffer, transparentColor, alpha);
}

method Window::draw() -> Void {

    workspace->drawRect(rect(), rect(), true, DefaultPalette, 0x0C);
    if (isDecorated()) {
        workspace->drawRect(rect(), rect(), false, DefaultPalette, 0);
    }
    workspace->drawRect(contentRect(), rect(), true, DefaultPalette, 14);

    if (isDecorated() && hasTitlebar()) {
        var origin = Point(rect().x + WINDOW_BORDER_THICKNESS, rect().y + WINDOW_TITLEBAR_HEIGHT);
        var end = Point(rect().x + rect().width - WINDOW_BORDER_THICKNESS, rect().y + WINDOW_TITLEBAR_HEIGHT);
        workspace->drawLine(origin, end, rect(), DefaultPalette, 0);

        origin.x = rect().x + WINDOW_BORDER_THICKNESS;
        origin.y = rect().y + 3;
        end.x = rect().x + rect().width - WINDOW_BORDER_THICKNESS;
        end.y = origin.y;
        workspace->drawLine(origin, end, rect(), DefaultPalette, 0);

        origin.y += 3;
        end.y = origin.y;
        workspace->drawLine(origin, end, rect(), DefaultPalette, 0);

        origin.y += 3;
        end.y = origin.y;
        workspace->drawLine(origin, end, rect(), DefaultPalette, 0);

        origin.y += 3;
        end.y = origin.y;
        workspace->drawLine(origin, end, rect(), DefaultPalette, 0);

        origin.y += 3;
        end.y = origin.y;
        workspace->drawLine(origin, end, rect(), DefaultPalette, 0);

        if (hasCloseButton()) {
            var buttonRect = Rect(rect().x + 8, rect().y + 2, WINDOW_TITLEBAR_HEIGHT, WINDOW_TITLEBAR_HEIGHT - 2);
            workspace->drawRect(buttonRect, rect(), true, DefaultPalette, 0x0C);
            buttonRect.x += 2;
            buttonRect.y += 1;
            buttonRect.width -= 5;
            buttonRect.height -= 4;
            workspace->drawRect(buttonRect, rect(), false, DefaultPalette, 0);
        }

        if (isResizable()) {
            origin.x = rect().x;
            origin.y = rect().y + rect().height - 12;
            end.x = origin.x + WINDOW_BORDER_THICKNESS;
            end.y = origin.y;
            workspace->drawLine(origin, end, rect(), DefaultPalette, 0);

            origin.x = rect().x + 12;
            origin.y = rect().y + rect().height - WINDOW_BORDER_THICKNESS;
            end.x = origin.x;
            end.y = origin.y + rect().height;
            workspace->drawLine(origin, end, rect(), DefaultPalette, 0);

            origin.x = rect().x + rect().width;
            origin.y = rect().y + rect().height - 12;
            end.x = origin.x - WINDOW_BORDER_THICKNESS;
            end.y = origin.y;
            workspace->drawLine(origin, end, rect(), DefaultPalette, 0);

            origin.x = rect().x + rect().width - 12;
            origin.y = rect().y + rect().height - WINDOW_BORDER_THICKNESS;
            end.x = origin.x;
            end.y = origin.y + rect().height;
            workspace->drawLine(origin, end, rect(), DefaultPalette, 0);
        }
        
        workspace->drawRect(contentRect(), rect(), false, DefaultPalette, 0);

    } else if (isDecorated()) {
        workspace->drawRect(contentRect(), rect(), false, DefaultPalette, 0);

        var origin = Point(0, 0);
        var end = Point(0, 0);
        
        if (isResizable()) {
            origin.x = rect().x;
            origin.y = rect().y + rect().height - 12;
            end.x = origin.x + WINDOW_BORDER_THICKNESS;
            end.y = origin.y;
            workspace->drawLine(origin, end, rect(), DefaultPalette, 0);

            origin.x = rect().x + 12;
            origin.y = rect().y + rect().height - WINDOW_BORDER_THICKNESS;
            end.x = origin.x;
            end.y = origin.y + rect().height;
            workspace->drawLine(origin, end, rect(), DefaultPalette, 0);

            origin.x = rect().x + rect().width;
            origin.y = rect().y + rect().height - 12;
            end.x = origin.x - WINDOW_BORDER_THICKNESS;
            end.y = origin.y;
            workspace->drawLine(origin, end, rect(), DefaultPalette, 0);

            origin.x = rect().x + rect().width - 12;
            origin.y = rect().y + rect().height - WINDOW_BORDER_THICKNESS;
            end.x = origin.x;
            end.y = origin.y + rect().height;
            workspace->drawLine(origin, end, rect(), DefaultPalette, 0);
        }
    }
}
