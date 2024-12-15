---
generator: doxide
---


# kernel.h



<style>
.linenodiv pre span {padding-left:4px;padding-right:4px}
</style>

```cpp linenums="1"
/*
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
 */

#pragma once

#include "capi.h"
#include "graphics/geometry.h"
#include "graphics/screen.h"

#define MAX_GAMEPADS 8

/**
 * The kernel class is the core of Capi's OS. It manages hardware and interrupts, as
 * well as setting up the system at boot time.
*/
class Kernel
{
public:
	friend class Multicore;
	friend class FPSMonitor;
	friend class Workspace;

	/**
	 * An enumeration specifying the possible shutdown modes in Capi.
	 */
	enum class ShutdownMode
	{
		None,
		Halt,
		Reboot
	};

	/**
	 * A class implementing support for using all the cores of the Pi's CPU.
	 */
	class Multicore: public CMultiCoreSupport {
	public:

		Multicore(CMemorySystem *memory);

		~Multicore();

		method Run(UInt32 core_id) -> Void;

	private:
	};

	class FPSMonitor: CTask {
	public:
		FPSMonitor();
		~FPSMonitor();

		method Run() -> Void;
	};

	Double fps;

	/**
	 * Create the kernel instance. There should only ever be one active instance of this
     * class.
	 */
	Kernel();

	/**
	 * Initializes the kernel.
	 * 
	 * @return true for success, false for falure.
	 */
	method initialize() -> Bool;

	/**
	 * Updates the USB driver.
	 */
	method updateUSB() -> Void;

	/**
	 * Enters the kernel's main loop. This must be called after [Kernel::initialize()](#initialize).
	 * 
	 * @return The shutdown mode for the system.
	 */
	method run() -> ShutdownMode;

private:

	/**
	 * The method which handles the debug cable sending the "magic" string that causes a system
	 * reboot.;
	 */
	static method magicRebootStringHandler() -> Void;

	/**
	 * The method which handles the mouse being unplugged.
	 *
	 * @param pDevice A handle to the Circle CDevice intance for the mouse.
	 * @param pContext A pointer to a context structure holding internal data.
	 */
	static method mouseRemovedHandler(CDevice *pDevice, void *pContext) -> Void;

	/**
	 * The method which handles the keyboard being unplugged.
	 */
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

```

