// workspace/view.cpp
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

#include "workspace/view.h"

method View::rect() -> Rect {
    return _rect;
}

method View::setRect(Rect rect) -> Void {
    _rect = rect;
}

method View::parent() -> std::weak_ptr<Drawable> {
    return _parent;
}

method View::setParent(std::shared_ptr<Drawable> parent) -> Void {
    _parent.reset();
    _parent = parent;
}

method View::scrollX() -> Int32 {
    return _scrollX;
}
   
method View::setScrollX(Int32 scroll) -> Void {
    _scrollX = scroll;
}

method View::scrollY() -> Int32 {
    return _scrollX;
}
   
method View::setScrollY(Int32 scroll) -> Void {
    _scrollY = scroll;
}

method View::translate(Point origin) -> Point {
    
    var result = origin;
    var clip = rect();
    result.x += (clip.x + -scrollX());
    result.y += (clip.y + -scrollY());

    return result;
}

method View::translate(Rect origin) -> Rect {
    
    var result = origin;
    var clip = rect();
    result.x += (clip.x + -scrollX());
    result.y += (clip.y + -scrollY());

    return result;
}

method View::drawRect(Rect rect, Bool fill, UInt8 palette, UInt8 color, UInt8 alpha) -> Void {

    if (var _parent = parent().lock()) {
        _parent->drawRect(translate(rect), fill, palette, color, alpha);
    }
}

method View::drawCircle(Point origin, UInt32 radius, Bool fill, UInt8 palette, UInt8 color, UInt8 alpha) -> Void {

    if (var _parent = parent().lock()) {
        _parent->drawCircle(translate(origin), radius, fill, palette, color, alpha);
    }
}

method View::drawLine(Point origin, Point end, UInt8 palette, UInt8 color, UInt8 alpha) -> Void {

    if (var _parent = parent().lock()) {
        _parent->drawLine(translate(origin), translate(end), palette, color, alpha);
    }
}

method View::drawImage(Rect rect, Color *pixelBuffer, UInt8 alpha) -> Void {

    if (var _parent = parent().lock()) {
        _parent->drawImage(translate(rect), pixelBuffer, alpha);
    }
}

method View::drawImageTransparent(Rect rect, Color *pixelBuffer, Color transparentColor, UInt8 alpha) -> Void {

    if (var _parent = parent().lock()) {
        _parent->drawImageTransparent(translate(rect), pixelBuffer, transparentColor, alpha);
    }
}

method View::drawImageRect(Rect rect, Point sourceOrigin, Color *pixelBuffer, UInt8 alpha) -> Void {

    if (var _parent = parent().lock()) {
        _parent->drawImageRect(translate(rect), sourceOrigin, pixelBuffer, alpha);
    }
}

method View::drawImageRectTransparent(Rect rect, Rect sourceRect, Color *pixelBuffer, Color transparentColor, UInt8 alpha) -> Void {

    if (var _parent = parent().lock()) {
        _parent->drawImageRectTransparent(translate(rect), sourceRect, pixelBuffer, transparentColor, alpha);
    }
}

method View::draw()-> Void {}