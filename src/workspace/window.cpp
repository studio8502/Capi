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
#include "graphics/screen.h"

Window::Window(Point origin, Size size, Bool hasTitlebar, Bool isDecorated):
    _x(origin.x),
    _y(origin.y),
    _width(size.width),
    _height(size.height),
    _isDecorated(isDecorated),
    _hasTitlebar(hasTitlebar),
    _isVisible(false),
    _hasCloseButton(true),
    _hasRollUpButton(true),
    _opacity(255),
    _dirty(true),
    windowSurface(nullptr),
    contentSurface(nullptr),
    drawCallback(nullptr)
{
    resize(size);
}

Window::~Window() {}

method Window::width() -> UInt64 {
    return _width;
}

method Window::height() -> UInt64 {
    return _height;
}

method Window::rect() -> Rect {
    return Rect(_x, _y, _width, _height);
}

method Window::contentRect() -> Rect {
    var rect = Rect(_x, _y, _width, _height);
    if (_isDecorated && _hasTitlebar) {
        rect.x += WINDOW_BORDER_WIDTH;
        rect.y += WINDOW_TITLEBAR_HEIGHT;
        rect.width -= WINDOW_BORDER_WIDTH * 2;
        rect.height -= WINDOW_BORDER_WIDTH + WINDOW_TITLEBAR_HEIGHT;
    } else if (_isDecorated) {
        rect.x += WINDOW_BORDER_WIDTH;
        rect.y += WINDOW_BORDER_WIDTH;
        rect.width -= WINDOW_BORDER_WIDTH * 2;
        rect.height -= WINDOW_BORDER_WIDTH * 2;
    }

    return rect;
}

method Window::resize(Size size) -> Void {
    _width = size.width;
    _height = size.height;
    windowSurface.reset();
    contentSurface.reset();
    windowSurface = make_shared<Surface>(size);
    contentSurface = make_shared<Surface>(contentRect().size());
}

method Window::setDrawCallback(WindowDrawCallback callback) -> Void {
    drawCallback = callback;
}

method Window::isVisible() -> Bool {
    return _isVisible;
}

method Window::show() -> Void {
    _isVisible = true;
}

method Window::hide() -> Void {
    _isVisible = false;
}

method Window::hasCloseButton() -> Bool {
    return _hasCloseButton;
}

method Window::setHasCloseButton(Bool closeButton) -> Void {
    _hasCloseButton = closeButton;
}

method Window::hasRollUpButton() -> Bool {
    return _hasRollUpButton;
}

method Window::setHasRollUpButton(Bool rollUpButton) -> Void {
    _hasRollUpButton = rollUpButton;
}

method Window::opacity() -> UInt8 {
    return _opacity;
}

method Window::setOpacity(UInt8 opacity) -> Void {
    _opacity = opacity;
}

method Window::acquire() -> Void {
    _lock.Acquire();
}

method Window::release() -> Void {
    _lock.Release();
}

method Window::clear(UInt8 palette, UInt8 color) -> Void {
    contentSurface->clear(palette, color);
}

method Window::drawLine(Point begin, Point end, UInt8 palette, UInt8 color, UInt8 alpha) -> Void {
    contentSurface->drawLine(begin, end, palette, color, alpha);
}

method Window::drawRect(Rect rect, Bool fill, UInt8 palette, UInt8 color, UInt8 alpha) -> Void {
    contentSurface->drawRect(rect, fill, palette, color, alpha);
}

method Window::drawCircle(Point origin, UInt32 radius, Bool fill, UInt8 palette, UInt8 color, UInt8 alpha) -> Void {
    contentSurface->drawCircle(origin, radius, fill, palette, color, alpha);
}

method Window::drawImageRect(Rect rect, Rect sourceRect, Color *pixelBuffer, UInt8 alpha) -> Void {
    contentSurface->drawImageRect(rect, sourceRect, pixelBuffer, alpha);
}

method Window::drawImageRectTransparent(Rect rect, Rect sourceRect, Color *pixelBuffer, Color transparentColor, UInt8 alpha) -> Void {
    contentSurface->drawImageRectTransparent(rect, sourceRect, pixelBuffer, transparentColor, alpha);
}

