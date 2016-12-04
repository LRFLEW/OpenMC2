/**********************************************************************
* OpenMC2 - An Open Source Re-Implementation of Midnight Club 2
* Copyright (C) 2016  LRFLEW
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
**********************************************************************/
#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include "Game.hpp"
#include "FileHandler.hpp"
#include "Logging.hpp"

void FileHandler::sub_617FB0(){
    if (this->unk_14 == 0 &&
        this->unk_10 != 0) {
        sub_617AF0();
    }

    this->file_funcs->close_file(this->handle);
    this->handle = INVALID_HANDLE_VALUE;
    this->file_funcs = nullptr;
}

// mc2: 0x00618050
void sub_618050(FileHandler *a, const char *format, ...) {
    char buffer[0x400];
    va_list ap;
    va_start(ap, format);
    size_t len = std::vsnprintf(buffer, 0x400, format, ap);
    a->sub_617E40(buffer, max(len, (size_t) 0));
    va_end(ap);
}

// mc2: 0x00617BB0
FileHandler *register_file_handle(char * path, HANDLE file, unk_679810_funcTable * fileFuncs) {
    int32_t i = 0;
    FileHandler *freeHandle = glo_FileHandles;

    do {
        if (freeHandle->file_funcs == nullptr) {
            freeHandle->unk_0C = 0;
            freeHandle->unk_10 = 0;
            freeHandle->unk_14 = 0;
            freeHandle->handle = file;
            freeHandle->buffer_size = 0x1000;
            freeHandle->text_buffer = glo_FileHandle_TextBuffer[i];
            freeHandle->file_funcs = fileFuncs;
            if (i > glo_679818) {
                glo_679818 = i;
            }
            return freeHandle;
        }
        ++i;
    } while (++freeHandle < glo_FileHandles_end);

    sub_617AA0();
    mc2_log_error("Out of file handles.");
    return nullptr;
}