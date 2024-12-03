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

static function now() -> UInt64;

Multicore::Multicore(CMemorySystem *memory):
	CMultiCoreSupport (memory)
{}

Multicore::~Multicore() {}

method Multicore::Run(UInt32 core_id) -> Void {

    switch (core_id) {
    case 0:
        while (true) {
            CScheduler::Get()->Sleep(5);
        }
        break;
    case 1: 
        while (true) {
            screen->updateDisplay();  
        }
        break;
    case 2: {
            var win1 = createWindow(300, 200);
            win1->setTitle("Window One");
            var win2 = createWindow(200, 100);
            win2->setTitle("Window Two: Window Harder");

            win1->show();
            win2->show();

            Int64 begin = 0;
            Int64 end = 0;
            Int64 delta = end - begin;

            while (true) {
                begin = now();
                workspace->update(delta);
                workspace->draw();
                end = now();
                delta = end - begin;
            }
        }
        break;
    case 3: 
        while (true) {
            
        }
    default:
        return;
    }

    var log = CLogger::Get();

    log->Write("Core 1", LogNotice, "Running!");
}

static function drawWindow(Window *win) {
    win->clear(SystemPalette[0][22]);
    win->acquire();

    win->drawCircle(Point(0,0), 60 , true, ALPHA(SystemPalette[0][15], 127));
    win->drawCircle(Point(450,0), 49 , true, ALPHA(SystemPalette[0][15], 127));
    win->drawCircle(Point(0,293), 49 , true, ALPHA(SystemPalette[0][15], 127));
    win->drawCircle(Point(450, 293), 49 , true, ALPHA(SystemPalette[0][15], 127));
    win->drawCircle(Point(50,50), 25, true, SystemPalette[0][43]);
    win->drawCircle(Point(60,60), 25, true, ALPHA(SystemPalette[0][57], 127));

    win->drawRect(Rect(50,100,45,76), true, ALPHA(SystemPalette[0][15], 127));
    win->drawRect(Rect(49,99,46,77), false, SystemPalette[0][0]);


    win->drawRect(Rect(-50,-50,10,10), true, SystemPalette[0][15]);
    win->drawRect(Rect(-50,350,10,10), true, SystemPalette[0][15]);
    win->drawRect(Rect(500,-50,10,10), true, SystemPalette[0][15]);
    win->drawRect(Rect(500,350,10,10), true, SystemPalette[0][15]);

    var color = 0;
    var box = make_shared<Surface>(256, 256);
    var border = make_shared<Surface>(264, 264);
    
    border->acquire();
    border->clear(SystemPalette[0][0]);
    border->release();

    box->acquire();
    box->clear(SystemPalette[0][0]);
    for (var row = 0; row < 16; row += 1) {     
        for (var col = 0; col < 16; col += 1) {
            var rect = Rect(col * 16, row * 16, 16, 16);
            box->drawRect(rect, true, SystemPalette[0][color]);
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

static function now() -> UInt64 {
    using namespace std::chrono;
    var since_epoch = system_clock::now().time_since_epoch();
    var millis = duration_cast<milliseconds>(since_epoch);
    Int64 time = millis.count();
    return time;
}