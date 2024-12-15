/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ graphics/draw_context.cpp                                                 ║
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

#include "graphics/draw_context.h"
#include "graphics/screen.h"
#include "fonts.h"

#define TRANSPARENT 0xFF

static func pixel_callback(Int16 x, Int16 y, UInt8 count, UInt8 alpha, UnsafeMutablePointer state) -> Void;

static func char_callback(Int16 x0, Int16 y0, mf_char character, UnsafeMutablePointer state) -> UInt8;

static func line_callback(const char *line, uint16_t count, void *state) -> Bool;

DrawContext::DrawContext(UInt16 x, UInt16 y, UInt16 width, UInt16 height):
    x(x),
    y(y),
    width(width),
    height(height),
    contextLock(false),
    locked(false),
    align(Alignment::left),
    textMargin(2),
    color(0x00),
    font(Font::Helvetica(Font::Size::large))
{
    clip.top = std::max(y, (UInt16) 0);
    clip.bottom = std::min((UInt16)(y + height), (UInt16)(screen->height() - 1));
    clip.left = std::max(x, (UInt16) 0);
    clip.right = std::min((UInt16)(x + width), (UInt16)(screen->width() - 1));
}

method DrawContext::lock() -> Void {
	contextLock.Acquire();
    locked = true;
}

method DrawContext::unlock() -> Void {
    locked = false;
	contextLock.Release();
}

method DrawContext::createChildContext(UInt16 x, UInt16 y, UInt16 width, UInt16 height) -> DrawContext {
    var context = DrawContext(this->x + x, this->y + y, width, height);

    context.clip.top = std::max(context.clip.top, this->clip.top);
    context.clip.bottom = std::min(context.clip.bottom, this->clip.bottom);
    context.clip.left = std::max(context.clip.left, this->clip.left);
    context.clip.right = std::min(context.clip.right, this->clip.right);

    return context;
}

DrawContext::~DrawContext() {}

DrawContext::TextDrawingContext::TextDrawingContext():
    align(Alignment::left),
    anchorX(0),
    textY(0),
    textMargin(0),
    color(0x00),
    font(Font::Helvetica(Font::Size::medium)),
    clip({0,0,0,0})
{}

DrawContext::TextDrawingContext::~TextDrawingContext() {}

method DrawContext::drawText(String message) -> Void {

    var context = new TextDrawingContext;
    context->align = align;
    context->textY = 2;
    context->textMargin = textMargin;
    context->color = color;
    context->font = font;
    context->x = x;
    context->y = y;
    context->width = width;
    context->clip.top = clip.top;
    context->clip.bottom = clip.bottom;
    context->clip.left = clip.left;
    context->clip.right = clip.right;

    switch (align) {
    case DrawContext::Alignment::left:
    case DrawContext::Alignment::justify:
        context->anchorX = 0;
        break;
    case DrawContext::Alignment::center:
        context->anchorX = width / 2;
        break;
    case DrawContext::Alignment::right:
        context->anchorX = width;
        break;
        break;
    }

    mf_wordwrap(font.data, width, message.c_str(), line_callback, (UnsafeMutablePointer) context);

}

static func pixel_callback(Int16 x, Int16 y, UInt8 count, UInt8 alpha, UnsafeMutablePointer state) -> Void {
    var context = (DrawContext::TextDrawingContext *) state;

    if (context->color == 0xFF) {
        return;
    }
        
    for (var c = 0; c < count; c += 1) {
        var targetX = context->x + x;
        var targetY = context->y + y;

        if (targetX < context->clip.left) {
            continue;
        } else if (targetX > context->clip.right) {
            return;
        }

        if (targetY < context->clip.top) {
            continue;
        } else if (targetY > context->clip.bottom) {
            return;
        }


        var offset = screen->width() * targetY + targetX;

        screen->buffer()[offset] = context->color;
		
        x += 1;
	}
}

static func char_callback(Int16 x0, Int16 y0, mf_char character, UnsafeMutablePointer state) -> UInt8 {
    var context = (DrawContext::TextDrawingContext *) state;

    return mf_render_character(context->font.data, x0, y0, character, pixel_callback, state);
}

