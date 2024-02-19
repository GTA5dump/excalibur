#include "pch.h"
#include "player.h"
#include "features/manager/manager.h"
#include "menu/util/globals.h"
#include "gui/options/option.h"
#include "gui/util/panels.h"
#include "rage/classes/CPed.h"
#include "player/appearance.h"
#include "player/animation.h"
#include "player/movement.h"
#include "player/particles.h"
#include "player/visions.h"

using namespace base::gui;
using namespace menu::player::vars;

namespace menu::player::vars {
	variables m_vars;

	bool get_player_otr(Player player) {
		return *script_global(2657704).at(1 + (player * 463)).at(213).as<int*>();
	}

	void local_set_player_otr_flag(bool toggle) {
		*script_global(2657704).at(PLAYER::PLAYER_ID(), 463).at(213).as<int*>() = toggle;
	}

	void local_set_player_otr_time(int time) {
		*script_global(2672524).at(58).as<int*>() = time;
	}

	int get_character() {
		return *script_global(1574918).as<int*>();
	}


	static bool was_otr_radar_on;
	void cops_turn_blind_eye() {
		if (m_vars.m_cops_turn_blind_eye) {
			*script_global(2794162).at(4661).as<std::int32_t*>() = 1;
			*script_global(2794162).at(4664).as<std::int32_t*>() = NETWORK::GET_NETWORK_TIME() + 638000;
		}
		else {
			*script_global(2794162).at(4661).as<std::int32_t*>() = 0;
			*script_global(2794162).at(4664).as<std::int32_t*>() = NETWORK::GET_NETWORK_TIME();
		}
	}


	void off_the_radar() {
		if (m_vars.m_off_the_radar) {
			*menu::script_global(2657704).at(PLAYER::PLAYER_ID(), 463).at(210).as<int*>() = 1;
			*menu::script_global(2672524).at(57).as<int*>() = NETWORK::GET_NETWORK_TIME() + 758000;
		}
		else {
			*menu::script_global(2657704).at(PLAYER::PLAYER_ID(), 463).at(210).as<int*>() = 0;
			*menu::script_global(2672524).at(57).as<int*>() = NETWORK::GET_NETWORK_TIME();
		}
	}

	void reveal_hidden_players() {
		if (!m_vars.m_off_the_radar) {
			if (was_otr_radar_on)
			{
				local_set_player_otr_flag(false);
				was_otr_radar_on = false;
			}
			return;
		}
		was_otr_radar_on = true;
		local_set_player_otr_flag(true);
		local_set_player_otr_time(NETWORK::GET_NETWORK_TIME() + 758000);
	}

	void ApplyForceToEntity(Entity entity, float x, float y, float z, float offX, float offY, float offZ) {
		ENTITY::APPLY_FORCE_TO_ENTITY(entity, 1, { x, y, z }, { offX, offY, offZ }, 0, 1, 1, 1, 0, 1);
	}

	const char* invisibleNames[] = {
		"Local", "Network", "Network + Local"
	}; std::size_t invisible_id = 0;

}

namespace menu {
	
