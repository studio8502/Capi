/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ graphics/screen.h                                                         ║
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

#pragma once

#include "capi.h"
#include "graphics/geometry.h"

class Screen {
public:

	Double fpsCounter;
	Double fps;

	Screen(UInt32 width, UInt32 height, UInt8 display = 0);

	~Screen(void);

	method initialize(void) -> Bool;
    
	method resize(unsigned nWidth, unsigned nHeight) -> Bool;

	method width() const -> UInt32;

	method height() const -> UInt32;

    method screenRect() -> Rect;

	method buffer() -> Color *;

	method pageFlip() -> Void;

	method lock() -> Void;

	method unlock() -> Void;

	method clear(Color color = 0x0F) -> Void;

    method updateDisplay() -> Void;
	
private:
	UInt32 _width;
	UInt32 _height;
	UInt8 display;

	unique_ptr<CBcmFrameBuffer>	framebuffer;
	
    Color *baseBuffer;
	Color *frontBuffer;
	Color *backBuffer;
	CSpinLock frontBufferLock;
	CSpinLock backBufferLock;
	Bool backBufferSwapped;
	boolean bufferSwapped;
	Bool _dirty;

	CDMAChannel dma;
};

extern unique_ptr<Screen> screen;
