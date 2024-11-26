// graphics/screen.h
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

#pragma once

#include <memory>

#include <circle/screen.h>
#include <circle/spinlock.h>

#include "graphics/palette.h"
#include "graphics/geometry.h"
#include "custom_types.h"

using std::unique_ptr;

class Screen {
public:

	Screen(UInt32 width, UInt32 height, Bool vsync = true, UInt8 display = 0);

	~Screen(void);

	method initialize(void) -> Bool;
    
	method resize(unsigned nWidth, unsigned nHeight) -> Bool;

	method width() const -> UInt32;

	method height() const -> UInt32;

    method screenRect() -> Rect;

	method acquire() -> Void;

	method release() -> Void;

	method buffer() -> Color *;

	method clear(UInt8 palette, UInt8 color) -> Void;

    method updateDisplay() -> Void;
	

private:
	UInt32 _width;
	UInt32 _height;
	UInt8 display;

	unique_ptr<CBcmFrameBuffer>	framebuffer;
	
    Color *baseBuffer;
	Color *_buffer;
	boolean vsync;
	boolean bufferSwapped;
	CSpinLock _bufferLock;
	Bool _dirty;
};

extern Screen *screen;