/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ task.h                                                                    ║
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
#include "tina.h"

#define TASK_BUFFER_SIZE (256*1024)

// A Task is a class representing a coroutine. It is not necessary to subclass
// Task to use it; the constructor takes a lambda expression to use as the body
// of the task.
class Task {
public:
    using Context = tina *;

    using TaskBody = Void (*)(Context);

    Task(String name, 
         std::size_t bufSize = TASK_BUFFER_SIZE, 
         UnsafeMutablePointer userData = nullptr);

    ~Task();

    method completed() -> Bool;
    
    method resume() -> Void;

    method yield() -> Void;

private:
    static method funct(Context context, UnsafeMutablePointer value) -> UnsafeMutablePointer;

    String _name;
    TaskBody body;
    Context context;
    UnsafeMutablePointer buffer;
};
