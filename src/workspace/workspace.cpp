// workspace/workspace.cpp
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

#include <memory>

#include "workspace/workspace.h"
#include "workspace/window.h"

Workspace::Workspace(unsigned width, unsigned height, boolean vsync, unsigned display):
    Graphics(width, height, vsync, display) 
{
    
}

Workspace::~Workspace() {
    
}