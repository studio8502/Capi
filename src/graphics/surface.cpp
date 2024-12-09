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
#include "file.h"

Surface::Surface(Size size, Point origin):
    _width(size.width),
    _height(size.height),
    _data(shared_ptr<Color[]>(new Color[size.width * size.height])),
    _opacity(255),
    _canvas(make_shared<Canvas>(size.width, size.height)),
    _origin(origin),
    subsurfaces(),
    _lock()
{
    _canvas->translate(0.5,0.5);
    reset();
}

Surface::Surface(UInt32 width, UInt32 height, Point origin):
    _width(width),
    _height(height),
    _data(shared_ptr<Color[]>(new Color[width * height])),
    _opacity(255),
    _canvas(make_shared<Canvas>(width, height)),
    _origin(origin),
    _lock()
{
    reset();
}

Surface::~Surface() {
    _data.reset();
}

method Surface::addSubsurface(shared_ptr<Surface> child, Point origin) -> Void {
    child->setOrigin(origin);
    subsurfaces.push_back(child);
}

method Surface::origin() -> Point {
    return _origin;
}

method Surface::setOrigin(Point origin) -> Void {
    _origin = origin;
}

method Surface::render() -> Void {
    std::for_each(subsurfaces.rbegin(), subsurfaces.rend(), [this](shared_ptr<Surface> sfc) {
        sfc->render();
        this->drawSurface(sfc, sfc->origin());
    });

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

method Surface::saveState() -> Void {
    _canvas->save();
}

method Surface::restoreState() -> Void {
    _canvas->restore();
}

method Surface::resetTransform() -> Void {
    _canvas->set_transform(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
}

method Surface::scaleTransform(Single x, Single y) -> Void {
    _canvas->scale(x, y);
}

method Surface::rotateTransform(Single angle) -> Void {
    _canvas->rotate(angle);
}

method Surface::translateTransform(Single x, Single y) -> Void {
    _canvas->translate(x, y);
}

method Surface::appendTransform(AffineTransform &transform) {
    _canvas->transform(transform.horizontalScale,
                       transform.verticalSkew,
                       transform.horizontalSkew,
                       transform.verticalScale,
                       transform.horizontalTranslation,
                       transform.verticalTranslation);
}

method Surface::replaceTransform(AffineTransform &transform) {
    _canvas->set_transform(transform.horizontalScale,
                           transform.verticalSkew,
                           transform.horizontalSkew,
                           transform.verticalScale,
                           transform.horizontalTranslation,
                           transform.verticalTranslation);
}

method Surface::setCompositeOperation(CompositeOperation op) -> Void {
    _canvas->global_composite_operation = (canvas_ity::composite_operation) op;
}

method Surface::clear(Color color) -> Void {
    _canvas->save();
    setFillColor(color);
    fillRect(Rect(0, 0, _width, _height));
    _canvas->restore();
}

method Surface::setColor(BrushType type, Color color) -> Void {
    var b = (color & 0xFF) * (1.0 / 255.0);
    var g = ((color >> 8) & 0xFF) * (1.0 / 255.0);
    var r = ((color >> 16) & 0xFF) * (1.0 / 255.0);
    var a = ((color >> 24) & 0xFF) * (1.0 / 255.0);
    _canvas->set_color((canvas_ity::brush_type) type, r, g, b, a);
}

method Surface::setFillColor(Color color) -> Void {
    setColor(BrushType::fill, color);
}

method Surface::setStrokeColor(Color color) -> Void {
    setColor(BrushType::stroke, color);
}

method Surface::setStrokeLinearGradient(Single startX, Single startY, Single endX, Single endY) -> Void {
    _canvas->set_linear_gradient((canvas_ity::brush_type) BrushType::stroke, startX, startY, endX, endY);
}

method Surface::setFillLinearGradient(Single startX, Single startY, Single endX, Single endY) -> Void {
    _canvas->set_linear_gradient((canvas_ity::brush_type) BrushType::fill, startX, startY, endX, endY);
}

method Surface::setStrokeRadialGradient(Single startX, Single startY, Single startRadius,   
                                        Single endX, Single endY, Single endRadius) -> Void {
    _canvas->set_radial_gradient((canvas_ity::brush_type) BrushType::stroke, 
                                  startX, startY, startRadius, 
                                  endX, endY, endRadius);
}

method Surface::setFillRadialGradient(Single startX, Single startY, Single startRadius, Single endX, 
                                      Single endY, Single endRadius) -> Void {
    _canvas->set_radial_gradient((canvas_ity::brush_type) BrushType::fill, 
                                  startX, startY, startRadius, 
                                  endX, endY, endRadius);
}
method Surface::addStrokeColorStop(Single offset, Color color) -> Void {
    var b = (color & 0xFF) * (1.0 / 255.0);
    var g = ((color >> 8) & 0xFF) * (1.0 / 255.0);
    var r = ((color >> 16) & 0xFF) * (1.0 / 255.0);
    var a = ((color >> 24) & 0xFF) * (1.0 / 255.0);
    _canvas->add_color_stop((canvas_ity::brush_type) BrushType::stroke, offset, r, g, b, a);
}

method Surface::addFillColorStop(Single offset, Color color) -> Void {
    var b = (color & 0xFF) * (1.0 / 255.0);
    var g = ((color >> 8) & 0xFF) * (1.0 / 255.0);
    var r = ((color >> 16) & 0xFF) * (1.0 / 255.0);
    var a = ((color >> 24) & 0xFF) * (1.0 / 255.0);
    _canvas->add_color_stop((canvas_ity::brush_type) BrushType::fill, offset, r, g, b, a);
}

method Surface::setStrokeImagePattern(shared_ptr<Image> image, RepetitionStyle rep) -> Void {
    var width = image->rect().width;
    var height = image->rect().height;
    Int stride = width * sizeof(Color);
    _canvas->set_pattern((canvas_ity::brush_type) BrushType::stroke,
                         (const unsigned char*)(image->data), width, height, stride, 
                         (canvas_ity::repetition_style) rep);
}

method Surface::setFillImagePattern(shared_ptr<Image> image, RepetitionStyle rep) -> Void {
    var width = image->rect().width;
    var height = image->rect().height;
    Int stride = width * sizeof(Color);
    _canvas->set_pattern((canvas_ity::brush_type) BrushType::fill,
                         (const unsigned char*)(image->data), width, height, stride, 
                         (canvas_ity::repetition_style) rep);
}

method Surface::setShadowColor(Color color) -> Void {
    var b = (color & 0xFF) * (1.0 / 255.0);
    var g = ((color >> 8) & 0xFF) * (1.0 / 255.0);
    var r = ((color >> 16) & 0xFF) * (1.0 / 255.0);
    var a = ((color >> 24) & 0xFF) * (1.0 / 255.0);
    _canvas->set_shadow_color(r, g, b, a);
}

method Surface::setShadowHorizontalOffset(Single offset) -> Void {
    _canvas->shadow_offset_x = offset;
}

method Surface::setShadowVerticallOffset(Single offset) -> Void {
    _canvas->shadow_offset_y = offset;
}

method Surface::setShadowBlur(Single blur) -> Void {
    _canvas->set_shadow_blur(blur);
}

method Surface::setLineWidth(Int width) -> Void {
    _canvas->set_line_width(width);
}

method Surface::setLineCapStyle(LineCapStyle style) -> Void {
    _canvas->line_cap = (canvas_ity::cap_style) style;
}


method Surface::setLineJoinStyle(LineJoinStyle style) -> Void {
    _canvas->line_join = (canvas_ity::join_style) style;
}

method Surface::setMiterLimit(Single limit) -> Void {
    _canvas->set_miter_limit(limit);
}

method Surface::setLineDashOffset(Single offset) -> Void {
    _canvas->line_dash_offset = offset;
}

method Surface::setLineDashPattern(Single const *pattern, Int count) -> Void {
    _canvas->set_line_dash(pattern, count);
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

method Surface::moveTo(Single x, Single y) -> Void {
    _canvas->move_to(x, y);
}

method Surface::lineTo(Single x, Single y) -> Void {
    _canvas->line_to(x, y);
}

method Surface::rectangle(Rect rect) -> Void {
    _canvas->rectangle(rect.x, rect.y, rect.width, rect.height);
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

method Surface::measureText(String message) -> Single {
    return _canvas->measure_text(message.c_str());
}

method Surface::setFont(shared_ptr<Font> font, Double size) -> Void {
    var status = _canvas->set_font((unsigned char const *) font->data, font->length, size);
    if (status != true) {
        CLogger::Get()->Write("Surface", LogNotice, "Failed to set font!");
    }
}

method Surface::fillText(String message, Point origin) -> Void {
    _canvas->fill_text(message.c_str(), origin.x, origin.y);
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