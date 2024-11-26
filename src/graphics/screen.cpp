// graphics/screen.cpp
//
// Copyright © 2024 Kyle K Cardoza, Studio 8502 <Kyle.Cardoza@icloud.com>
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

#include <cstring>
#include <memory>

#include "graphics/screen.h"

using std::make_unique;

Screen::Screen(UInt32 width, UInt32 height, Bool vsync, UInt8 display):
 	_width(width),
	_height(height),
	display (display),
	framebuffer(nullptr),
	_buffer(nullptr),
	vsync(vsync),
	bufferSwapped(TRUE),
	_bufferLock(),
	_dirty(false)
{}

Screen::~Screen (void)
{
    delete [] _buffer;
}

method Screen::initialize (void) -> Bool {
	framebuffer = make_unique<CBcmFrameBuffer>(_width, _height, DEPTH, _width, 2 * _height,
					                           display, TRUE);

	if (!framebuffer || !framebuffer->Initialize ())
	{
		return FALSE;
	}

	baseBuffer = (Color *) (uintptr) framebuffer->GetBuffer();
	_width = framebuffer->GetWidth();
	_height = framebuffer->GetHeight();

	_buffer = new Color[_width * _height];
	if (_buffer == nullptr) {
		return false;
	}

    screen = this;
	
	return TRUE;
}

method Screen::resize (unsigned nWidth, unsigned nHeight) -> Bool {
	framebuffer.reset();

	_width = nWidth;
	_height = nHeight;

	delete [] _buffer;
	_buffer = nullptr;
	bufferSwapped = TRUE;

	return initialize ();
}

method Screen::width () const -> UInt32 {
	return _width;
}

method Screen::height () const -> UInt32 {
	return _height;
}

method Screen::screenRect() -> Rect {
	return Rect(0, 0, _width, _height);
}

method Screen::acquire() -> Void {
	_bufferLock.Acquire();
}

method Screen::release() -> Void {
	_dirty = true;
	_bufferLock.Release();
}

method Screen::buffer() -> Color * {
	return _buffer;
}

method Screen::clear(UInt8 palette, UInt8 color) -> Void {

    Color c = SystemPalette[palette][color];

	memset(_buffer, c, _width * _height * sizeof(Color));
}

method Screen::updateDisplay() -> Void {

	if (_dirty == false) {
		return;
	}

	_bufferLock.Acquire();

	if(vsync) {
		framebuffer->WaitForVerticalSync();
		memcpy(baseBuffer + bufferSwapped * _width * _height, 
			   _buffer, 
			   _width * _height * sizeof(Color));
		framebuffer->SetVirtualOffset(0, bufferSwapped ? _height : 0);
		bufferSwapped = !bufferSwapped;
	} else {
		memcpy(baseBuffer, _buffer, _width * _height * sizeof(Color));
	}

	_dirty = false;
	_bufferLock.Release();
}

Screen *screen;
