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

#include "capi.h"
#include "graphics/canvas.h"
#include "graphics/geometry.h"
#include "graphics/paragraph_style.h"
#include "graphics/image.h"

using std::shared_ptr;
using std::weak_ptr;

using Canvas = canvas_ity::canvas;
using namespace canvas_ity;

// The Surface class manages a 2D surface of arbitrary width and height,
// to which graphics and text can be drawn. Surfaces are protected with
// spinlocks -- calling code is expected to acquire the lock before
// using draw functions.
class Surface {
public:

    friend class Screen;

    enum class BrushType {
        fill = fill_style,
        stroke = stroke_style
    };

	struct TextDrawingContext {
	public:
		shared_ptr<ParagraphStyle> style; 
		Point origin;
		Surface *surface;
	};

    Surface(Size size);

    Surface(UInt32 width, UInt32 height);
    
    ~Surface();

    method reset() -> Void;

    method canvas() -> shared_ptr<Canvas>;

    method render() -> Void;

    virtual method width() -> UInt64;

    virtual method height() -> UInt64;

    virtual method opacity() -> UInt8;

    virtual method setOpacity(UInt8 newValue) -> Void;

    virtual method data() -> shared_ptr<Color[]>;

    method acquire() -> Void;

    method release() -> Void;

    // The functions below require holding the spinlock or crashes may result.

    method clear(Color color) -> Void;

    method setColor(BrushType type, Color color) -> Void;

    method setLineWidth(Int width) -> Void;

    method fill() -> Void;

    method fillRect(Rect rect) -> Void;

    method stroke() -> Void;

    method beginPath() -> Void;

    method rectangle(Int x, Int y, Int width, Int height) -> Void;

    method drawImage(shared_ptr<Image> image, Point dest) -> Void;

    method drawSurface(shared_ptr<Surface> src, Point dest, Bool alpha = false) -> Void;

    method drawText(String message, shared_ptr<ParagraphStyle> style, Point origin) -> Void;

private:
    UInt64 _width;
    UInt64 _height;
    shared_ptr<Color[]> _data;
    UInt8 _opacity; 

    shared_ptr<Canvas> _canvas;

    CSpinLock _lock;
};

using BrushType = Surface::BrushType;