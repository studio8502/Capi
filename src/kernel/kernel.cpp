/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ kernel.cpp                                                                ║
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

#include "kernel/kernel.h"
#include "kernel/event.h"
#include "kernel/mouse.h"
#include "graphics/screen.h"
#include "workspace/workspace.h"

#define NTPServer "pool.ntp.org"

static const char *magicRebootString = "DEADC0DE";

static Kernel *staticThis = nullptr;

Kernel::Kernel():
	fps(0.0),
	irq(CInterruptSystem::Get()),
	systemTimer(irq),
	debugPort(irq, true, 0),
	log(LogDebug, 0, false),
	usb(irq, &systemTimer, true /* Enable hotplug */),
	mmc(irq, &systemTimer, &activityLED),
	mouse(nullptr),
	keyboard(nullptr),
	dns(&net),
	ntp(&net),
	sound(irq),
	mousePosition(0, 0),
	multicore(CMemorySystem::Get())
{ 
	staticThis = this;
}

method Kernel::initialize() -> Bool {

	systemTimer.Initialize();
	
	debugPort.Initialize(115200);

	debugPort.RegisterMagicReceivedHandler(magicRebootString, Kernel::magicRebootStringHandler);

	log.Initialize(&debugPort);

	log.Write ("Kernel", LogNotice, VersionString());
	log.Write ("Kernel", LogNotice, "Built at " __TIME__ ", " __DATE__ "." );

	usb.Initialize();

	mmc.Initialize();

	// Mount file system
	if (f_mount(&fatfs, "SD:", 1) != FR_OK) {
		log.Write("Kernel", LogPanic, "Cannot mount drive SD:");
	} else {
		log.Write("Kernel", LogNotice, "Mounted drive SD:");
	}

	net.Initialize();

	ntpd = new CNTPDaemon(NTPServer, &net);
	
	screen = make_unique<Screen>(kernelOptions.GetWidth(), kernelOptions.GetHeight());

	screen->initialize();

	screen->clear();

	workspace = make_unique<Workspace>();

	return true;
}

method Kernel::magicRebootStringHandler() -> Void {
	reboot();
}

method Kernel::updateUSB() -> Void {

	if (usb.UpdatePlugAndPlay()) {
	
		if (mouse == nullptr) {
			mouse = dynamic_cast<CMouseDevice *>(deviceNameService.GetDevice("mouse1", FALSE));
			if (mouse != nullptr) {
				mouse->RegisterRemovedHandler(mouseRemovedHandler);
				mouse->RegisterStatusHandler(Mouse::statusHandler);
				mouse->Setup(kernelOptions.GetWidth(), kernelOptions.GetHeight());
				mouse->SetCursor(kernelOptions.GetWidth()/2, kernelOptions.GetHeight()/2);
				mouse->ShowCursor(false);
			}
		}

		if (keyboard == nullptr) {
			keyboard = dynamic_cast<CUSBKeyboardDevice *>(deviceNameService.GetDevice("ukbd1", FALSE));
			if (keyboard != nullptr) {
				keyboard->RegisterRemovedHandler(keyboardRemovedHandler);
				keyboard->RegisterShutdownHandler(shutdownHandler);
				keyboard->RegisterKeyPressedHandler(keyPressedHandler);
			}
		}

		for (Int pad = 0; pad < MAX_GAMEPADS; pad += 1) {
			if (gamePad[pad] != nullptr) {
				continue;
			}

			gamePad[pad] = dynamic_cast<CUSBGamePadDevice *>(deviceNameService.GetDevice ("upad", pad, FALSE));
			
			if (gamePad[pad] == nullptr) {
				continue;
			}

			gamePad[pad]->RegisterRemovedHandler(gamePadRemovedHandler, this);
			gamePad[pad]->RegisterStatusHandler(gamePadStatusHandler);
		}
	}

	if (mouse != nullptr) {
		mouse->UpdateCursor();
	}

	if (keyboard != nullptr) {
		keyboard->UpdateLEDs();
	}
}

method Kernel::mouseRemovedHandler(CDevice *pDevice, void *pContext) -> Void {
	staticThis->mouse = nullptr;
}

method Kernel::keyboardRemovedHandler(CDevice *pDevice, void *pContext) -> Void {
	staticThis->keyboard = nullptr;
}

method Kernel::shutdownHandler() -> Void { 
	halt();
}

method Kernel::keyPressedHandler(const char *str) -> Void {
	staticThis->log.Write("Keyboard", LogDebug, str);
}

method Kernel::gamePadStatusHandler(unsigned pad, const TGamePadState *state) -> Void {

}

method Kernel::gamePadRemovedHandler(CDevice *pad, void *context) -> Void {
	for (unsigned i = 0; i < MAX_GAMEPADS; i += 1) {
		if (staticThis->gamePad[i] == dynamic_cast<CUSBGamePadDevice *>(pad)) {
			staticThis->gamePad[i] = nullptr;
			break;
		}
	}
}

method Kernel::run() -> ShutdownMode {

	using enum Kernel::ShutdownMode;

	CCPUThrottle::Get()->SetSpeed(CPUSpeedMaximum);

	multicore.Initialize();

	new FPSMonitor();

	multicore.Run(0);

	return Halt;
}

Kernel::FPSMonitor::FPSMonitor() {}

Kernel::FPSMonitor::~FPSMonitor() {}

method Kernel::FPSMonitor::Run() -> Void {
	SetName("FPS Monitor");
	while (true) {
		kernel->fps = screen->fpsCounter;
		screen->fpsCounter = 0.0;
		workspace->fps = workspace->fpsCounter;
		workspace->fpsCounter = 0.0;
		workspace->ups = workspace->upsCounter;
		workspace->upsCounter = 0.0;
		workspace->setDirtyFlag();
		CScheduler::Get()->Sleep(1);
	}
}

Kernel::Multicore::Multicore(CMemorySystem *memory):
	CMultiCoreSupport (memory)
{}

Kernel::Multicore::~Multicore() {}

method Kernel::Multicore::Run(UInt32 core_id) -> Void {

    switch (core_id) {
	case 0: {
			while (true) {
				kernel->updateUSB();
				CCPUThrottle::Get()->Update();
				workspace->update();
				workspace->draw();
				CScheduler::Get()->Yield();
			}
		}
		break;
    case 1: {
            while (true) {
		        screen->updateDisplay();
            }
        }
        break;
    case 2: 
        while (true) {
            // This is where sprites and tiles and audio happen (maybe?)
        }
        break;
    case 3: 
        while (true) {
            // This is where user code will run (maybe?)
        }
        break;
    default:
        break;
    }
}