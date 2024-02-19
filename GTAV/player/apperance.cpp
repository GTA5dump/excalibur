#include "pch.h"
#include "appearance.h"
#include "features/manager/manager.h"
#include "menu/util/globals.h"
#include "gui/options/option.h"
#include "gui/util/panels.h"
#include "rage/classes/CPed.h"
#include "util/util.h"

using namespace base::gui;
using namespace menu::player::appearance::vars;

namespace menu::player::appearance::vars {
	variables m_vars;

	const char* comp_names[] = {
		"Face", "Mask", "Hair", "Torso", "Leg", "Misc", "Shoes", "Accessories", "Undershirt", "Kevlar", "Badge", "Torso 2"
	};

	const char* acc_names[] = {
		"Hats", "Glasses", "Ears", "Watches", "Bracelets"
	};

	template<typename Type>
	struct scroll_struct {
		const char* m_name;
		Type m_result;
	};

	scroll_struct<std::pair<int, Vector3>> components[] = {
		{ ("Face"), { 0, { 0.000f, 0.300f, -0.300f } } },
		{ ("Mask"), { 1, { 0.000f, 0.300f, -0.300f } } },
		{ ("Hair"), { 2, { 0.000f, 0.300f, -0.300f } } },
		{ ("Torso"), { 3, { 0.000f, -0.400f, 0.100f } } },
		{ ("Legs"), { 4, { 0.000f, -0.400f, 0.800f } } },
		{ ("Misc"), { 5, { 0.00f, -2.00f, 0.40f } } },
		{ ("Shoes"), { 6, { 0.000f, 0.000f, 1.200f } } },
		{ ("Accessories"), { 7, { 0.00f, -2.00f, 0.40f } } },
		{ ("Undershirt"), { 8, { 0.000f, -0.400f, 0.100f } } },
		{ ("Kevlar"), { 9, { 0.000f, -0.400f, 0.100f } } },
		{ ("Badge"), { 10, { 0.000f, -0.400f, 0.100f } } },
		{ ("Torso 2"), { 11, { 0.000f, -0.400f, 0.100f } } }
	};

	scroll_struct<std::pair<int, Vector3>> accessories[] = {
		{ ("Hats"), { 0, { 0.000f, 0.300f, -0.300f } } },
		{ ("Glasses"), { 1, { 0.000f, 0.300f, -0.300f } } },
		{ ("Ears"), { 2, { 0.000f, 0.300f, -0.300f } } },
		{ ("Watches"), { 6, { 0.300f, 0.750f, 0.400f /*RIGHT*/ } } },
		{ ("Bracelets"), { 7, { 0.300f, 0.750f, 0.400f /*RIGHT*/ } } },
	};

	inline const char* g_ped_model_popular[8] = {
		"s_m_m_movalien_01",
		"s_m_m_movspace_01",
		"mp_f_deadhooker",
		"u_m_y_pogo_01",
		"s_f_y_stripper_01",
		"s_m_y_swat_01",
		"a_f_y_topless_01",
		"u_m_y_zombie_01"
	}; inline int g_ped_model_popular_id;

	inline const char* g_ped_model_popular_names[8] = {
		"Alien",
		"Astronaut",
		"Hooker",
		"Pogo",
		"Stripper",
		"Swat",
		"Topless",
		"Zombie"
	};

	inline const char* g_ped_model_story[25] = {
		"player_zero",
		"player_one",
		"player_two",
		"ig_amandatownley",
		"ig_ashley",
		"ig_brad",
		"ig_chef",
		"ig_chrisformage",
		"ig_clay",
		"ig_cletus",
		"ig_davenorton",
		"ig_denise",
		"ig_fabien",
		"ig_floyd",
		"ig_jay_norris",
		"ig_jimmydisanto",
		"ig_lamardavis",
		"ig_lestercrest",
		"ig_mrsphillips",
		"ig_stretch",
		"ig_taocheng",
		"ig_tenniscoach",
		"ig_tracydisanto"
	}; inline int g_ped_model_story_id;


