/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ multicore.cpp                                                             ║
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

#include "multicore.h"
#include "kernel.h"
#include "graphics/font.h"
#include "workspace/workspace.h"

static function now() -> UInt64;

Multicore::Multicore(CMemorySystem *memory):
	CMultiCoreSupport (memory)
{}

Multicore::~Multicore() {}

method Multicore::Run(UInt32 core_id) -> Void {

    switch (core_id) {
    case 0: {
        while (true) {
            CScheduler::Get()->Sleep(1);
        }
    }
    case 1: {
            var win = workspace->createWindow();
            win->show();

            while (true) {
                workspace->update();
            }
        }
        break;
    case 2: 
        while (true) {
    		workspace->draw();
        }
        break;
    case 3: 
        while (true) {
		    screen->updateDisplay();  
        }
        break;
    default:
        break;
    }
}

static function now() -> UInt64 {
    using namespace std::chrono;
    var since_epoch = system_clock::now().time_since_epoch();
    var millis = duration_cast<milliseconds>(since_epoch);
    Int64 time = millis.count();
    return time;
}