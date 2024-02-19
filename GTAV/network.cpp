#include "pch.h"
#include "network.h"
#include "network/network_session.h"
#include "network/network_players.h"
#include "network/network_new_session.h"
#include "network/network_transitions.h"
#include "network/network_spoofing.h"
#include "network/network_friends.h"
#include "network//network_recent_players.h"
#include "network/network_tunables.h"
#include "network/network_global_chat.h"
#include "network/network_browsers.h"
using namespace base::gui;
using namespace menu::network::vars;

namespace menu::network::vars {
	variables m_vars;
	const char* targeting_mode[] = {
		"Traditional", "Free Aim", "Assisted Aim", "Assisted Aim - Full", "Assisted Aim - Partial"
	};

	int targeting_mode_id = 0;
}

namespace menu {

	void network_menu::render() {
		renderer::addSubmenu("Network", "Network", [](core* core) {
			core->addOption(submenuOption("Players")
				.setTarget("Network Players"));

			core->addOption(submenuOption("New Session")
				.setTarget("Network New Session"));

			core->addOption(submenuOption("Session")
				.setTarget("Network Session"));

			core->addOption(submenuOption("Transitions")
				.setTarget("Network Transitions"));

			core->addOption(submenuOption("Spoofing")
				.setTarget("Network Spoofing"));

			core->addOption(submenuOption("Browsers")
				.setTarget("Network Browsers"));

			core->addOption(submenuOption("Friends")
				.setTarget("Network Friends"));

			core->addOption(submenuOption("Recent Players")
				.setTarget("Network Recent Players"));

			core->addOption(submenuOption("Tunables")
				.setTarget("Network Tunables"));

			core->addOption(submenuOption("Visuals")
				.setTarget("Network Visuals"));

			core->addOption(submenuOption("Global Chat")
				.setTarget("Network Chat"));

			core->addOption(submenuOption("Request Services")
				.setTarget("Request Services"));

			core->addOption(submenuOption("Set Targeting Mode")
				.setTarget("Set Targeting Mode"));
		});

		renderer::addSubmenu("Visuals", "Network Visuals", [](core* core) {
			core->addOption(toggleOption("Box")
				.addToggle(&m_vars.m_esp_box));

			core->addOption(toggleOption("Line")
				.addToggle(&m_vars.m_esp_line));

			core->addOption(toggleOption("Name")
				.addToggle(&m_vars.m_esp_name));
		});


		renderer::addSubmenu("Set Targeting Mode", "Set Targeting Mode", [](core* core) {
			for (const auto& mode : targeting_mode) {
				core->addOption(buttonOption(mode)
					.addClick([=] {
						PLAYER::SET_PLAYER_TARGETING_MODE(mode[targeting_mode_id]);
				}));
			}
		});

		renderer::addSubmenu("Request Services", "Request Services", [](core* core) {
			core->addOption(buttonOption("Request Airstrike")
				.addClick([] { rage::engine::request_airstrike(); }));

			core->addOption(buttonOption("Request Ammo Drop")
				.addClick([] { rage::engine::request_ammo_drop(); }));

			core->addOption(buttonOption("Request Boat Pickup")
				.addClick([] { rage::engine::request_boat_pickup(); }));

			core->addOption(buttonOption("Request Ballistic Armour")
				.addClick([] { rage::engine::request_ballistic_armor(); }));

			core->addOption(buttonOption("Request Helicopter Pickup")
				.addClick([] { rage::engine::request_helicopter_pickup(); }));

			core->addOption(buttonOption("Request Helicopter Backup")
				.addClick([] { rage::engine::request_backup_helicopter(); }));
		});
	}

