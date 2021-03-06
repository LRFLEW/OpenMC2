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

#pragma once

#include "Addresses.hpp"

#include <array>

// size: 0x1C
class FileHandler {
public:
    enum Seek {
        SeekStart = 0,
        SeekCurrent = 1,
        SeekEnd = 2,
    };

    struct FuncTable {
        MC2_PROC_PTR<HANDLE, const char *, bool> open_file; // 0x00
        MC2_PROC_PTR<HANDLE, const char *> sub_04;
        MC2_PROC_PTR<std::int32_t, HANDLE, void *, std::int32_t> read; // 0x08
        MC2_PROC_PTR<std::int32_t, HANDLE, const void *, std::int32_t> write; // 0x0C
        MC2_PROC_PTR<std::int32_t, HANDLE, std::int32_t, Seek> seek; // 0x10
        MC2_PROC_PTR<void, HANDLE> close_file; // 0x14
        MC2_PROC_PTR<void> sub_18;
        MC2_PROC_PTR<std::int32_t, HANDLE> get_size; // 0x1C
        MC2_PROC_PTR<std::int32_t, HANDLE> sub_20;
        MC2_PROC_PTR<bool> sub_24;
    };

    FuncTable *file_funcs; // 0x00
    HANDLE handle; // 0x04
    char *buffer; //0x08
    std::int32_t seek_pos; // 0x0C
    std::int32_t buffer_offset; // 0x10
    std::int32_t buffer_read; // 0x14
    std::int32_t buffer_size; // 0x18

    void sub_617FB0();

    // mc2: 0x00617AF0
    std::int32_t flush();

    // mc2: 0x00617E40
    std::int32_t write(const void *data, std::int32_t size);
    // mc2: 0x00617F40
    std::int32_t put_char(char c) {
        return write(&c, 1) == 1 ? c : -1;
    }

    // mc2: 0x00617D20
    std::int32_t read(void *data, std::int32_t size);
    template<class T>
    std::int32_t read(T &value) {
        return read(&value, static_cast<std::int32_t>(sizeof(T)));
    }
    template<class T>
    std::int32_t read_array(T *array, size_t count) {
        return read(array, static_cast<std::int32_t>(count * sizeof(T)));
    }

    // mc2: 0x00617F60
    std::int32_t seek(std::int32_t offset);

    std::int32_t skip(std::int32_t count);

    // mc2: 0x00617FF0
    std::int32_t size();
};

FileHandler *sub_617CA0(char *path);
FileHandler *sub_617CD0(const char *, FileHandler::FuncTable *, bool);
void sub_618050(FileHandler *a, const char *format, ...);

// mc2: 0x00617BB0
FileHandler *register_file_handle(const char * path, HANDLE file, FileHandler::FuncTable * fileFuncs);

extern MC2_PROC_PTR<void> sub_617AA0;

extern std::array<FileHandler, 12> &glo_FileHandles;
extern std::array<char[0x1000], 12> &glo_FileHandle_TextBuffer;
extern FileHandler *&glo_86D28C;
extern std::int32_t &glo_679818;

extern FileHandler::FuncTable *&glo_679810;
extern FileHandler::FuncTable *&glo_679814;
extern FileHandler::FuncTable *&glo_692E1C;
extern FileHandler::FuncTable *&glo_85D1C8;

extern FileHandler::FuncTable &glo_6781C0;
extern FileHandler::FuncTable &glo_679884;
extern FileHandler::FuncTable &glo_692E20;
