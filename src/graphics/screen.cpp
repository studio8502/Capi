//
// 2dgraphics.cpp
//
// This file:
//	Copyright (C) 2021  Stephane Damo
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2014-2023  R. Stange <rsta2@o2online.de>
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
//
#include <circle/screen.h>
#include <circle/bcmpropertytags.h>
#include <circle/util.h>

#include "graphics/screen.h"
#include "mcufont.h"
#include "fonts/fonts.h"

static auto line_callback(mf_str line, uint16_t count, void *state) -> Bool;

static auto char_callback(int16_t x0, int16_t y0, mf_char character, void *state) -> uint8_t;

static auto pixel_callback(int16_t x, int16_t y, uint8_t count, uint8_t alpha, void *state) -> Void;

Screen::Screen (UInt32 width, UInt32 height, Bool vsync, UInt8 display)
: 	width(width),
	height(height),
	display (display),
	framebuffer(nullptr),
	buffer(nullptr),
	vsync(vsync),
	bufferSwapped(TRUE)
{

}

Screen::~Screen (void)
{
    delete [] buffer;
}

method Screen::initialize (void) -> Bool {
	framebuffer = make_unique<CBcmFrameBuffer>(width, height, DEPTH, width, 2*height,
					      display, TRUE);

	if (!framebuffer || !framebuffer->Initialize ())
	{
		return FALSE;
	}

	baseBuffer = (Color *) (uintptr) framebuffer->GetBuffer();
	width = framebuffer->GetWidth();
	height = framebuffer->GetHeight();

	buffer = new Color[width * height];
	if (buffer == nullptr) {
		return false;
	}
	
	return TRUE;
}

method Screen::resize (unsigned nWidth, unsigned nHeight) -> Bool {
	framebuffer.reset();

	width = nWidth;
	height = nHeight;

	delete [] buffer;
	buffer = nullptr;
	bufferSwapped = TRUE;

	return initialize ();
}

method Screen::getWidth () const -> UInt32 {
	return width;
}

method Screen::getHeight () const -> UInt32 {
	return height;
}

method Screen::getScreenRect() -> Rect {
	return Rect(0, 0, width, height);
}

method Screen::clearScreen(UInt8 palette, UInt8 color) -> Void {
    Rect clip = getScreenRect();
	drawRect(clip, clip, true, palette, color, 255);
}

method Screen::drawRect(Rect rect, Rect clip, Bool fill, UInt8 palette, UInt8 color, UInt8 alpha) -> Void {
    if (fill == true) {
        _drawRect(rect, clip, palette, color, alpha);
    } else {
        _drawRectOutline(rect, clip, palette, color, alpha);
    }
}

method Screen::_drawRect (Rect rect, Rect clip, UInt8 palette, UInt8 color, UInt8 alpha) -> Void {
    var target = Point(0, 0);

    Color c = SystemPalette[palette][color];
	
	for(unsigned i = rect.y; i < rect.y + rect.height; i += 1) {

        target.y = i;

		for(unsigned j = rect.x; j < rect.x + rect.width; j += 1) {

            target.x = j;

            if (clip.checkPoint(target) == false) {
                continue;
            }

            var offset = i * width + j;
			
			buffer[offset] = alpha_blend(buffer[offset], c, alpha);
		}
	}
}

method Screen::_drawRectOutline (Rect rect, Rect clip, UInt8 palette, UInt8 color, UInt8 alpha) -> Void {
    var begin = Point(rect.x, rect.y);
    var end = Point(rect.x + rect.width, rect.y);
	drawLine(begin, end, clip, palette, color, alpha);

    begin = end;
    end.y += rect.height;
	drawLine(begin, end, clip, palette, color, alpha);

    begin = end;
    end.x -= rect.width;
	drawLine(begin, end, clip, palette, color, alpha);

    begin = end;
    end.y -= rect.height;
	drawLine(begin, end, clip, palette, color, alpha);
}

method Screen::drawLine(Point begin, Point end, Rect clip, UInt8 palette, UInt8 color, UInt8 alpha) -> Void {
    Color lineColor = SystemPalette[palette][color];
	
	int dx = end.x - begin.x;
	int dy = end.y - begin.y;
	int dxabs = (dx>0) ? dx : -dx;
	int dyabs = (dy>0) ? dy : -dy;
	int sgndx = (dx>0) ? 1 : -1;
	int sgndy = (dy>0) ? 1 : -1;
	int x = dyabs >> 1;
	int y = dxabs >> 1;

	buffer[width * begin.y + begin.x] = alpha_blend(buffer[width * begin.y + begin.x], lineColor, alpha);

    var target = Point(0, 0); 

	if(dxabs >= dyabs)
	{
		for(int n=0; n<dxabs; n++)
		{
			y += dyabs;
			if(y >= dxabs)
			{
				y -= dxabs;
				begin.y += sgndy;
			}
			begin.x += sgndx;
            
            target.x = begin.x;
            target.y = begin.y;
            if (clip.checkPoint(target) == false) {
                continue;
            }

			buffer[width * begin.y + begin.x] = alpha_blend(buffer[width * begin.y + begin.x], lineColor, alpha);
		}
	}
	else
	{
		for(int n=0; n<dyabs; n++)
		{
			x += dxabs;
			if(x >= dyabs)
			{
				x -= dyabs;
				begin.x += sgndx;
			}
			begin.y += sgndy;
            
            target.x = begin.x;
            target.y = begin.y;
            if (clip.checkPoint(target) == false) {
                continue;
            }

			buffer[width * begin.y + begin.x] = alpha_blend(buffer[width * begin.y + begin.x], lineColor, alpha);
		}
	}
}

