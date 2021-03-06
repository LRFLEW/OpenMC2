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

#include "mcGame.hpp"
#include "Config.hpp"
#include "Logging.hpp"
#include "mcGameState.hpp"
#include "mcLayerMgr.hpp"

#include "UnkObjects/unk405630.hpp"
#include "UnkObjects/unk405C90.hpp"
#include "UnkObjects/unk406950.hpp"
#include "UnkObjects/unk4094A0.hpp"
#include "UnkObjects/unk412280.hpp"
#include "UnkObjects/unk419D20.hpp"
#include "UnkObjects/unk41FB40.hpp"
#include "UnkObjects/unk421350.hpp"
#include "UnkObjects/unk467180.hpp"
#include "UnkObjects/unk477E80.hpp"
#include "UnkObjects/unk4788D0.hpp"
#include "UnkObjects/unk47C830.hpp"
#include "UnkObjects/unk482C30.hpp"
#include "UnkObjects/unk498A90.hpp"
#include "UnkObjects/unk4A9E30.hpp"
#include "UnkObjects/unk4CE870.hpp"
#include "UnkObjects/unk4E8B70.hpp"
#include "UnkObjects/unk4E9480.hpp"
#include "UnkObjects/unk4FAE70.hpp"
#include "UnkObjects/unk503110.hpp"
#include "UnkObjects/unk504CE0.hpp"
#include "UnkObjects/unk5187E0.hpp"
#include "UnkObjects/unk52AA80.hpp"
#include "UnkObjects/unk53C670.hpp"
#include "UnkObjects/unk53C9E0.hpp"
#include "UnkObjects/unk540EB0.hpp"
#include "UnkObjects/unk5769E0.hpp"
#include "UnkObjects/unk577F00.hpp"
#include "UnkObjects/unk57DC70.hpp"
#include "UnkObjects/unk580A00.hpp"
#include "UnkObjects/unk5FAC30.hpp"
#include "UnkObjects/unk611C60.hpp"
#include "UnkObjects/unk612850.hpp"
#include "UnkObjects/unk6144B0.hpp"
#include "UnkObjects/unk6633B0.hpp"

#include <timeapi.h>

constexpr DWORD disclaimer_time = 5000;

// mc2: 0x0062D530
const mcGame_p::vtable_t mcGame_p::vtable_values = {
    &mcGame_p::scalar_deleter,
};

static void call_glo_6CE2E4_vir10() {
    glo_6CE2E4->vir10();
}

void mcGame_p::sub_401860() {
    glo_675024 = false;
    sub_53DE60();
    sub_53C6B0();
    sub_405D50();

    if (sub_612E10("nooverframe")) glo_662284 = false;
    if (sub_612E10("drawnothing")) glo_692E6C = true;
    sub_52B6C0(!sub_612E10("noaudio"));
    unk_614400 var10(&call_glo_6CE2E4_vir10);
    glo_860618.sub_6144D0(&var10);
    sub_4069B0();
    glo_6C50F0.unk02 = false;
    glo_6C50F0.sub_6126E0(0xD3);
    sub_4CEB00(0x13);
    sub_5670D0(nullptr);
    this->unk04 = false;

    sub_53C9E0();
    sub_479100();
    sub_477EF0();
    sub_482C60();

    sub_40E240();
    glo_8582A8 = 0;
    glo_6745C0 = 0;
    glo_8582C4 = "popup";
    sub_57E250();
    glo_675028 = glo_662288;
}

static void sub_506CF0() {
    glo_6A04BC = 0;
    glo_6A04B4 = 0;
}

