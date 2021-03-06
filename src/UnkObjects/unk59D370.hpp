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

class unk_59D370 {
private:

public:
    unk_59D370() {
        MC2_CALL_MEMBER<0x0059D370, void>(this);
    }

    // mc2: 0x0059F4B0
    ~unk_59D370() {
        MC2_CALL_MEMBER<0x0059F4B0, void>(this);
    }
};

extern unk_59D370 &glo_6C933C;
extern unk_59D370 &glo_6C93A8;