method Window::drawSurface(shared_ptr<Surface> src, Point dest, UInt8 alpha) -> Void {
    contentSurface->drawSurface(src, dest, alpha);
}

method Window::draw() -> Void{
    guard (_dirty == true) else {
        return;
    }

    drawWindowChrome();
    drawWindowContent();

    var contentOrigin = Point(WINDOW_BORDER_WIDTH,0);
    if (_isDecorated && _hasTitlebar) {
        contentOrigin.y = WINDOW_TITLEBAR_HEIGHT;
    } else if (_isDecorated) {
        contentOrigin.y = WINDOW_BORDER_WIDTH;
    } else {
        contentOrigin.x = 0;
    }
    

    windowSurface->drawSurface(contentSurface, contentOrigin);
    screen->drawSurface(windowSurface, Point(_x, _y));
}

// Draw the window chrome to the window's main surface.
method Window::drawWindowChrome() -> Void {
    if (_isDecorated == false) {
        return;
    }
    windowSurface->acquire();

    windowSurface->clear(0, 12);

    var windowBorder = Rect(0,0,_width - 1, _height - 1);

    windowSurface->drawRect(windowBorder, false, 0, 3);

    var contentBorder = Rect(0,0,0,0);

    contentBorder.x = WINDOW_BORDER_WIDTH - 1;
    
    if (_isDecorated && _hasTitlebar) {
        contentBorder.y = WINDOW_TITLEBAR_HEIGHT - 1;
    } else if (_isDecorated) {
        contentBorder.y = WINDOW_BORDER_WIDTH - 1;
    }

    contentBorder.width = _width - WINDOW_BORDER_WIDTH * 2 + 1;
    
    if (_isDecorated && _hasTitlebar) {
        contentBorder.height = _height - WINDOW_TITLEBAR_HEIGHT - WINDOW_BORDER_WIDTH + 1;
    } else if (_isDecorated) {
        contentBorder.height = _height - WINDOW_BORDER_WIDTH * 2 + 1;
    }

    windowSurface->drawRect(contentBorder, false, 0, 4);

    if (_hasTitlebar == true) {

        var lineStart = Point(WINDOW_BORDER_WIDTH - 1, WINDOW_BORDER_WIDTH - 1);
        var lineEnd = Point(_width - WINDOW_BORDER_WIDTH, WINDOW_BORDER_WIDTH -1);
        windowSurface->drawLine(lineStart, lineEnd, 0, 0);
        lineStart.y += 3;
        lineEnd.y = lineStart.y; 
        windowSurface->drawLine(lineStart, lineEnd, 0, 0);
        lineStart.y += 3;
        lineEnd.y = lineStart.y; 
        windowSurface->drawLine(lineStart, lineEnd, 0, 0);
        lineStart.y += 3;
        lineEnd.y = lineStart.y; 
        windowSurface->drawLine(lineStart, lineEnd, 0, 0);

        if (_hasCloseButton == true) {
            var closeButtonMargin = Rect(WINDOW_BORDER_WIDTH - 1, WINDOW_BORDER_WIDTH - 1, 12, 12);
            var closeButtonBorder = Rect(WINDOW_BORDER_WIDTH - 1, WINDOW_BORDER_WIDTH - 1, 9, 9);
            var closeSymbolStart1 = Point(WINDOW_BORDER_WIDTH + 2, WINDOW_BORDER_WIDTH + 2);
            var closeSymbolEnd1 = Point(WINDOW_BORDER_WIDTH + 5, WINDOW_BORDER_WIDTH + 5);

            var closeSymbolStart2 = Point(WINDOW_BORDER_WIDTH + 2, WINDOW_BORDER_WIDTH + 5);
            var closeSymbolEnd2 = Point(WINDOW_BORDER_WIDTH + 5, WINDOW_BORDER_WIDTH + 2);

            windowSurface->drawRect(closeButtonMargin, true, 0, 12);
            windowSurface->drawRect(closeButtonBorder, false, 0, 0);
            windowSurface->drawLine(closeSymbolStart1, closeSymbolEnd1, 0, 0);
            windowSurface->drawLine(closeSymbolStart2, closeSymbolEnd2, 0, 0);
        }

        if (_hasRollUpButton == true) {

        }
    } else {

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
