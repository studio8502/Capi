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

#include "file.h"

inline File::Mode operator | (File::Mode lhs, File::Mode rhs)
{
    using T = std::underlying_type_t<File::Mode>;
    return static_cast<File::Mode>(static_cast<T>(lhs) | static_cast<T>(rhs));
}

inline File::Mode operator |= (File::Mode& lhs, File::Mode rhs)
{
    return lhs = lhs | rhs;
}

File::File(String path):
    _path(path),
    _isOpen(false)
{}

File::~File() {}

method File::isOpen() -> Bool {
    return _isOpen;
}

method File::open(Mode mode) -> Void {
    f_open(&file, _path.c_str(), (typeof(FA_READ)) mode);
    _isOpen = true;
    _mode = mode;
}

method File::close() -> Void {
    f_close(&file);
    _isOpen = false;
}

method File::mode() -> Mode {
    return _mode;
}

method File::size() -> UInt64 {
    f_stat(_path.c_str(), &fileInfo);
    return fileInfo.fsize;
}

method File::seek(UInt64 offset) -> Void {
    f_lseek(&file, 0);
}

method File::dump() -> FileData {
    var data = (FileData) malloc(size() + 1);
    var idx = f_tell(&file);
    var bytesRead = 0u;
    
    seek(0);

    status = f_read(&file, data, size(), &bytesRead);
    if (status != FR_OK) {
        CLogger::Get()->Write("Filesystem", LogNotice, "Failed to read file!");
        return nullptr;
    }

    seek(idx);

    return data;
}