	void network_menu::update() {
		render();
		getNetworkPlayersMenu()->update();
		getNetworkSessionMenu()->update();
		getNetworkNewSessionMenu()->update();
		getNetworkTransitionsMenu()->update();
		getNetworkSpoofingMenu()->update();
		getNetworkFriendsMenu()->update();
		getNetworkRecentPlayersMenu()->update();
		getNetworkTunablesMenu()->update();
		getNetworkChatMenu()->update();
		getNetworkBrowsersMenu()->update();

		if (m_vars.m_esp_box)
		{
			for (uint32_t j = 0; j < 32; j++) {
				Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(j), false);
				if (!coords.empty()) {
					Vector3 min_dimensions;
					Vector3 max_dimensions;
					MISC::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(j)), &min_dimensions, &max_dimensions);

					Vector3 diameter = { max_dimensions.x - min_dimensions.x, max_dimensions.y - min_dimensions.y, max_dimensions.z - min_dimensions.z };
					Vector3 radius = { diameter.x / 2.f, diameter.y / 2.f, diameter.z / 2.f };

					Vector3 FACE_UL = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(j), { radius.x * -1, radius.y, radius.z });
					Vector3 FACE_UR = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(j), { radius.x, radius.y, radius.z });
					Vector3 FACE_BL = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(j), { radius.x * -1, radius.y, radius.z * -1 });
					Vector3 FACE_BR = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(j), { radius.x, radius.y, radius.z * -1 });

					Vector3 BACK_UL = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(j), { radius.x * -1, radius.y * -1, radius.z });
					Vector3 BACK_UR = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(j), { radius.x, radius.y * -1, radius.z });
					Vector3 BACK_BL = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(j), { radius.x * -1, radius.y * -1, radius.z * -1 });
					Vector3 BACK_BR = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(j), { radius.x, radius.y * -1, radius.z * -1 });

					// Poles
					GRAPHICS::DRAW_LINE(FACE_BL, FACE_UL, m_vars.m_3d_box_color.r, m_vars.m_3d_box_color.g, m_vars.m_3d_box_color.b, 255);
					GRAPHICS::DRAW_LINE(FACE_BR, FACE_UR, m_vars.m_3d_box_color.r, m_vars.m_3d_box_color.g, m_vars.m_3d_box_color.b, 255);
					GRAPHICS::DRAW_LINE(BACK_BL, BACK_UL, m_vars.m_3d_box_color.r, m_vars.m_3d_box_color.g, m_vars.m_3d_box_color.b, 255);
					GRAPHICS::DRAW_LINE(BACK_BR, BACK_UR, m_vars.m_3d_box_color.r, m_vars.m_3d_box_color.g, m_vars.m_3d_box_color.b, 255);
					GRAPHICS::DRAW_LINE(FACE_UL, FACE_UR, m_vars.m_3d_box_color.r, m_vars.m_3d_box_color.g, m_vars.m_3d_box_color.b, 255);
					GRAPHICS::DRAW_LINE(FACE_BL, FACE_BR, m_vars.m_3d_box_color.r, m_vars.m_3d_box_color.g, m_vars.m_3d_box_color.b, 255);
					GRAPHICS::DRAW_LINE(BACK_UL, BACK_UR, m_vars.m_3d_box_color.r, m_vars.m_3d_box_color.g, m_vars.m_3d_box_color.b, 255);
					GRAPHICS::DRAW_LINE(BACK_BL, BACK_BR, m_vars.m_3d_box_color.r, m_vars.m_3d_box_color.g, m_vars.m_3d_box_color.b, 255);

					// Bridges
					GRAPHICS::DRAW_LINE(FACE_UL, BACK_UL, m_vars.m_3d_box_color.r, m_vars.m_3d_box_color.g, m_vars.m_3d_box_color.b, 255);
					GRAPHICS::DRAW_LINE(FACE_UR, BACK_UR, m_vars.m_3d_box_color.r, m_vars.m_3d_box_color.g, m_vars.m_3d_box_color.b, 255);
					GRAPHICS::DRAW_LINE(FACE_BL, BACK_BL, m_vars.m_3d_box_color.r, m_vars.m_3d_box_color.g, m_vars.m_3d_box_color.b, 255);
					GRAPHICS::DRAW_LINE(FACE_BR, BACK_BR, m_vars.m_3d_box_color.r, m_vars.m_3d_box_color.g, m_vars.m_3d_box_color.b, 255);

					// Inner Bridges
					GRAPHICS::DRAW_LINE(coords, FACE_UL, m_vars.m_3d_box_color.r, m_vars.m_3d_box_color.g, m_vars.m_3d_box_color.b, 255);
					GRAPHICS::DRAW_LINE(coords, FACE_UR, m_vars.m_3d_box_color.r, m_vars.m_3d_box_color.g, m_vars.m_3d_box_color.b, 255);
					GRAPHICS::DRAW_LINE(coords, FACE_BL, m_vars.m_3d_box_color.r, m_vars.m_3d_box_color.g, m_vars.m_3d_box_color.b, 255);
					GRAPHICS::DRAW_LINE(coords, FACE_BR, m_vars.m_3d_box_color.r, m_vars.m_3d_box_color.g, m_vars.m_3d_box_color.b, 255);
					GRAPHICS::DRAW_LINE(coords, BACK_UL, m_vars.m_3d_box_color.r, m_vars.m_3d_box_color.g, m_vars.m_3d_box_color.b, 255);
					GRAPHICS::DRAW_LINE(coords, BACK_UR, m_vars.m_3d_box_color.r, m_vars.m_3d_box_color.g, m_vars.m_3d_box_color.b, 255);
					GRAPHICS::DRAW_LINE(coords, BACK_BL, m_vars.m_3d_box_color.r, m_vars.m_3d_box_color.g, m_vars.m_3d_box_color.b, 255);
					GRAPHICS::DRAW_LINE(coords, BACK_BR, m_vars.m_3d_box_color.r, m_vars.m_3d_box_color.g, m_vars.m_3d_box_color.b, 255);
				}
			
			}

		}
		if (m_vars.m_esp_line)
		{
			for (uint32_t j = 0; j < 32; j++) {
				Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(j), false);
				if (!coords.empty()) {
					GRAPHICS::DRAW_LINE(ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true), coords, m_vars.m_snapline_color.r, m_vars.m_snapline_color.g, m_vars.m_snapline_color.b, 255);
				}
			}
		}
		if (m_vars.m_esp_name)
		{
			for (std::uint32_t i = 0; i < PLAYER::GET_NUMBER_OF_PLAYERS(); ++i) {
				Vector3 pHCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), { 0, 0, 0 });

				float xPos;
				float yPos;

				BOOL screencoords = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(pHCoords, &xPos, &yPos);

				HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char*)"STRING");
				HUD::SET_TEXT_COLOUR(255, 255, 255, 255);
				HUD::SET_TEXT_FONT(0);
				HUD::SET_TEXT_SCALE(0.3f, 0.3f);
				HUD::SET_TEXT_CENTRE(true);

				std::string name = PLAYER::GET_PLAYER_NAME(i);
				/*if (distance) {
					NativeVector3 Coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), false);
					float distance = GetDistanceFloat(ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false), Coords);
					name.append(std::format("\n{}", (int)distance));
				}*/
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(name.c_str());
				HUD::END_TEXT_COMMAND_DISPLAY_TEXT({ xPos, yPos }, 0);
			}
			
		}
	}
}