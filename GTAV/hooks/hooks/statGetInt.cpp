#include "pch.h"
#include "hooks/hooks.h"
#include "rage/classes/scrNativeCallContext.h"
#include "rage/invoker/natives.h"
#include "menu/submenus/main.h"
#include "util/fiber.h"
#include "features/features.h"
#include "gui/util/fonts.h"
#include "gui/util/texture.h"
#include "gui/util/panels.h"
#include "util/fiber_pool.h"
#include "gui/renderer.h"
#include "gui/util/notify.h"
#include "menu/util/players.h"
#include "menu/submenus/main/weapon/weapon_disables.h"
#include "menu/submenus/main/network/network_session.h"
#include "menu/submenus/main/network/spoofing/network_spoofing_name.h"
#include "menu/submenus/main/network/network_tunables.h"
#include "menu/submenus/main/settings.h"
#include "menu/submenus/main/player.h"
#include "menu/submenus/main/spawner.h"
#include "menu/submenus/main/network.h"
#include "menu/submenus/main/weapon.h"
#include "menu/submenus/main/vehicle.h"
#include "menu/submenus/main/teleport.h"
#include "menu/submenus/main/protections.h"
#include "menu/submenus/main/recovery.h"
#include "menu/submenus/main/world.h"
#include "menu/submenus/main/misc.h"
#include "menu/util/script_patcher_service.h"
namespace base::hooks {


	void set_current_ped_weapon(rage::scrNativeCallContext* context) {
		const auto ped = context->get_arg<Ped>(0);
		const auto hash = context->get_arg<rage::joaat_t>(1);
		if (menu::weapon::disables::vars::m_vars.m_interior_block && menu::weapon::disables::vars::m_vars.m_passive_block && ped == PLAYER::PLAYER_PED_ID() && hash == RAGE_JOAAT("WEAPON_UNARMED"))
			return;

		WEAPON::SET_CURRENT_PED_WEAPON(ped, hash, context->get_arg<int>(2));

	}

	void network_session_host(rage::scrNativeCallContext* context) {
		if (menu::network::session::vars::m_vars.join_queued) {
			caller::call<uint64_t>(patterns::join_session_by_info, *patterns::network, &menu::network::session::vars::m_vars.info, 1, 1 | 2, nullptr, 0);
			menu::network::session::vars::m_vars.join_queued = false;
			context->set_return_value<BOOL>(TRUE);
		}
		context->set_return_value<BOOL>(NETWORK::NETWORK_SESSION_HOST(context->get_arg<int>(0), context->get_arg<int>(1), context->get_arg<BOOL>(2)));
	}

	void set_player_name(rage::scrNativeCallContext* context) {
		const auto playerId = context->get_arg<Player>(0);
		context->set_return_value(PLAYER::GET_PLAYER_NAME(playerId));
		const auto network_player_mgr = (*patterns::network_player_mgr);
		if (menu::network::spoofing::name::vars::m_vars.m_spoof && network_player_mgr && network_player_mgr->m_local_net_player && playerId == network_player_mgr->m_local_net_player->m_player_id) {
			context->set_return_value(menu::network::spoofing::name::vars::m_vars.m_name.c_str());
		}
	}

	void base::hooks::return_true(rage::scrNativeCallContext* context) {
		if (menu::network::tunables::vars::m_vars.m_bypass_country_restrictions) {
			context->set_return_value<BOOL>(TRUE);
		}
	}

	void base::hooks::return_false(rage::scrNativeCallContext* context) {
		context->set_return_value<BOOL>(FALSE);
		
	}


	void base::hooks::terminate_this_thread(rage::scrNativeCallContext* context) {
		g_freemode_terminated = true;
		SCRIPT::TERMINATE_THIS_THREAD();
	}

