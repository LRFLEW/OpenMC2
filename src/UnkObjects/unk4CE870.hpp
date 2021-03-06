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

// originally malloc'd in carmanager.c
class unk_4CE870 {
private:
    std::uint8_t pad00[0x98];

public:
    unk_4CE870(std::uint32_t arg1) {
        MC2_CALL_MEMBER<0x004CE870, void>(this, arg1);
    }
};
static_assert(sizeof(unk_4CE870) == 0x98, "Wrong size for unk_4CE870");

extern unk_4CE870 *(&glo_6C523C);
inline unk_4CE870 *sub_4CEB00(std::uint32_t arg1) {
    assert(glo_6C523C == nullptr);
    return glo_6C523C = new unk_4CE870(arg1);
}
