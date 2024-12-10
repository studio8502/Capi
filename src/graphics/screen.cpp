/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ graphics/screen.cpp                                                       ║
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

#include "graphics/screen.h"
#include "workspace/workspace.h"
#include "kernel.h"

unique_ptr<Screen> screen;

Screen::Screen(UInt32 width, UInt32 height, UInt8 display):
	fpsCounter(0.0),
	fps(0.0),
 	_width(width),
	_height(height),
	display (display),
	framebuffer(nullptr),
	_buffer(nullptr),
	bufferSwapped(TRUE),
	_bufferLock(),
	_dirty(false),
	dma(DMA_CHANNEL_NORMAL, CInterruptSystem::Get())
{
    if (screen != nullptr) {
		throw std::runtime_error("There can be only a single Screen instance!");
    }
}

Screen::~Screen(void)
{
    delete [] _buffer;
}

method Screen::initialize(void) -> Bool {
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
	
	return true;
}

method Screen::resize(unsigned nWidth, unsigned nHeight) -> Bool {
	framebuffer.reset();

	_width = nWidth;
	_height = nHeight;

	delete [] _buffer;
	_buffer = nullptr;
	bufferSwapped = true;

	return initialize();
}

method Screen::width() const -> UInt32 {
	return _width;
}

method Screen::height() const -> UInt32 {
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

method Screen::clear() -> Void {

    Color c = RGBA(0xFFFFFFFF);

	memset(_buffer, c, _width * _height * sizeof(Color));
}

method Screen::drawSurface(shared_ptr<Surface> src, Point dest, UInt8 alpha) -> Void {

    var target = Point(0 ,0);
	var pixelBuffer = src.get()->data();
	var clip = screenRect();
	
	for(unsigned i = 0; i < src->height(); i += 1)
	{
		target.y = dest.y + i;

		for(unsigned j = 0; j < src->width(); j += 1)
		{
            target.x = j + dest.x;

			_buffer[target.y * _width + target.x] = pixelBuffer[i * src->width() + j];
    	}
	}
}

method Screen::updateDisplay() -> Void {
	framebuffer->WaitForVerticalSync();

	var surface = workspace->frontSurface();
	surface->acquire();
	memcpy(baseBuffer + bufferSwapped * _width * _height, 
						surface->data().get(), 
						_width * _height * sizeof(Color));
	surface->release();
	framebuffer->SetVirtualOffset(0, bufferSwapped ? _height : 0);
	bufferSwapped = !bufferSwapped;
	fpsCounter += 1.0;
	
	workspace->setDirtyFlag();
}
