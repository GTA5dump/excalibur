#pragma once

#include "gui/options/core.h"
#include "gui/options/submenu.h"
#include "gui/options/option.h"
#include "gui/options/button.h"
#include "gui/options/submenu_option.h"
#include "gui/options/number.h"
#include "gui/options/toggle.h"
#include "gui/options/scroll.h"
#include "gui/options/break.h"
namespace menu {
	class misc_menu {
	public:
		void render();
		void update();
	};

	static misc_menu* getMiscMenu() {
		static misc_menu instance;
		return &instance;
	}


	namespace misc::vars {

		struct spawned_ped
		{
			Ped ped_handle;
			Player spawned_for_player;
		};
		struct variables {
			bool m_disable_police_automobile;
			bool m_disable_police_helicopter;
			bool m_disable_police_riders;
			bool m_disable_police_vehicle_request;
			bool m_disable_police_roadblock;
			bool m_disable_police_boat;
			bool m_disable_swat_automobile;
			bool m_disable_swat_helicopter;
			bool m_disable_fire_department;
			bool m_disable_ambulance_department;
			bool m_disable_gangs;
			bool m_disable_army_vehicle;
			bool m_disable_bikers;
			bool instant_alt_f4;
			bool dev_dlc;
			bool bypass_country_restricions = true;
			bool toggle_zoom;
			float cam_zoom = 1;
			bool free_cam;
			bool anti_crash_cam;
			bool gta_cam;
			int gta_cam_distance = 20;
			bool mobile_radio;
			bool disable_idle_kick;
			bool disable_cutscene;
			bool disable_phone;
			bool disable_cinematics;
			bool bypass_chat;
			bool disable_filter;
			bool disable_chat_messages;
			bool disable_text_messages;
			bool disable_notifications;
			bool disable_hud;
			bool disable_map;
			bool disable_restrictions;
			bool disable_world_limit;
			bool snow_trails;
			bool no_orbital_cannon_cooldown;
			bool display_fps;
			bool display_system_time;
			bool display_coords;
			bool display_pool_count;
			bool display_connected_players;
			bool m_toggle_phone_scale;
			float m_phone_scale = 500.f;
			Vector3 m_phone_pos = { 2, -13, 0 };
			float m_phone_pitch = 12;
			float m_phone_roll;
			float m_phone_yaw;
			std::string model = "Adder";
			std::string new_model = "T20";
			bool m_toggle_fov;
			float m_fov = 50.f;
			Cam m_freecam_handle;
			Cam m_anti_crash_handle;
			Cam m_gta_cam_handle;
			int hud_r;
			int hud_g;
			int hud_b;
			int hud_a = 255;
			int m_hud;
			std::vector<std::pair<std::string, std::string>> models;
			std::mutex m;
			bool update = false;
			std::string HUD_MPREENTER = { "Joining Session with Excalibur" };
			std::string HUD_JOINING = { "Loading GTA Online with Excalibur" };
			std::string PM_QUIT_MP = { "Leave GTA Online with Excalibur" };
			std::string PM_ENTER_MP = { "Join GTA Online with Excalibur" };
			std::string PM_EXIT_GAME = { "Exit Game with Excalibur" };
			std::string PM_GO = { "Go Online with Excalibur" };
			std::string PM_FRIEND_FM = { "Join Friend with Excalibur" };
			std::string PM_FIND_SESS = { "Find New Session with Excalibur" };

			bool drive_train;
			bool render_as_derailed;

			bool tv;
			int channel;
			float x = 0.84f;
			float y = 0.20f;
			float w = 0.26f;
			float h = 0.27f;
			float rotation;

			std::vector<spawned_ped> spawned_bodyguards;

			bool spawn_godmode;
			bool spawn_invisible;
		};

		extern variables m_vars;
	}
}