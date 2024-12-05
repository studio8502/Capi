/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ graphics/surface.cpp                                                      ║
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

#include "graphics/surface.h"
#include "mcufont.h"

static function pixel_callback(int16_t x, int16_t y, uint8_t count, uint8_t alpha, void *state) -> Void;

static function char_callback(int16_t x0, int16_t y0, mf_char character, void *state) -> uint8_t;

static function line_callback(mf_str line, uint16_t count, void *state) -> Bool;

Surface::Surface(Size size):
    _width(size.width),
    _height(size.height),
    _data(shared_ptr<Color[]>(new Color[size.width * size.height])),
    _opacity(255),
    _lock()
{
    reset();
}

Surface::Surface(UInt32 width, UInt32 height):
    _width(width),
    _height(height),
    _data(shared_ptr<Color[]>(new Color[width * height])),
    _opacity(255),
    _lock()
{
    reset();
}

Surface::~Surface() {
    _data.reset();
}

method Surface::opacity() -> UInt8 {
    return _opacity;
}

method Surface::setOpacity(UInt8 newValue) -> Void {
    _opacity = newValue;
}

method Surface::reset() -> Void {
    var bounds = Rect(0,0,_width,_height);

    Color color = 0x00FFFFFF;
    
    var buffer = _data.get();
    var target = Point(0, 0);
    
    for(unsigned i = bounds.y; i < bounds.y + bounds.height; i += 1) {

        target.y = i;
    
        if (target.y > _height) {
            return;
        } else if (target.y < 0) {
            continue;
        }

        for(unsigned j = bounds.x; j < bounds.x + bounds.width; j += 1) {

            target.x = j;

            var offset = i * _width + j;
            
            buffer[offset] = color;
        }
    }
}

method Surface::width() -> UInt64 {
    return _width;
}

method Surface::height() -> UInt64 {
    return _height;
}

method Surface::data() -> shared_ptr<Color[]> {
    return _data;
}

method Surface::acquire() -> Void {
    _lock.Acquire();
}

method Surface::release() -> Void {
    _lock.Release();
}

method Surface::clear(Color color) -> Void {
    drawRect(Rect(0,0,_width,_height), true, color);
}

method Surface::drawRect(Rect rect, Bool fill, Color color) -> Void {
    var bounds = Rect(0,0,_width,_height);
    guard (bounds.checkRect(rect) == true) else {
        return;
    }

    if (fill == true) {

        var buffer = _data.get();
        var target = Point(0, 0);
        Color c = color;
        
        for(unsigned i = rect.y; i < rect.y + rect.height; i += 1) {

            target.y = i;
		
            if (target.y > _height) {
                return;
            } else if (target.y < 0) {
                continue;
            }

            for(unsigned j = rect.x; j < rect.x + rect.width; j += 1) {

                target.x = j;
		
                if (target.x > _width) {
                    return;
                } else if (target.x < 0) {
                    continue;
                }

                var offset = i * _width + j;
                
                buffer[offset] = alpha_blend(buffer[offset], c);
            }
        }
    } else {   
        var begin = Point(rect.x, rect.y);
        var end = Point(rect.x + rect.width, rect.y);
        drawLine(begin, end, color);

        begin = end;
        end.y += rect.height;
        drawLine(begin, end, color);

        begin = end;
        end.x -= rect.width;
        drawLine(begin, end, color);

        begin = end;
        end.y -= rect.height;
        drawLine(begin, end, color);
    }
}

method Surface::drawLine(Point begin, Point end, Color color) -> Void {

    Color lineColor = color;
	
	int dx = end.x - begin.x;
	int dy = end.y - begin.y;
	int dxabs = (dx>0) ? dx : -dx;
	int dyabs = (dy>0) ? dy : -dy;
	int sgndx = (dx>0) ? 1 : -1;
	int sgndy = (dy>0) ? 1 : -1;
	int x = dyabs >> 1;
	int y = dxabs >> 1;

	var buffer = _data.get();
	var width = _width;

	buffer[width * begin.y + begin.x] = alpha_blend(buffer[width * begin.y + begin.x], lineColor);

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

            if (target.x > _width || target.x < 0 || target.y < 0) {
                continue;
            } else if (target.y > _height) {
                return;
            }

			buffer[width * begin.y + begin.x] = alpha_blend(buffer[width * begin.y + begin.x], lineColor);
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

            if (target.x > _width || target.x < 0 || target.y < 0) {
                continue;
            } else if (target.y > _height) {
                return;
            }

			buffer[width * begin.y + begin.x] = alpha_blend(buffer[width * begin.y + begin.x], lineColor);
		}
	}
}

