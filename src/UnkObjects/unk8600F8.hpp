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

#include <cstdint>

struct unk_612150 {
    std::uint32_t count;
    char **args;
};

class unk_8600F8 {
private:
    std::uint8_t pad00[0x14];
    unk_8600F8 *unk14;

public:
    void loc_611DC0();
    void sub_612150(const char *a, unk_612150 *b);
    std::int32_t sub_6124A0(const char *a);
};
