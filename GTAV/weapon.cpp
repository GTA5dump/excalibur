	#include "pch.h"
#include "weapon.h"
#include "rage/invoker/natives.h"
#include "menu/util/lists.h"
#include "rage/engine.h"
#include "util/util.h"
#include "weapon/weapon_mods.h"

using namespace base::gui;

void upgrade_weapon_components(Ped ped, uint32_t weapon_hash) {
	for (const auto components : menu::lists::weapon_components) {
		if (WEAPON::DOES_WEAPON_TAKE_WEAPON_COMPONENT(weapon_hash, components.hash)) {
			WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(ped, weapon_hash, components.hash);
		}
	}
}

void remove_weapon_upgrades(Ped ped, uint32_t weapon_hash) {
	for (const auto components : menu::lists::weapon_components) {
		if (WEAPON::DOES_WEAPON_TAKE_WEAPON_COMPONENT(weapon_hash, components.hash)) {
			WEAPON::REMOVE_WEAPON_COMPONENT_FROM_PED(ped, weapon_hash, components.hash);
		}
	}
}

void give_weapon(Ped ped, uint32_t weapon_hash, bool equip_now, bool fully_upgraded) {
	int ammo = -1;
	WEAPON::GET_MAX_AMMO(ped, weapon_hash, &ammo);
	WEAPON::GIVE_WEAPON_TO_PED(ped, weapon_hash, ammo, false, equip_now);

	if (fully_upgraded) {
		upgrade_weapon_components(ped, weapon_hash);
	}
} 

const char* give_components[] = {
	"Current", "All"
}; std::size_t give_components_id = 0;

const char* remove_components[] = {
	"Current", "All"
}; std::size_t remove_components_id = 0;

const char* give_ammo[] = {
	"Current", "All"
}; std::size_t give_ammo_id = 0;

const char* remove_ammo[] = {
	"Current", "All"
}; std::size_t remove_ammo_id = 0;

const char* remove_weapons[] = {
	"Current", "All"
}; std::size_t remove_weapons_id = 0;

namespace menu {
	void weapon_menu::render() {
		renderer::addSubmenu("Weapons", "Weapons", [](core* core) {

			core->addOption(submenuOption("Weapon Mods")
				.addTranslate()
				.setTarget("Weapon Mods"));

			core->addOption(breakOption("Quick Access"));

			core->addOption(buttonOption("Give All Weapons")
				.addTranslate()
				.addClick([] {
					for (const auto& weapon : lists::g_weapons) {
						give_weapon(PLAYER::PLAYER_PED_ID(), weapon.id, true, false);
					}
				}));

			uint32_t m_weapon_hash = 0;
			WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &m_weapon_hash, false);
			auto curWeapon = WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &m_weapon_hash, false);

			core->addOption(scrollOption<const char*, std::size_t>("Remove Weapons")
				.addTranslate()
				.addScroll(&remove_weapons).setPosition(&remove_weapons_id)
				.addClick([=] {
					uint32_t hash;
					switch (remove_weapons_id) {
					case 0:
						if (Util::is_key_pressed(VK_RETURN)) {
							WEAPON::REMOVE_WEAPON_FROM_PED(PLAYER::PLAYER_PED_ID(), curWeapon);
						}
						break;
					case 1:
						if (Util::is_key_pressed(VK_RETURN)) {
							WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::PLAYER_PED_ID(), 0);
						}
						break;
					}
				}));

			core->addOption(scrollOption<const char*, std::size_t>("Give Ammo")
				.addTranslate()
				.addScroll(&give_ammo).setPosition(&give_ammo_id)
				.addClick([=] {
					uint32_t hash;
					int ammo = -1;
					WEAPON::GET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), curWeapon, &ammo);
					switch (give_ammo_id) {
					case 0:
						if (Util::is_key_pressed(VK_RETURN)) {
							WEAPON::REFILL_AMMO_INSTANTLY(PLAYER::PLAYER_PED_ID());
						}

						break;
					case 1:
						if (Util::is_key_pressed(VK_RETURN)) {
							for (const auto& weapon : lists::g_weapons) {
								WEAPON::ADD_AMMO_TO_PED(PLAYER::PLAYER_PED_ID(), weapon.id, ammo);
							}
						}
						break;
					}
				}));

			core->addOption(scrollOption<const char*, std::size_t>("Remove Ammo")
				.addTranslate()
				.addScroll(&remove_ammo).setPosition(&remove_ammo_id)
				.addClick([=] {
					uint32_t hash;
					int ammo = -1;
					WEAPON::GET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), curWeapon, &ammo);
					switch (remove_ammo_id) {
					case 0:
						if (Util::is_key_pressed(VK_RETURN)) {
							WEAPON::SET_PED_AMMO(PLAYER::PLAYER_PED_ID(), curWeapon, 0, 0);
						}

						break;
					case 1:
						if (Util::is_key_pressed(VK_RETURN)) {
							for (const auto& weapon : lists::g_weapons) {
								WEAPON::SET_PED_AMMO(PLAYER::PLAYER_PED_ID(), weapon.id, 0, 0);
							}
						}
	
						break;
					}
				}));

			core->addOption(scrollOption<const char*, std::size_t>("Upgrade Components")
				.addTranslate()
				.addScroll(&give_components).setPosition(&give_components_id)
				.addClick([=] {
					uint32_t hash;
					int ammo = -1;
					WEAPON::GET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), curWeapon, &ammo);
					switch (give_components_id) {
					case 0:
						if (Util::is_key_pressed(VK_RETURN)) {
							upgrade_weapon_components(PLAYER::PLAYER_PED_ID(), curWeapon);
						}

						break;
					case 1:
						if (Util::is_key_pressed(VK_RETURN)) {
							for (const auto& weapon : lists::g_weapons) {
								upgrade_weapon_components(PLAYER::PLAYER_PED_ID(), weapon.id);
							}
						}

						break;
					}
				}));

			core->addOption(scrollOption<const char*, std::size_t>("Downgrade Components")
				.addTranslate()
				.addScroll(&remove_components).setPosition(&remove_components_id)
				.addClick([=] {
					uint32_t hash;
					int ammo = -1;
					WEAPON::GET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), curWeapon,&ammo);
					switch (remove_components_id) {
					case 0:
						if (Util::is_key_pressed(VK_RETURN)) {
							remove_weapon_upgrades(PLAYER::PLAYER_PED_ID(), curWeapon);
						}

						break;
					case 1:

						if (Util::is_key_pressed(VK_RETURN)) {
							for (const auto& weapon : lists::g_weapons) {
								remove_weapon_upgrades(PLAYER::PLAYER_PED_ID(), weapon.id);
							}
						}
						break;
					}
					}));
		});
	}

	void weapon_menu::update() {
		render();
		getWeaponModsMenu()->update();
	}
}