#include "pch.h"
#include "entity_gun.h"
#include "menu/util/globals.h"
#include "gui/options/option.h"
#include "gui/util/panels.h"
#include "rage/classes/CPed.h"
#include "rage/classes/CPlayerInfo.h"
#include "menu/util/control.h"
#include "menu/util/raycast.h"
#include "gui/util/timer.h"


using namespace base::gui;
using namespace menu::weapon::entity_gun::vars;

namespace menu::weapon::entity_gun::vars {
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

	const char* typesNames[] = {
		"Object", "Vehicle", "Ped"
	}; 
	const char* objectNames[] = {
		"Meteor",
		"Stairs",
		"Egg",
		"Barbell",
		"Campfire",
		"Volleyball",
		"Dildo",
		"Guitar",
		"Gold",
		"Missile",
		"Toilet",
		"Money Bag",
		"Wheelchair",
		"Pumpkin"
	};

	uint32_t objectValues[] = {
		0xDF9841D7,
		0x757C28D,
		0x6B795EBC,
		0xE2FBA8D8,
		0xC079B265,
		0xC79A987E,
		0xE6CB661E,
		0xD5C0BC07,
		0xF046EA37,
		0xB2274905,
		0x6F9939C7,
		0x113FD533,
		0x4B3D240F,
		0x83C07621
	}; int object_id = 0;

	const char* vehicleNames[] = {
	"Hauler",
	"Issi",
	"Kanjo",
	"Rhapsody",
	"Dominator",
	"Hermes",
	"Clique",
	"Slam Van",
	"Dune",
	"Formula",
	"Vagrant",
	"Hellion",
	"Bf Injection",
	"Bifta",
	"Bkazer",
	"Peyote",
	"Hustler",
	"Imperator",
	"Ellie",
	"Sea Shark",
	"Titan"
	};

	uint32_t vehicleValues[] = {
	0x5A82F9AE,
	0x5BA0FF1E,
	0x18619B7E,
	0x322CF98F,
	0xB2E046FB,
	0xE83C17,
	0xA29F78B0,
	0x42BC5E19,
	0x1FD824AF,
	0x8B213907,
	0x2C1FEA99,
	0xEA6A047F,
	0x432AA566,
	0xEB298297,
	0xB44F0582,
	0x9472CD24,
	0x23CA25F2,
	0x619C1B82,
	0xB472D2B5,
	0xC2974024,
	0x761E2AD3
	}; int vehicle_id = 0;


	const char* pedNames[] = {
	"Whale",
	"Cow",
	"Seagull",
	"Topless Girl",
	"Bride",
	"Hooker",
	"Astronaut",
	"Human Statue",
	"Mime",
	"Jesus",
	"Pogo",
	"Zombie"
	};


	uint32_t pedValues[] = {
	0x8D8AC8B9,
	0xFCFA9E1E,
	0xD3939DFD,
	0x9CF26183,
	0x6162EC47,
	0x28ABF95,
	0xE7B31432,
	0x795AC7A8,
	0x3CDCA742,
	0xCE2CB751,
	0xDC59940D,
	0xAC4B4506
	}; int ped_id = 0;
}



namespace menu {

	void entity_gun_menu::render() {
		renderer::addSubmenu("Entity Gun", "Weapon Entity Gun", [](core* core) {
			core->addOption(toggleOption("Toggle Entity Gun")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_toggle));

			core->addOption(scrollOption<const char*, int>("Type")
				.addScroll(&typesNames)
				.setPosition(&m_vars.m_type));

			core->addOption(numberOption<int>("Delay")
				.addNumber(&m_vars.m_wait)
				.addMin(0).addMax(1000).addStep(1));

			core->addOption(numberOption<float>("Speed")
				.addNumber(&m_vars.m_speed)
				.addMin(0).addMax(10000).addStep(100).setPrecision(0));

			core->addOption(breakOption("Types"));

			core->addOption(scrollOption<const char*, int>("Object")
				.addScroll(&objectNames)
				.setPosition(&m_vars.m_object));

			core->addOption(scrollOption<const char*, int>("Vehicle")
				.addScroll(&vehicleNames)
				.setPosition(&m_vars.m_vehicle));

			core->addOption(scrollOption<const char*, int>("Ped")
				.addScroll(&pedNames)
				.setPosition(&m_vars.m_ped));


		});
	}

	void entity_gun_menu::update() {
		render();

		WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &m_vars.m_weapon_hash, false);

		m_vars.m_has_weapon_in_hand = (m_vars.m_weapon_hash && m_vars.m_weapon_hash != 2725352035);

		if (m_vars.m_toggle) {
			if (isPedShooting(PLAYER::PLAYER_PED_ID())) {
				static int timer = 0;
				run_timed(&timer, m_vars.m_wait, [] {
					Entity handle = 0;
					switch (m_vars.m_type) {
					case 0: // object
						menu::control::requestModel(objectValues[m_vars.m_object]);
						*(unsigned short*)patterns::set_this_thread_networked = 0x9090;
						handle = OBJECT::CREATE_OBJECT(objectValues[m_vars.m_object], { 0.f, 0.f, 0.f }, true, true, false);
						*(unsigned short*)patterns::set_this_thread_networked = 0x0574;
						break;

					case 1: // vehicle
						menu::control::requestModel(vehicleValues[m_vars.m_vehicle]);
						*(unsigned short*)patterns::set_this_thread_networked = 0x9090;
						handle = VEHICLE::CREATE_VEHICLE(vehicleValues[m_vars.m_vehicle], { 0.f, 0.f, 0.f }, 0.f, true, true, 0);
						*(unsigned short*)patterns::set_this_thread_networked = 0x0574;
						break;

					case 2: // ped
						menu::control::requestModel(pedValues[m_vars.m_ped]);
						*(unsigned short*)patterns::set_this_thread_networked = 0x9090;
						handle = PED::CREATE_PED(21, pedValues[m_vars.m_ped], { 0.f, 0.f, 0.f }, 0.f, true, false);
						*(unsigned short*)patterns::set_this_thread_networked = 0x0574;
						break;
					}
					if (ENTITY::DOES_ENTITY_EXIST(handle)) {
						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(handle, true, true);
						ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(PLAYER::PLAYER_PED_ID(), handle, true);

						Vector3 rotation = CAM::GET_GAMEPLAY_CAM_ROT(0);
						Vector3 target = CAM::GET_GAMEPLAY_CAM_COORD() + (get_direction(rotation) * 25.f);

						ENTITY::SET_ENTITY_COORDS(handle, target, false, false, false, false);
						ENTITY::SET_ENTITY_ROTATION(handle, rotation.x, 0.f, rotation.z, 0, 1);

						if (ENTITY::IS_ENTITY_A_VEHICLE(handle)) VEHICLE::SET_VEHICLE_OUT_OF_CONTROL(handle, true, true);
						ENTITY::APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS(handle, 1, { 0.f, m_vars.m_speed, 0.f }, false, true, true, false);
					}
				});
			}
		}
	}
}