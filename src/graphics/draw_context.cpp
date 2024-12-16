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

DrawContext::DrawContext(UInt16 x, UInt16 y, UInt16 width, UInt16 height, Color *target):
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

    if (target == nullptr) {
        this->target = screen->buffer();
    } else {
        this->target = target;
    }
}

DrawContext::DrawContext(Rect clip, Color *target):
    DrawContext(clip.x, clip.y, clip.width, clip.height, target)
{}

DrawContext::~DrawContext(){}

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
    context->target = target;

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

    delete context;
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

        context->target[offset] = context->color;
		
        x += 1;
	}
}

static func char_callback(Int16 x0, Int16 y0, mf_char character, UnsafeMutablePointer state) -> UInt8 {
    var context = (DrawContext::TextDrawingContext *) state;

    // This is where the character stream gets interpreted.

    return mf_render_character(context->font.data, x0, y0, character, pixel_callback, state);
}

method DrawContext::drawPixmap(Pixmap *src, Point dest) -> Void {
    drawPixmap(src, Rect(0, 0, src->width, src->height), dest);
}

method DrawContext::drawPixmap(Pixmap *src, Rect srcRect, Point dest) -> Void {

    for (Int row = 0; row < srcRect.height; row += 1) {
        var targetY = y + dest.y + row;

        if (targetY <= clip.top) {
            continue;
        } else if (targetY >= clip.bottom) {
            return;
        }

        for (Int col = 0; col < srcRect.width; col += 1) {
            var targetX = x + dest.x + col;

            if (targetX <= clip.left || targetX >= clip.right) {
                continue;
            }

            var destOffset = screen->width() * targetY + targetX;

            var sourcePixel = src->data[src->width * row + srcRect.x + col];

            if (sourcePixel != 0xFF) {
                target[destOffset] = sourcePixel;
            }

        }
    }
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