method Surface::drawCircle(Point origin, UInt32 radius, Bool fill, Color color) -> Void {

    var area = Rect(origin.x - radius, origin.y - radius, radius * 2, radius * 2);
    var bounds = Rect(0,0,_width,_height);
    Color pixelValue = color;
    guard (bounds.checkRect(area) == true) else {
        return;
    }

    if (fill == true) {
        
        unsigned nX = origin.x;
        unsigned nY = origin.y;
        
        int r2 = radius * radius;
        unsigned area = r2 << 2;
        unsigned rr = radius << 1;

        var target = Point(0, 0);
        var surface = _data.get();
        var width = _width;

        for (unsigned i = 0; i < area; i++)
        {
            int tx = (int) (i % rr) - radius;
            int ty = (int) (i / rr) - radius;

            if (tx * tx + ty * ty < r2)
            {   
                target.x = nX + tx;
                target.y = nY + ty;

                if (target.x > _width || target.x < 0 || target.y < 0) {
                    continue;
                } else if (target.y > _height) {
                    return;
                }

                surface[width * (nY + ty) + nX + tx] = alpha_blend(surface[width * (nY + ty) + nX + tx], pixelValue);
            }
        }
    } else {            
        unsigned nX = origin.x;
        unsigned nY = origin.y;
        var buffer = _data.get();
        var width = _width;

        var target = Point(radius + nX, nY);

        if (target.x > 0 && target.x > _width && target.x > 0 && target.y < _height) {
            buffer[width * target.y + target.x] = alpha_blend(buffer[width * target.y + target.x], pixelValue);
        }

        if (radius > 0) {
            target.y = -radius + nY;
            if (target.x > 0 && target.x > _width && target.x > 0 && target.y < _height) {
                buffer[width * target.y + target.x] = alpha_blend(buffer[width * target.y + target.x], pixelValue);
            }

            target.x = -radius + nX;
            target.y = nY;
            if (target.x > 0 && target.x > _width && target.x > 0 && target.y < _height) {
                buffer[width * target.y + target.x] = alpha_blend(buffer[width * target.y + target.x], pixelValue);
            }

            target.x = nX;
            target.y = radius + nY;
            if (target.x > 0 && target.x > _width && target.x > 0 && target.y < _height) {
                buffer[width * target.y + target.x] = alpha_blend(buffer[width * target.y + target.x], pixelValue);
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
            if (target.x > 0 && target.x > _width && target.x > 0 && target.y < _height) {
                buffer[width * target.y + target.x] = alpha_blend(buffer[width * target.y + target.x], pixelValue);
            }

            target.x = -radius + nX;
            if (target.x > 0 && target.x > _width && target.x > 0 && target.y < _height) {
                buffer[width * target.y + target.x] = alpha_blend(buffer[width * target.y + target.x], pixelValue);
            }

            target.x = radius + nX;
            target.y = -y + nY;
            if (target.x > 0 && target.x > _width && target.x > 0 && target.y < _height) {
                buffer[width * target.y + target.x] = alpha_blend(buffer[width * target.y + target.x], pixelValue);
            }

            target.x = -radius + nX;
            if (target.x > 0 && target.x > _width && target.x > 0 && target.y < _height) {
                buffer[width * target.y + target.x] = alpha_blend(buffer[width * target.y + target.x], pixelValue);
            }

            if ((int) radius != y)
            {
                target.x = y + nX;
                target.y = radius + nY;
                if (target.x > 0 && target.x > _width && target.x > 0 && target.y < _height) {
                    buffer[width * target.y + target.x] = alpha_blend(buffer[width * target.y + target.x], pixelValue);
                }

                target.x = -y + nX;
                if (target.x > 0 && target.x > _width && target.x > 0 && target.y < _height) {
                    buffer[width * target.y + target.x] = alpha_blend(buffer[width * target.y + target.x], pixelValue);
                }
                
                target.x = y + nX;
                target.y = -radius + nY;
                if (target.x > 0 && target.x > _width && target.x > 0 && target.y < _height) {
                    buffer[width * target.y + target.x] = alpha_blend(buffer[width * target.y + target.x], pixelValue);
                }

                target.x = -y + nX;
                if (target.x > 0 && target.x > _width && target.x > 0 && target.y < _height) {
                    buffer[width * target.y + target.x] = alpha_blend(buffer[width * target.y + target.x], pixelValue);
                }
            }
        }
    }
}

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

method Surface::drawImageRectTransparent(Rect rect, Rect sourceRect, shared_ptr<Image> image, Color transparentColor, Bool alpha) -> Void {
    var target = Point(0, 0);
	var buffer = _data.get();
	var width = _width;
	
	for(unsigned i = 0; i < rect.height; i++)
	{
		for(unsigned j = 0; j < rect.width; j++)
		{
			Color sourcePixel = (image->data)[(sourceRect.y + i) * sourceRect.width + j + sourceRect.x];
			if(sourcePixel != transparentColor)
			{
                target.x = j + rect.x;
                target.y = rect.y + i;

                if (target.x > _width || target.x < 0 || target.y < 0) {
                    continue;
                } else if (target.y > _height) {
                    return;
                }

                if (alpha == true) {
                    buffer[(rect.y + i) * width + j + rect.x] = 
                        alpha_blend(buffer[(rect.y + i) * width + j + rect.x], sourcePixel);
                } else {
                    buffer[(rect.y + i) * width + j + rect.x] = sourcePixel;
                }
            }
		}
	}
}

method Surface::drawSurface(shared_ptr<Surface> src, Point dest, Bool alpha) -> Void {

    var target = Point(0 ,0);
	var pixelBuffer = src.get()->data();
	var buffer = _data.get();
	
	for(unsigned i = 0; i < src->height(); i += 1)
	{
		target.y = dest.y + i;
		
		if (target.y >= _height || target.y < 0) {
			continue;
		}

		for(unsigned j = 0; j < src->width(); j += 1)
		{
            target.x = j + dest.x;
		
			if (target.x < 0 || target.x >= _width || target.x >= dest.x + src->width()) {
				continue;
			}

            if (alpha == false) {
			    buffer[target.y * _width + target.x] = pixelBuffer[i * src->width() + j];
            } else {
                buffer[target.y * _width + target.x] =
                    alpha_blend(buffer[target.y * _width + target.x], 
                                        pixelBuffer[i * src->width() + j]);
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
