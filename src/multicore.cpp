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

#include <memory>

#include <circle/memory.h>
#include <circle/logger.h>

#include "kernel.h"
#include "graphics/screen.h"
#include "graphics/ui_font.h"
#include "graphics/surface.h"
#include "multicore.h"

using std::make_shared;

static auto draw() -> Void;

CoreTest::CoreTest(CMemorySystem *memory):
	CMultiCoreSupport (memory)
{}

CoreTest::~CoreTest() {}

method CoreTest::Run(UInt32 core_id) -> Void {
    switch (core_id) {
    case 0:
        while (true) {
            kernel->updateUSB();

            CScheduler::Get()->Yield();
        }
    case 1:
        while (true) {
            screen->updateDisplay();
        }
        break;
    case 2:
        draw();
        break;
    default:
        return;
    }

    var log = CLogger::Get();

    log->Write("Core 1", LogNotice, "Running!");
}

static auto draw() -> Void {

    UInt8 color = 0;
    var box = make_shared<Surface>(256, 256);
    var border = make_shared<Surface>(264, 264);

    while (true) {

        border->acquire();
        border->clear(0, 0);
        border->release();

        box->acquire();
        box->clear(0, 0);
        for (UInt16 row = 0; row < 16; row += 1) {     
            for (UInt16 col = 0; col < 16; col += 1) {
                var rect = Rect(col * 16, row * 16, 16, 16);
                box->drawRect(rect, true, 0, color);
                color += 1;
            }
        }
        box->release();

        screen->acquire();
        screen->clear();
        screen->drawSurface(border, Point(252, 252));
        screen->drawSurface(box, Point(256, 256));
        screen->release();
    }
}