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
#include "graphics/font.h"

using std::shared_ptr;
using std::weak_ptr;

using Canvas = canvas_ity::canvas;



// The Surface class manages a 2D surface of arbitrary width and height,
// to which graphics and text can be drawn. Surfaces are protected with
// spinlocks -- calling code is expected to acquire the lock before
// using draw functions.
class Surface {
public:

    friend class Screen;

    // An enumerated type that defines the various compositing operations
    // possible.
    enum class CompositeOperation {
        sourceAtop = canvas_ity::source_atop,    // Show new over old where old is opaque.
        sourceCopy = canvas_ity::source_copy,    // Replace old with new.
        sourceIn = canvas_ity::source_in,        // Replace old with new where old was opaque.
        sourceOut = canvas_ity::source_out,      // Replace old with new where old was transparent.
        sourceOver = canvas_ity::source_over,    // Show new over old.
        destAtop = canvas_ity::destination_atop, // Show old over new where new is opaque.
        destIn = canvas_ity::destination_in,     // Clear old where new is transparent.
        destOut = canvas_ity::destination_out,   // Clear old where new is opaque.
        destOver = canvas_ity::destination_over, // Show new under old.
        exclusiveOr = canvas_ity::exclusive_or,          // Show new and old but clear where both are opaque.
        lighten = canvas_ity::lighter            // Sum the new with the old.
    };

    // An enumerated type that defines the line-cap styles available.
    enum class LineCapStyle {
        butt = canvas_ity::butt,
        square = canvas_ity::square,
        circle = canvas_ity::circle
    };

    // An enumerated type that defines the line join styles available.
    enum class LineJoinStyle {
        mitered = canvas_ity::miter,
        beveled = canvas_ity::bevel,
        rounded = canvas_ity::rounded
    };

    enum class BrushType {
        fill = canvas_ity::fill_style,
        stroke = canvas_ity::stroke_style
    };

    enum class RepetitionStyle {
        tile = canvas_ity::repeat, 
        tileX = canvas_ity::repeat_x, 
        tileY = canvas_ity::repeat_y,
        noTile = canvas_ity::no_repeat
    };

	struct TextDrawingContext {
	public:
		shared_ptr<ParagraphStyle> style; 
		Point origin;
		Surface *surface;
	};

    Surface(Size size, Point origin = Point(0, 0));

    Surface(UInt32 width, UInt32 height, Point origin = Point(0, 0));
    
    ~Surface();

    method reset() -> Void;

    method canvas() -> shared_ptr<Canvas>;

    method addSubsurface(shared_ptr<Surface> child, Point origin) -> Void;

    method render() -> Void;

    method origin() -> Point;

    method setOrigin(Point origin) -> Void;

    virtual method width() -> UInt64;

    virtual method height() -> UInt64;

    virtual method opacity() -> UInt8;

    virtual method setOpacity(UInt8 newValue) -> Void;

    virtual method data() -> shared_ptr<Color[]>;

    method acquire() -> Void;

    method release() -> Void;

    // The functions below require holding the spinlock or crashes may result.

    // Push the state of the canvas to an internal stack;
    method saveState() -> Void;

    // Pop the most recently saved state from the stack.
    method restoreState() -> Void;

    // Reset the transform to the default state.
    method resetTransform() -> Void;

    // Scale the current transform.
    //
    // Arguments:
    //      x: Horizontal scale factor
    //      y: Vertical scale factor
    method scaleTransform(Float x, Float y) -> Void;

    // Rotate the current transform.
    //
    // Arguments:
    //      angle: Rotation angle in radians
    method rotateTransform(Float angle) -> Void;

    // Translate the current transform.
    //
    // Arguments:
    //      x: Distance to move horizontally
    //      y: Distance to move vertically
    method translateTransform(Float x, Float y) -> Void;

    // Append an arbitrary transform to the current one.
    //
    // Arguments:
    //      transform: Structure representing the transform.
    method appendTransform(AffineTransform &transform);

    // Replace the current transform entirely with a new one.
    //
    // Arguments:
    //      transform: Structure representing the transform.
    method replaceTransform(AffineTransform &transform);

    // Set the global compositing operation to be applied.
    method setCompositeOperation(CompositeOperation op) -> Void;

    method clear(Color color) -> Void;

    method setFillColor(Color color) -> Void;

    method setStrokeColor(Color color) -> Void;

    method setStrokeLinearGradient(Float startX, Float startY, Float endX, Float endY) -> Void;

    method setFillLinearGradient(Float startX, Float startY, Float endX, Float endY) -> Void;

    method setStrokeRadialGradient(Float startX, Float startY, Float startRadius, Float endX, Float endY, Float endRadius) -> Void;

    method setFillRadialGradient(Float startX, Float startY, Float startRadius, Float endX, Float endY, Float endRadius) -> Void;

    method addStrokeColorStop(Float offset, Color color) -> Void;

    method addFillColorStop(Float offset, Color color) -> Void;

    method setStrokeImagePattern(shared_ptr<Image> image, RepetitionStyle rep) -> Void;

    method setFillImagePattern(shared_ptr<Image> image, RepetitionStyle rep) -> Void;
        
    method setShadowColor(Color color) -> Void;

    method setShadowHorizontalOffset(Float offset) -> Void;

    method setShadowVerticallOffset(Float offset) -> Void;

    method setShadowBlur(Float blur) -> Void;

    method setLineWidth(Int width) -> Void;

    method setLineCapStyle(LineCapStyle style) -> Void;

    method setLineJoinStyle(LineJoinStyle style) -> Void;

    method setMiterLimit(Float limit) -> Void;

    method setLineDashOffset(Float offset) -> Void;

    method setLineDashPattern(Float const *pattern, Int count) -> Void;

    method fill() -> Void;

    method fillRect(Rect rect) -> Void;

    method stroke() -> Void;

    method beginPath() -> Void;

    method moveTo(Float x, Float y) -> Void;

    method lineTo(Float x, Float y) -> Void;

    method rectangle(Rect rect) -> Void;

    method drawImage(shared_ptr<Image> image, Point dest) -> Void;

    method drawSurface(shared_ptr<Surface> src, Point dest, Bool alpha = false) -> Void;

    method setFont(shared_ptr<Font> font, Double size) -> Void;

    method measureText(String message) -> Float;

    method fillText(String message, Point origin) -> Void;

private:

    method setColor(BrushType type, Color color) -> Void;
    
    UInt64 _width;
    UInt64 _height;
    shared_ptr<Color[]> _data;
    UInt8 _opacity; 

    shared_ptr<Canvas> _canvas;

    Point _origin;

    std::vector<shared_ptr<Surface>> subsurfaces;

    CSpinLock _lock;
};

using BrushType = Surface::BrushType;