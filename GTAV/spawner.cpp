#include "pch.h"
#include "spawner.h"
#include "hooks/patterns.h"
#include "rage/engine.h"
#include "gui/util/panels.h"
#include "spawner/spawner_settings.h"
#include "gui/util/notify.h"
using namespace base::gui;

using namespace menu::spawner::vars;

namespace menu::spawner::vars {
	variables m_vars;

	const char* submenu_name;
}

namespace menu {

	inline Vehicle spawn_vehicle(std::uint32_t hash) {
		if (!STREAMING::IS_MODEL_VALID(hash)) {
			return NULL;
		}
		rage::engine::request_model(hash);
		float forward = 5.f;
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
		float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
		float x = forward * sin(rage::engine::deg_to_rad(heading)) * -1.f;
		float y = forward * cos(rage::engine::deg_to_rad(heading));

		if (menu::spawner::settings::vars::m_vars.m_delete_current) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) {
				if (VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), -1, 0) == PLAYER::PLAYER_PED_ID()) {
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), true, true);
					Entity ent = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
					ENTITY::DELETE_ENTITY(&ent);
				}
			}
		}

		*(unsigned short*)patterns::set_this_thread_networked = 0x9090; // we set this thread as networked so we can spawn the vehicle / u can add rage classes and use excute under thread instead of this
		Vehicle the_vehicle = VEHICLE::CREATE_VEHICLE(hash, { coords.x + x, coords.y + y, coords.z }, heading, NETWORK::NETWORK_IS_SESSION_ACTIVE(), false, false);
		*(unsigned short*)patterns::set_this_thread_networked = 0x0574; // We restore it so we don't get detected 
		if (menu::spawner::settings::vars::m_vars.m_fade) {
			NETWORK::NETWORK_FADE_IN_ENTITY(the_vehicle, true, false);
		}
		
		std::int32_t net_id = NETWORK::VEH_TO_NET(the_vehicle);
		NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(net_id, TRUE);

		if (menu::spawner::settings::vars::m_vars.m_blip) {
			Blip blip = HUD::ADD_BLIP_FOR_ENTITY(the_vehicle);
			HUD::SET_BLIP_SPRITE(blip, 227);
			HUD::SET_BLIP_DISPLAY(blip, 8);
			HUD::SET_BLIP_CATEGORY(blip, 4);
		}

		if (menu::spawner::settings::vars::m_vars.m_teleport_inside) {
			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), the_vehicle, -1);
			VEHICLE::SET_VEHICLE_ENGINE_ON(the_vehicle, true, true, false);
		}

		if (menu::spawner::settings::vars::m_vars.m_godmode) {
			ENTITY::SET_ENTITY_INVINCIBLE(the_vehicle, true);
			ENTITY::SET_ENTITY_PROOFS(the_vehicle, true, true, true, true, true, true, true, true);
			VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(the_vehicle, false);
			VEHICLE::SET_VEHICLE_ENGINE_ON(the_vehicle, true, true, true);
		}


		if (menu::spawner::settings::vars::m_vars.m_notification) {
			menu::notify::stacked(std::format("{} {}", HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(hash)), "Spawned").c_str());
		}

		bool is_air_veh = VEHICLE::IS_THIS_MODEL_A_PLANE(hash) || VEHICLE::IS_THIS_MODEL_A_HELI(hash);

		if (menu::spawner::settings::vars::m_vars.m_air_vehicles_in_air && is_air_veh) {
			ENTITY::SET_ENTITY_COORDS(NETWORK::NET_TO_VEH(net_id), { coords.x, coords.y, coords.z + menu::spawner::settings::vars::m_vars.m_spawn_height }, false, false, false, false);
			VEHICLE::SET_VEHICLE_ENGINE_ON(NETWORK::NET_TO_VEH(net_id), true, true, false);
		}

		if (ENTITY::IS_ENTITY_VISIBLE_TO_SCRIPT(NETWORK::NET_TO_VEH(net_id))) {
			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), NETWORK::NET_TO_VEH(net_id), -1);
			float speed = ENTITY::GET_ENTITY_SPEED(the_vehicle);
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(NETWORK::NET_TO_VEH(net_id), speed);
			VEHICLE::SET_VEHICLE_ENGINE_ON(NETWORK::NET_TO_VEH(net_id), TRUE, TRUE, TRUE);
			DECORATOR::DECOR_SET_INT(NETWORK::NET_TO_VEH(net_id), "MPBitset", (1 << 10));
			return the_vehicle;
		}
		return NULL;
	}
	static bool active = false;
	void spawn_by_name() {
		MISC::DISPLAY_ONSCREEN_KEYBOARD(true, (char*)"Input", (char*)"", (char*)"", (char*)"", (char*)"", (char*)"", 256);
		while (MISC::UPDATE_ONSCREEN_KEYBOARD() == 0) {
			active = true;
			renderer::getRenderer()->reset_keys();
			util::fiber::go_to_main();
		}
		active = false;
		if (!MISC::GET_ONSCREEN_KEYBOARD_RESULT())
			return;
		std::string result = MISC::GET_ONSCREEN_KEYBOARD_RESULT();
		spawn_vehicle(rage::joaat(result));
	}

	void spawner_menu::render() {
		renderer::addSubmenu("Spawner", "Spawner", [](core* core) {
			
			core->addOption(submenuOption("Spawn Settings")
				.addTranslate()
				.setTarget("Spawner Settings"));

			core->addOption(submenuOption("Manage Spawned Vehicles")
				.addTranslate()
				.setTarget("Spawner Settings"));

			core->addOption(keyboardOption("Spawn by Name")
				.addClick([] { spawn_by_name(); }));

			core->addOption(breakOption("Vehicles"));

			for (std::int32_t i = 0; i < 23; i++) {
				core->addOption(submenuOption(rage::engine::get_vehicle_class_name(i))
					.addClick([=] { m_vars.m_selected_vehicle_class = i; })
					.setTarget(rage::engine::get_vehicle_class_name(m_vars.m_selected_vehicle_class)));
			}
		});


		renderer::addVehicleSubmenu(&m_vars.m_selected_vehicle_class, rage::joaat(rage::engine::get_vehicle_class_name(m_vars.m_selected_vehicle_class)), [](vcore* core) {
			if (patterns::hash_list != nullptr) {
				for (std::int32_t i = 0; i < patterns::hash_list->capacity; i++) {
					std::uint64_t info = patterns::hash_list->get(i);
					if (info != NULL) {
						if ((*(BYTE*)(info + 157) & 0x1F) == 5) {
							std::string make_ptr = (char*)((uintptr_t)info + 0x2A4);
							std::string model_ptr = (char*)((uintptr_t)info + 0x298);
							if (VEHICLE::GET_VEHICLE_CLASS_FROM_NAME(rage::joaat(model_ptr)) == m_vars.m_selected_vehicle_class) {
								std::stringstream ss;
								std::string make(make_ptr);
								std::string model(model_ptr);
								if (make[0] || model[0]) {
									model = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(model.c_str());
									if (model != "NULL") {
										ss << model;
									}
									else {
										ss << "Unknown";
									}
								}
								core->addOption(vehicleOption((ss.str().c_str()))
									.addClick([=] { spawn_vehicle(*(std::uint32_t*)(info + 0x18)); }));
							}
						}
					}
				}
			}
		});
	}
	
	void spawner_menu::update() {
		render();
		getSpawnerSettingsMenu()->update();
	}

}