	inline const char* g_ped_model_story_names[25] = {
		"Michael",
		"Franklin",
		"Trevor",
		"Amanda",
		"Ashley",
		"Brad",
		"Chef",
		"Chris Formage",
		"Clay",
		"Cletus",
		"Dave Norton",
		"Denise",
		"Fabien",
		"Floyd",
		"Jay Norris",
		"Jimmy",
		"Lamar",
		"Lester",
		"Mrs Phillips",
		"Stretch",
		"Tao Cheng",
		"Tennis Coach",
		"Tracy"
	};

	inline const char* g_ped_model_animal[18] = {
		"a_c_boar",
		"a_c_chimp",
		"a_c_chop",
		"a_c_cow",
		"a_c_coyote",
		"a_c_crow",
		"a_c_deer",
		"a_c_fish",
		"a_c_chickenhawk",
		"a_c_hen",
		"a_c_husky",
		"a_c_mtlion",
		"a_c_pig",
		"a_c_retriever",
		"a_c_rhesus",
		"a_c_rottweiler",
		"a_c_seagull",
		"a_c_shepherd"
	}; inline int g_ped_model_animal_id;

	inline const char* g_ped_model_animal_names[18] = {
		"Boar",
		"Chimp",
		"Chop",
		"Cow",
		"Coyote",
		"Crow",
		"Deer",
		"Fish",
		"Chicken Hawk",
		"Hen",
		"Husky",
		"Mountain Lion",
		"Pig",
		"Retriever",
		"Rhesus",
		"Rottweiler",
		"Seagull",
		"Shepherd"
	};

	inline const char* g_ped_model_emergency[12] = {
		"s_m_y_blackops_01",
		"s_m_y_cop_01",
		"csb_cop",
		"s_m_y_fireman_01",
		"u_m_m_prolsec_01",
		"s_m_y_hwaycop_01",
		"s_m_y_marine_03",
		"s_m_m_paramedic_01",
		"s_m_y_ranger_01",
		"s_m_m_security_01",
		"s_m_y_sheriff_01",
		"s_m_m_snowcop_01"
	}; inline int g_ped_model_emergency_id;

	inline const char* g_ped_model_emergency_names[12] = {
		"Black Ops",
		"City Cop",
		"County Cop",
		"Fireman",
		"Security Guard",
		"Highway Cop",
		"Marine",
		"Paramedic",
		"Ranger",
		"Security Guard",
		"Sheriff",
		"Snow Cop"
	};

	inline const char* g_ped_model_role[14] = {
		"s_m_m_bouncer_01",
		"ig_bride",
		"s_m_y_pestcont_01",
		"s_m_m_doctor_01",
		"s_m_y_factory_01",
		"s_m_y_garbage",
		"ig_groom",
		"ig_hunter",
		"u_m_m_jesus_01",
		"s_m_y_mime",
		"ig_priest",
		"s_m_y_prisoner_01",
		"s_m_m_scientist_01",
		"u_f_y_spyactress"
	}; inline int g_ped_model_role_id;

	inline const char* g_ped_model_role_names[14] = {
		"Bouncer",
		"Bride",
		"Pest Control",
		"Doctor",
		"Factory Worker",
		"Garbage Man",
		"Groom",
		"Hunter",
		"Jesus",
		"Mime",
		"Priest",
		"Prisoner",
		"Scientist",
		"Spy"
	};

	inline const char* g_ped_model_ambient[6] = {
		"u_m_y_babyd",
		"u_m_y_justin",
		"u_m_y_guido_01",
		"s_m_m_strperf_01",
		"u_m_y_mani",
		"u_m_m_griff_01"
	}; inline int g_ped_model_ambient_id;

	inline const char* g_ped_model_ambient_names[6] = {
		"Body Builder",
		"Nonce",
		"Guido",
		"Statue",
		"Mani",
		"Griff"
	};

	inline const char* g_ped_model_misc[5] = {
		"mp_f_deadhooker",
		"u_m_y_imporage",
		"mp_m_marston_01",
		"mp_f_misty_01",
		"mp_m_niko_01"
	}; inline int g_ped_model_misc_id;

	inline const char* g_ped_model_misc_names[5] = {
		"Dead Hooker",
		"Imporage",
		"Marston",
		"Misty",
		"Niko"
	};

