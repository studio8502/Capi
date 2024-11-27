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

#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include <circle/actled.h>
#include <circle/interrupt.h>

#define method auto
#define var auto
#define let auto const

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

using ActivityLED = CActLED;

using InterruptSystem = CInterruptSystem;