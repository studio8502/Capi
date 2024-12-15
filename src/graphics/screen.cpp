/*
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
 */

#include "graphics/screen.h"
#include "workspace/workspace.h"
#include "kernel/kernel.h"

unique_ptr<Screen> screen;

static UInt32 SystemPalette[] = {
#include "graphics/aurora.hex"
};

Screen::Screen(UInt32 width, UInt32 height, UInt8 display):
	fpsCounter(0.0),
	fps(0.0),
 	_width(width),
	_height(height),
	display (display),
	framebuffer(nullptr),
	frontBuffer(nullptr),
	backBuffer(nullptr),
	frontBufferLock(),
	backBufferLock(),
	backBufferSwapped(false),
	bufferSwapped(true),
	_dirty(false),
	dma(DMA_CHANNEL_NORMAL, CInterruptSystem::Get())
{
    if (screen != nullptr) {
		throw std::runtime_error("There can be only a single Screen instance!");
    }
}

Screen::~Screen(void)
{
    delete [] frontBuffer;
    delete [] backBuffer;
}

method Screen::initialize(void) -> Bool {
	framebuffer = make_unique<CBcmFrameBuffer>(_width, _height, DEPTH, _width, 2 * _height,
					                           display, TRUE);

	for (Int i = 0; i < 256; i += 1) {
		framebuffer->SetPalette32(i, SystemPalette[i]);
	}											   

	if (!framebuffer || !framebuffer->Initialize ())
	{
		return FALSE;
	}

	baseBuffer = (Color *) (uintptr) framebuffer->GetBuffer();
	_width = framebuffer->GetWidth();
	_height = framebuffer->GetHeight();

	frontBuffer = new Color[_width * _height];
	if (frontBuffer == nullptr) {
		return false;
	}

	backBuffer = new Color[_width * _height];
	if (backBuffer == nullptr) {
		return false;
	}
	
	return true;
}

method Screen::resize(unsigned nWidth, unsigned nHeight) -> Bool {
	framebuffer.reset();

	_width = nWidth;
	_height = nHeight;

	frontBufferLock.Acquire();
	backBufferLock.Acquire();

	delete [] frontBuffer;
	delete [] backBuffer;
	frontBuffer = nullptr;
	backBuffer = nullptr;
	bufferSwapped = true;

	backBufferLock.Release();
	frontBufferLock.Release();

	return initialize();
}

method Screen::lock() -> Void {
	backBufferLock.Acquire();
}

method Screen::unlock() -> Void {
	backBufferLock.Release();
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

method Screen::buffer() -> Color * {
	return backBufferSwapped ? backBuffer : frontBuffer;
}

method Screen::pageFlip() -> Void {
	guard (_dirty == false) else {
		return;
	}
	backBufferSwapped = !backBufferSwapped;
	_dirty = true;
}

method Screen::clear(Color color) -> Void {
	memset(buffer(), color, _width * _height * sizeof(Color));
}

method Screen::updateDisplay() -> Void {
	guard (_dirty == true) else {
		return;
	}
	framebuffer->WaitForVerticalSync();

	memcpy(baseBuffer + bufferSwapped * _width * _height, 
		   backBufferSwapped ? frontBuffer : backBuffer, 
		   _width * _height * sizeof(Color));
	framebuffer->SetVirtualOffset(0, bufferSwapped ? _height : 0);
	bufferSwapped = !bufferSwapped;
	fpsCounter += 1.0;
	_dirty = false;
	
	workspace->setDirtyFlag();
}
