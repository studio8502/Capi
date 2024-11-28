/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ capi.h                                                                    ║
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

#include <cmath>
#include <cstring>
#include <cstdint>
#include <string>
#include <memory>
#include <vector>

#include <circle/actled.h>
#include <circle/bcmrandom.h>
#include <circle/cputhrottle.h>
#include <circle/devicenameservice.h>
#include <circle/dmachannel.h>
#include <circle/exceptionhandler.h>
#include <circle/input/mouse.h>
#include <circle/interrupt.h>
#include <circle/koptions.h>
#include <circle/logger.h>
#include <circle/multicore.h>
#include <circle/net/dnsclient.h>
#include <circle/net/netsubsystem.h>
#include <circle/net/ntpclient.h>
#include <circle/net/ntpdaemon.h>
#include <circle/sched/scheduler.h>
#include <circle/sched/task.h>
#include <circle/screen.h>
#include <circle/serial.h>
#include <circle/sound/hdmisoundbasedevice.h>
#include <circle/spinlock.h>
#include <circle/startup.h>
#include <circle/usb/usbhcidevice.h>
#include <circle/usb/usbgamepad.h>
#include <circle/usb/usbkeyboard.h>
#include <SDCard/emmc.h>
#include <fatfs/ff.h>

#define method auto
#define function auto
#define var auto
#define let auto const

#define guard(STMT) if ((STMT)) {}

using Void = void;

using UnsafePointer = void const *;
using UnsafeMutablePointer = void *;

using Bool = boolean;

using UInt64 = uint64_t;
using UInt32 = uint32_t;
using UInt16 = uint16_t;
using UInt8 = uint8_t;
using UInt = uint32_t;

using Int64 = int64_t;
using Int32 = int32_t;
using Int16 = int16_t;
using Int8 = int8_t;
using Int = int32_t;

using Double = double;
using Single = float;

using String = std::string;

using std::shared_ptr;
using std::make_shared;

using std::unique_ptr;
using std::make_unique;
