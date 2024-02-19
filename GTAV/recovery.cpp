#include "pch.h"
#include "recovery.h"
#include "gui/util/timer.h"
#include "rage/engine.h"
#include <vector>
#include <array>
#include "menu/util/stats.h"
#include "recovery/recovery_level.h"
#include "recovery/unlocks.h"
using namespace base::gui;
using namespace menu::recovery::vars;

namespace menu::recovery::vars {
	variables m_vars;
	
	void fleeca_job() {
		rage::engine::add_basket_transaction(rage::joaat("CATEGORY_SERVICE_WITH_THRESHOLD"), 1445302971, 4,
			{
				{ (int)rage::joaat("SERVICE_EARN_JOB_BONUS"), 1, 15000000, 0, 1},
			});
	}

	void bend_job() {
		rage::engine::add_basket_transaction(rage::joaat("CATEGORY_SERVICE_WITH_THRESHOLD"), 1445302971, 4,
			{
				{ (int)rage::joaat("SERVICE_EARN_BEND_JOB"), 1, 15000000, 0, 1},
			});
	}

	void doomsday_finale() {
		rage::engine::add_basket_transaction(rage::joaat("CATEGORY_SERVICE_WITH_THRESHOLD"), 1445302971, 4,
			{
				{ (int)rage::joaat("SERVICE_EARN_DOOMSDAY_FINALE_BONUS"), 1, 200000, 0, 1},
			});
	}

	void avenger_operations() {
		rage::engine::add_basket_transaction(rage::joaat("CATEGORY_SERVICE_WITH_THRESHOLD"), 1445302971, 4,
			{
				{ (int)rage::joaat("SERVICE_EARN_AVENGER_OPERATIONS"), 1, 1000000, 0, 1},
			});
	}

	void gang_award() {
		rage::engine::add_basket_transaction(rage::joaat("CATEGORY_SERVICE_WITH_THRESHOLD"), 1445302971, 4,
			{
				{ (int)rage::joaat("SERVICE_EARN_GANGOPS_AWARD_ORDER"), 1, 2000000, 0, 1},
			});
	}

	void daily_objective() {
		rage::engine::add_basket_transaction(rage::joaat("CATEGORY_SERVICE_WITH_THRESHOLD"), 1445302971, 4,
			{
				{ (int)rage::joaat("SERVICE_EARN_DAILY_OBJECTIVE_EVENT"), 1, 1000000, 0, 1},
			});
	}

	void music_studio() {
		rage::engine::add_basket_transaction(rage::joaat("CATEGORY_SERVICE_WITH_THRESHOLD"), 1445302971, 4,
			{
				{ (int)rage::joaat("SERVICE_EARN_MUSIC_STUDIO_SHORT_TRIP"), 1, 1000000, 0, 1},
			});
	}

	void casino_heist_finale() {
		rage::engine::add_basket_transaction(rage::joaat("CATEGORY_SERVICE_WITH_THRESHOLD"), 1445302971, 4,
			{
				{ (int)rage::joaat("SERVICE_EARN_CASINO_HEIST_FINALE"), 1, 3619000, 0, 1 },
			});
	}

	void gang_money() {
		rage::engine::add_basket_transaction(rage::joaat("CATEGORY_SERVICE_WITH_THRESHOLD"), 1445302971, 4,
			{
				{ (int)rage::joaat("SERVICE_EARN_GANGOPS_AWARD_MASTERMIND_4"), 1, 7000000, 0, 1 },
			});
	}

	void gang_money_2() {
		rage::engine::add_basket_transaction(rage::joaat("CATEGORY_SERVICE_WITH_THRESHOLD"), 1445302971, 4,
			{
				{ (int)rage::joaat("SERVICE_EARN_GANGOPS_AWARD_MASTERMIND_3"), 1, 7000000, 0, 1 },
			});
	}

