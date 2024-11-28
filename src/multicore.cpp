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
#include "workspace/window.h"

static function draw() -> Void;

static function drawWindow(UInt16 x, UInt16 y) -> Void;

Multicore::Multicore(CMemorySystem *memory):
	CMultiCoreSupport (memory)
{}

Multicore::~Multicore() {}

method Multicore::Run(UInt32 core_id) -> Void {
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

static function draw() -> Void {

    while (true) {
        screen->acquire();
        screen->clear();

        drawWindow(400, 200);

        screen->release();
    }
}

static function drawWindow(UInt16 x, UInt16 y) -> Void {
    var win = make_shared<Window>(Point(x, y), Size(450, 250));

    win->acquire();

    win->clear(0, 22);
    win->drawCircle(Point(50,50), 25, true, 0, 43);
    win->drawCircle(Point(60,60), 25, true, 0, 57, 127);

    win->drawRect(Rect(50,100,45,76), true, 0, 76);
    win->drawRect(Rect(49,99,47,78), false, 0, 0);

    var color = 0;
    var box = make_shared<Surface>(256, 256);
    var border = make_shared<Surface>(264, 264);
    
    border->acquire();
    border->clear(0, 0);
    border->release();

    box->acquire();
    box->clear(0, 0);
    for (var row = 0; row < 16; row += 1) {     
        for (var col = 0; col < 16; col += 1) {
            var rect = Rect(col * 16, row * 16, 16, 16);
            box->drawRect(rect, true, 0, color);
            color += 1;
        }
    }
    box->release();

    win->drawSurface(border, Point(100, 10));
    win->drawSurface(box, Point(104, 14));

    win->release();
    win->draw();
}