	void suicide(features::actionFeature* feature) {
		ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 0, 0);
	}


	void player_menu::render() {
		renderer::addSubmenu("Player", "Player", [](core* core) {
			core->addOption(submenuOption("Movement")
				.setTarget("Player Movement"));

			core->addOption(submenuOption("Appearance")
				.setTarget("Player Appearance"));

			core->addOption(submenuOption("Animation")
				.setTarget("Player Animation"));

			core->addOption(submenuOption("Particles")
				.setTarget("Player Particles"));

			core->addOption(submenuOption("Visions")
				.setTarget("Player Visions"));

			core->addOption(toggleOption("Godmode")
				.addHotkey().addTranslate()
				.addToggle(&m_vars.m_godmode).addClick([] {
					if (!m_vars.m_godmode) {
						ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), false);
					}
				}));

			core->addOption(toggleOption("Auto Heal")
				.addHotkey().addTranslate()
				.addToggle(&m_vars.m_auto_heal));

			core->addOption(toggleOption("Never Wanted")
				.addHotkey().addTranslate()
				.addToggle(&m_vars.m_disable_police));

			core->addOption(toggleScrollOption<const char*, std::size_t>("Invisibility")
				.addToggle(&m_vars.m_invisible)
				.addScroll(&invisibleNames)
				.setPosition(&invisible_id)
				.addClick([] {
					if (!m_vars.m_invisible) {
						ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true, true);
						NETWORK::NETWORK_SET_ENTITY_ONLY_EXISTS_FOR_PARTICIPANTS(PLAYER::PLAYER_PED_ID(), false);
						NETWORK::SET_LOCAL_PLAYER_INVISIBLE_LOCALLY(false);
					}
				}));

			core->addOption(toggleOption("Fast Respawn")
				.addHotkey().addTranslate()
				.addToggle(&m_vars.m_fast_respawn));

			core->addOption(toggleOption("Disable Ragdoll")
				.addHotkey().addTranslate()
				.addToggle(&m_vars.m_disable_ragdoll));

			core->addOption(toggleOption("Reduced Collision")
				.addHotkey().addTranslate()
				.addToggle(&m_vars.m_reduced_collision));

			core->addOption(toggleOption("No Collision")
				.addHotkey().addTranslate()
				.addToggle(&m_vars.m_no_collision));

			core->addOption(toggleOption("Off the Radar")
				.addHotkey().addTranslate()
				.addToggle(&m_vars.m_off_the_radar)
				.addClick(off_the_radar));

			core->addOption(toggleOption("Reveal Hidden Players")
				.addHotkey().addTranslate()
				.addToggle(&m_vars.m_reveal_hidden_players)
				.addClick(reveal_hidden_players));

			core->addOption(toggleOption("Cops turn Blind Eye")
				.addHotkey().addTranslate()
				.addToggle(&m_vars.m_cops_turn_blind_eye)
				.addClick(cops_turn_blind_eye));

			core->addOption(toggleOption("Superman")
				.addHotkey().addTranslate()
				.addToggle(&m_vars.m_superman));

			core->addOption(toggleOption("Karma")
				.addHotkey().addTranslate()
				.addToggle(&m_vars.m_karma));

			core->addOption(toggleOption("Shrink")
				.addHotkey().addTranslate()
				.addToggle(&m_vars.m_shrink));

			core->addOption(toggleOption("Forcefield")
				.addHotkey().addTranslate()
				.addToggle(&m_vars.m_forcefield));

			core->addOption(toggleOption("Vegetable Mode")
				.addHotkey().addTranslate()
				.addToggle(&m_vars.m_vegetable_mode));

			core->addOption(buttonOption("Sky Dive")
				.addClick([] {
					if (ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(PLAYER::PLAYER_PED_ID()) < 50.f) {
						ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), { ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1).x, ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1).y, ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1).z + 1000.f }, true, true, true, false);
						TASK::TASK_SKY_DIVE(PLAYER::PLAYER_PED_ID(), TRUE);
					}
					}));

			core->addOption(buttonOption("Max Health & Armour")
				.addClick([] {
					PED::SET_PED_ARMOUR(PLAYER::PLAYER_PED_ID(), 100);
					ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), ENTITY::GET_ENTITY_MAX_HEALTH(PLAYER::PLAYER_PED_ID()), 0);
					}));

			core->addOption(buttonOption("Clone")
				.addClick([] { PED::CLONE_PED(PLAYER::PLAYER_PED_ID(), ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), true, false); }));

			core->addOption(buttonOption("Suicide")
				.addHotkey().addTranslate()
				.addClick([] { suicide("player_suicide"_AF); }));
		});
	}

	void player_menu::update() {
		render();	
		getPlayerAppearanceMenu()->update();
		getPlayerMovementMenu()->update();
		getPlayerAnimationMenu()->update();
		getPlayerParticlesMenu()->update();
		getPlayerVisionsMenu()->update();

		if (m_vars.m_shrink) {
			PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 223, true);
		}
		if (!m_vars.m_shrink) {
			PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 223, false);
		}

		if (m_vars.m_forcefield) {
			ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), true);
			FIRE::ADD_EXPLOSION(ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true), 29, 100, false, true, 0.0f, false);
		}
		if (!m_vars.m_forcefield) {
			ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), false);
		}

		if (m_vars.m_godmode) {
			ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), true);
		}

		if (m_vars.m_off_the_radar) {
			off_the_radar();
		}

		if (m_vars.m_reveal_hidden_players) {
			reveal_hidden_players();
		}

		if (m_vars.m_cops_turn_blind_eye) {
			cops_turn_blind_eye();
		}

		if (m_vars.m_disable_police) {
			(*patterns::ped_factory)->m_local_ped->m_player_info->m_wanted_level = 0;
			patterns::max_wanted_level->apply();
			patterns::max_wanted_level_2->apply();
		}
		else {
			patterns::max_wanted_level->restore();
			patterns::max_wanted_level_2->restore();
		}

		if (m_vars.m_vegetable_mode) {
			PED::SET_PED_TO_RAGDOLL(PLAYER::PLAYER_PED_ID(), 10, 10, 0, true, true, true);
			if (Util::is_key_pressed(0x57)) ApplyForceToEntity(PLAYER::PLAYER_PED_ID(), 0, 2, 0, 0, 0 ,0);
			if (Util::is_key_pressed(0x53)) ApplyForceToEntity(PLAYER::PLAYER_PED_ID(), 0, -2, 0, 0, 0, 0);
			if (Util::is_key_pressed(0x41)) ApplyForceToEntity(PLAYER::PLAYER_PED_ID(), 2, 0, 0, 0, 0, 0);
			if (Util::is_key_pressed(0x44)) ApplyForceToEntity(PLAYER::PLAYER_PED_ID(), -2, 0, 0, 0, 0, 0);
		}

		if (m_vars.m_fast_respawn) {
			if (PED::IS_PED_DEAD_OR_DYING(PLAYER::PLAYER_PED_ID(), true)) {
				Vector3 c = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
				PED::RESURRECT_PED(PLAYER::PLAYER_PED_ID());
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PLAYER::PLAYER_PED_ID(), c, 0, 0, 0);
				TASK::CLEAR_PED_TASKS_IMMEDIATELY(PLAYER::PLAYER_PED_ID());
				MISC::FORCE_GAME_STATE_PLAYING();
			}
		}

		if (m_vars.m_disable_ragdoll) {
			PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), false);
		}
		else {
			PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), true);
		}

		if (m_vars.m_auto_heal) {
			ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 400, 0);
		}

		if (m_vars.m_reduced_collision) {
			PED::SET_PED_CAPSULE(PLAYER::PLAYER_PED_ID(), 0.001f);
		}

		if (m_vars.m_no_collision) {
			ENTITY::SET_ENTITY_COLLISION(PLAYER::PLAYER_PED_ID(), false, true);
		}
		else {
			ENTITY::SET_ENTITY_COLLISION(PLAYER::PLAYER_PED_ID(), true, true);
		}

		if (m_vars.m_invisible) {
			switch (invisible_id) {
			case 0:
				NETWORK::SET_LOCAL_PLAYER_INVISIBLE_LOCALLY(true);
				break;

			case 1:
				NETWORK::NETWORK_SET_ENTITY_ONLY_EXISTS_FOR_PARTICIPANTS(PLAYER::PLAYER_PED_ID(), true);
				NETWORK::SET_ENTITY_LOCALLY_VISIBLE(PLAYER::PLAYER_PED_ID());
				break;

			case 2:
				NETWORK::NETWORK_SET_ENTITY_ONLY_EXISTS_FOR_PARTICIPANTS(PLAYER::PLAYER_PED_ID(), true);
				NETWORK::SET_LOCAL_PLAYER_INVISIBLE_LOCALLY(true);
				break;
			}
		}

		if (m_vars.m_invisible) {
			ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), false, false);
		}
		else {
			ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true, true);
		}

		if (m_vars.m_superman) {
			int left_right = PAD::GET_CONTROL_VALUE(2, 188);
			int up_down = PAD::GET_CONTROL_VALUE(2, 189);

			if (ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(PLAYER::PLAYER_PED_ID()) < 3.f) {
				WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, -1, true, true);

				Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
				coords.z += 100.f;
				ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), coords, false, false, false, false);
			}
			else {
				if (up_down == 254 || Util::is_key_pressed(0x53)) {
					ENTITY::APPLY_FORCE_TO_ENTITY(PLAYER::PLAYER_PED_ID(), 1, { 0.f, 3.f, 10.f }, { 0.f, 0.f, 0.f }, false, true, true, true, false, true);
				}

				if (up_down == 0 || Util::is_key_pressed(0x57)) {
					ENTITY::APPLY_FORCE_TO_ENTITY(PLAYER::PLAYER_PED_ID(), 1, { 0.f, 3.f, 0.f }, { 0.f, 0.f, 0.f }, false, true, true, true, false, true);
				}

				if (Util::is_key_pressed(VK_SHIFT) || Util::is_key_pressed(ControlFrontendRt)) {
					ENTITY::APPLY_FORCE_TO_ENTITY(PLAYER::PLAYER_PED_ID(), 1, { 0.f, 15.f, .3f }, { 0.f, 0.f, 0.f }, false, true, true, true, false, true);
				}

				if (left_right == 254 || Util::is_key_pressed(0x44)) {
					ENTITY::APPLY_FORCE_TO_ENTITY(PLAYER::PLAYER_PED_ID(), 1, { 1.20f, 0.f, 0.f }, { 0.f, 0.1f, 0.f }, false, true, true, true, false, true);
				}

				if (left_right == 0 || Util::is_key_pressed(0x41)) {
					ENTITY::APPLY_FORCE_TO_ENTITY(PLAYER::PLAYER_PED_ID(), 1, { -1.20f, 0.f, 0.f }, { 0.f, 0.1f, 0.f }, false, true, true, true, false, true);
				}
			}
		}

		if (m_vars.m_karma) {
			if (ENTITY::IS_ENTITY_DEAD(PLAYER::PLAYER_PED_ID(), 0)) {
				Entity killer = PED::GET_PED_SOURCE_OF_DEATH(PLAYER::PLAYER_PED_ID());
				if (ENTITY::DOES_ENTITY_EXIST(killer)) {
					if (!ENTITY::IS_ENTITY_DEAD(killer, 0)) {
						Vector3 position = ENTITY::GET_ENTITY_COORDS(killer, true);
						FIRE::ADD_EXPLOSION(position, 0, 50.f, false, true, 0.f, false);

					}
				}
			}
		}

	}
}