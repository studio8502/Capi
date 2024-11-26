// kernel.cpp
//
// Copyright © 2024 Kyle J Cardoza, Studio 8502 <Kyle.Cardoza@icloud.com>
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

#include "kernel.h"

#include <circle/startup.h>
#include <circle/synchronize.h>
#include <cstring>
#include <string>
#include <memory>

#include "graphics/geometry.h"
#include "workspace/workspace.h"
#include "workspace/window.h"
#include "graphics/palette.h"
#include "graphics/paragraph_style.h"
#include "graphics/ui_font.h"

#define NTPServer "pool.ntp.org"

using std::make_shared;

static const char *magicRebootString = "DEADC0DE";

static Kernel *staticThis = nullptr;

Kernel::Kernel():
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
	screen(kernelOptions.GetWidth(), kernelOptions.GetHeight())
{ 
	staticThis = this;
}

method Kernel::initialize() -> Bool {

	activityLED.Blink(5);

	systemTimer.Initialize();
	
	debugPort.Initialize(115200);

	debugPort.RegisterMagicReceivedHandler(magicRebootString, Kernel::magicRebootStringHandler);

	log.Initialize(&debugPort);

	usb.Initialize();

	mmc.Initialize();

	net.Initialize();

	ntpd = new CNTPDaemon(NTPServer, &net);

	screen.initialize();

	workspace = new Workspace();

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
				mouse->RegisterEventHandler(mouseEventHandler);
				mouse->Setup(kernelOptions.GetWidth(), kernelOptions.GetHeight());
				mouse->SetCursor(kernelOptions.GetWidth()/2, kernelOptions.GetHeight()/2);
				mouse->ShowCursor(true);
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

method Kernel::mouseEventHandler(TMouseEvent Event, unsigned nButtons, unsigned nPosX, unsigned nPosY, int nWheelMove) -> Void {
	switch (Event) {
	case MouseEventMouseMove:
		staticThis->mousePosition.x = nPosX;
		staticThis->mousePosition.y = nPosY;
		staticThis->mousebuttons = nButtons;
		staticThis->mouseScroll = nWheelMove;
		break;
	default:
		break;
	}
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

	log.Write ("Kernel", LogNotice, "Compiled on: " __DATE__ " at " __TIME__);

	// Mount file system
	if (f_mount(&fatfs, "SD:", 1) != FR_OK) {
		log.Write("Kernel", LogPanic, "Cannot mount drive SD:");
	} else {
		log.Write("Kernel", LogNotice, "Mounted drive SD:");
	}

	deviceNameService.ListDevices(auto(&debugPort));
		
	new CPUMonitor();

	taskScheduler.ListTasks(&debugPort);

	var win = make_shared<Window>();

	var testRect = Rect(-20, -10, 200, 800);

	char message[256];

	Int64 counter = 0;

	while (true) {
		updateUSB();

		screen.acquire();

		screen.clear(DefaultPalette, 50);

		win->draw();

		testRect.x = 100;
		testRect.y = 100;
		testRect.width = 500;
		testRect.height = 200;

		win->drawRect(testRect, true, DefaultPalette, 28);

		var origin = Point(50, 75);
		win->drawCircle(origin, 94, true, DefaultPalette, 87);
		win->drawCircle(origin, 90, true, DefaultPalette, 86);

		origin.x += 100;
		var end = Point(270, 500);
		win->drawLine(origin, end, DefaultPalette, 130);
		origin.y -= 1;
		end.y -= 1;
		win->drawLine(origin, end, DefaultPalette, 130);
		origin.y -= 1;
		end.y -= 1;
		win->drawLine(origin, end, DefaultPalette, 130);

		testRect.x = 50;
		testRect.y = 50;
		testRect.width = 200;
		testRect.height = 200;

		win->drawRect(testRect, true, DefaultPalette, 40, 127);

		var clip = Rect(300, 100, 500, 56);
		var font = make_shared<UIFont>(Font::Size::xxLarge, Font::Weight::bold);
		var style = make_shared<ParagraphStyle>(font, 0, 0);
		sprintf(message, "%lu", counter += 1);
		workspace->drawText(message, style, Point(300, 100), clip);

		screen.release();

		screen.updateDisplay();

		CScheduler::Get()->Yield();
	}

	return Halt;
}

Kernel::CPUMonitor::CPUMonitor() {

}

Kernel::CPUMonitor::~CPUMonitor() {

}

method Kernel::CPUMonitor::Run() -> Void {

	SetName("CPU Monitor");

	CCPUThrottle::Get()->SetSpeed(CPUSpeedMaximum);
	
	while (true) {
		unsigned temp = CCPUThrottle::Get()->GetClockRate() / 1000000;
		CLogger::Get()->Write("CPU Monitor", LogNotice, "Clock rate: %uMHz\n", temp);

		if (temp == 0) {
			CCPUThrottle::Get()->SetSpeed (CPUSpeedLow);

			CLogger::Get()->Write("CPU Monitor", LogPanic, "Cannot get SoC temperature");
		}

		if (CCPUThrottle::Get()->Update() == false) {
			CCPUThrottle::Get()->SetSpeed (CPUSpeedLow);
			CLogger::Get()->Write("CPU Monitor", LogPanic, "CPU temperature management failed");
		}

		CScheduler::Get()->Sleep(2);
	}
}