// mc2: 0x00402120
void mcGame_p::Execute() {
    mc2_log_display("mcGame:Execute - kDebugLevel %d", 0); // macro kDebugLevel?
    unk_611C60 timer;
    bool stop = false;

    do {
        glo_6C3890->vir08();
        timer.fetch_time();
        glo_692EB4->sub_4064E0();

        switch (glo_6C3890->get_gamestate()) {
        case GameState::Boot:
            mc2_log_display("Welcome to the boot state.");
            glo_6C3890->vir04(17);
            break;

        case GameState::Game:
        case GameState::Replay:
            sub_5ECFD0();
            this->sub_401960();
            this->Update();
            sub_5ED000();

            if  (glo_858384 & 2) {
                Sleep(30); // near-30 fps cap?
                if (glo_858384 & 2) sub_506CF0();
                glo_6CE2E4->set_unk51_1();
                glo_6CE2E4->vir10();
                glo_692EB0->sub_405360();
                if (glo_6C3890->unk0A != 0) {
                    this->sub_401960();
                    this->Update();
                    glo_692EB0->sub_405360();
                }
            } else {
                sub_5ED050(0);
                this->sub_4019C0();
                glo_692EB0->sub_405360();
                if (glo_6C3890->unk0A != 0) {
                    this->sub_401960();
                    this->Update();
                    glo_692EB0->sub_405360();
                }
                sub_5ED0C0();
            }
            break;

        case GameState::Movie:
            glo_6957BC->sub_420EA0();
            if (glo_6957BC != nullptr && glo_6957BC->unk1C == 0) {
                sub_5ED9C0();
                sub_5EF3F0();
                sub_5EF420(3, 0xFF000000, 1.0f, 0);
                if (glo_6957BC != nullptr) glo_6957BC->sub_421050();
                sub_5F0F00();
            } else {
                glo_6C3890->vir04(16);
            }
            break;

        case GameState::FrontEnd:
        {
            if (glo_6622B0 && !startup_config.fast_disclaimer) {
                std::uint32_t esi = timeGetTime() - glo_692E90;
                if (esi < disclaimer_time) Sleep(disclaimer_time - esi);
            }
            glo_6622B0 = false;

            unk_41FB40 *esi = glo_692E88->get6().unk14;
            sub_5ECFD0();
            sub_613FC0();
            if (glo_8582DC == 4) {
                glo_6C38B4->vir58();
            }
            esi->sub_420B70();
            sub_5ED000();
            if (glo_858384 & 2) {
                Sleep(30);
                glo_6CE2E4->set_unk51_1();
                glo_6CE2E4->vir10();
            } else {
                sub_5ED050(0);
                esi->sub_41A960();
                sub_5ED0C0();
            }
            break;
        }

        case GameState::RaceEditor:
            sub_5ECFD0();
            sub_613FC0();
            glo_6956DC->sub_4158F0();
            sub_5ED000();
            if (glo_858384 & 2) {
                Sleep(30);
                glo_6CE2E4->set_unk51_1();
                glo_6CE2E4->vir10();
            } else {
                sub_5ED050(0);
                sub_5F23A0(glo_858378);
                sub_5EF420(3, glo_674F9C, 1.0f, 0);
                glo_6956DC->sub_4155D0();
                sub_5ED0C0();
            }
            break;

        case GameState::CarViewer:
            sub_613FC0();
            sub_5ED4A0(1);
            glo_695760->sub_419980();
            glo_695760->sub_419CA0();
            sub_5ED000();
            sub_5ED0C0();
            Sleep(10);
            break;

        case GameState::Quit:
            stop = true;
            sub_5ED4A0(1);
            sub_5ED000();
            sub_5ED0C0();
            sub_5ED4A0(0);
            sub_5ED000();
            sub_5ED0C0();
            break;

        default:
            mc2_log_quit("Invalid State");
            break;
        }

        if (glo_6C3890->get_gamestate() == GameState::Replay) {
            while (timer.get_delta_seconds() < 0.33) {
                if ((glo_6797CC - timer.get_delta_seconds()) / glo_6797CC <= 0.25f) break;
                Sleep(1);
            }
        }

    } while (!stop && !sub_5ED220());
}

