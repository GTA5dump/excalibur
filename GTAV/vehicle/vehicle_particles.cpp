#include "pch.h"
#include "vehicle_particles.h"
#include "menu/util/globals.h"
#include "gui/options/option.h"
#include "gui/util/panels.h"
#include "rage/classes/CPed.h"
#include "rage/classes/CPlayerInfo.h"
#include "menu/util/control.h"
#include "menu/util/raycast.h"
#include "gui/util/notify.h"
#include "gui/util/timer.h"
using namespace base::gui;
using namespace menu::vehicle::particles::vars;

namespace menu::vehicle::particles::vars {
	variables m_vars;


	struct particle { const char* name; const char* dict; const char* texture; };

	std::vector<particle> particles = {
		{"Purple Cloud 1", "scr_rcbarry2", "scr_clown_appears" },
		{"Purple Cloud 2", "scr_rcbarry2", "scr_clown_death" },
		{"Purple Cloud 3", "scr_rcbarry2", "scr_exp_clown" },
		{"Firework Starburst", "scr_indep_fireworks", "scr_indep_firework_starburst" },
		{"Firework Fountain", "scr_indep_fireworks", "scr_indep_firework_fountain" },
		{"Firework Shotburst", "scr_indep_fireworks", "scr_indep_firework_shotburst" },
		{"Xmas Firework Burst", "proj_xmas_firework", "scr_firework_xmas_spiral_burst_rgw" },
		{"Teleport", "scr_rcbarry1", "scr_alien_teleport" },
		{"Disintegration", "scr_rcbarry1", "scr_alien_disintegrate" },
		{"Drip", "scr_agencyheist", "scr_fbi_mop_drips" },
		{"Flower Jet", "scr_rcbarry2", "scr_clown_bul" },
		{"Flash", "scr_rcpaparazzo1", "scr_rcpap1_camera" },
		{"Blue Flash", "scr_rcbarry1", "scr_alien_impact_bul" },
		{"Burnout", "scr_recartheft", "scr_wheel_burnout" },
		{"Splash", "scr_trevor1", "scr_trev1_trailer_splash" },
		{"Blood", "scr_solomon3", "scr_trev4_747_blood_impact" },
		{"Sparks", "scr_family4", "scr_fam4_trailer_sparks" },
		{"Shock", "scr_trevor1", "scr_trev1_trailer_boosh" },
		{"Money Cloud", "scr_ornate_heist", "scr_heist_ornate_banknotes" },
		{"Tire Smoke", "scr_carsteal4", "scr_carsteal4_wheel_burnout" },
		{"Clouds",  "wpn_projectile", "proj_missile_trail" },
		{"Golf Trail", "scr_minigamegolf", "scr_golf_ball_trail" },
		{"Tennis Trail", "scr_minigametennis", "scr_tennis_ball_trail" },
		{"Water Trail",  "core", "trail_splash_water" },
		{"Parachute Trail",  "core", "ped_parachute_trail" },
		{"Flare Trail",  "core", "proj_flare_trail" },
		{"Blood Trail",  "core", "trail_splash_blood" },
		{"Grenade Trail",  "wpn_projectile", "proj_grenade_trail" },
		{"Flaregun Trail",  "wpn_projectile", "proj_flare_trail" },
	};

	const char* particleNames[] = {
	"Purple Cloud 1",
	"Purple Cloud 2",
	"Purple Cloud 3",
	"Firework Starburst",
	"Firework Fountain",
	"Firework Shotburst",
	"Xmas Firework Burst",
	"Teleport",
	"Disintegration",
	"Drip",
	"Flower Jet",
	"Flash",
	"Blue Flash",
	"Burnout",
	"Splash",
	"Blood",
	"Sparks",
	"Shock",
	"Money Cloud",
	"Tire Smoke",
	"Clouds",
	"Golf Trail",
	"Tennis Trail",
	"Water Trail",
	"Parachute Trail",
	"Flare Trail",
	"Blood Trail",
	"Grenade Trail",
	"Flaregun Trail"
	}; int particle_id = 0;

	template<typename Type>
	struct scroll_struct {
		const char* m_name;
		Type m_result;

	};

	struct VehicleBone {
		std::string name;
		const char* boneName;
	};

	std::vector<VehicleBone> vehicle_bones = {
		{ "Front Left Wheel", "wheel_lf" },
		{ "Front Right Wheel", "wheel_rf" },
		{ "Rear Left Wheel", "wheel_lr" },
		{ "Rear Right Wheel", "wheel_rr" },
		{ "Left Tail Light", "taillight_l" },
		{ "Left Headlight", "headlight_l" },
		{ "Right Tail Light", "taillight_r" },
		{ "Right Headlight", "headlight_r" },
		{ "Exhaust", "exhaust" }
	};
}



namespace menu {

	void vehicle_particles_menu::render() {
		renderer::addSubmenu("Vehicle Particles", "Vehicle Particles", [](core* core) {
			const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

			core->addOption(toggleOption("Toggle Particles")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_toggle));

			core->addOption(scrollOption<const char*, int>("Type")
				.addScroll(&particleNames).setPosition(&particle_id));

			core->addOption(numberOption<float>("Scale")
				.addNumber(&m_vars.m_scale)
				.addMin(0).addMax(10)
				.addStep(0.01f).setPrecision(2));

			core->addOption(breakOption("Bones"));

			for (int i = 0; i < vehicle_bones.size(); i++) {
				VehicleBone bone = vehicle_bones[i];

				if (ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, bone.boneName) > 0) {
					core->addOption(toggleOption(bone.name.c_str())
						.addToggle(&m_vars.m_bones[i]));
				}
				else {
					m_vars.m_bones[i] = false;
					core->addOption(buttonOption("~c~Empty"));
				}
			}
		});
	}

	void vehicle_particles_menu::update() {
		render();
		
		static int timer[11];
		static int timer2[16];

		const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) {
			if (m_vars.m_toggle) {
				for (int i = 0; i < vehicle_bones.size(); i++) {
					if (m_vars.m_bones[i]) {
						if (i == vehicle_bones.size() - 1) {
							for (int j = 0; j < 16; j++) {
								int index = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, j == 0 ? "exhaust" : std::format("exhaust_{}", j).c_str());

								if (index) {
									Vector3 coords = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, index);
									if (!coords.empty()) {
										particle particle = particles[particle_id];

										run_timed(&timer2[j], 100, [=] {
											STREAMING::REQUEST_NAMED_PTFX_ASSET(particle.dict);
											GRAPHICS::USE_PARTICLE_FX_ASSET(particle.dict);
											GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particle.texture, coords, { 0.f, 0.f, 0.f }, m_vars.m_scale, false, false, false, false);
										});
									}
								}
							}
						}
						else {
							VehicleBone bone = vehicle_bones[i];
							int index = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, bone.boneName);

							if (index) {
								Vector3 coords = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, index);
								if (!coords.empty()) {
									particle particle = particles[particle_id];

									run_timed(&timer[i], 100, [=] {
										STREAMING::REQUEST_NAMED_PTFX_ASSET(particle.dict);
										GRAPHICS::USE_PARTICLE_FX_ASSET(particle.dict);
										GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(particle.texture, coords, { 0.f, 0.f, 0.f }, m_vars.m_scale, false, false, false, false);
									});
								}
							}
							else {
								m_vars.m_bones[i] = false;
							}
						}
					}
				}
			}
		}
	}
}