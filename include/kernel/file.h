/*
 ╔═══════════════════════════════════════════════════════════════════════════╗
 ║ file.h                                                                    ║
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

#include "capi.h"

using FileData = unsigned char *;

class File {
public:

    enum class Mode {
        read = FA_READ,                 // Specifies read access to the file. Data 
                                        // can be read from the file.
        write = FA_WRITE,	            // Specifies write access to the file. Data 
                                        // can be written to the file.
        readWrite = FA_WRITE | FA_READ, // Combines read and write access to the file.
                                        //
        openExisting = FA_OPEN_EXISTING,// Opens the file. The function fails if the 
                                        // file doesn't exist.
        truncate = FA_CREATE_ALWAYS,    // Creates a new file. If the file exists,
                                        // the file is truncated and overwritten.
        create = FA_CREATE_NEW,	        // Creates a new file. The function fails if 
                                        // the file already exists.
        openAlways = FA_OPEN_ALWAYS,    // Opens the file. If it is not exist, a new
                                        // file is created.
        append = FA_OPEN_APPEND	        // Same as FA_OPEN_ALWAYS except the read/write 
                                        // pointer is set end of the file.
    };

    File(String path);

    ~File();

    method isOpen() -> Bool;

    method open(Mode mode = Mode::openExisting) -> Void;

    method close() -> Void;

    method mode() -> Mode;

    method size() -> UInt64;

    method seek(UInt64 offset) -> Void;

    // Copy the entire file into a memory buffer, and return a pointer to it.
    // It is the caller's responsibility to free the resulting buffer.
    method dump() -> FileData;

private:
    String _path;
    Mode _mode;
    Bool _isOpen;
    FIL file;
    FILINFO fileInfo;
    FRESULT status;
};

inline File::Mode operator | (File::Mode lhs, File::Mode rhs);

inline File::Mode operator |= (File::Mode& lhs, File::Mode rhs);