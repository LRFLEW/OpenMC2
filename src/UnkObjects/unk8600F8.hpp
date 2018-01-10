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

#include "../Addresses.hpp"

struct unk_612150 {
    std::uint32_t count = 0;
    char **args = nullptr;
};

class unk_8600F8 {
public:
    struct hash_map_entry {
        char *name;
        unk_612150 *value;
        hash_map_entry *next;
        
        hash_map_entry() = default;
        inline hash_map_entry(char *name, unk_612150 *value, hash_map_entry *next) :
            name(name), value(value), next(next) { }
    };

    struct indexed_map_entry {
        uint32_t index;
        char *name;
        unk_612150 *value;
    };

private:
    std::uint8_t pad00[0x2];
    std::uint8_t unk02;
    std::uint8_t unk03;
    std::uint8_t pad04[0x4];
    std::int32_t max_entries;  // 0x08
    std::int32_t num_entries;  // 0x0C
    hash_map_entry **entries;  // 0x10
    unk_8600F8 *unk14;

public:
    void loc_611DC0();
    
    hash_map_entry *sub_611DF0(const char *a, unk_612150 *b, hash_map_entry *unk_loc) {
        return mc2_call_proc_thiscall<0x0053ACB0, hash_map_entry *>(this, a, b, unk_loc);
    }

    bool sub_612150(const char *a, unk_612150 *b);
    // mc2: 0x00611E70
    uint32_t get_entry_index(const char *a);
    unk_612150* sub_6124A0(const char *a);

    void sub_6125A0(uint32_t new_max_entries) {
        return mc2_call_proc_thiscall<0x006125A0, void>(this, new_max_entries);
    }

    bool sub_611FE0(indexed_map_entry *eax);

    void sub_612050() {
        return mc2_call_proc_thiscall<0x00612050, void>(this);
    }

    bool sub_612020(indexed_map_entry *eax);

    hash_map_entry *unk_8600F8::sub_611F60(int32_t unk);
};

bool sub_612E10(const char *key);
bool sub_612E30(const char *key, std::uint32_t index, int32_t * decimal_value);

constexpr mc2_pointer<0x008600E8, unk_8600F8 *> loc_8600E8;
constexpr mc2_pointer<0x008600F8, unk_8600F8> loc_8600F8;