	void apply_model(const char* To_Change) {
		util::fiber::pool::add([=] {
			Hash Model_To_Change = rage::joaat(To_Change); {
				Vector3 Coordinates = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
				Coordinates.x + 2;
				if (STREAMING::IS_MODEL_IN_CDIMAGE(Model_To_Change)) {
					if (!STREAMING::HAS_MODEL_LOADED(Model_To_Change)) {
						STREAMING::REQUEST_MODEL(Model_To_Change);
						util::fiber::go_to_main();
					}
					if (!STREAMING::HAS_MODEL_LOADED(Model_To_Change)) {
						return;
					}
					if (STREAMING::IS_MODEL_VALID(Model_To_Change)) {
						*(unsigned short*)patterns::set_this_thread_networked = 0x9090;
						Ped PED_Spawn = PED::CREATE_PED(26, Model_To_Change, Coordinates, 0, true, true);
						*(unsigned short*)patterns::set_this_thread_networked = 0x0574;

						util::fiber::go_to_main();

						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(Model_To_Change);
						if (*patterns::is_session_started) {
							NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED_Spawn);
							auto NET_ID = NETWORK::PED_TO_NET(PED_Spawn);
							DECORATOR::DECOR_SET_INT(PED_Spawn, (char*)"MPBitset", 0);
							NETWORK::NETWORK_REGISTER_ENTITY_AS_NETWORKED(PED_Spawn);
							ENTITY::SET_ENTITY_SHOULD_FREEZE_WAITING_ON_COLLISION(PED_Spawn, false);
							if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(PED_Spawn))
								NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(NET_ID, true);
							ENTITY::SET_ENTITY_AS_MISSION_ENTITY(PED_Spawn, true, true);
							NETWORK::SET_NETWORK_ID_CAN_MIGRATE(NETWORK::PED_TO_NET(PED_Spawn), TRUE);

							if (!DECORATOR::DECOR_EXIST_ON(PED_Spawn, "MissionType")) {
								DECORATOR::DECOR_REGISTER("MissionType", 3);
								DECORATOR::DECOR_SET_INT(PED_Spawn, "MissionType", 0);
							}
						}
						Ped PED_TO_DELETE = PLAYER::PLAYER_PED_ID();
						PLAYER::CHANGE_PLAYER_PED(PLAYER::PLAYER_ID(), PED_Spawn, true, true);
						ENTITY::SET_ENTITY_ALPHA(PED_Spawn, 255, 0);
						ENTITY::SET_ENTITY_VISIBLE(PED_Spawn, true, 1);
						ENTITY::DELETE_ENTITY(&PED_TO_DELETE);
					}
				}
			}
		});
	}
}

namespace menu {

