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

// originally malloc'd in memcard.c
class unk_405C90 {
private:
    std::uint8_t pad00[0x1D80];

public:
    unk_405C90() {
        MC2_CALL_MEMBER<0x00405C90, void>(this);
    }

    void sub_4064E0() {
        MC2_CALL_MEMBER<0x004064E0, void>(this);
    }
};
static_assert(sizeof(unk_405C90) == 0x1D80, "Wrong size for unk_405C90");

extern unk_405C90 *(&glo_692EB4);
inline unk_405C90 *sub_405D50() {
    assert(glo_692EB4 == nullptr);
    return glo_692EB4 = new unk_405C90;
}
