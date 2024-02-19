#include "pch.h"
#include "particles.h"
#include "features/manager/manager.h"
#include "menu/util/globals.h"
#include "gui/options/option.h"
#include "gui/util/panels.h"
#include "rage/classes/CPed.h"
#include "menu/util/control.h"
using namespace base::gui;
using namespace menu::player::particles::vars;

namespace menu::player::particles::vars {

	variables m_vars;

	void start_particle(const char* dict, const char* texture, bool toggle) {
		if (toggle) {
			STREAMING::REQUEST_NAMED_PTFX_ASSET(dict);
			GRAPHICS::USE_PARTICLE_FX_ASSET(dict);
			GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_ENTITY(texture, PLAYER::PLAYER_PED_ID(), { 0, 0, 0 }, { 0, 0, 0 }, 0.5f, 0, 0, 0);
		}
		
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


}

namespace menu {
	void player_particles_menu::render() {
		renderer::addSubmenu("Particles", "Player Particles", [](core* core) {
			for (const auto particle : particles) {
				core->addOption(toggleOption(particle.name)
					.addTranslate().addHotkey()
					.addToggle(&m_vars.m_particleToggles[particle.name])
					.addClick([=] {
						if (m_vars.m_particleToggles[particle.name]) {
							start_particle(particle.dict, particle.texture, m_vars.m_particleToggles[particle.name]);
						}
					}));
			}
		});
	}

	void player_particles_menu::update() {
		render();

		for (const auto particle : particles) {
			start_particle(particle.dict, particle.texture, m_vars.m_particleToggles[particle.name]);
		}
	}
}