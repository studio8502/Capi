---
generator: doxide
---


# mouse.h



<style>
.linenodiv pre span {padding-left:4px;padding-right:4px}
</style>

```cpp linenums="1"
/*
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ mouse.h                                                                   ║
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

class Mouse {
public: 

    Mouse();

    ~Mouse();

    static method statusHandler(UInt buttons, 
                                Int deltaX, 
                                Int deltaY, 
                                Int deltaW) -> Void;

    Bool leftButtonDown;
    Bool middleButtonDown;
    Bool rightButtonDown;
};

extern Mouse *mouse;
```

