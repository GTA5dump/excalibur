#include "pch.h"
#include "weapon_disables.h"
#include "menu/util/globals.h"
#include "gui/options/option.h"
#include "gui/util/panels.h"
#include "rage/classes/CPed.h"
#include "rage/classes/CPlayerInfo.h"
#include "menu/util/control.h"
#include "menu/util/raycast.h"

#include "paint_gun.h"
#include "aimbot.h"
using namespace base::gui;
using namespace menu::weapon::disables::vars;

namespace menu::weapon::disables::vars {
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
}



namespace menu {

	void weapon_disables_menu::render() {
		renderer::addSubmenu("Disables", "Weapon Disables", [](core* core) {

			core->addOption(toggleOption("Vehicle Block")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_vehicle_block)
				.addTooltip("Allows you to equip any weapon on a vehicle"));

			core->addOption(toggleOption("Passive Block")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_passive_block)
				.addTooltip("Allows you to equip weapon while in passive mode"));

			core->addOption(toggleOption("Interior Block")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_interior_block)
				.addTooltip("Allows you to equip weapons while in apartments"));

			core->addOption(toggleOption("Spread")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_spread)
				.addTooltip("Disable spread")
				.addClick([] {
					if (!m_vars.m_spread) {
						if (get_weapon_info()) {
							if (m_vars.m_original_spread.find(get_weapon_info()) != m_vars.m_original_spread.end()) {
								get_weapon_info()->m_batch_spread = m_vars.m_original_spread[get_weapon_info()].first;
								get_weapon_info()->m_accuracy_spread = m_vars.m_original_spread[get_weapon_info()].second;
							}
						}
					}
					}));

			core->addOption(toggleOption("Recoil")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_recoil)
				.addTooltip("Disable recoil")
				.addClick([] {
					if (!m_vars.m_recoil) {
						if (get_weapon_info()) {
							if (m_vars.m_original_recoil.find(get_weapon_info()) != m_vars.m_original_recoil.end()) {
								get_weapon_info()->m_recoil_shake_amplitude = m_vars.m_original_recoil[get_weapon_info()].first;
								get_weapon_info()->m_explosion_shake_amplitude = m_vars.m_original_recoil[get_weapon_info()].second;
							}
						}
					}
					}));

			core->addOption(toggleOption("Recharge")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_recharge)
				.addTooltip("Disable recharge on weapons such as railgun, stungun etc")
				.addClick([] {
					if (!m_vars.m_recharge) {
						if (get_weapon_info()) {
							if (m_vars.m_original_time_between_shots.find(get_weapon_info()) != m_vars.m_original_time_between_shots.end()) {
								get_weapon_info()->m_time_between_shots = m_vars.m_original_time_between_shots[get_weapon_info()];
							}
						}
					}
					}));

			core->addOption(toggleOption("Spin Delay")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_spin_delay)
				.addTooltip("Disable spin time wait on the minigun")
				.addClick([] {
					if (!m_vars.m_spin_delay) {
						if (get_weapon_info()) {
							if (m_vars.m_original_instant_spin.find(get_weapon_info()) != m_vars.m_original_instant_spin.end()) {
								get_weapon_info()->m_spinup_time = m_vars.m_original_instant_spin[get_weapon_info()].first;
								get_weapon_info()->m_spindown_time = m_vars.m_original_instant_spin[get_weapon_info()].second;
							}
						}
					}
					}));

			core->addOption(toggleOption("Reload Animation")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_reload_animation)
				.addTooltip("Disables the reload animation and reloads the clip instantly")
				.addClick([] {
					if (!m_vars.m_reload_animation) {
						if (get_weapon_info()) {
							if (m_vars.m_original_anim_reload_rate.find(get_weapon_info()) != m_vars.m_original_anim_reload_rate.end()) {
								get_weapon_info()->m_anim_reload_time = m_vars.m_original_anim_reload_rate[get_weapon_info()];
							}
						}
					}
					}));
		});
	}

	void weapon_disables_menu::update() {
		render();
		
		uint32_t m_weapon_hash = 0;
		WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &m_weapon_hash, false);

		m_vars.m_has_weapon_in_hand = (m_weapon_hash && m_weapon_hash != 2725352035);

		if (m_vars.m_has_weapon_in_hand) {
			if (m_vars.m_reload_animation) {
				CWeaponInfo* weapon_info = get_weapon_info();
				if (weapon_info) {
					if (weapon_info->m_name != 0xb1ca77b1
						&& weapon_info->m_name != 0x7f7497e5
						&& weapon_info->m_name != 0x63ab0442) {
						if (m_vars.m_original_anim_reload_rate.find(get_weapon_info()) == m_vars.m_original_anim_reload_rate.end()) {
							m_vars.m_original_anim_reload_rate[weapon_info] = weapon_info->m_anim_reload_time;
						}

						weapon_info->m_anim_reload_time = 100.f;
					}
				}
			}

			if (m_vars.m_spread) {
				CWeaponInfo* weapon_info = get_weapon_info();
				if (weapon_info) {
					if (m_vars.m_original_spread.find(get_weapon_info()) == m_vars.m_original_spread.end()) {
						m_vars.m_original_spread[weapon_info].first = weapon_info->m_batch_spread;
						m_vars.m_original_spread[weapon_info].second = weapon_info->m_accuracy_spread;
					}

					weapon_info->m_batch_spread = 0.f;
					weapon_info->m_accuracy_spread = 0.f;
				}
			}

			if (m_vars.m_recoil) {
				CWeaponInfo* weapon_info = get_weapon_info();
				if (weapon_info) {
					if (m_vars.m_original_recoil.find(get_weapon_info()) == m_vars.m_original_recoil.end()) {
						m_vars.m_original_recoil[weapon_info].first = weapon_info->m_recoil_shake_amplitude;
						m_vars.m_original_recoil[weapon_info].second = weapon_info->m_explosion_shake_amplitude;
					}

					weapon_info->m_recoil_shake_amplitude = 0.f;
					weapon_info->m_explosion_shake_amplitude = 0.f;
				}
			}

			if (m_vars.m_recharge) {
				if (m_weapon_hash == 0x6d544c99
					|| m_weapon_hash == 0xaf3696a1
					|| m_weapon_hash == 0x3656c8c1) {
					CWeaponInfo* weapon_info = get_weapon_info();
					if (weapon_info) {
						if (m_vars.m_original_time_between_shots.find(get_weapon_info()) == m_vars.m_original_time_between_shots.end()) {
							m_vars.m_original_time_between_shots[weapon_info] = weapon_info->m_time_between_shots;
						}

						weapon_info->m_time_between_shots = 0.f;
					}
				}
			}

			if (m_vars.m_spin_delay) {
				if (m_weapon_hash == 0x42bf8a85) {
					CWeaponInfo* weapon_info = get_weapon_info();
					if (weapon_info) {
						if (m_vars.m_original_instant_spin.find(get_weapon_info()) == m_vars.m_original_instant_spin.end()) {
							m_vars.m_original_instant_spin[weapon_info].first = weapon_info->m_spinup_time;
							m_vars.m_original_instant_spin[weapon_info].second = weapon_info->m_spindown_time;
						}

						weapon_info->m_spinup_time = 0.f;
						weapon_info->m_spindown_time = 0.f;
					}
				}
			}
		}
	}
}