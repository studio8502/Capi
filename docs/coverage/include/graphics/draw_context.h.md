---
generator: doxide
---


# draw_context.h



<style>
.linenodiv pre span {padding-left:4px;padding-right:4px}
</style>

```cpp linenums="1"
/*
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ graphics/draw_context.h                                                   ║
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

#pragma once

#include "capi.h"

/*
 * A DrawContext is a lightweight type which represents a region of the screen,
 * and has the ability to draw to that region using various resource types.
 * When created, a DrawContext has a position, width, and height; the intersection
 * of that rectangle and the screen's rectangle form the maximum of the context's
 * clipping region. Any attempt to draw using a context to a pixel position outside
 * the clipping region will be silently ignored. Additionally, colour index 255/0xFF
 * is designated the transparent colour -- any pixel of that colour will be skipped,
 * allowing the background to show through.
 */

 class DrawContext {
public:

    // Create a DrawContext relative to the screen origin.
    DrawContext(UInt16 x, UInt16 y, UInt16 width, UInt16 height);

    ~DrawContext();

    // Create a DrawContext with x and y coordinates relative to another context's
    // orgin, and clipped to the intersection of its area and the parent context's
    // clipping area.
    method createChildContext(UInt16 x, UInt16 y, UInt16 width, UInt16 height) -> DrawContext;

    method drawHorizontalLine(UInt16 x, UInt16 y, UInt16 length, Color color) -> Void;

private:
    UInt16 x;
    UInt16 y;
    UInt16 width;
    UInt16 height;

    struct {
        UInt16 top;
        UInt16 bottom;
        UInt16 left;
        UInt16 right;
    } clip;
 };

```

