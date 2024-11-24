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

#include "graphics/graphics.h"
#include "mcufont.h"

Graphics::Graphics (UInt32 width, UInt32 height, Bool vsync, UInt8 display)
: 	width(width),
	height(height),
	display (display),
	framebuffer(nullptr),
	buffer(nullptr),
	vsync(vsync),
	bufferSwapped(TRUE)
{

}

Graphics::~Graphics (void)
{
    
}

method Graphics::initialize (void) -> Bool {
	framebuffer = make_unique<CBcmFrameBuffer>(width, height, DEPTH, width, 2*height,
					      display, TRUE);

	if (!framebuffer || !framebuffer->Initialize ())
	{
		return FALSE;
	}

	baseBuffer = (Color *) (uintptr) framebuffer->GetBuffer();
	width = framebuffer->GetWidth();
	height = framebuffer->GetHeight();
	buffer = baseBuffer + width * height;
	
	return TRUE;
}

method Graphics::resize (unsigned nWidth, unsigned nHeight) -> Bool {
	framebuffer.reset();

	width = nWidth;
	height = nHeight;

	buffer = 0;
	bufferSwapped = TRUE;

	return initialize ();
}

method Graphics::getWidth () const -> UInt32 {
	return width;
}

method Graphics::getHeight () const -> UInt32 {
	return height;
}

method Graphics::getScreenRect() -> Rect {
	return Rect(0, 0, width, height);
}

method Graphics::clearScreen(UInt8 palette, UInt8 color) -> Void {
    Rect clip = getScreenRect();
	drawRect(clip, clip, true, palette, color, 255);
}

method Graphics::drawRect(Rect rect, Rect clip, Bool fill, UInt8 palette, UInt8 color, UInt8 alpha) -> Void {
    if (fill == true) {
        _drawRect(rect, clip, palette, color, alpha);
    } else {
        _drawRectOutline(rect, clip, palette, color, alpha);
    }
}

method Graphics::_drawRect (Rect rect, Rect clip, UInt8 palette, UInt8 color, UInt8 alpha) -> Void {
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

method Graphics::_drawRectOutline (Rect rect, Rect clip, UInt8 palette, UInt8 color, UInt8 alpha) -> Void {
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

method Graphics::drawLine(Point begin, Point end, Rect clip, UInt8 palette, UInt8 color, UInt8 alpha) -> Void {
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

method Graphics::drawCircle(Point origin, UInt32 radius, Rect clip, Bool fill, UInt8 palette, UInt8 color, UInt8 alpha) -> Void {
    if (fill == true) {
        _drawCircle(origin, radius, clip, palette, color, alpha);
    } else {
        _drawCircleOutline(origin, radius, clip, palette, color, alpha);
    }
}


method Graphics::_drawCircle(Point origin, UInt32 radius, Rect clip, UInt8 palette, UInt8 color, UInt8 alpha) -> Void {
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

method Graphics::_drawCircleOutline(Point origin, UInt32 radius, Rect clip, UInt8 palette, UInt8 color, UInt8 alpha) -> Void {

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

method Graphics::drawImage(Rect rect, Rect clip, Color *pixelBuffer, UInt8 alpha) -> Void {
    var sourceOrigin = Point(0, 0);
	drawImageRect(rect, sourceOrigin, clip, pixelBuffer, alpha);
}

method Graphics::drawImageTransparent(Rect rect, Rect clip, Color *pixelBuffer, Color transparentColor, UInt8 alpha) -> Void {
    Rect sourceRect(0, 0, rect.width, rect.height);
	drawImageRectTransparent(rect, sourceRect, clip, pixelBuffer, transparentColor, alpha);
}

method Graphics::drawImageRect(Rect rect, Point sourceOrigin, Rect clip, Color *pixelBuffer, UInt8 alpha) -> Void {
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

method Graphics::drawImageRectTransparent(Rect rect, Rect sourceRect, Rect clip, Color *pixelBuffer, Color transparentColor, UInt8 alpha) -> Void {
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

method Graphics::drawPixel(Point point, Rect clippingRect, UInt8 paletteIndex, UInt8 colorIndex, UInt8 alpha) -> Void {
	if(clippingRect.checkPoint(point) == false)
	{
		return;
	}
	
	buffer[width * point.y + point.x] = alpha_blend(buffer[width * point.y + point.x], 
													SystemPalette[paletteIndex][colorIndex], 
													alpha);
}

method Graphics::getBuffer()  -> Color * {
	return buffer;
}

method Graphics::updateDisplay() -> Void {
	
	if(vsync) {
		framebuffer->SetVirtualOffset(0, bufferSwapped ? height : 0);
		framebuffer->WaitForVerticalSync();
		bufferSwapped = !bufferSwapped;
		buffer = baseBuffer + bufferSwapped * width * height;
	} else {
		memcpy(baseBuffer, buffer, width * height * sizeof(Color));
	}
}
