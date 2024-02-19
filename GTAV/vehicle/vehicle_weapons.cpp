#include "pch.h"
#include "vehicle_weapons.h"
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
using namespace menu::vehicle::weapons::vars;

namespace menu::vehicle::weapons::vars {
	variables m_vars;

	struct vehicle_weapon_context {
		std::string name;
		uint32_t weaponHash;
	};

	std::vector<vehicle_weapon_context> vehicle_weapons = {
		{ "RPG", 0xb1ca77b1 },
		{ "Snowball", 0x787F0BB },
		{ "Firework", 0x7f7497e5 },
		{ "Flare", 0x497FACC3 },
		{ "Player Laser", 0xeffd014b },
		{ "Enemy Laser", 0x5d6660ab },
		{ "Space Rocket", 0xf8a3939f },
		{ "Player Bullet", 0x4b139b2d },
		{ "Player Buzzard", 0x46b89c8e }
	};
}



namespace menu {

	void vehicle_weapons_menu::render() {
		renderer::addSubmenu("Vehicle Weapons", "Vehicle Weapons", [](core* core) {
			const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

			core->addOption(toggleOption("Toggle Weapons")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_toggle));

			core->addOption(toggleOption("Aiming Lines")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_aiming_lines));

			core->addOption(numberOption<float>("Bullet Speed")
				.addNumber(&m_vars.m_bullet_spped)
				.addMin(0).addMax(10000)
				.addStep(1.f).setPrecision(0));

			core->addOption(breakOption("Bullets"));


			for (int i = 0; i < vehicle_weapons.size(); i++) {
				core->addOption(toggleOption(vehicle_weapons[i].name.c_str())
					.addToggle(&m_vars.m_context.m_toggles[i]));
			}
		});
	}

	void vehicle_weapons_menu::update() {
		render();

		// Update the selected particle index
		int previousSelectedParticleIndex = m_vars.m_context.m_selected;
		for (int i = 0; i < vehicle_weapons.size(); i++) {
			if (m_vars.m_context.m_toggles[i]) {
				m_vars.m_context.m_selected = i;
				break;
			}
		}

		// Uncheck other particle toggles if a different particle is selected
		if (previousSelectedParticleIndex != m_vars.m_context.m_selected) {
			for (int i = 0; i < vehicle_weapons.size(); i++) {
				if (i != m_vars.m_context.m_selected) {
					m_vars.m_context.m_toggles[i] = false;
				}
			}
		}

		const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) {
			if (m_vars.m_toggle) {
				notify::subtitle("Press + To Shoot");
				static int Timer = 0;

				Vector3 model_size_min;
				Vector3 model_size_max;
				MISC::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(vehicle), &model_size_min, &model_size_max);

				Vector3 calculation = model_size_max - model_size_min;

				Vector3 origin_left = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(vehicle, { calculation.x / 4.f, model_size_max.y + 1.f, 0.5f });
				Vector3 origin_right = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(vehicle, { -(calculation.x / 4.f), model_size_max.y + 1.f, 0.5f });
				Vector3 target_left = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(vehicle, { (calculation.x / 4.f) + 8.f, model_size_max.y + 300.f, 0.5f });
				Vector3 target_right = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(vehicle, { -(calculation.x / 4.f) - 8.f, model_size_max.y + 300.f, 0.5f });

				run_timed(&Timer, 100, [=] {
					if (Util::is_key_pressed(VK_ADD)) {
						menu::control::requestWeapon(vehicle_weapons[m_vars.m_context.m_selected].weaponHash);
						MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS_IGNORE_ENTITY(origin_right, target_right, 250, 0, vehicle_weapons[m_vars.m_context.m_selected].weaponHash, 0, true, false, ENTITY::GET_ENTITY_SPEED(vehicle) + m_vars.m_bullet_spped, vehicle, 0);
						MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS_IGNORE_ENTITY(origin_left, target_left, 250, 0, vehicle_weapons[m_vars.m_context.m_selected].weaponHash, 0, true, false, ENTITY::GET_ENTITY_SPEED(vehicle) + m_vars.m_bullet_spped, vehicle, 0);
					}
				});

				if (m_vars.m_aiming_lines) {
					GRAPHICS::DRAW_LINE(origin_right, target_right, 255, 0, 0, 255);
					GRAPHICS::DRAW_LINE(origin_left, target_left, 255, 0, 0, 255);
				}
			}
		}
	}
}