method Screen::drawCircle(Point origin, UInt32 radius, Rect clip, Bool fill, UInt8 palette, UInt8 color, UInt8 alpha) -> Void {
    if (fill == true) {
        _drawCircle(origin, radius, clip, palette, color, alpha);
    } else {
        _drawCircleOutline(origin, radius, clip, palette, color, alpha);
    }
}


method Screen::_drawCircle(Point origin, UInt32 radius, Rect clip, UInt8 palette, UInt8 color, UInt8 alpha) -> Void {
    Color pixelValue = SystemPalette[palette][color];
    
    unsigned nX = origin.x;
    unsigned nY = origin.y;
	
    int r2 = radius * radius;
	unsigned area = r2 << 2;
	unsigned rr = radius << 1;

    var target = Point(0, 0);

	for (unsigned i = 0; i < area; i++)
	{
		int tx = (int) (i % rr) - radius;
		int ty = (int) (i / rr) - radius;

		if (tx * tx + ty * ty < r2)
		{   
            target.x = nX + tx;
            target.y = nY + ty;
            if (clip.checkPoint(target) == false) {
                continue;
            }

			buffer[width * (nY + ty) + nX + tx] = alpha_blend(buffer[width * (nY + ty) + nX + tx], pixelValue, alpha);
		}
	}
}

method Screen::_drawCircleOutline(Point origin, UInt32 radius, Rect clip, UInt8 palette, UInt8 color, UInt8 alpha) -> Void {

    Color pixelValue = SystemPalette[palette][color];
    
    unsigned nX = origin.x;
    unsigned nY = origin.y;

    var target = Point(radius + nX, nY);

    if (clip.checkPoint(target) == true) {
		buffer[width * target.y + target.x] = alpha_blend(buffer[width * target.y + target.x], pixelValue, alpha);
    }

	if (radius > 0) {
        target.y = -radius + nY;
        if (clip.checkPoint(target) == true) {
			buffer[width * target.y + target.x] = alpha_blend(buffer[width * target.y + target.x], pixelValue, alpha);
        }

        target.x = -radius + nX;
        target.y = nY;
        if (clip.checkPoint(target) == true) {
			buffer[width * target.y + target.x] = alpha_blend(buffer[width * target.y + target.x], pixelValue, alpha);
        }

        target.x = nX;
        target.y = radius + nY;
        if (clip.checkPoint(target) == true) {
			buffer[width * target.y + target.x] = alpha_blend(buffer[width * target.y + target.x], pixelValue, alpha);
        }
	}
      
	int p = 1 - radius;
	int y = 0;
	
	while ((int) radius > y)
	{
		y++;

		if (p <= 0)
		{
			p = p + 2 * y + 1;
		}
		else
		{
			radius--;
			p = p + 2 * y - 2 * radius + 1;
		}

		if ((int) radius < y)
		{
			break;
		}

        target.x = radius + nX;
        target.y = y + nY;
        if (clip.checkPoint(target) == true) {
			buffer[width * target.y + target.x] = alpha_blend(buffer[width * target.y + target.x], pixelValue, alpha);
        }

        target.x = -radius + nX;
        if (clip.checkPoint(target) == true) {
			buffer[width * target.y + target.x] = alpha_blend(buffer[width * target.y + target.x], pixelValue, alpha);
        }

        target.x = radius + nX;
        target.y = -y + nY;
        if (clip.checkPoint(target) == true) {
			buffer[width * target.y + target.x] = alpha_blend(buffer[width * target.y + target.x], pixelValue, alpha);
        }

        target.x = -radius + nX;
        if (clip.checkPoint(target) == true) {
			buffer[width * target.y + target.x] = alpha_blend(buffer[width * target.y + target.x], pixelValue, alpha);
        }

		if ((int) radius != y)
		{
            target.x = y + nX;
            target.y = radius + nY;
            if (clip.checkPoint(target) == true) {
				buffer[width * target.y + target.x] = alpha_blend(buffer[width * target.y + target.x], pixelValue, alpha);
            }

            target.x = -y + nX;
            if (clip.checkPoint(target) == true) {
				buffer[width * target.y + target.x] = alpha_blend(buffer[width * target.y + target.x], pixelValue, alpha);
            }
            
            target.x = y + nX;
            target.y = -radius + nY;
            if (clip.checkPoint(target) == true) {
				buffer[width * target.y + target.x] = alpha_blend(buffer[width * target.y + target.x], pixelValue, alpha);
            }

            target.x = -y + nX;
            if (clip.checkPoint(target) == true) {
				buffer[width * target.y + target.x] = alpha_blend(buffer[width * target.y + target.x], pixelValue, alpha);
            }
		}
	}
}

