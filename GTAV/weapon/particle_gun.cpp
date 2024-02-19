#include "pch.h"
#include "particle_gun.h"
#include "menu/util/globals.h"
#include "gui/options/option.h"
#include "gui/util/panels.h"
#include "rage/classes/CPed.h"
#include "rage/classes/CPlayerInfo.h"
#include "menu/util/control.h"
#include "menu/util/raycast.h"
#include "gui/util/timer.h"


using namespace base::gui;
using namespace menu::weapon::particle_gun::vars;

namespace menu::weapon::particle_gun::vars {
	variables m_vars;

	CWeaponInfo* get_weapon_info() {
		CPed* ped = (*patterns::ped_factory)->m_local_ped;
		if (ped) {
			CPedWeaponManager* weapon_manager = ped->m_weapon_manager;
			if (weapon_manager) {
				return weapon_manager->m_weapon_info;
			}
		}

		return nullptr;
	}

	Vector3 get_direction(Vector3 rotation) {
		Vector3 tmp;
		tmp.y = rotation.z * 0.0174532924f;
		tmp.x = rotation.x * 0.0174532924f;
		tmp.z = abs(cos(tmp.x));

		return Vector3((-sin(tmp.y)) * tmp.z, (cos(tmp.y)) * tmp.z, sin(tmp.x));
	}

	bool isPedShooting(Ped ped) {
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(ped, 1);
		return PED::IS_PED_SHOOTING_IN_AREA(ped, coords, coords, true, true);
	}

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

	template<typename Type>
	struct scroll_struct {
		const char* m_name;
		Type m_result;
	};
	
}



namespace menu {

	void particle_gun_menu::render() {
		renderer::addSubmenu("Particle Gun", "Weapon Particle Gun", [](core* core) {
			core->addOption(toggleOption("Toggle Particle Gun")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_toggle));

			core->addOption(numberOption<float>("Scale")
				.addNumber(&m_vars.m_scale).addStep(0.01).addMin(0).addMax(10).setPrecision(2));

			core->addOption(breakOption("Particles"));

			for (int i = 0; i < particles.size(); i++) {
				core->addOption(toggleOption(particles[i].name)
					.addToggle(&m_vars.m_context.m_toggles[i]));
			}
		});
	}

	void particle_gun_menu::update() {
		render();

		WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &m_vars.m_weapon_hash, false);
		m_vars.m_has_weapon_in_hand = (m_vars.m_weapon_hash && m_vars.m_weapon_hash != 2725352035);

		// Update the selected particle index
		int previousSelectedParticleIndex = m_vars.m_context.m_selected;
		for (int i = 0; i < particles.size(); i++) {
			if (m_vars.m_context.m_toggles[i]) {
				m_vars.m_context.m_selected = i;
				break;
			}
		}

		// Uncheck other particle toggles if a different particle is selected
		if (previousSelectedParticleIndex != m_vars.m_context.m_selected) {
			for (int i = 0; i < particles.size(); i++) {
				if (i != m_vars.m_context.m_selected) {
					m_vars.m_context.m_toggles[i] = false;
				}
			}
		}

		if (m_vars.m_toggle) {
			if (isPedShooting(PLAYER::PLAYER_PED_ID())) {
				auto BulletCoord = raycast::m_ShapeTestDestination;
				if (!raycast::IsEmpty(BulletCoord)) {
					int selectedParticleIndex = m_vars.m_context.m_selected;
					if (selectedParticleIndex >= 0 && selectedParticleIndex < particles.size()) {
						particle selectedParticle = particles[selectedParticleIndex];

						STREAMING::REQUEST_NAMED_PTFX_ASSET(selectedParticle.dict);
						GRAPHICS::USE_PARTICLE_FX_ASSET(selectedParticle.dict);

						GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD(selectedParticle.texture, BulletCoord, { 0.f, 0.f, 0.f }, m_vars.m_scale, false, false, false);
					}
				}
			}
		}
	}
}