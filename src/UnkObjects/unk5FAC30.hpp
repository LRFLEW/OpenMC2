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

class unk_5FAC30 {
private:
    std::uint8_t pad00[0x184];

public:
    unk_5FAC30() {
        MC2_CALL_MEMBER<0x005FAC30, void>(this);
    }

    void sub_419DB0() {
        return MC2_CALL_MEMBER<0x00419DB0, void>(this);
    }
};
static_assert(sizeof(unk_5FAC30) == 0x184, "Wrong size for unk_5FAC30");

inline unk_5FAC30 *sub_5ED990() {
    return new unk_5FAC30;
}

extern MC2_PROC_PTR<void, unk_5FAC30 *> sub_5F23A0;

extern unk_5FAC30 *&glo_858378;
extern unk_5FAC30 *&glo_858394;
