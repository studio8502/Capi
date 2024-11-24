//
// graphics.h
//
// This file:
//	Copyright (C) 2021  Stephane Damo
//  Modificiations for Capi (C) 2024 Kyle J Cardoza <Kyle.Cardoza@icloud.com>
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

#pragma once

#include <memory>

#include <circle/screen.h>

#include "graphics/geometry.h"
#include "graphics/palette.h"

using std::unique_ptr;
using std::make_unique;

// This class is based on the C2DGraphics class, by Stephane Damo. It was
// extensively modified by Kyle J Cardoza <Kyle.Cardoza@icloud.com> to support
// features needed for Capi, such as clipping, as well as to shrink the API
// surface.

class Screen
{
public:
	friend class Kernel;
	friend class Window;

	Screen (UInt32 width, UInt32 height, Bool vsync = true, UInt8 display = 0);

	~Screen (void);

	method initialize(void) -> Bool;
    
	method resize(unsigned nWidth, unsigned nHeight) -> Bool;

    method getScreenRect() -> Rect;

	method fontRenderTest(String message, UInt16 x, UInt16 y) -> Void;

	method getBuffer() -> Color *;
	
    method updateDisplay() -> Void;

	method getWidth() const -> UInt32;

	method getHeight() const -> UInt32;

	method clearScreen(UInt8 palette, UInt8 color) -> Void;

    method drawRect(Rect rect, Rect clip, Bool fill, UInt8 palette, UInt8 color, UInt8 alpha = 255) -> Void;

    method drawCircle(Point origin, UInt32 radius, Rect clip, Bool fill, UInt8 palette, UInt8 color, UInt8 alpha = 255) -> Void;

	method drawLine(Point begin, Point end, Rect clip, UInt8 palette, UInt8 color, UInt8 alpha = 255) -> Void;
	
	method drawImage(Rect rect, Rect clip, Color *pixelBuffer, UInt8 alpha = 255) -> Void;
	
	method drawImageTransparent(Rect rect, Rect clip, Color *pixelBuffer, Color transparentColor, UInt8 alpha = 255) -> Void;
	
	method drawImageRect(Rect rect, Point sourceOrigin, Rect clip, Color *pixelBuffer, UInt8 alpha = 255) -> Void;
	
	method drawImageRectTransparent(Rect rect, Rect sourceRect, Rect clip, Color *pixelBuffer, Color transparentColor, UInt8 alpha = 255) -> Void;
	
	inline method drawPixel(Point point, Rect clippingRect, UInt8 paletteIndex, UInt8 colorIndex, UInt8 alpha = 255) -> Void;

private:
	UInt32 width;
	UInt32 height;
	UInt8 display;

	unique_ptr<CBcmFrameBuffer>	framebuffer;
	
    Color *baseBuffer;
	Color *buffer;
	boolean vsync;
	boolean bufferSwapped;
	
	method _drawRect(Rect rect, Rect clip, UInt8 palette, UInt8 color, UInt8 alpha) -> Void;

	method _drawRectOutline(Rect rect, Rect clip, UInt8 palette, UInt8 color, UInt8 alpha) -> Void;
	
	method _drawCircle(Point origin, UInt32 radius, Rect clip, UInt8 palette, UInt8 color, UInt8 alpha) -> Void;
	
	method _drawCircleOutline(Point origin, UInt32 radius, Rect clip, UInt8 palette, UInt8 color, UInt8 alpha) -> Void;
};
