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
    _canvas(make_shared<Canvas>(size.width, size.height)),
    _lock()
{
    _canvas->translate(0.5,0.5);
    reset();
}

Surface::Surface(UInt32 width, UInt32 height):
    _width(width),
    _height(height),
    _data(shared_ptr<Color[]>(new Color[width * height])),
    _opacity(255),
    _canvas(make_shared<Canvas>(width, height)),
    _lock()
{
    reset();
}

Surface::~Surface() {
    _data.reset();
}

method Surface::render() -> Void {
    _canvas->get_image_data_bgra((unsigned char *) _data.get(), _width, _height, _width * sizeof(Color), 0, 0);
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
    _canvas->save();
    setColor(BrushType::fill, color);

    fillRect(Rect(0, 0, _width, _height));

    _canvas->restore();
}

method Surface::setColor(BrushType type, Color color) -> Void {
    var b = (color & 0xFF) * (1.0 / 255.0);
    var g = ((color >> 8) & 0xFF) * (1.0 / 255.0);
    var r = ((color >> 16) & 0xFF) * (1.0 / 255.0);
    var a = ((color >> 24) & 0xFF) * (1.0 / 255.0);
    _canvas->set_color((brush_type) type, r, g, b, a);
}

method Surface::setLineWidth(Int width) -> Void {
    _canvas->set_line_width(width);
}

method Surface::fill() -> Void {
    _canvas->fill();
}

method Surface::fillRect(Rect rect) -> Void {
    _canvas->fill_rectangle(rect.x, rect.y, rect.width, rect.height);
}

method Surface::stroke() -> Void {
    _canvas->stroke();
}

method Surface::beginPath() -> Void {
    _canvas->begin_path();
}

method Surface::rectangle(Int x, Int y, Int width, Int height) -> Void {
    _canvas->rectangle(x, y, width, height);
}

method Surface::drawImage(shared_ptr<Image> image, Point dest) -> Void {
    _canvas->draw_image((unsigned char *)(image->data),
                         image->rect().width, 
                         image->rect().height, 
                         image->rect().width * sizeof(Color),
                         dest.x,
                         dest.y,
                         image->rect().width, 
                         image->rect().height);
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