	void premium_job() {
		rage::engine::add_basket_transaction(rage::joaat("CATEGORY_SERVICE_WITH_THRESHOLD"), 1445302971, 4,
			{
				{ (int)rage::joaat("SERVICE_EARN_PREMIUM_JOB"), 1, 300000, 0, 1 },
			});
	}

	void juggallo_phone() {
		rage::engine::add_basket_transaction(rage::joaat("CATEGORY_SERVICE_WITH_THRESHOLD"), 1445302971, 4,
			{
				{ (int)rage::joaat("SERVICE_EARN_JUGGALO_PHONE_MISSION"), 1, 100000, 0, 1 },
			});
	}

	void juggalo_story() {
		rage::engine::add_basket_transaction(rage::joaat("CATEGORY_SERVICE_WITH_THRESHOLD"), 1445302971, 4,
			{
				{ (int)rage::joaat("SERVICE_EARN_WINTER_22_AWARD_JUGGALO_STORY"), 1, 500000, 0, 1 },
			});
	}

	void agency_story_finale() {
		rage::engine::add_basket_transaction(rage::joaat("CATEGORY_SERVICE_WITH_THRESHOLD"), 1445302971, 4,
			{
				{ (int)rage::joaat("SERVICE_EARN_AGENCY_STORY_FINALE"), 1, 3000000, 0, 1 },
			});
	}

	void island_heist_finale() {
		rage::engine::add_basket_transaction(rage::joaat("CATEGORY_SERVICE_WITH_THRESHOLD"), 1445302971, 4,
			{
				{ (int)rage::joaat("SERVICE_EARN_ISLAND_HEIST_FINALE"), 1, 2550000, 0, 1 },
			});
	}

	void job_bonus() {
		rage::engine::add_basket_transaction(rage::joaat("CATEGORY_SERVICE_WITH_THRESHOLD"), 1445302971, 4,
			{
				{ (int)rage::joaat("SERVICE_EARN_JOB_BONUS_HEIST_AWARD"), 1, 2000000, 0, 1 },
			});
	}

	void tuner_robbery_finale() {
		rage::engine::add_basket_transaction(rage::joaat("CATEGORY_SERVICE_WITH_THRESHOLD"), 1445302971, 4,
			{
				{ (int)rage::joaat("SERVICE_EARN_TUNER_ROBBERY_FINALE"), 1, 2000000, 0, 1 },
			});
	}

	const char* characters[] = {
		"PLACEHOLDER", "PLACEHOLDER"
	}; 

	int get_character_count() {
		const char* character_two = STATS::STAT_GET_STRING(0xD2AB0EC6, -1);
		if (!character_two || strlen(character_two) < 1) return 1;
		return 2;
	}

	float calculate() {
		float calculated = 0.f;
		if (m_vars.m_deaths == 0) {
			calculated = (float)m_vars.m_kills;
		}
		else calculated = (float)((float)m_vars.m_kills / (float)m_vars.m_deaths);

		return calculated;
	}

	inline void set_kd() {
		stats<float>::set("MPPLY_KILLS_PLAYERS", m_vars.m_kills);
		stats<float>::set("MPPLY_DEATHS_PLAYER", m_vars.m_deaths);
	}
}


namespace menu {

	void recovery_menu::render() {
		renderer::addSubmenu("Recovery", "Recovery", [](core* core) {

			int current_char = 0;
			STATS::STAT_GET_INT(0x2F2F120F, &current_char, -1);
			m_vars.m_selected_character = current_char ? 1 : 0;

			core->addOption(numberOption<int>("Selected Character")
				.addNumber(&m_vars.m_selected_character).addMin(0).addMax(get_character_count()));

			core->addOption(submenuOption("Money")
				.setTarget("Recovery Money"));

			core->addOption(submenuOption("Level")
				.setTarget("Recovery Level"));

			core->addOption(submenuOption("Unlocks")
				.setTarget("Recovery Unlocks"));

			core->addOption(submenuOption("Abilities")
				.setTarget("recovery_abilities"));

			core->addOption(submenuOption("Inventory")
				.setTarget("snacks"));

			core->addOption(submenuOption("Strippers")
				.setTarget("strippers"));

			core->addOption(submenuOption("ATM")
				.setTarget("ATM"));

			core->addOption(submenuOption("K/D")
				.setTarget("K/D"));

			core->addOption(buttonOption("Redesign Character")
				.addClick([] { stats<bool>::set("FM_CHANGECHAR_ASKED", false); }));

			core->addOption(buttonOption("Clear Mental State")
				.addClick([] { stats<float>::set("PLAYER_MENTAL_STATE", 0.0f); }));

			static int night_club_pop = 1000;
			core->addOption(numberOption<int>("Set Nightclub Popularity")
				.addNumber(&night_club_pop).addMin(0).addMax(1000).addClick([=] {
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), night_club_pop, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STAM"), night_club_pop, 0);
				}));
		
		});