method Screen::drawImage(Rect rect, Rect clip, Color *pixelBuffer, UInt8 alpha) -> Void {
    var sourceOrigin = Point(0, 0);
	drawImageRect(rect, sourceOrigin, clip, pixelBuffer, alpha);
}

method Screen::drawImageTransparent(Rect rect, Rect clip, Color *pixelBuffer, Color transparentColor, UInt8 alpha) -> Void {
    Rect sourceRect(0, 0, rect.width, rect.height);
	drawImageRectTransparent(rect, sourceRect, clip, pixelBuffer, transparentColor, alpha);
}

method Screen::drawImageRect(Rect rect, Point sourceOrigin, Rect clip, Color *pixelBuffer, UInt8 alpha) -> Void {
    var target = Point(0 ,0);
	
	for(unsigned i = 0; i < rect.height; i++)
	{
		for(unsigned j = 0; j < rect.width; j++)
		{
            target.y = rect.y + i;
            target.x = j + rect.x;
            if (clip.checkPoint(target) == true) {
				buffer[(rect.y + i) * width + j + rect.x] =
					alpha_blend(buffer[(rect.y + i) * width + j + rect.x], 
					pixelBuffer[(sourceOrigin.y + i) * rect.width + j + sourceOrigin.x], 
					alpha);
            }
    	}
	}
}

method Screen::drawImageRectTransparent(Rect rect, Rect sourceRect, Rect clip, Color *pixelBuffer, Color transparentColor, UInt8 alpha) -> Void {
    var target = Point(0, 0);
	
	for(unsigned i = 0; i < rect.height; i++)
	{
		for(unsigned j = 0; j < rect.width; j++)
		{
			Color sourcePixel = pixelBuffer[(sourceRect.y + i) * sourceRect.width + j + sourceRect.x];
			if(sourcePixel != transparentColor)
			{
                target.x = j + rect.x;
                target.y = rect.y + i;
                if (clip.checkPoint(target) == true) {
					buffer[(rect.y + i) * width + j + rect.x] = 
						alpha_blend(buffer[(rect.y + i) * width + j + rect.x], 
						sourcePixel, 
						alpha);
                }
			}
		}
	}
}

method Screen::drawPixel(Point point, Rect clippingRect, UInt8 paletteIndex, UInt8 colorIndex, UInt8 alpha) -> Void {
	if(clippingRect.checkPoint(point) == false)
	{
		return;
	}
	
	buffer[width * point.y + point.x] = alpha_blend(buffer[width * point.y + point.x], 
													SystemPalette[paletteIndex][colorIndex], 
													alpha);
}

method Screen::getBuffer()  -> Color * {
	return buffer;
}

method Screen::updateDisplay() -> Void {
	
	if(vsync) {
		framebuffer->WaitForVerticalSync();
		memcpy(baseBuffer + bufferSwapped * width * height, 
			   buffer, 
			   width * height * sizeof(Color));
		framebuffer->SetVirtualOffset(0, bufferSwapped ? height : 0);
		bufferSwapped = !bufferSwapped;
	} else {
		memcpy(baseBuffer, buffer, width * height * sizeof(Color));
	}
}

method Screen::drawText(String message, shared_ptr<ParagraphStyle> style, Point origin, Rect clip) -> Void {

	var context = new Screen::TextDrawingContext(style, origin, clip, this);

	mf_render_aligned(context->style->font()->data(),
            		  context->origin.x, context->origin.y, 
					  (mf_align_t) context->style->align(), 
					  message.c_str(), 0, 
					  &char_callback, (void *) context);
	
	delete context;
}

static auto line_callback(mf_str line, uint16_t count, void *state) -> Bool {

	var context = (Screen::TextDrawingContext *) state;
	
	return false;
}

// Character callback
static auto char_callback(int16_t x0, int16_t y0, mf_char character, void *state) -> uint8_t {

	var context = (Screen::TextDrawingContext *) state;

    return mf_render_character(context->style->font()->data(), x0, y0, character, &pixel_callback, state);
}

// Pixel callback
static auto pixel_callback(int16_t x, int16_t y, uint8_t count, uint8_t alpha, void *state) -> Void {

	var context = (Screen::TextDrawingContext *) state;

	while (count--) {
		/* your code goes here, ex: drawPixel(x, y, alpha, color::black); */

		Color *buffer = context->screen->getBuffer();

		UInt32 offset = context->screen->getWidth() * y + x;

		var target = Point(x, y);
		
		if (context->clip.checkPoint(target) == true) {
			buffer[offset] = alpha_blend(buffer[offset], context->style->color(), alpha);
		}
		x++;
	}
}