	void disable_control_action(rage::scrNativeCallContext* context)
	{
		const auto action = context->get_arg<eControllerInputs>(1);

		if (menu::weapon::disables::vars::m_vars.m_interior_block && menu::weapon::disables::vars::m_vars.m_passive_block) // Filtering from the inside of Kosatka
		{
			switch (action)
			{
				// case ControllerInputs::INPUT_JUMP: TODO: add as separate feature
			case eControllerInputs::INPUT_ATTACK:
			case eControllerInputs::INPUT_AIM:
			case eControllerInputs::INPUT_DUCK:
			case eControllerInputs::INPUT_SELECT_WEAPON:
			case eControllerInputs::INPUT_COVER:
			case eControllerInputs::INPUT_TALK:
			case eControllerInputs::INPUT_DETONATE:
			case eControllerInputs::INPUT_WEAPON_SPECIAL:
			case eControllerInputs::INPUT_WEAPON_SPECIAL_TWO:
			case eControllerInputs::INPUT_VEH_AIM:
			case eControllerInputs::INPUT_VEH_ATTACK:
			case eControllerInputs::INPUT_VEH_ATTACK2:
			case eControllerInputs::INPUT_VEH_HEADLIGHT:
			case eControllerInputs::INPUT_VEH_NEXT_RADIO:
			case eControllerInputs::INPUT_VEH_PREV_RADIO:
			case eControllerInputs::INPUT_VEH_NEXT_RADIO_TRACK:
			case eControllerInputs::INPUT_VEH_PREV_RADIO_TRACK:
			case eControllerInputs::INPUT_VEH_RADIO_WHEEL:
			case eControllerInputs::INPUT_VEH_PASSENGER_AIM:
			case eControllerInputs::INPUT_VEH_PASSENGER_ATTACK:
			case eControllerInputs::INPUT_VEH_SELECT_NEXT_WEAPON:
			case eControllerInputs::INPUT_VEH_SELECT_PREV_WEAPON:
			case eControllerInputs::INPUT_VEH_ROOF:
			case eControllerInputs::INPUT_VEH_JUMP:
			case eControllerInputs::INPUT_VEH_FLY_ATTACK:
			case eControllerInputs::INPUT_MELEE_ATTACK_LIGHT:
			case eControllerInputs::INPUT_MELEE_ATTACK_HEAVY:
			case eControllerInputs::INPUT_MELEE_ATTACK_ALTERNATE:
			case eControllerInputs::INPUT_MELEE_BLOCK:
			case eControllerInputs::INPUT_SELECT_WEAPON_UNARMED:
			case eControllerInputs::INPUT_SELECT_WEAPON_MELEE:
			case eControllerInputs::INPUT_SELECT_WEAPON_HANDGUN:
			case eControllerInputs::INPUT_SELECT_WEAPON_SHOTGUN:
			case eControllerInputs::INPUT_SELECT_WEAPON_SMG:
			case eControllerInputs::INPUT_SELECT_WEAPON_AUTO_RIFLE:
			case eControllerInputs::INPUT_SELECT_WEAPON_SNIPER:
			case eControllerInputs::INPUT_SELECT_WEAPON_HEAVY:
			case eControllerInputs::INPUT_SELECT_WEAPON_SPECIAL:
			case eControllerInputs::INPUT_ATTACK2:
			case eControllerInputs::INPUT_MELEE_ATTACK1:
			case eControllerInputs::INPUT_MELEE_ATTACK2:
			case eControllerInputs::INPUT_VEH_GUN_LEFT:
			case eControllerInputs::INPUT_VEH_GUN_RIGHT:
			case eControllerInputs::INPUT_VEH_GUN_UP:
			case eControllerInputs::INPUT_VEH_GUN_DOWN:
			case eControllerInputs::INPUT_VEH_HYDRAULICS_CONTROL_TOGGLE:
			case eControllerInputs::INPUT_VEH_MELEE_HOLD:
			case eControllerInputs::INPUT_VEH_MELEE_LEFT:
			case eControllerInputs::INPUT_VEH_MELEE_RIGHT:
			case eControllerInputs::INPUT_VEH_CAR_JUMP:
			case eControllerInputs::INPUT_VEH_ROCKET_BOOST:
			case eControllerInputs::INPUT_VEH_FLY_BOOST:
			case eControllerInputs::INPUT_VEH_PARACHUTE:
			case eControllerInputs::INPUT_VEH_BIKE_WINGS:
			case eControllerInputs::INPUT_VEH_TRANSFORM: return;
			}
		}

		PAD::DISABLE_CONTROL_ACTION(context->get_arg<int>(0), (int)action, context->get_arg<int>(2));
	}