		renderer::addSubmenu("Abilities", "recovery_abilities", [](core* core) {
			core->addOption(buttonOption("Max all Abilities")
				.addClick([] {
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STAM"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STRN"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_LUNG"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_DRIV"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_FLY"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_SHO"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STL"), 100, 0);
					}));
			core->addOption(buttonOption("Max Stamina Ability")
				.addClick([] {
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STAM"), 100, 0);
					}));
			core->addOption(buttonOption("Max Strength Ability")
				.addClick([] {
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STRN"), 100, 0);
					}));
			core->addOption(buttonOption("Max Lung Function Ability")
				.addClick([] {
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_LUNG"), 100, 0);
					}));
			core->addOption(buttonOption("Max Driving Ability")
				.addClick([] {
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_DRIV"), 100, 0);
					}));
			core->addOption(buttonOption("Max Flying Ability")
				.addClick([] {
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_FLY"), 100, 0);
					}));
			core->addOption(buttonOption("Max Shooting Ability")
				.addClick([] {
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_SHO"), 100, 0);
					}));
			core->addOption(buttonOption("Max Stealth Ability")
				.addClick([] {
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, 0);
					STATS::STAT_SET_INT(MISC::GET_HASH_KEY("MP1_SCRIPT_INCREASE_STL"), 100, 0);
					}));
			});

		renderer::addSubmenu("Inventory", "snacks", [](core* core) {
			core->addOption(buttonOption("Max Snacks")
				.addClick([] {
					STATS::STAT_SET_INT(rage::joaat("MP0_NO_BOUGHT_YUM_SNACKS"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP0_NO_BOUGHT_HEALTH_SNACKS"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP0_NO_BOUGHT_EPIC_SNACKS"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP0_NUMBER_OF_ORANGE_BOUGHT"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP0_CIGARETTES_BOUGHT"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP1_NO_BOUGHT_YUM_SNACKS"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP1_NO_BOUGHT_HEALTH_SNACKS"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP1_NO_BOUGHT_EPIC_SNACKS"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP1_NUMBER_OF_ORANGE_BOUGHT"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP1_CIGARETTES_BOUGHT"), 2000000000, 1);
					}));
			core->addOption(buttonOption("Max Armor")
				.addClick([] {
					STATS::STAT_SET_INT(rage::joaat("MP0_MP_CHAR_ARMOUR_1_COUNT"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP0_MP_CHAR_ARMOUR_2_COUNT"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP0_MP_CHAR_ARMOUR_3_COUNT"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP0_MP_CHAR_ARMOUR_4_COUNT"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP0_MP_CHAR_ARMOUR_5_COUNT"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP1_MP_CHAR_ARMOUR_1_COUNT"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP1_MP_CHAR_ARMOUR_2_COUNT"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP1_MP_CHAR_ARMOUR_3_COUNT"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP1_MP_CHAR_ARMOUR_4_COUNT"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP1_MP_CHAR_ARMOUR_5_COUNT"), 2000000000, 1);
					}));

			core->addOption(buttonOption("Max Fireworks")
				.addClick([] {
					STATS::STAT_SET_INT(rage::joaat("MP0_FIREWORK_TYPE_1_WHITE"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP0_FIREWORK_TYPE_1_RED"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP0_FIREWORK_TYPE_1_BLUE"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP0_FIREWORK_TYPE_2_WHITE"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP0_FIREWORK_TYPE_2_RED"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP0_FIREWORK_TYPE_2_BLUE"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP0_FIREWORK_TYPE_3_WHITE"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP0_FIREWORK_TYPE_3_RED"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP0_FIREWORK_TYPE_3_BLUE"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP0_FIREWORK_TYPE_4_WHITE"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP0_FIREWORK_TYPE_4_RED"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP0_FIREWORK_TYPE_4_BLUE"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP1_FIREWORK_TYPE_1_WHITE"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP1_FIREWORK_TYPE_1_RED"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP1_FIREWORK_TYPE_1_BLUE"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP1_FIREWORK_TYPE_2_WHITE"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP1_FIREWORK_TYPE_2_RED"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP1_FIREWORK_TYPE_2_BLUE"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP1_FIREWORK_TYPE_3_WHITE"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP1_FIREWORK_TYPE_3_RED"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP1_FIREWORK_TYPE_3_BLUE"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP1_FIREWORK_TYPE_4_WHITE"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP1_FIREWORK_TYPE_4_RED"), 2000000000, 1);
					STATS::STAT_SET_INT(rage::joaat("MP1_FIREWORK_TYPE_4_BLUE"), 2000000000, 1);
					}));
			});

		renderer::addSubmenu("Strippers", "strippers", [](core* core) {
			core->addOption(buttonOption("Get Juliet to Like You")
				.addClick([] { *script_global::script_global(114054).as<int*>() = 7500; }));

			core->addOption(buttonOption("Get Nikki to Like You")
				.addClick([] { *script_global::script_global(114054).at(5).as<int*>() = 7500; }));

			core->addOption(buttonOption("Get Chastity to Like You")
				.addClick([] { *script_global::script_global(114054).at(10).as<int*>() = 7500; }));

			core->addOption(buttonOption("Get Cheetah to Like You")
				.addClick([] { *script_global::script_global(114054).at(15).as<int*>() = 7500; }));

			core->addOption(buttonOption("Get Sapphire to Like You")
				.addClick([] { *script_global::script_global(114054).at(20).as<int*>() = 7500; }));

			core->addOption(buttonOption("Get Infernus to Like You")
				.addClick([] { *script_global::script_global(114054).at(25).as<int*>() = 7500; }));

			core->addOption(buttonOption("Get Fufu to Like You")
				.addClick([] { *script_global::script_global(114054).at(30).as<int*>() = 7500; }));

			core->addOption(buttonOption("Get Peach to Like You")
				.addClick([] { *script_global::script_global(114054).at(35).as<int*>() = 7500; }));
		});

		renderer::addSubmenu("K/D", "K/D", [](core* core) {
			core->addOption(numberOption<int>("Set Kills")
				.addNumber(&m_vars.m_kills).addMin(0).addMax(999999));

			core->addOption(numberOption<int>("Set Deaths")
				.addNumber(&m_vars.m_deaths).addMin(0).addMax(999999));

			m_vars.m_calculated = calculate();

			core->addOption(buttonOption(std::format("Set K/D: {}", m_vars.m_calculated).c_str()));
			});
		renderer::addSubmenu("ATM", "ATM", [](core* core) {

			core->addOption(buttonOption("Transfer Money to Wallet")
				.addClick([] {  }));

			core->addOption(buttonOption("Transfer Money to Bank")
				.addClick([] {  }));
			});

		renderer::addSubmenu("Money", "Recovery Money", [](core* core) {

			core->addOption(toggleOption("1 Million Loop")
				.addToggle(&m_vars.m_loop));

			core->addOption(breakOption("Transactions"));

			core->addOption(buttonOption("Fleeca Job (15M)")
				.addClick(fleeca_job));

			core->addOption(buttonOption("Bend Job (15M)")
				.addClick(bend_job));

			core->addOption(buttonOption("Gang Money(7M)")
				.addClick(gang_money));

			core->addOption(buttonOption("Gang Award (7M)")
				.addClick(gang_money_2));

			core->addOption(buttonOption("Casino Heist (3.6M)")
				.addClick(casino_heist_finale));

			core->addOption(buttonOption("Gang Operations (2M)")
				.addClick(gang_award));

			core->addOption(buttonOption("Job Bonus (2M)")
				.addClick(job_bonus));

			core->addOption(buttonOption("Tuner Robbery Finale (2M)")
				.addClick(tuner_robbery_finale));

			core->addOption(buttonOption("Daily Objective (1M)")
				.addClick(daily_objective));

			core->addOption(buttonOption("Music Studio (1M)")
				.addClick(music_studio));

			core->addOption(buttonOption("Avenger Operations (1M)")
				.addClick(avenger_operations));

			core->addOption(buttonOption("Juggalo Story Award (500k)")
				.addClick(juggalo_story));

			core->addOption(buttonOption("Premium Job (300k)")
				.addClick(premium_job));

			core->addOption(buttonOption("Agency Story Finale (300k)")
				.addClick(agency_story_finale));

			core->addOption(buttonOption("Island Heist Finale (250k)")
				.addClick(island_heist_finale));

			core->addOption(buttonOption("Doomsday Finale (200k)")
				.addClick(doomsday_finale));

			core->addOption(buttonOption("Juggalo Phone (100k)")
				.addClick(juggallo_phone));

		});
	}

	void recovery_menu::update() {
		render();
		getRecoveryLevelMenu()->update();
		getRecoveryUnlocksMenu()->update();


		if (m_vars.m_loop2) {

			*script_global(278108).as<int*>() = 6000000;
			*script_global(277873).as<int*>() = 0;
			*script_global(277874).as<int*>() = 0;

			util::fiber::go_to_main();

			if (auto script = rage::engine::find_script_thread("gb_contraband_sell"_joaat)) {
				if (*script_local(script->m_stack, 2).as<int*>() == 1) {
					*script_local(script->m_stack, 1136).as<int*>() = 1;
					*script_local(script->m_stack, 596).as<int*>() = 0;
					*script_local(script->m_stack, 1125).as<int*>() = 0;
					*script_local(script->m_stack, 548).as<int*>() = 7;
					util::fiber::sleep(500);
					*script_local(script->m_stack, 542).as<int*>() = 99999;
				}
			}

			if (auto script = rage::engine::find_script_thread("appsecuroserv"_joaat)) {
				if (*script_local(script->m_stack, 2).as<int*>() == 1) {
					util::fiber::sleep(500);
					*script_local(script->m_stack, 737).as<int*>() = 1;
					util::fiber::sleep(200);
					*script_local(script->m_stack, 738).as<int*>() = 1;
					util::fiber::sleep(200);
					*script_local(script->m_stack, 556).as<int*>() = 3012;
					util::fiber::sleep(1000);
				}
			}

			if (auto script = rage::engine::find_script_thread("gb_contraband_sell"_joaat)) {
				if (*script_local(script->m_stack, 2).as<int*>() != 1) {
					util::fiber::sleep(500);
					if (auto script2 = rage::engine::find_script_thread("am_mp_warehouse"_joaat)) {
						if (*script_local(script2->m_stack, 2).as<int*>() == 1) {
							SCRIPT::REQUEST_SCRIPT("appsecuroserv");
							SYSTEM::START_NEW_SCRIPT("appsecuroserv", 8344);
							SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED("appsecuroserv");
						}
					}

				}
			}
		}

		int m_timer = 0;
		if (m_vars.m_loop) {
			run_timed(&m_timer, 1000, [] {
				rage::engine::send_basket_transaction(rage::joaat("CATEGORY_SERVICE_WITH_THRESHOLD"), 1633116913, rage::joaat("NET_SHOP_ACTION_EARN"), 1000000, 4);
			});
		}
	}
}