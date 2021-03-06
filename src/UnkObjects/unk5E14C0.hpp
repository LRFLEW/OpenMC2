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

#include "../Addresses.hpp"

class unk_5E14C0 {
private:
    std::uint32_t unk00 = 0;
    std::uint32_t unk04 = 0;
    std::uint32_t unk08 = 0;

public:
    void sub_5E1A80() {
        return MC2_CALL_MEMBER<0x005E1A80, void>(this);
    }

    bool sub_5E1500(const char *arg0, std::uint32_t arg1, std::uint32_t arg2, std::uint32_t arg3) {
        return MC2_CALL_MEMBER<0x005E1500, bool>(this, arg0, arg1, arg2, arg3);
    }
};

extern unk_5E14C0 &glo_8582C8;