	void stat_get_int(rage::scrNativeCallContext* context) {
		static bool call_once_loaded = false;
		static int frame_cache = 0;
		static uint32_t this_frame = 0;
		static uint32_t last_frame = 0;

		if (frame_cache < MISC::GET_FRAME_COUNT()) {
			frame_cache = MISC::GET_FRAME_COUNT();

			this_frame = timeGetTime();
			menu::renderer::getRenderer()->m_delta = (float)(this_frame - last_frame) / 1000;
			last_frame = this_frame;

			if (!call_once_loaded) {
				try {

					util::fiber::load();
					util::fiber::pool::load();
					fonts::load();
					menu::textures::initialize();

					/*menu::g_script_patcher_service->add_patch({ RAGE_JOAAT("freemode"), "2D 01 04 00 ? 2C ? ? ? 5D ? ? ? 71 57 ? ? 2C", 5, {0x2E, 0x01, 0x00}, nullptr }); // script host kick
					menu::g_script_patcher_service->add_patch({ RAGE_JOAAT("freemode"), "5D ? ? ? 76 57 ? ? 5D ? ? ? 76", 0, {0x2E, 0x00, 0x00}, nullptr }); // end session kick protection
					menu::g_script_patcher_service->add_patch({ RAGE_JOAAT("freemode"), "2D 01 09 00 00 5D ? ? ? 56 ? ? 2E", 5, {0x2E, 0x01, 0x00}, nullptr }); // disable death when undermap/spectating
					menu::g_script_patcher_service->add_patch({ RAGE_JOAAT("freemode"), "71 2E ? ? 55 ? ? 61 ? ? ? 47 ? ? 63", 0, {0x72}, nullptr }); // load island even if stranded animal IPL choice is not set
					menu::g_script_patcher_service->add_patch({ RAGE_JOAAT("freemode"), "2D 00 07 00 00 7B", 5, {0x2E, 0x00, 0x00}, nullptr }); // disable population load balancing
					menu::g_script_patcher_service->add_patch({ RAGE_JOAAT("shop_controller"), "38 00 5D ? ? ? 38 00 5D ? ? ? 38 00 41", 0, std::vector<uint8_t>(12, 0x0), nullptr }); // godmode/invisibility detection bypass*/

					/*for (auto& entry : *patterns::script_program)
					{
						if (entry.m_program)
							menu::g_script_patcher_service->on_script_load(entry.m_program);
					}*/

					util::fiber::add("F_BASE", [] {
						menu::notify::get_notify()->update();
					});

					util::fiber::add("F_MENU", [] {
						menu::getMainMenu()->update();
						menu::getSettingsMenu()->update();
						menu::getPlayerMenu()->update();
						menu::getSpawnerMenu()->update();
						menu::getNetworkMenu()->update();
						menu::getWeaponMenu()->update();
						menu::getVehicleMenu()->update();
						menu::getTeleportMenu()->update();
						menu::getProtectionsMenu()->update();
						menu::getRecoveryMenu()->update();
						menu::getWorldMenu()->update();
						menu::getMiscMenu()->update();
					});	

					call_once_loaded = true;
		
				}
				catch (std::exception& exception) {
					LOG("Exception initializing menu: %s", exception.what());
				}
			} 

			if (g_running && call_once_loaded) {
				util::fiber::update();
			}
		}

		context->set_return_value(STATS::STAT_GET_INT(context->get_arg<Hash>(0), context->get_arg<int*>(1), context->get_arg<int>(2)));
	}
}