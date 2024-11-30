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

static function createWindow(UInt16 x, UInt16 y) -> shared_ptr<Window>;

Multicore::Multicore(CMemorySystem *memory):
	CMultiCoreSupport (memory)
{}

Multicore::~Multicore() {}

method Multicore::Run(UInt32 core_id) -> Void {

    switch (core_id) {
    case 0: {
		CScheduler::Get()->Sleep(5);
    }
    case 1: {
            while (true) {
                screen->updateDisplay();
            }
        }   
        break;
    case 2: {
            var win1 = createWindow(300, 200);
            var win2 = createWindow(200, 100);
            while (true) {
                workspace->draw();
            }
        }
        break;
    default:
        return;
    }

    var log = CLogger::Get();

    log->Write("Core 1", LogNotice, "Running!");
}

static function drawWindow(Window *win) {win->clear(0, 22);
    win->acquire();

    win->drawCircle(Point(0,0), 49 , true, 0, 15, 127);
    win->drawCircle(Point(450,0), 49 , true, 0, 15, 127);
    win->drawCircle(Point(0,293), 49 , true, 0, 15, 127);
    win->drawCircle(Point(450, 293), 49 , true, 0, 15, 127);
    win->drawCircle(Point(50,50), 25, true, 0, 43);
    win->drawCircle(Point(60,60), 25, true, 0, 57, 127);

    win->drawRect(Rect(50,100,45,76), true, 0, 76, 127);
    win->drawRect(Rect(49,99,46,77), false, 0, 0, 127);


    win->drawRect(Rect(-50,-50,10,10), true, 0, 76);
    win->drawRect(Rect(-50,350,10,10), true, 0, 76);
    win->drawRect(Rect(500,-50,10,10), true, 0, 76);
    win->drawRect(Rect(500,350,10,10), true, 0, 76);

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

    var style = ParagraphStyle::DefaultStyle();
    style->setColor(SystemPalette[0][15]);

    win->drawSurface(border, Point(175, 5));
    win->drawSurface(box, Point(179, 9));

    win->drawText(VersionString(), style, Point(2, 255));

    win->release();
}

static function createWindow(UInt16 x, UInt16 y) -> shared_ptr<Window> {
    var win = workspace->createWindow();

    win->setDrawCallback(drawWindow);
    win->setTitle("Fancy Title");
    win->resize(Size(450, 293));
    win->move(Point(x, y));

    return win;
}
