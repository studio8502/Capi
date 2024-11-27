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

#include "capi.h"

Surface::Surface(UInt64 width, UInt64 height):
    _width(width),
    _height(height),
    _data(shared_ptr<Color[]>(new Color[width * height])),
    _lock()
{}

Surface::~Surface() {
    _data.reset();
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

method Surface::clear(UInt8 palette, UInt8 color) -> Void {

    drawRect(Rect(0,0,_width,_height), true, palette, color);
}

method Surface::drawRect(Rect rect, Bool fill, UInt8 palette, UInt8 color, UInt8 alpha) -> Void {

    if (fill == true) {

        var buffer = _data.get();
        var target = Point(0, 0);
        Color c = SystemPalette[palette][color];
        
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
                
                buffer[offset] = alpha_blend(buffer[offset], c, alpha);
            }
        }
    } else {    
        var begin = Point(rect.x, rect.y);
        var end = Point(rect.x + rect.width, rect.y);
        drawLine(begin, end, palette, color, alpha);

        begin = end;
        end.y += rect.height;
        drawLine(begin, end, palette, color, alpha);

        begin = end;
        end.x -= rect.width;
        drawLine(begin, end, palette, color, alpha);

        begin = end;
        end.y -= rect.height;
        drawLine(begin, end, palette, color, alpha);
    }
}

method Surface::drawLine(Point begin, Point end, UInt8 palette, UInt8 color, UInt8 alpha) -> Void {

    Color lineColor = SystemPalette[palette][color];
	
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
		
            if (target.x > _width) {
                return;
            } else if (target.x < 0) {
                continue;
            } else if (target.y > _height) {
                return;
            } else if (target.y < 0) {
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

            if (target.x > _width) {
                return;
            } else if (target.x < 0) {
                continue;
            } else if (target.y > _height) {
                return;
            } else if (target.y < 0) {
                continue;
            }

			buffer[width * begin.y + begin.x] = alpha_blend(buffer[width * begin.y + begin.x], lineColor, alpha);
		}
	}
}