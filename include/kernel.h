/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ kernel.h                                                                  ║
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

#pragma once

#include "capi.h"
#include "graphics/geometry.h"
#include "graphics/screen.h"
#include "multicore.h"

#define MAX_GAMEPADS 8

class Kernel
{
public:
	friend class Multicore;
	friend class FPSMonitor;

	enum class ShutdownMode
	{
		None,
		Halt,
		Reboot
	};

	class CPUMonitor: CTask {
	public:
		CPUMonitor();
		~CPUMonitor();

		method Run() -> Void;
	};

	class USBPNPMonitor: CTask {
	public:
		USBPNPMonitor();
		~USBPNPMonitor();

		method Run() -> Void;
	};

	class FPSMonitor: CTask {
	public:
		FPSMonitor();
		~FPSMonitor();

		method Run() -> Void;
	};

	Double fps;

	Kernel();

	method initialize() -> Bool;

	method updateUSB() -> Void;

	method run() -> ShutdownMode;

private:
	static method magicRebootStringHandler() -> Void;
	static method mouseRemovedHandler(CDevice *pDevice, void *pContext) -> Void;
	static method keyboardRemovedHandler(CDevice *pDevice, void *pContext) -> Void;
	static method gamePadRemovedHandler (CDevice *pad, void *context) -> Void;

	static method shutdownHandler() -> Void;

	static method mouseEventHandler(TMouseEvent Event, unsigned nButtons, unsigned nPosX, unsigned nPosY, int nWheelMove) -> Void;
	static method keyPressedHandler(const char *str) -> Void;
	static method gamePadStatusHandler (unsigned pad, const TGamePadState *state) -> Void;

	CActLED	activityLED;

	CKernelOptions kernelOptions;
	
	CDeviceNameService deviceNameService;
	
	CCPUThrottle cpuThrottle;
	
	CInterruptSystem *irq;
	
	CTimer systemTimer;
	
	CSerialDevice debugPort;
	
	CExceptionHandler exceptionhandler;
	
	CLogger log;
	
	CUSBHCIDevice usb;
	CEMMCDevice	mmc;
	FATFS fatfs;
	
	CMouseDevice* volatile mouse;
	CUSBKeyboardDevice* volatile keyboard;
	CUSBGamePadDevice* volatile gamePad[MAX_GAMEPADS];
	
	CScheduler taskScheduler;
	
	CNetSubSystem net;
	CDNSClient dns;
	CNTPClient ntp;
	CNTPDaemon *ntpd;
	
	CBcmRandomNumberGenerator rng;
	
	CHDMISoundBaseDevice sound;

	Point mousePosition;
	UInt16 mousebuttons;
	Int16 mouseScroll; 

	Multicore multicore;
};

extern Kernel *kernel;
