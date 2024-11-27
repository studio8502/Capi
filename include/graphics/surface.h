/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ graphics/surface.h                                                        ║
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

#pragma once

using std::shared_ptr;
using std::weak_ptr;

// The Surface class manages a 2D surface of arbitrary width and height,
// to which graphics and text can be drawn. Surfaces are protected with
// spinlocks -- calling code is expected to acquire the lock before
// using draw functions.
class Surface {
public:

    friend class Screen;

    Surface(UInt64 width = 64, UInt64 height = 64);
    
    ~Surface();

    virtual method width() -> UInt64;

    virtual method height() -> UInt64;

    virtual method data() -> shared_ptr<Color[]>;

    method acquire() -> Void;

    method release() -> Void;

    // The functions below require holding the spinlock or crashes may result.

	virtual method clear(UInt8 palette, UInt8 color) -> Void;

    method drawLine(Point begin, Point end, UInt8 palette, UInt8 color, UInt8 alpha = 255) -> Void;

    method drawRect(Rect rect, Bool fill, UInt8 palette, UInt8 color, UInt8 alpha = 255) -> Void;

private:
    UInt64 _width;
    UInt64 _height;
    shared_ptr<Color[]> _data;

    CSpinLock _lock;
};
