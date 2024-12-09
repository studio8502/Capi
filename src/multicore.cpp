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
#define TINA_IMPLEMENTATION
#include "tina.h"
#include "graphics/font.h"
#include "workspace/workspace.h"

static function now() -> UInt64;

static void* coro_body(tina* coro, void* value);
size_t buffer_size = 256*1024;
void* buffer = NULL;
void* user_data = NULL;

Multicore::Multicore(CMemorySystem *memory):
	CMultiCoreSupport (memory)
{}

Multicore::~Multicore() {}

method Multicore::Run(UInt32 core_id) -> Void {

    switch (core_id) {
    case 1: {
            var win = workspace->createWindow();
            win->show();

            var win2 = workspace->createWindow();
            win2->move(Point(300, 240));
            win2->show();

            var win3 = workspace->createWindow();
            win3->move(Point(200, 200));
            win3->becomeActive();
            win3->setHasTitlebar(false);
            win3->show();

            tina* coro = tina_init(buffer, buffer_size, coro_body, user_data);
	        coro->name = "MyCoro";
	        void* value = tina_resume(coro, (void *) "hello");

            while (true) {
                if(!coro->completed) {
                    tina_resume(coro, NULL);
                }
                workspace->update();
            }

	        free(coro->buffer);
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

static char msg[256];
static void* coro_body(tina* coro, void* value){
	CLogger::Get()->Write("Tina:", LogNotice, "coro_body() enter\n");
	printf("user_data: '%s'\n", (char*)coro->user_data);
	
	for(unsigned i = 0; i < 3; i++){
		sprintf(msg, "coro_body(): %u\n", i);
        CLogger::Get()->Write("Tina:", LogNotice, msg);
		// Yielding suspends this coroutine and returns control back to the caller.
		tina_yield(coro, 0);
	}
	
	CLogger::Get()->Write("Tina:", LogNotice, "coro_body() return\n");
	// The return value is returned from tina_resume() in the caller.
	return 0;
}