static func line_callback(const char *line, uint16_t count, void *state) -> Bool {
    var context = (DrawContext::TextDrawingContext *) state;

    switch (context->align) {
    case DrawContext::Alignment::left:
        mf_render_aligned(context->font.data,
            		      context->anchorX, context->textY, 
                          MF_ALIGN_LEFT, 
                          line, count, 
                          char_callback, state);
        break;
    case DrawContext::Alignment::center:
        mf_render_aligned(context->font.data,
            		      context->anchorX, context->textY, 
                          MF_ALIGN_CENTER, 
                          line, count, 
                          char_callback, state);
        break;
    case DrawContext::Alignment::right:
        mf_render_aligned(context->font.data,
            		      context->anchorX, context->textY, 
                          MF_ALIGN_RIGHT, 
                          line, count, 
                          char_callback, state);
        break;
    case DrawContext::Alignment::justify:
        mf_render_justified(context->font.data, 
            		        context->anchorX, context->textY, 
                            context->width,
                            line, count, char_callback, state);
        break;
    }

    context->textY += context->font.data->line_height;
    return true;
}

/*

struct TextDrawingContext {
public:
    shared_ptr<ParagraphStyle> style; 
    Point origin;
    Surface *surface;
};

method Surface::drawImageRect(Rect rect, Rect sourceRect, shared_ptr<Image> image, Bool replace) -> Void {
    var target = Point(0 ,0);
	var buffer = _data.get();
	var width = _width;

	for(unsigned i = 0; i < rect.height; i++)
	{
		for(unsigned j = 0; j < rect.width; j++)
		{
			Color sourcePixel = (image->data)[(sourceRect.y + i) * sourceRect.width + j + sourceRect.x];

            target.x = j + rect.x;
            target.y = rect.y + i;

            if (target.x >= _width || target.x < 0 || target.y < 0) {
                continue;
            } else if (target.y >= _height) {
                return;
            }
            
            if (replace == false) {
                buffer[(rect.y + i) * width + j + rect.x] = \
                    alpha_blend(buffer[(rect.y + i) * width + j + rect.x], sourcePixel);
            } else {
                buffer[(rect.y + i) * width + j + rect.x] = sourcePixel;
            }
		}
	}
}

method Surface::drawText(String message, shared_ptr<ParagraphStyle> style, Point origin) -> Void {

	var context = new Surface::TextDrawingContext(style, origin, this);

	mf_render_aligned(context->style->font()->data(),
            		  context->origin.x, context->origin.y, 
					  (mf_align_t) context->style->align(), 
					  message.c_str(), 0, 
					  &char_callback, (void *) context);
	
	delete context;
}

static function line_callback(mf_str line, uint16_t count, void *state) -> Bool {

    [[gnu::unused]]
	var context = (Surface::TextDrawingContext *) state;
	
	return false;
}

// Character callback
static function char_callback(int16_t x0, int16_t y0, mf_char character, void *state) -> uint8_t {

    [[gnu::unused]]
	var context = (Surface::TextDrawingContext *) state;

    return mf_render_character(context->style->font()->data(), x0, y0, character, &pixel_callback, state);
}

// Pixel callback
static function pixel_callback(int16_t x, int16_t y, uint8_t count, uint8_t alpha, void *state) -> Void {

	var context = (Surface::TextDrawingContext *) state;
    Surface *surface = context->surface;
    Color *buffer = surface->data().get();

    for (var c = 0; c < count; c += 1) {
        Color textColor = (context->style->color() & 0x00FFFFFF) | (alpha << 24);
        var offset = surface->width() * y + x;
        var target = Point(x, y);
        
        if (target.x > surface->width() || target.x < 0 || target.y < 0) {
            continue;
        } else if (target.y > surface->height()) {
            return;
        }

        buffer[offset] = alpha_blend(buffer[offset], textColor);
		
        x += 1;
	}
}
*/