// mc2: 0x00401CB0
void mcGame_p::Update() {
    if (glo_6622BC > 2) {
        mc2_log_print("mcGame:Update - pre-update heap sanity check...");
        global_primary_unk5769E0->sub_576210();
        mc2_log_display("done");
    }
    if (glo_6C3890->unk09 == 0) sub_613FC0();
    sub_5F1D80(glo_6C3890->unk09 == 0 ? glo_6797CC : 0.0f);

    if (glo_6C3890->unk09 == 0 && glo_697B88 != nullptr && (glo_6C38B4->unk08 < 0 || glo_6C38B4->unk74 == 5)) {
        glo_6C8EEC->sub_584FB0();
        glo_6968B0->sub_4782D0();
        glo_6968AC->sub_477A50();
        glo_69585C->sub_4673B0();
        glo_69C868->sub_503F30();
        sub_509000();
        glo_697B88->sub_47C7A0();
        glo_69C7D0->sub_4FBAA0();
        glo_69947C->sub_4E84D0();
        glo_699498->sub_4E9260();
        if (glo_6C38B8 != nullptr) glo_6C38B8->sub_541280();
        glo_698624->sub_4A9F30();
        sub_4AA890();
        glo_6C263C->sub_517AB0();
        glo_6C5304->sub_578000();
        glo_69C858->sub_5031F0();
        if (glo_692E6C == 0) sub_505EF0();
    } else {
        glo_69585C->sub_4673B0();
        if (glo_697B88 != nullptr) glo_697B88->sub_47C7A0();
    }

    if (glo_6984B4 != nullptr) glo_6984B4->sub_498760();
    sub_417FD0();
    if (glo_6622BC > 3) {
        mc2_log_print("mcGame:Update - post-update heap sanity check...");
        global_primary_unk5769E0->sub_576210();
        mc2_log_display("done");
    }
}

MC2_DEF_PROC(sub_4069B0, 0x004069B0);
MC2_DEF_PROC(sub_40E240, 0x0040E240);
MC2_DEF_PROC(sub_417FD0, 0x00417FD0);
MC2_DEF_PROC(sub_4AA890, 0x004AA890);
MC2_DEF_PROC(sub_505EF0, 0x00505EF0);
MC2_DEF_PROC(sub_509000, 0x00509000);
MC2_DEF_PROC(sub_5670D0, 0x005670D0);
MC2_DEF_PROC(sub_5D36D0, 0x005D36D0);
MC2_DEF_PROC(sub_5ECFD0, 0x005ECFD0);
MC2_DEF_PROC(sub_5ED000, 0x005ED000);
MC2_DEF_PROC(sub_5ED050, 0x005ED050);
MC2_DEF_PROC(sub_5ED0C0, 0x005ED0C0);
MC2_DEF_PROC(sub_5ED220, 0x005ED220);
MC2_DEF_PROC(sub_5ED4A0, 0x005ED4A0);
MC2_DEF_PROC(sub_5ED9C0, 0x005ED9C0);
MC2_DEF_PROC(sub_5EF3F0, 0x005EF3F0);
MC2_DEF_PROC(sub_5EF420, 0x005EF420);
MC2_DEF_PROC(sub_5F0F00, 0x005F0F00);
MC2_DEF_PROC(sub_5F1D80, 0x005F1D80);
MC2_DEF_PROC(sub_613FC0, 0x00613FC0);

MC2_DEF_GLOBAL(glo_662284, 0x00662284);
MC2_DEF_GLOBAL(glo_662288, 0x00662288);
MC2_DEF_GLOBAL(glo_6622B0, 0x006622B0);
MC2_DEF_GLOBAL(glo_6745C0, 0x006745C0);
MC2_DEF_GLOBAL(glo_674F9C, 0x00674F9C);
MC2_DEF_GLOBAL(glo_675024, 0x00675024);
MC2_DEF_GLOBAL(glo_675028, 0x00675028);
MC2_DEF_GLOBAL(glo_6797CC, 0x006797CC);
MC2_DEF_GLOBAL(glo_692E6C, 0x00692E6C);
MC2_DEF_GLOBAL(glo_692E7C, 0x00692E7C);
MC2_DEF_GLOBAL(glo_692E90, 0x00692E90);
MC2_DEF_GLOBAL(glo_6A04B4, 0x006A04B4);
MC2_DEF_GLOBAL(glo_6A04BC, 0x006A04BC);

MC2_DEF_GLOBAL(glo_8582A8, 0x008582A8);
MC2_DEF_GLOBAL(glo_8582C4, 0x008582C4);
MC2_DEF_GLOBAL(glo_8582DC, 0x008582DC);
MC2_DEF_GLOBAL(glo_858384, 0x00858384);