	void player_appearance_menu::render() {
		renderer::addSubmenu("Appearance", "Player Appearance", [](core* core) {
			core->addOption(submenuOption("Wardrobe")
				.setTarget("Wardrobe"));

			core->addOption(submenuOption("Model")
				.setTarget("Player Model"));

			core->addOption(breakOption("Modifiers"));

			core->addOption(scrollOption<const char*, int>("Clothing")
				.addScroll(&comp_names).setPosition(&m_vars.m_clothing)
				.addClick([=] {
					m_vars.m_clothing_model = PED::GET_PED_DRAWABLE_VARIATION(PLAYER::PLAYER_PED_ID(), components[m_vars.m_clothing].m_result.first);
					m_vars.m_clothing_variation = PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(), components[m_vars.m_clothing].m_result.first);
					}));

			core->addOption(numberOption<int>("Clothing Model")
				.addNumber(&m_vars.m_clothing_model).addMin(-1).addMax(PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), components[m_vars.m_clothing].m_result.first) - 1)
				.addClick([=] {
					PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), components[m_vars.m_clothing].m_result.first, m_vars.m_clothing_model, PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(), components[m_vars.m_clothing].m_result.first), 0);
					m_vars.m_clothing_variation = PED::GET_PED_TEXTURE_VARIATION(PLAYER::PLAYER_PED_ID(), components[m_vars.m_clothing].m_result.first);
					}));

			core->addOption(numberOption<int>("Clothing Variation")
				.addNumber(&m_vars.m_clothing_variation).addMin(-1).addMax(PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), components[m_vars.m_clothing].m_result.first, m_vars.m_clothing_model))
				.addClick([=] {
					PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), components[m_vars.m_clothing].m_result.first, m_vars.m_clothing_model, m_vars.m_clothing_variation, 0);
					}));

			core->addOption(scrollOption<const char*, int>("Accessory")
				.addScroll(&acc_names).setPosition(&m_vars.m_accessory)
				.addClick([=] {
					m_vars.m_accessory_model = PED::GET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), accessories[m_vars.m_accessory].m_result.first);
					m_vars.m_accessory_variation = PED::GET_PED_PROP_TEXTURE_INDEX(PLAYER::PLAYER_PED_ID(), accessories[m_vars.m_accessory].m_result.first);
					}));

			core->addOption(numberOption<int>("Accessory Model")
				.addNumber(&m_vars.m_accessory_model).addMin(-1).addMax(PED::GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(PLAYER::PLAYER_PED_ID(), accessories[m_vars.m_accessory].m_result.first))
				.addClick([=] {
					PED::SET_PED_PROP_INDEX(PLAYER::PLAYER_PED_ID(), accessories[m_vars.m_accessory].m_result.first, m_vars.m_accessory_model, 0, true);
					m_vars.m_accessory_variation = PED::GET_PED_PROP_TEXTURE_INDEX(PLAYER::PLAYER_PED_ID(), accessories[m_vars.m_accessory].m_result.first);
					}));

			core->addOption(numberOption<int>("Accessory Variation")
				.addNumber(&m_vars.m_accessory_variation).addMin(-1).addMax(PED::GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(PLAYER::PLAYER_PED_ID(), accessories[m_vars.m_accessory].m_result.first, m_vars.m_accessory_variation))
				.addClick([=] {
					PED::SET_PED_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), components[m_vars.m_clothing].m_result.first, m_vars.m_clothing_model, m_vars.m_clothing_variation, 0);
					}));
		});

		renderer::addSubmenu("Model", "Player Model", [](core* core) {
			core->addOption(scrollOption<const char*, int>("Popular")
				.addScroll(&g_ped_model_popular_names).setPosition(&g_ped_model_popular_id)
				.addClick([=] {
					if (Util::is_key_pressed(VK_RETURN)) {
						apply_model(g_ped_model_popular[g_ped_model_popular_id]);
					}
				}));

			core->addOption(scrollOption<const char*, int>("Story")
				.addScroll(&g_ped_model_story_names).setPosition(&g_ped_model_story_id)
				.addClick([=] {
					if (Util::is_key_pressed(VK_RETURN)) {
						apply_model(g_ped_model_story[g_ped_model_story_id]);
					}
				}));

			core->addOption(scrollOption<const char*, int>("Animals")
				.addScroll(&g_ped_model_animal_names).setPosition(&g_ped_model_animal_id)
				.addClick([=] {
					if (Util::is_key_pressed(VK_RETURN)) {
						apply_model(g_ped_model_animal[g_ped_model_animal_id]);
					}
				}));

			core->addOption(scrollOption<const char*, int>("Emergency")
				.addScroll(&g_ped_model_emergency_names).setPosition(&g_ped_model_emergency_id)
				.addClick([=] {
					if (Util::is_key_pressed(VK_RETURN)) {
						apply_model(g_ped_model_emergency[g_ped_model_emergency_id]);
					}
				}));

			core->addOption(scrollOption<const char*, int>("Role")
				.addScroll(&g_ped_model_role_names).setPosition(&g_ped_model_role_id)
				.addClick([=] {
					if (Util::is_key_pressed(VK_RETURN)) {
						apply_model(g_ped_model_role[g_ped_model_role_id]);
					}
				}));

			core->addOption(scrollOption<const char*, int>("Ambient")
				.addScroll(&g_ped_model_ambient_names).setPosition(&g_ped_model_ambient_id)
				.addClick([=] {
					if (Util::is_key_pressed(VK_RETURN)) {
						apply_model(g_ped_model_ambient[g_ped_model_ambient_id]);
					}
				}));


			core->addOption(scrollOption<const char*, int>("Misc")
				.addScroll(&g_ped_model_misc_names).setPosition(&g_ped_model_misc_id)
				.addClick([=] {
					if (Util::is_key_pressed(VK_RETURN)) {
						apply_model(g_ped_model_misc[g_ped_model_misc_id]);
					}
				}));
		});
	}

	void player_appearance_menu::update() {
		render();
	
	}
}