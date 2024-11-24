// Workspace/workspace.h
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

#include "graphics/screen.h"
#include "custom_types.h"

// The Workspace is the GUI layer of Capi; it replaces the C2DGraphics
// class with equivalent functionality applied to a WIMP interface -- that
// is, all drawing in Workspace is done within the bounds of clipping
// rectangles supplied as arguments to draw functions.

class Workspace: public Screen {
public:

    Workspace(unsigned width, unsigned height, boolean vsync = true, unsigned display = 0);

    ~Workspace();
};

extern Workspace *workspace;