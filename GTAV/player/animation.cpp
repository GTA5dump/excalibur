#include "pch.h"
#include "animation.h"
#include "features/manager/manager.h"
#include "menu/util/globals.h"
#include "gui/options/option.h"
#include "gui/util/panels.h"
#include "rage/classes/CPed.h"
#include "rage/classes/enums.h"

using namespace base::gui;
using namespace menu::player::animation::vars;

namespace menu::player::animation::vars {
	variables m_vars;

	struct animation_struct {
		const char* name;
		std::pair<const char*, const char*> values;
	};

	std::vector<animation_struct> sexual = {
		{ "Doggystyle 1", { "rcmpaparazzo_2", "shag_loop_poppy" } },
		{ "Doggystyle 2", { "rcmpaparazzo_2", "shag_loop_a" } },
		{ "Shaking Ass", { "switch@trevor@mocks_lapdance", "001443_01_trvs_28_idle_stripper" } },
		{ "Slow Humping", { "misscarsteal2pimpsex", "shagloop_pimp" } }
	};

	const char* sexualNames[] = {
		"Doggystyle 1",
		"Doggystyle 2",
		"Shaking Ass",
		"Slow Humping"
	};

	std::vector<animation_struct> animals = {
		{"Monkey", { "missfbi5ig_30monkeys", "monkey_b_freakout_loop" } },
		{"Chop Hump", { "missfra0_chop_find", "hump_loop_chop" } },
		{"Chop Swim", { "creatures@rottweiler@swim@", "swim" } }
	};

	const char* animalsNames[] = {
		"Monkey",
		"Chop Hump",
		"Chop Swim"
	};

	std::vector<animation_struct> actions = {
		{"Air Guitar", { "anim@mp_player_intcelebrationfemale@air_guitar", "air_guitar" } },
		{"Blow Kiss", { "anim@mp_player_intcelebrationfemale@blow_kiss", "blow_kiss" } },
		{"Bro Hug", { "anim@mp_player_intcelebrationpaired@f_m_bro_hug", "bro_hug_right" } },
		{"Challenge", { "misscommon@response", "face_palm" } },
		{"Face Palm", { "anim@mp_player_intcelebrationmale@face_palm", "" } },
		{"Finger", { "anim@mp_player_intcelebrationmale@finger", "finger" } },
		{"Hands Up", { "mp_pol_bust_out", "guard_handsup_loop" } },
		{"Hump Air", { "anim@mp_player_intcelebrationfemale@air_shagging", "air_shagging" } },
		{"Jazz Hands", { "anim@mp_player_intcelebrationmale@jazz_hands", "jazz_hands" } },
		{"Nose Pick", { "anim@mp_player_intcelebrationmale@nose_pick", "nose_pick" } },
		{"Photographer", { "anim@mp_player_intcelebrationmale@photography", "photography" } },
		{"Salute", { "anim@mp_player_intcelebrationmale@salute", "salute" } },
		{"Shush", { "anim@mp_player_intcelebrationmale@shush", "shush" } },
		{"Slow Clap", { "anim@mp_player_intcelebrationmale@slow_clap", "slow_clap" } },
		{"Smoke", { "anim@mp_player_intcelebrationmale@smoke_flick", "smoke_flick" } },
		{"Surrender", { "anim@mp_player_intcelebrationmale@surrender", "surrender" } },
		{"Synth", { "anim@mp_player_intcelebrationfemale@air_synth", "air_synth" } },
		{"Thumbs Up", { "anim@mp_player_intcelebrationmale@thumbs_up", "thumbs_up" } },
		{"Wank", { "mp_player_intwank", "mp_player_int_wank" } }
	};

	const char* actionsNames[] = {
	"Air Guitar",
	"Blow Kiss",
	"Bro Hug",
	"Challenge",
	"Face Palm",
	"Finger",
	"Hands Up",
	"Hump Air",
	"Jazz Hands",
	"Nose Pick",
	"Photographer",
	"Salute",
	"Shush",
	"Slow Clap",
	"Smoke",
	"Surrender",
	"Synth",
	"Thumbs Up",
	"Wank"
	};

	std::vector<animation_struct> dance = {
		{"Casual", { "rcmnigel1bnmt_1b", "dance_loop_tyler" } },
		{"Clown", { "rcm_barry2", "clown_idle_6" } },
		{"Pole", { "mini@strip_club@pole_dance@pole_dance3", "pd_dance_03" } },
		{"Private", { "mini@strip_club@private_dance@part2", "priv_dance_p2" } },
		{"Receive", { "mp_am_stripper", "lap_dance_player" } },
		{"Sexual", { "mini@strip_club@pole_dance@pole_a_2_stage", "pole_a_2_stage" } },
		{"Yacht", { "oddjobs@assassinate@multi@yachttarget@lapdance", "yacht_ld_f" } }
	};

