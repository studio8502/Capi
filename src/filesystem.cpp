/*****************************************************************************
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ filesystem.cpp                                                            ║
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

#include "filesystem.h"

function Filesystem::readFile(String path, UInt *length) -> FileData {
    FileData data;
    FIL file;
    FILINFO fileInfo;
    UInt bytesRead;
    FRESULT status;
    
    status = f_stat(path.c_str(), &fileInfo);
    if (status != FR_OK) {
        CLogger::Get()->Write("Filesystem", LogNotice, "Failed to stat file!");
        *length = 0;
        return nullptr;
    }
    
    *length = fileInfo.fsize;

    data = (FileData) malloc(*length + 1);

    status = f_open(&file, path.c_str(), FA_READ);
    if (status != FR_OK) {
        CLogger::Get()->Write("Filesystem", LogNotice, "Failed to open file!");
        *length = 0;
        return nullptr;
    }

    status = f_read(&file, data, *length, &bytesRead);
    if (status != FR_OK) {
        CLogger::Get()->Write("Filesystem", LogNotice, "Failed to read file!");
        *length = 0;
        return nullptr;
    }

    return data;
}