	std::vector<animation_struct> misc = {
		{"Electrocute", { "ragdoll@human", "electrocute" } },
		{"Hover", { "swimming@base", "dive_idle" } },
		{"Jump", { "move_jump", "jump_launch_l_to_skydive" } },
		{"Meditate", { "rcmcollect_paperleadinout@", "meditiate_idle" } },
		{"Party", { "rcmfanatic1celebrate", "celebrate" } },
		{"Pissing", { "misscarsteal2peeing", "peeing_loop" } },
		{"Push Ups", { "rcmfanatic3", "ef_3_rcm_loop_maryann" } },
		{"Run", { "move_m@alien", "alien_run" } },
		{"Shitting", { "missfbi3ig_0", "shit_loop_trev" } },
		{"Showering", { "mp_safehouseshower@male@", "male_shower_idle_b" } },
		{"Swim", { "swimming@scuba", "dive_idle" } },
		{"Vomit", { "missfam5_blackout", "vomit" } },
		{"Wave Forward", { "friends@frj@ig_1", "wave_d" } },
		{"Wave Hands High", { "random@prisoner_lift", "arms_waving" } },
		{"Wave One Arm", { "random@shop_gunstore", "_greeting" } }
	};
	
	const char* danceNames[] = {
	"Casual",
	"Clown",
	"Pole",
	"Private",
	"Receive",
	"Sexual",
	"Yacht"
	};

	const char* miscNames[] = {
		"Electrocute",
		"Hover",
		"Jump",
		"Meditate",
		"Party",
		"Pissing",
		"Push Ups",
		"Run",
		"Shitting",
		"Showering",
		"Swim",
		"Vomit",
		"Wave Forward",
		"Wave Hands High",
		"Wave One Arm"
	};

	std::size_t sexual_id = 0;
	std::size_t animal_id = 0;
	std::size_t actions_id = 0;
	std::size_t dance_id = 0;
	std::size_t misc_id = 0;

}

namespace menu {

	void start_animation(std::pair<const char*, const char*> anim) {
		util::fiber::pool::add([=] {
			int flag = AnimationRepeat;
			if (m_vars.m_controllable) flag |= AnimationEnablePlayerControl | AnimationUpperBody;

			while (!STREAMING::HAS_ANIM_DICT_LOADED(anim.first)) {
				STREAMING::REQUEST_ANIM_DICT(anim.first);
				util::fiber::sleep(100);
			}

			TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
			TASK::TASK_PLAY_ANIM(PLAYER::PLAYER_PED_ID(), anim.first, anim.second, 8.f, 8.f, -1, flag, 0.f, false, false, false);
		});
	}

	void player_animation_menu::render() {
		renderer::addSubmenu("Animation", "Player Animation", [](core* core) {
			core->addOption(buttonOption("Stop Animation")
				.addClick([] { TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID()); }));


			core->addOption(toggleOption("Controllable")
				.addToggle(&m_vars.m_controllable));

			core->addOption(breakOption("Animations"));

			core->addOption(scrollOption<const char*, std::size_t>("Sexual")
				.addScroll(&sexualNames)
				.setPosition(&sexual_id)
				.addClick([] {
					start_animation(std::make_pair(sexual[sexual_id].values.first, sexual[sexual_id].values.second));
				}));

			core->addOption(scrollOption<const char*, std::size_t>("Animals")
				.addScroll(&animalsNames)
				.setPosition(&animal_id)
				.addClick([] {
					start_animation(std::make_pair(animals[animal_id].values.first, animals[animal_id].values.second));
					}));

			core->addOption(scrollOption<const char*, std::size_t>("Actions")
				.addScroll(&actionsNames)
				.setPosition(&actions_id)
				.addClick([] {
					start_animation(std::make_pair(actions[actions_id].values.first, actions[actions_id].values.second));
					}));


			core->addOption(scrollOption<const char*, std::size_t>("Dance")
				.addScroll(&danceNames)
				.setPosition(&dance_id)
				.addClick([] {
					start_animation(std::make_pair(dance[dance_id].values.first, dance[dance_id].values.second));
					}));


			core->addOption(scrollOption<const char*, std::size_t>("Misc")
				.addScroll(&miscNames)
				.setPosition(&misc_id)
				.addClick([] {
					start_animation(std::make_pair(misc[misc_id].values.first, misc[misc_id].values.second));
					}));
		});
	}

	void player_animation_menu::update() {
		render();

	}
}