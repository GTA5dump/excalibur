#include "pch.h"
#include "hooks.h"
#include "memory/pattern.h"
#include "util/hooking/hooking.h"
#include "patterns.h"
#include "util/caller.h"
#include "gui/util/fonts.h"
#include "rage/classes/enums.h"
#include "gui/util/notify.h"
#include "gui/renderer.h"

#include "rage/classes/scrNativeCallContext.h"
#include "rage/invoker/natives.h"
#include "menu/submenus/main.h"
#include "menu/submenus/main/settings.h"
#include "menu/submenus/main/player.h"
#include "menu/submenus/main/spawner.h"
#include "menu/submenus/main/network.h"
#include "menu/submenus/main/weapon.h"
#include "menu/submenus/main/vehicle.h"
#include "util/fiber.h"
#include "features/features.h"
#include "gui/util/fonts.h"
#include "gui/util/texture.h"
#include "gui/util/panels.h"
#include "util/fiber_pool.h"
#include "gui/renderer.h"
#include "gui/util/notify.h"
#include "menu/util/players.h"
#include "rage/classes/scrThread.h"
#include "menu/submenus/main/weapon/weapon_disables.h"
#include "menu/submenus/main/network/network_global_chat.h"
#include "security/xor.h"
#include "util/hooking/script.h"
#include "menu/util/script_patcher_service.h"
#include "security/themdia/secure_engine.h"
#include "rage/classes/netShopping.h"
#include "rage/classes/dataNodes.h"
#include "menu/submenus/main/network/network_spoofing.h"
using namespace memory;



namespace base::hooks {


	bool(*join_timeout_fix_t)(uint64_t);
	bool join_timeout_fix(uint64_t config) {
		uint64_t g_game_base = g_game_address.first;
		int offset = 0x0;

		if (!caller::call<uint8_t>(g_timeout_fix_funcs[0], *(uint64_t*)(config + 0x20 + offset))) {
			return false;
		}

		if (!*(uint64_t*)(*(uint64_t*)(g_timeout_fix_funcs[1]) + 8)) {
			return false;
		}

		uint64_t v3 = *(uint64_t*)(g_timeout_fix_funcs[2]);

		if (*(uint32_t*)(v3 + 0x288)) {
			uint32_t current_time = timeGetTime() | 1;

			uint32_t max_timeout = caller::call<uint32_t>(g_timeout_fix_funcs[5], config);
			if (current_time - *(uint32_t*)(config + 0x869C + offset) >= max_timeout - 1) {
				LOG(XOR("Join timeout detected"));

				*(uint32_t*)(config + 0x869C + offset) = current_time;
				*(uint32_t*)(v3 + 0x288) = 0;
				*(uint8_t*)(config + 0x1A96C + offset) = 0;
				return true;
			}
		}

		return join_timeout_fix_t(config);
	}

	bool patterns() {
		batch batch;
		bool out = true;
	  // VM_TIGER_BLACK_START
		batch.Add({ XOR("GS"), XOR("83 3D ? ? ? ? ? 75 17 8B 43 20") }, [](Ptr ptr) {
			patterns::game_state = ptr.lea().as<decltype(patterns::game_state)>();
			return util::is_valid_ptr(patterns::game_state);
		}, out);

		batch.Add({ XOR("NRT"), XOR("48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A") }, [](Ptr ptr) {
			patterns::init_native_tables = ptr.sub(37).as<uint64_t>();
			patterns::native_registration_table = ptr.from_instruction().as<decltype(patterns::native_registration_table)>();
			patterns::get_native_handler = ptr.add(12).rip().as<decltype(patterns::get_native_handler)>();
			return hooking::detour("INT", patterns::init_native_tables, &initNativeTablesHook, &ogInitNativeTablesHook);
		}, out);

		batch.Add({ XOR("JRR"), XOR("23 C3 C1 E0 0C") }, [](Ptr ptr) {
			patterns::jmp_rbx_register = ptr.sub(1).as<decltype(patterns::jmp_rbx_register)>();
			return util::is_valid_ptr(patterns::jmp_rbx_register);
		}, out);

		batch.Add({ XOR("SP"), XOR("48 8B 1D ? ? ? ? 41 83 F8 FF") }, [](Ptr ptr) {
			patterns::script_program = ptr.from_instruction().as<decltype(patterns::script_program)>();
			return util::is_valid_ptr(patterns::script_program);
		}, out);

		batch.Add({ XOR("GFX_FT"), XOR("48 8B 05 ? ? ? ? 48 8B CB 48 69 C9 ? ? ? ? 40 38 AC 01 ? ? ? ? 74 0F E8 ? ? ? ? 0F 28 CE 8B CB E8 ? ? ? ? F3 0F 10 05 ? ? ? ? B2 01 E8") }, [](Ptr ptr) {
			patterns::font_table = ptr.from_instruction().as<uint64_t>();
			return util::is_valid_ptr(patterns::font_table);
		}, out);

		batch.Add({ XOR("GFX_FMH"), XOR("48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 33 DB 48 85 C9") }, [](Ptr ptr) {
			patterns::font_memory_helper = ptr.from_instruction().as<uint64_t>();
			return util::is_valid_ptr(patterns::font_memory_helper);
		}, out);

		batch.Add({ XOR("GFX_D"), XOR("48 83 EC 28 F0 FF 49 08 75 0F 48 85 C9 74 0A 48 8B 01 BA ? ? ? ? FF 10 48 83 C4 28 C3") }, [](Ptr ptr) {
			patterns::destruct = ptr.as<uint64_t>();
			return util::is_valid_ptr(patterns::destruct);
			}, out);

		batch.Add({ XOR("GFX_CGF"), XOR("40 53 48 83 EC 20 C7 41 ? ? ? ? ? 48 8D 05 ? ? ? ? 48 8B D9 48 89 01 C7 41 ? ? ? ? ? 48 8D 05 ? ? ? ? 48 89 01") }, [](Ptr ptr) {
			patterns::construct_gfx_font = ptr.as<uint64_t>();//gfx :thumbs_up:
			return util::is_valid_ptr(patterns::construct_gfx_font);
		}, out);

		batch.Add({ XOR("GFX_CIFF"), XOR("40 55 48 8B EC 48 81 EC ? ? ? ? 49 8B 00 F3 0F 10 02 F3 0F 10 4A ? 83 65 B8 00 83 65 C0 00 83 65 C4 00 F3") }, [](Ptr ptr) {
			patterns::create_id_for_font = ptr.as<uint64_t>();
			return util::is_valid_ptr(patterns::create_id_for_font);
			}, out);

		batch.Add({ XOR("GFX_AFL"), XOR("40 53 48 83 EC 20 48 8B 41 40 4D 63 C8 4C 8B D9 46 0F B6 14 08 48 8B DA 41 81 E2 ? ? ? ? 41 8B C2 45 8B CA 49 F7 D9 4C 0B") }, [](Ptr ptr) {
			patterns::add_font_lib = ptr.as<uint64_t>();
			return util::is_valid_ptr(patterns::add_font_lib);
			}, out);

		batch.Add({ XOR("GFX_GFIFT"), XOR("48 85 D2 74 10 49 83 C8 FF 49 FF C0 42 80 3C 02 ? 75 F6 EB 03 45 33 C0 E9") }, [](Ptr ptr) {
			patterns::get_font_id_table = ptr.as<uint64_t>();
			}, out);

		batch.Add({ XOR("GFX_SM"), XOR("48 8D 0D ? ? ? ? 03 D3 E8 ? ? ? ? 66 44 39 7D ? 74 09 48 8B 4D E8 E8") }, [](Ptr ptr) {
			patterns::store_manager = ptr.from_instruction().as<rage::types::store_manager*>();
			}, out);

		batch.Add({ XOR("GFX_GSME"), XOR("40 53 48 83 EC 20 48 8B C2 48 8B D9 33 D2 48 8B C8 E8 ? ? ? ? 33 D2 44 8B D0 F7 35 ? ? ? ? 44 8B C2 48 8B 15 ? ? ? ? 46 8B 0C 82 41") }, [](Ptr ptr) {
			patterns::get_store_module_extension = ptr.as<uint64_t>();
			}, out);

		batch.Add({ XOR("GFX_RSF"), XOR("48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 48 8B EA 4C 8B FA 48 8B D9 4D 85 C9 B2") }, [](Ptr ptr) {
			patterns::register_streaming_file = ptr.as<uint64_t>();
			}, out);

		batch.Add({ XOR("GFX_RSF2"), XOR("E8 ? ? ? ? 83 4F 48 10") }, [](Ptr ptr) {
			patterns::request_streaming_file = ptr.call().as<uint64_t>();
			}, out);

		batch.Add({ XOR("VHL"), XOR("4C 03 05 ? ? ? ? EB 09 49 83 C2 04 EB 8B") }, [](Ptr ptr) {
			patterns::hash_list = ptr.from_instruction().as<decltype(patterns::hash_list)>();
			}, out);

		batch.Add({ XOR("STTN"), XOR("48 8B C8 FF 52 30 84 C0 74 05 48") }, [](Ptr ptr) {
			patterns::set_this_thread_networked = ptr.add(8).as<decltype(patterns::set_this_thread_networked)>();
		}, out);

		batch.Add({ XOR("SG"), XOR("48 8D 15 ? ? ? ? 4C 8B C0 E8 ? ? ? ? 48 85 FF 48 89 1D") }, [](Ptr ptr) {
			patterns::script_globals = ptr.from_instruction().as<std::int64_t**>();
			}, out);

		batch.Add({ XOR("GFX_SD"), XOR("E8 ? ? ? ? EB 03 48 8B C3 48 89 47 18") }, [](Ptr ptr) {
			patterns::setup_dictionary = ptr.call().as<decltype(patterns::setup_dictionary)>();
			}, out);

		batch.Add({ XOR("GFX_ATTD"), XOR("E8 ? ? ? ? 84 C0 74 1F 48 8D 4F 30") }, [](Ptr ptr) {
			patterns::add_texture_to_dictionary = ptr.call().as<decltype(patterns::add_texture_to_dictionary)>();
			}, out);

		batch.Add({ XOR("GFX_SSI"), XOR("E8 ? ? ? ? 8B 18 48 8B 45 07") }, [](Ptr ptr) {
			patterns::setup_store_item = ptr.call().as<decltype(patterns::setup_store_item)>();
			}, out);

		batch.Add({ XOR("GFX_ADTP"), XOR("89 54 24 10 48 83 EC 28 48 8B 41 40 4C 63 CA 46 0F B6 14 08 8B 41 4C 41 81 E2 ? ? ? ? 45 8B CA 0F AF C2") }, [](Ptr ptr) {
			patterns::add_dictionary_to_pool = ptr.as<decltype(patterns::add_dictionary_to_pool)>();
			}, out);

		batch.Add({ XOR("GFX_TS"), XOR("48 8D 0D ? ? ? ? E8 ? ? ? ? 8B 45 EC 4C 8D 45 F0 48 8D 55 EC 48 8D 0D ? ? ? ? 89 45 F0 E8") }, [](Ptr ptr) {
			patterns::texture_store = ptr.from_instruction().as<decltype(patterns::texture_store)>();
			}, out);

		batch.Add({ XOR("GFX_TF"), XOR("48 8B 0D ? ? ? ? 45 33 C0 48 8B 01 33 D2 FF 90 ? ? ? ? 48 8B 0D ? ? ? ? 83 64 24") }, [](Ptr ptr) {
			patterns::texture_factory = ptr.from_instruction().as<decltype(patterns::texture_factory)>();
			}, out);

		batch.Add({ XOR("IDSC"), XOR("48 8B 0D ? ? ? ? 48 8B 01 44 8D 43 01 33 D2 FF 50 40 8B C8") }, [](Ptr ptr) {
			patterns::swapchain = ptr.from_instruction().as<decltype(patterns::swapchain)>();
			}, out);

		batch.Add({ XOR("PF"), XOR("48 8B 05 ? ? ? ? 48 8B 48 08 48 85 C9 74 52 8B 81") }, [](Ptr ptr) {
			patterns::ped_factory = ptr.from_instruction().as<decltype(patterns::ped_factory)>();
			}, out);

		batch.Add({ XOR("GNGP"), XOR("48 83 EC ? 33 C0 38 05 ? ? ? ? 74 ? 83 F9") }, [](Ptr ptr) {
			patterns::get_net_player = ptr.as<decltype(patterns::get_net_player)>();
			}, out);

		batch.Add({ XOR("WCHL"), XOR("4C 8D 35 ?? ?? ?? ?? 4C 8B F8") }, [](Ptr ptr) {
			patterns::weapon_components = ptr.from_instruction().as<decltype(patterns::weapon_components)>();
			}, out);

		batch.Add({ XOR("WIHL"), XOR("4C 8D 05 ?? ?? ?? ?? 49 8B 18") }, [](Ptr ptr) {
			patterns::weapon_info = ptr.from_instruction().as<decltype(patterns::weapon_info)>();
			}, out);

		batch.Add({ XOR("HTP"), XOR("83 F9 FF 74 31 4C 8B 0D") }, [](Ptr ptr) {
			patterns::handle_to_ptr = ptr.as<decltype(patterns::handle_to_ptr)>();
			}, out);

		batch.Add({ XOR("RNC"), XOR("E8 ? ? ? ? EB 3E 48 8B D3") }, [](Ptr ptr) {
			patterns::request_control = ptr.call().as<decltype(patterns::request_control)>();
			}, out);

		batch.Add({ XOR("IST"), XOR("40 38 35 ? ? ? ? 75 0E 4C 8B C3 49 8B D7 49 8B CE") }, [](Ptr ptr) {
			patterns::is_session_started = ptr.from_instruction().as<decltype(patterns::is_session_started)>();
			}, out);

		batch.Add({ XOR("FV"), XOR("83 79 18 00 48 8B D1 74 4A FF 4A 18 48 63 4A 18 48 8D 41 04 48 8B 4C CA") }, [](Ptr ptr) {
			patterns::fix_vectors = ptr.as<decltype(patterns::fix_vectors)>();
			}, out);

		batch.Add({ XOR("PEP"), XOR("4C 8B 35 ? ? ? ? B8 ? ? ? ? 0F 57 F6 89 05 ? ? ? ? 49 63 76 10 4C 8B FE 85 F6 0F 84 ? ? ? ? 49 8B 46 08 49 FF CF FF CE 42 0F B6 0C 38") }, [](Ptr ptr) {
			patterns::ped_pool = ptr.from_instruction().as<decltype(patterns::ped_pool)>();
			}, out);

		batch.Add({ XOR("PRP"), XOR("48 8B 0D ? ? ? ? 49 8B D0 E8 ? ? ? ? 39 03 EB 19 41 80 78 ? ? 75 15 48 8B 0D ? ? ? ? 49 8B D0 E8 ? ? ? ? 39 43 04") }, [](Ptr ptr) {
			patterns::prop_pool = ptr.from_instruction().as<decltype(patterns::prop_pool)>();
		}, out);

		batch.Add({ XOR("PUP"), XOR("48 8B 05 ? ? ? ? 0F B7 48 10 66 03 CA 66 44 03 C1 41 80 F9 04") }, [](Ptr ptr) {
			patterns::pickup_pool = ptr.from_instruction().as<decltype(patterns::pickup_pool)>();
		}, out);

		batch.Add({ XOR("VEP"), XOR("4C 8B 25 ? ? ? ? 8B 29 33 F6 49 8B 04 24 33 DB 4C 8D 71 08 44 8B 78 08 45 85 FF 0F 8E ? ? ? ? 4D 8B 0C 24 41 3B 59 08 7D 29 49 8B 51 30 44 8B C3 8B CB 49 C1 E8 05 83 E1 1F 44 8B D3 42 8B 04 82") }, [](Ptr ptr) {
			patterns::vehicle_pool = ptr.from_instruction().as<decltype(patterns::vehicle_pool)>();
			}, out);

		batch.Add({ XOR("PTH"), XOR("48 8B F9 48 83 C1 10 33 DB") }, [](Ptr ptr) {
			patterns::ptr_to_handle = ptr.sub(0x15).as<decltype(patterns::ptr_to_handle)>();
			}, out);

		batch.Add({ XOR("SR"), XOR("66 0F 6E 0D ? ? ? ? 0F B7 3D") }, [](Ptr ptr) {
			patterns::resolution_x = ptr.add(4).rip().as<decltype(patterns::resolution_x)>();
			patterns::resolution_y = ptr.add(4).rip().as<decltype(patterns::resolution_y)>();
			}, out);

		batch.Add({ XOR("GEA"), XOR("E8 ? ? ? ? 48 8B D8 48 85 C0 0F 84 ? ? ? ? 48 8B 0D ? ? ? ? 8B D7 E8 ? ? ? ? 48 8B F8 48 85 C0") }, [](Ptr ptr) {
			patterns::get_entity_address = ptr.call().as<uint64_t>();
			}, out);

		batch.Add({ XOR("SVG"), XOR("8B 91 ? ? ? ? F3 0F 10 05 ? ? ? ? 8D 42 FD A9") }, [](Ptr ptr) {
			patterns::set_vehicle_gravity = ptr.as<decltype(patterns::set_vehicle_gravity)>();
			}, out);

		batch.Add({ XOR("WVFX"), XOR("48 8D 05 ? ? ? ? 48 6B FF 45 F3 0F 59 0D ? ? ? ? F3 41 0F 59 9E ? ? ? ? F3 0F 10 BD ? ? ? ? 48 03 FE 48 69 FF ? ? ? ? F3") }, [](Ptr ptr) {
			patterns::vfx_wheel.first = ptr.from_instruction().as<decltype(patterns::vfx_wheel.first)>();
			patterns::vfx_wheel.second = ptr.add(0xA).as<decltype(*(uint8_t*)patterns::vfx_wheel.second)>();
			}, out);

		batch.Add({ XOR("BL"), XOR("4C 8D 05 ? ? ? ? 0F B7 C1") }, [](Ptr ptr) {
			patterns::blip_list = ptr.from_instruction().as<decltype(patterns::blip_list)>();
			}, out);

		batch.Add({ XOR("GT"), XOR("45 33 F6 8B E9 85 C9 B8") }, [](Ptr ptr) {
			patterns::script_threads = ptr.sub(4).rip().sub(8).as<decltype(patterns::script_threads)>();
			}, out);

		batch.Add({ XOR("NPM"), XOR("48 8B 0D ? ? ? ? 8A D3 48 8B 01 FF 50 ? 4C 8B 07 48 8B CF") }, [](Ptr ptr) {
			patterns::network_player_mgr = ptr.from_instruction().as<decltype(patterns::network_player_mgr)>();
			}, out);

		batch.Add({ XOR("NOM"), XOR("48 8B 0D ? ? ? ? 45 33 C0 E8 ? ? ? ? 33 FF 4C 8B F0") }, [](Ptr ptr) {
			patterns::network_object_mgr = ptr.from_instruction().as<decltype(patterns::network_object_mgr)>();
			}, out);

		batch.Add({ XOR("SGSBGH"), XOR("E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? 8B 05 ? ? ? ? 48 8D 4C 24") }, [](Ptr ptr) {
			patterns::start_get_session_by_gamer_handle = ptr.call().as<decltype(patterns::start_get_session_by_gamer_handle)>();
			}, out);

		batch.Add({ XOR("N"), XOR("48 8B 0D ? ? ? ? 8A D3 48 8B 01 FF 50 ? 4C 8B 07 48 8B CF") }, [](Ptr ptr) {
			patterns::network = ptr.from_instruction().as<decltype(patterns::network)>();
			}, out);

		batch.Add({ XOR("ESI"), XOR("E8 ? ? ? ? C6 83 94 01 00 00 01") }, [](Ptr ptr) {
			patterns::encode_session_info = ptr.call().as<decltype(patterns::encode_session_info)>();
			}, out);

		batch.Add({ XOR("DSI"), XOR("E8 ? ? ? ? 84 C0 74 16 48 8B 4B 60") }, [](Ptr ptr) {
			patterns::decode_session_info = ptr.call().as<decltype(patterns::decode_session_info)>();
			}, out);

		batch.Add({ XOR("JSBI"), XOR("E8 ? ? ? ? 0F B6 CB 84 C0 41 0F 44 CD") }, [](Ptr ptr) {
			patterns::join_session_by_info = ptr.call().as<decltype(patterns::join_session_by_info)>();
			}, out);

		batch.Add({ XOR("GUUID"), XOR("E8 ? ? ? ? 84 C0 74 0C 48 8B 44 24 ? 48 89 03") }, [](Ptr ptr) {
			patterns::generate_uuid = ptr.call().as<decltype(patterns::generate_uuid)>();
			}, out);

		batch.Add({ XOR("HT"), XOR("48 8B 05 ? ? ? ? 48 83 F8 FF") }, [](Ptr ptr) {
			patterns::host_token = ptr.from_instruction().as<decltype(patterns::host_token)>();
			}, out);

		batch.Add({ XOR("PGI"), XOR("48 8D 05 ? ? ? ? 48 8B FE") }, [](Ptr ptr) {
			patterns::profile_gamer_info = ptr.from_instruction().as<decltype(patterns::profile_gamer_info)>();
			}, out);

		batch.Add({ XOR("PIGI"), XOR("E8 ? ? ? ? 48 8D 4D 20 48 8B D0 E8 ? ? ? ? 41 8A CF") }, [](Ptr ptr) {
			patterns::player_info_gamer_info = ptr.call().from_instruction().as<decltype(patterns::player_info_gamer_info)>();
			}, out);

		batch.Add({ XOR("C"), XOR("48 8B 1D ? ? ? ? 48 8D 4C 24 30") }, [](Ptr ptr) {
			patterns::communications = ptr.from_instruction().as<decltype(patterns::communications)>();
			}, out);

		batch.Add({ XOR("NS_NSM"), XOR("48 8B 0D ? ? ? ? 41 8A D9") }, [](Ptr ptr) {
			patterns::net_shop_mgr = *ptr.add(3).rip().as<rage::netShopping::CNetworkShoppingMgr**>();
			return util::is_valid_ptr(patterns::net_shop_mgr);
			}, out);

		/*batch.Add({ XOR("NS_BS"), XOR("54 E9 9B 9B 94") }, [](Ptr ptr) {
			patterns::begin_service = ptr.as<decltype(patterns::begin_service)>();
			return util::is_valid_ptr(patterns::begin_service);
			}, out);*/

		batch.Add({ XOR("NS_CB"), XOR("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 54 41 56 41 57 48 83 EC 30 48 8B F1") }, [](Ptr ptr) {
			patterns::construct_basket = ptr.as<decltype(patterns::construct_basket)>();
			return util::is_valid_ptr(patterns::construct_basket);
			}, out);

		batch.Add({ XOR("NS_AITB"), XOR("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 48 8B F2 48 8D 54 24") }, [](Ptr ptr) {
			patterns::add_item_to_basket = ptr.as<decltype(patterns::add_item_to_basket)>();
			//return hooking::detour("NS_AITB", patterns::add_item_to_basket, &addItemToBasketHook, &ogAddItemToBasketHook);
		}, out);

		batch.Add({ XOR("SEA"), XOR("E8 ? ? ? ? 66 83 7B 08 5B") }, [](Ptr ptr) {
			patterns::send_event_ack = ptr.call().as<decltype(patterns::send_event_ack)>();
			}, out);


		batch.Add({ XOR("WBD"), XOR("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 83 EC 20 8B EA BF 01") }, [](Ptr ptr) {
			patterns::write_bitbuf_dword = ptr.as<decltype(patterns::write_bitbuf_dword)>();
			}, out);

		batch.Add({ XOR("WBQ"), XOR("48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 20 41 8B F0 48 8B EA 48 8B D9 41 83 F8 20") }, [](Ptr ptr) {
			patterns::write_bitbuf_qword = ptr.as<decltype(patterns::write_bitbuf_qword)>();
			}, out);

		batch.Add({ XOR("WBI64"), XOR("E8 ? ? ? ? 8A 53 39 48 8B CF") }, [](Ptr ptr) {
			patterns::write_bitbuf_int64 = ptr.call().as<decltype(patterns::write_bitbuf_int64)>();
			}, out);

		batch.Add({ XOR("WBI32"), XOR("E8 ? ? ? ? 8A 53 74") }, [](Ptr ptr) {
			patterns::write_bitbuf_int32 = ptr.call().as<decltype(patterns::write_bitbuf_int32)>();
			}, out);

		batch.Add({ XOR("WBB"), XOR("E8 ? ? ? ? 8A 57 39") }, [](Ptr ptr) {
			patterns::write_bitbuf_bool = ptr.call().as<decltype(patterns::write_bitbuf_bool)>();
			}, out);

		batch.Add({ XOR("WBA"), XOR("E8 ? ? ? ? 01 7E 08") }, [](Ptr ptr) {
			patterns::write_bitbuf_array = ptr.call().as<decltype(patterns::write_bitbuf_array)>();
			}, out);

		batch.Add({ XOR("HR"), XOR("45 33 C9 45 85 C0 74 56 41 FF C8 74 4C 41 FF C8 74 42 41 FF C8 74 38 41 FF C8 74 2E 41 FF") }, [](Ptr ptr) {
			patterns::handle_rotation = ptr.as<decltype(patterns::handle_rotation)>();
			}, out);

		batch.Add({ XOR("GST"), XOR("E8 ? ? ? ? 48 8B BC 24 B0 00 00 00") }, [](Ptr ptr) {
			patterns::read_bitbuffer_into_sync_tree = ptr.add(1).rip().as<patterns::read_bitbuffer_into_sync_tree_t>();
			}, out);

		batch.Add({ XOR("GEAT"), XOR("48 83 EC 28 48 8B 51 50 48 85 D2 74 04") }, [](Ptr ptr) {
			patterns::get_entity_attached_to = ptr.as<decltype(patterns::get_entity_attached_to)>();
			}, out);

		batch.Add({ XOR("MHT"), XOR("4C 03 05 ? ? ? ? EB 03") }, [](Ptr ptr) {
			patterns::model_table = ptr.from_instruction().as<decltype(patterns::model_table)>();
			}, out);

		batch.Add({ XOR("TSE"), XOR("45 8B F0 41 8B F9 48 8B EA") }, [](Ptr ptr) {
			patterns::trigger_script_event = ptr.sub(0x1C).as<decltype(patterns::trigger_script_event)>();
			}, out);

		batch.Add({ XOR("GPR"), XOR("48 8B C8 33 C0 48 85 C9 74 0A 44 8B C3 8B D7 E8") }, [](Ptr ptr) {
			patterns::give_pickup_rewards = ptr.sub(0x28).as<decltype(patterns::give_pickup_rewards)>();
			}, out);

		batch.Add({ XOR("RI"), XOR("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC 20 49 8B F0 8B EA 8B F9 E8") }, [](Ptr ptr) {
			patterns::remote_increment_stat = ptr.as<decltype(patterns::remote_increment_stat)>();
			}, out);

		batch.Add({ XOR("RD"), XOR("E8 ? ? ? ? 09 B3 ? ? ? ? 48 8B 5C 24") }, [](Ptr ptr) {
			patterns::request_ragdoll = ptr.call().as<patterns::request_ragdoll_t>();
			}, out);

		batch.Add({ XOR("WMSB"), XOR("48 85 C0 0F 84 ? ? ? ? 8B 48 50") }, [](Ptr ptr) {
			patterns::world_model_spawn_bypass = ptr.as<PVOID>();
			}, out);

		batch.Add({ XOR("CPTN"), XOR("E8 ? ? ? ? EB 28 48 8B 8F A0 10 00 00") }, [](Ptr ptr) {
			patterns::clear_ped_tasks_network = ptr.call().as<patterns::clear_ped_tasks_network_t>();
			}, out);

		batch.Add({ XOR("SCINFO"), XOR("48 8B D3 48 8D 4C 24 ? 48 69 D2") }, [](Ptr ptr) {
			patterns::sc_info = ptr.add(4).rip().as<decltype(patterns::sc_info)>();
			}, out);

		batch.Add({ XOR("FRG"), XOR("3B 0D ? ? ? ? 73 17") }, [](Ptr ptr) {
			patterns::friend_registry = ptr.add(2).rip().as<decltype(patterns::friend_registry)>();
			}, out);

		batch.Add({ XOR("SCP"), XOR("83 7E 1C 01 48 8B 3D") }, [](Ptr ptr) {
			patterns::chat_ptr = ptr.add(7).rip().as<int64_t**>();
			}, out);

		batch.Add({ XOR("CD"), XOR("48 8B 05 ? ? ? ? 0F 45 DF") }, [](Ptr ptr) {
			patterns::chat_data = ptr.from_instruction().as<decltype(patterns::chat_data)>();
			}, out);

		batch.Add({ XOR("GMI"), XOR("41 3B 0A 74 54") }, [](Ptr ptr) {
			patterns::get_model_info = ptr.sub(46).as<decltype(patterns::get_model_info)>();
			}, out);

		batch.Add({ XOR("DT"), XOR("48 8D 3D ? ? ? ? 80 3B 00 76 12 48 8B 0F 48 85 C9 74 0A 48 8B 01 FF 50 10 84 C0 75") }, [](Ptr ptr) {
			patterns::dispatch_table = ptr.from_instruction().as<decltype(patterns::dispatch_table)>();
			}, out);

		batch.Add({ XOR("VFX_W"), XOR("48 8D 0D ? ? ? ? 44 8A CE 44 8A C5 8B D3 44 89 64 24 ? 89 7C 24 20 E8 ? ? ? ? 8D") }, [](Ptr ptr) {
			patterns::ui_weather = ptr.from_instruction().add(0x60).as<rage::TimecycleKeyframeData*>();
			}, out);

		batch.Add({ XOR("VFX_WFX"), XOR("4C 8D 35 CE 98 8E 01") }, [](Ptr ptr) {
			patterns::weather_fx = ptr.from_instruction().as<rage::CWeatherVfx*>();
			}, out);

		batch.Add({ XOR("VFX_GV"), XOR("0F 2F 35 ? ? ? ? 0F 86 ? ? ? ? 0F 28 05 ? ? ? ? 48 8D 4D B0 41 0F 28 D9 48 8B D3 0F 28 D7 0F 29 45 A0") }, [](Ptr ptr) {
			patterns::game_visuals = ptr.from_instruction().as<rage::CGameVisuals*>();
			}, out);

		batch.Add({ XOR("VFX_VS"), XOR("48 8D 0D ? ? ? ? 0F 29 44 24 ? E8 ? ? ? ? 0F 28 05 ? ? ? ? 0F 59 44 24 ? F3 48 0F 2C C0 0F C6 C0 55") }, [](Ptr ptr) {
			patterns::visual_settings = ptr.from_instruction().as<rage::CVisualVfx*>();
			}, out);

		batch.Add({ XOR("VFX_UUV2"), XOR("48 8B C4 53 48 81 EC ? ? ? ? 80 B9 ? ? ? ? ? 0F 29 70 E8 0F 29 78 D8 48 8B D9 44 0F 29 40 ? 44 0F 29 48 ? 44") }, [](Ptr ptr) {
			patterns::update_ui_values_2 = ptr.as<decltype(patterns::update_ui_values_2)>();
			}, out);

		batch.Add({ XOR("MISC_MR"), XOR("40 53 48 83 EC 20 8A D9 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? 8B D0 E8 ? ? ? ? 48 85 C0 74 10") }, [](Ptr ptr) {
			patterns::mobile_radio = ptr.add(1).as<decltype(patterns::mobile_radio)>();
			}, out);

		batch.Add({ XOR("DHM"), XOR("48 89 05 ? ? ? ? EB 07 48 89 1D ? ? ? ? 48 8B CB") }, [](Ptr ptr) {
			patterns::draw_handler_mgr = ptr.from_instruction().as<PVOID*>();
		}, out);

		batch.Add({ XOR("WD"), XOR("48 8D 0D ? ? ? ? 48 98 4C 8B C6 41 8B 44 85 ? 0D ? ? ? ? 89 44 24 30 83 64 24 ? ? C6 44 24") }, [](Ptr ptr) {
			patterns::waypoint_data = ptr.from_instruction().as<rage::waypoint_data*>();
		}, out);

		batch.Add({ XOR("RR"), XOR("48 89 5C 24 08 57 48 83 EC 20 80 3D ? ? ? ? ? 48 8B FA 48 8B D9 74 13") }, [](Ptr ptr) {
			patterns::remove_reference = ptr.from_instruction().as<decltype(patterns::remove_reference)>();
		}, out);

		batch.Add({ XOR("IPP"), XOR("4C 8B 05 ? ? ? ? 4C 0F BF 0B") }, [](Ptr ptr) {
			patterns::interior_proxy_pool = ptr.from_instruction().as<decltype(patterns::interior_proxy_pool)>();
		}, out);

		batch.Add({ XOR("TCA"), XOR("48 8D 0D ? ? ? ? E8 ? ? ? ? 44 88 64 24 30 4C 8D 8C 24 60 02 00 00") }, [](Ptr ptr) {
			patterns::train_config_array = ptr.from_instruction().as<decltype(patterns::train_config_array)>();
			}, out);

		batch.Add({ XOR("NEM"), XOR("48 39 99 D0 00 00 00 74 3C") }, [](Ptr ptr) {
			patterns::m_net_event_manager = ptr.add(0xC).rip().as<rage::netEventMgr**>();
			patterns::m_check_event_queue = ptr.add(0x13).rip().as<patterns::check_event_queue_t>();
			patterns::m_net_event_pool = ptr.add(0x1A).rip().as<GenericPool**>();
			patterns::m_get_new_pool_item = ptr.add(0x1F).rip().as<patterns::get_new_pool_item_t>();
			patterns::m_queue_network_event = ptr.add(0x41).rip().as<patterns::queue_network_event_t>();
		}, out);

		//40 53 48 83 EC 20 8A D9 8A D1 48 8D 0D ? ? ? ? 45 33 C0 E8 ? ? ? ? 88 1D ? ? ? ? 48 83 C4 20

		batch.Add({ XOR("HVBO"), XOR("40 53 48 83 EC 20 8A D9 8A D1 48 8D 0D ? ? ? ? 45 33 C0 E8 ? ? ? ? 88 1D ? ? ? ? 48 83 C4 20") }, [](Ptr ptr) {
			patterns::set_seethrough = ptr.as<decltype(patterns::set_seethrough)>();
		}, out);

		batch.Add({ XOR("OQ"), XOR("40 53 48 83 EC 20 33 DB 44 8D 43 01 41 3B C8 75") }, [](Ptr ptr) {
			patterns::ocean_quads.m_ocean = (rage::ocean_quad_info*)ptr.add(118).from_instruction().as<decltype(patterns::ocean_quads.m_ocean)>();
			patterns::ocean_quads.m_calming = (rage::ocean_quad_info*)ptr.add(118).from_instruction().add(0xC).as<decltype(patterns::ocean_quads.m_calming)>();
			patterns::ocean_quads.m_wave = (rage::ocean_quad_info*)ptr.add(118).from_instruction().add(0x25).as<decltype(patterns::ocean_quads.m_wave)>();
		}, out);

		batch.Add({ XOR("WT"), XOR("4C 8D 0D ? ? ? ? 48 0F 45 D1 48 8B 0D ? ? ? ? 48 83 64 24 ? ? 4C 8D 05 ? ? ? ? E8 ? ? ? ? 84 C0 0F 85") }, [](Ptr ptr) {
			patterns::water_tune = (rage::water_tune*)ptr.from_instruction().as<decltype(patterns::water_tune)>();
		}, out);

		batch.Add({ XOR("VFXL"), XOR("48 8D 05 ? ? ? ? 4C 8D 1C 7F 48 8B 4A 10 49 C1 E3 05 4C 03 D8 0F B6 85 ? ? ? ? 48 23 C8 8B 42 18 48 3B") }, [](Ptr ptr) {
			patterns::vfx_liquid = ptr.from_instruction().as<decltype(patterns::vfx_liquid)>();
			}, out);

		/*batch.Add({ XOR("RI2"), XOR("0F B7 44 24 ? 66 89 44 4E") }, [](Ptr ptr) {
			patterns::replay_interface = ptr.add(0x1F).as<decltype(patterns::replay_interface)>();
		}, out);*/

		batch.Add({ XOR("BE"), XOR("0F 85 ? ? ? ? 48 8B 05 ? ? ? ? 48 8B 48 08 E8") }, [](Ptr ptr) {
			patterns::blame_explode = memory::byte_patch::make(ptr.as<std::uint16_t*>(), 0xE990).get();
			}, out);

		batch.Add({ XOR("MWL"), XOR("8B 43 6C 89 05") }, [](Ptr ptr) {
			patterns::max_wanted_level = byte_patch::make(ptr.add(5).rip().as<uint32_t*>(), 0).get();
			patterns::max_wanted_level_2 = byte_patch::make(ptr.add(14).rip().as<uint32_t*>(), 0).get();
			}, out);

		//VM_TIGER_BLACK_END	

		auto mod = memory::module(XOR("GTA5.exe"));
		batch.run(mod);



		//LOG_SUCCESS(XOR("Loaded patterns"));
		return true;
	}

	bool bypass() {
		batch batch;
		bool out = true;
		//VM_LION_BLACK_START
		/*batch.Add({ "IRC", "80 3D ? ? ? ? ? 0F 85 ? ? ? ? 48 8B 05 ? ? ? ? 48 85 C0" }, [](Ptr ptr) {
			//patterns::invalid_resource_check = ptr.as<uint64_t>();
			//memory::patchAddress(patterns::invalid_resource_check, 0xC3);
		}, out);

		batch.Add({ "ICP-1", "48 83 EC 48 48 83 64 24 ? ? 83 4C 24" }, [](Ptr ptr) {
			patterns::integ_check_1 = ptr.as<uint64_t>();
			memory::patchAddress(patterns::integ_check_1, 0xC3);
		}, out);*/

		//MUTATE_START

		batch.Add({ XOR("MEM_HS"), XOR("83 C8 01 48 8D 0D ? ? ? ? 41 B1 01 45 33 C0") }, [](Ptr ptr) {
			patterns::heap_size = ptr.add(17).as<decltype(patterns::heap_size)>();
		}, out);
		/*batch.Add({ XOR("AC_ICF"), XOR(48 8D 0D ? ? ? ? 88 05 ? ? ? ? 48 8D 05") }, [](Ptr ptr) {
			patterns::interval_check_func = ptr.from_instruction().as<PVOID>();
		}, out);*/

		/*batch.Add({ XOR("ACT"), XOR("48 83 EC 48 48 83 64 24 ? ? 83 4C 24 ? ? 33 D2 48 8D 05 ? ? ? ? 44 8D 4A 0F 48 8D 0D ? ? ? ? 41 B8 ? ? ? ? 48 89 44 24 ? E8") }, [](Ptr ptr) {
			HANDLE thread_id = ptr.add(51).from_instruction().as<HANDLE>();
			if (thread_id) {
				LOG_WARN("Suspended Arxan Thread -> ID: %i", GetThreadId(thread_id));
				SuspendThread(thread_id);
			}
			}, out);*/

		//MUTATE_END
		
		auto mod = memory::module(XOR("GTA5.exe"));
		batch.run(mod);
		
		//ARXAN ARXAN ARXAN ARXAN ARXAN ARXAN ARXAN ARXAN ARXAN ARXAN ARXAN ARXAN ARXAN ARXAN ARXAN 
		auto patches = mod.scan_all(XOR("48 8D 45 ? 48 89 45 ? 48 8D 05 ? ? ? ? 48 89 45"));
		for (auto patch : patches) {
			//sig lands us on the first lea instruction, we want to create the patch on the second so we skip the first one
			memset(patch.add(8).as<PVOID>(), 0x90, 7);
		}

	
		

		//48 8D 45 ? 48 8D 45


	//	LOG_SUCCESS(XOR("Loaded bypasses"));
		//VM_LION_BLACK_END
		return true;
	}

	bool hooks() {
		batch batch;
		bool out = false;
	//	MUTATE_START
		
		//VM_TIGER_BLACK_START



			batch.Add({ XOR("MEM_HS"), XOR("83 C8 01 48 8D 0D ? ? ? ? 41 B1 01 45 33 C0") }, [](Ptr ptr) {
			patterns::heap_size = ptr.add(17).as<decltype(patterns::heap_size)>();
			}, out);

		batch.Add({ XOR("AC_QD"), XOR("48 89 5C 24 ? 57 48 83 EC ? 0F B6 99") }, [](Ptr ptr) {
			patterns::queue_dependency = ptr.as<uint64_t>();
			return hooking::detour("QD", patterns::queue_dependency, &queueDependencyHook, &ogQueueDependencyHook);
			}, out);


		batch.Add({ XOR("AC_CRC"), XOR("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 83 EC 30 44 8B F1 48 8B 0D") }, [](Ptr ptr) {
			patterns::check_crc = ptr.add(0x64).as<uint64_t>();
		}, out);

		batch.Add({ XOR("AC_RMS"), XOR("40 53 48 83 EC 40 83 B9 ? ? ? ? ? 48 8B D9 75 67 48 83 64 24 ? ? 48 83 64 24 ? ? 48 8D 54 24 ? 48 81 C1") }, [](Ptr ptr) {
			patterns::report_myself = ptr.add(0x5E).call().add(0x22).as<uint64_t>();
		}, out);

		batch.Add({ XOR("AC_CS"), XOR("48 89 5C 24 08 57 48 83 EC 20 33 FF 48 8B D9 48 85 C9 74 0B") }, [](Ptr ptr) {
			patterns::cash_spawn = ptr.sub(0x3F).as<uint64_t>();
		}, out);

		batch.Add({ XOR("AC_AETL"), XOR("4C 8B D1 48 63 49 18") }, [](Ptr ptr) {
			patterns::add_event_to_list = ptr.as<uint64_t>();
			return hooking::detour("AETL", patterns::add_event_to_list, &addEventToListHook, &ogAddEventToListHook);
			}, out);

		batch.Add({ XOR("AC_SNE"), XOR("48 8B 5F 08 48 8B 7F 10 49 8B D6 48 8B 03 48 8B CB FF 90 ? ? ? ? 84 C0 0F 85") }, [](Ptr ptr) {
			patterns::send_network_event = ptr.sub(0x3A).as<uint64_t>();
			return hooking::detour("SNE", patterns::send_network_event, &sendNetworkEventHook, &ogSendNetworkEventHook);
			}, out);

		batch.Add({ XOR("AC_SHTTPR"), XOR("40 55 57 41 54 41 55") }, [](Ptr ptr) {
			patterns::send_http_request = ptr.as<uint64_t>();
			return hooking::detour("SHTTPR", patterns::send_http_request, &sendHTTPRequestHook, &ogSendHTTPRequestHook);
			}, out);

		batch.Add({ XOR("AC_SM"), XOR("E8 ? ? ? ? EB 69 41 8B D6") }, [](Ptr ptr) {
			patterns::send_metric = ptr.call().as<uint64_t>();
			return hooking::detour("SM", patterns::send_metric, &sendMetricHook, &ogSendMetricHook);
		}, out);

		batch.Add({ XOR("IDKBRUH"), XOR("48 8B 05 DD C4 61 00") }, [](Ptr ptr) {
			uint64_t target = ptr.as<uint64_t>();
			return hooking::detour("IDKBRUH", target, &write_unsigned_int_from_buffer, &write_unsigned_int_from_buffer_t);
		}, out);

		batch.Add({ XOR("RUTDRB"), XOR("48 8D 05 ? ? ? ? 48 8D 8E ? ? ? ? 48 8D 54 24 ? 48 89 5C 24 ? 48 89 44 24") }, [](Ptr ptr) {
			patterns::sync_data_reader_vtable = ptr.from_instruction().as<decltype(patterns::sync_data_reader_vtable)>();
			return hooking::vmt(XOR("BB_1"), patterns::sync_data_reader_vtable, 1, &read_unsigned_int_from_buffer, &read_unsigned_int_from_buffer_t)
				&& hooking::vmt(XOR("BB_2"), patterns::sync_data_reader_vtable, 2, &read_unsigned_short_from_buffer, &read_unsigned_short_from_buffer_t)
				&& hooking::vmt(XOR("BB_3"), patterns::sync_data_reader_vtable, 3, &read_unsigned_char_from_buffer, &read_unsigned_char_from_buffer_t)
				&& hooking::vmt(XOR("BB_4"), patterns::sync_data_reader_vtable, 4, &read_int_from_buffer, &read_int_from_buffer_t)
				&& hooking::vmt(XOR("BB_5"), patterns::sync_data_reader_vtable, 5, &read_short_from_buffer, &read_short_from_buffer_t)
				&& hooking::vmt(XOR("BB_6"), patterns::sync_data_reader_vtable, 6, &read_char_from_buffer, &read_char_from_buffer_t)
				&& hooking::vmt(XOR("BB_7"), patterns::sync_data_reader_vtable, 7, &read_bool_from_buffer, &read_bool_from_buffer_t)
				&& hooking::vmt(XOR("BB_8"), patterns::sync_data_reader_vtable, 8, &read_long_long_from_buffer, &read_long_long_from_buffer_t)
				&& hooking::vmt(XOR("BB_9"), patterns::sync_data_reader_vtable, 9, &read_int_from_buffer, &read_int_from_buffer_t)
				&& hooking::vmt(XOR("BB_10"), patterns::sync_data_reader_vtable, 10, &read_short_from_buffer, &read_short_from_buffer_t)
				&& hooking::vmt(XOR("BB_11"), patterns::sync_data_reader_vtable, 11, &read_char_from_buffer, &read_char_from_buffer_t)
				&& hooking::vmt(XOR("BB_12"), patterns::sync_data_reader_vtable, 12, &read_unsigned_long_long_from_buffer, &read_unsigned_long_long_from_buffer_t)
				&& hooking::vmt(XOR("BB_13"), patterns::sync_data_reader_vtable, 13, &read_unsigned_int_from_buffer, &read_unsigned_int_from_buffer_t)
				&& hooking::vmt(XOR("BB_14"), patterns::sync_data_reader_vtable, 14, &read_unsigned_short_from_buffer, &read_unsigned_short_from_buffer_t)
				&& hooking::vmt(XOR("BB_15"), patterns::sync_data_reader_vtable, 15, &read_unsigned_char_from_buffer, &read_unsigned_char_from_buffer_t)
				&& hooking::vmt(XOR("BB_16"), patterns::sync_data_reader_vtable, 16, &read_float_from_buffer, &read_float_from_buffer_t)
				&& hooking::vmt(XOR("BB_17"), patterns::sync_data_reader_vtable, 17, &read_unsigned_float_from_buffer, &read_unsigned_float_from_buffer_t)
				&& hooking::vmt(XOR("BB_18"), patterns::sync_data_reader_vtable, 18, &read_network_id_from_buffer, &read_network_id_from_buffer_t)
				&& hooking::vmt(XOR("BB_19"), patterns::sync_data_reader_vtable, 23, &read_array_from_buffer, &read_array_from_buffer_t)
				&& hooking::vmt(XOR("BB_20"), patterns::sync_data_reader_vtable, 24, &read_string_from_buffer, &read_string_from_buffer_t);
		}, out);

		batch.Add({ XOR("RBWD"), XOR("48 89 74 24 ? 57 48 83 EC 20 48 8B D9 33 C9 41 8B F0 8A") }, [](Ptr ptr) {
			patterns::read_bitbuf_dword = ptr.sub(5).as<decltype(patterns::read_bitbuf_dword)>();
			uint64_t target = ptr.sub(5).as<uint64_t>();
			return hooking::detour("RBWD", target, &read_bitbuf_dword, &read_bitbuf_dword_t);
			}, out);

		batch.Add({ XOR("RBA"), XOR("48 89 5C 24 ? 57 48 83 EC 30 41 8B F8 4C") }, [](Ptr ptr) {
			patterns::read_bitbuf_array = ptr.as<decltype(patterns::read_bitbuf_array)>();
			uint64_t target = ptr.as<uint64_t>();
			return hooking::detour("RBA", target, &read_bitbuf_array, &read_bitbuf_array_t);
			}, out);

		batch.Add({ XOR("RBS"), XOR("48 89 5C 24 08 48 89 6C 24 18 56 57 41 56 48 83 EC 20 48 8B F2 45") }, [](Ptr ptr) {
			patterns::read_bitbuf_string = ptr.as<decltype(patterns::read_bitbuf_string)>();
			uint64_t target = ptr.as<uint64_t>();
			return hooking::detour("RBS", target, &read_bitbuf_string, &read_bitbuf_string_t);
			}, out);

		batch.Add({ XOR("RBB"), XOR("E8 ? ? ? ? 84 C0 74 41 48 8D 56 2C") }, [](Ptr ptr) {
			patterns::read_bitbuf_bool = ptr.call().as<decltype(patterns::read_bitbuf_bool)>();
			uint64_t target = ptr.call().as<uint64_t>();
			return hooking::detour("RBB", target, &read_bitbuf_bool, &read_bitbuf_bool_t);
			}, out);


		batch.Add({ XOR("GFI"), XOR("85 D2 74 68 FF CA 74 5B FF CA 74 4E FF CA 74 41 FF CA 74 34 FF CA 74 27 FF CA 74 1A FF CA 74 0D") }, [](Ptr ptr) {
			patterns::get_font_id = ptr.as<uint64_t>();
			return hooking::detour("GFI", patterns::get_font_id, &getFontIdHook, &ogGetFontIdHook);
		}, out);

		batch.Add({ XOR("FGS"), XOR("E8 ? ? ? ? 8B 44 24 78 4C 8B 4C 24 ? 44 8B C7") }, [](Ptr ptr) {
			patterns::format_game_string = ptr.call().as<uint64_t>();
			return hooking::detour("FGS", patterns::format_game_string, &formatEngineStringHook, &ogFormatEngineStringHook);
			}, out);

		batch.Add({ XOR("GGSLC"), XOR("E8 ? ? ? ? 8B F8 48 8B 55 B8") }, [](Ptr ptr) {
			patterns::get_game_string_line_count = ptr.call().as<uint64_t>();
			return hooking::detour("GGSLC", patterns::get_game_string_line_count, &getEngineStringLineCountHook, &ogGetEngineStringLineCountHook);
			}, out);

		batch.Add({ XOR("AWIV"), XOR("49 8B 40 08 39 10") }, [](Ptr ptr) {
			patterns::allow_weapons_in_vehicle = ptr.sub(23).as<uint64_t>();
			return hooking::detour("AWIV", patterns::allow_weapons_in_vehicle, &allowWeaponsInVehicleHook, &ogAllowWeaponsInVehicleHook);
			}, out);

		batch.Add({ XOR("RNE"), XOR("66 41 83 F9 ? 0F 83") }, [](Ptr ptr) {
			patterns::received_network_event = ptr.as<uint64_t>();
			return hooking::detour("RNE", patterns::received_network_event, &receivedNetworkEventHook, &ogReceivedNetworkEventHook);
			}, out);

		batch.Add({ XOR("RCS"), XOR("48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 41 54 41 55 41 56 41 57 48 83 EC 40 4C 8B EA") }, [](Ptr ptr) {
			patterns::receive_clone_sync = ptr.as<decltype(patterns::receive_clone_sync)>();
			patterns::get_sync_tree_for_type = ptr.add(0x2F).add(1).rip().as<decltype(patterns::get_sync_tree_for_type)>(); // 0F B7 CA 83 F9 07 .as()
			patterns::get_net_object = ptr.add(0x109).add(1).rip().as<decltype(patterns::get_net_object)>(); // E8 ? ? ? ? 0F B7 53 7C .add(1).rip().as()
			patterns::get_sync_type_info = ptr.add(0x11F).add(1).rip().as<decltype(patterns::get_sync_type_info)>(); // 44 0F B7 C1 4C 8D 0D .as()
			return hooking::detour("RCS", patterns::receive_clone_sync, &receiveCloneSyncHook, &ogReceiveCloneSyncHook);
			}, out);

		batch.Add({ XOR("RCC"), XOR("48 8B C4 66 44 89 48") }, [](Ptr ptr) {
			patterns::receive_clone_create = ptr.as<uint64_t>();
			return hooking::detour("RCC", patterns::receive_clone_create, &receiveCloneCreateHook, &ogReceiveCloneCreateHook);
			}, out);

		batch.Add({ XOR("RCR"), XOR("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 54 41 56 41 57 48 83 EC 50 4C 8B F2 4D 8B E0 48") }, [](Ptr ptr) {
			patterns::receive_clone_remove = ptr.as<uint64_t>();
			return hooking::detour("RCR", patterns::receive_clone_remove, &receiveCloneRemoveHook, &ogReceiveCloneRemoveHook);
		}, out);

		batch.Add({ XOR("RCRA"), XOR("48 8B C4 48 89 58 ? 48 89 68 ? 48 89 70 ? 57 41 56 41 57 48 83 EC ? 4C 8B FA 49 8B D8") }, [](Ptr ptr) {
			patterns::receive_clone_remove_ack = ptr.as<uint64_t>();
			//return hooking::detour("RCRA", patterns::receive_clone_remove_ack, &receiveCloneRemoveAckHook, &ogReceiveCloneRemoveAckHook);
		}, out);

		batch.Add({ XOR("RCCA"), XOR("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 54 41 56 41 57 48 83 EC 50 4C 8B FA") }, [](Ptr ptr) {
			patterns::receive_clone_create_ack = ptr.as<uint64_t>();
			//return hooking::detour("RCCA", patterns::receive_clone_create_ack, &receiveCloneCreateAckHook, &ogReceiveCloneCreateAckHook);
		}, out);

		batch.Add({ XOR("RCSA"), XOR("48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC ? 4C 8B E2") }, [](Ptr ptr) {
			patterns::receive_clone_sync_ack = ptr.as<uint64_t>();
			//return hooking::detour("RCSA", patterns::receive_clone_sync_ack, &receiveCloneSyncAckHook, &ogReceiveCloneSyncAckHook);
		}, out);

		batch.Add({ XOR("CAD"), XOR("E8 ? ? ? ? 84 C0 0F 84 AF 01 00 00 48 8B 03") }, [](Ptr ptr) {
			patterns::can_apply_data = ptr.call().as<uint64_t>();
			return hooking::detour("CAD", patterns::can_apply_data, &canApplyDataHook, &ogCanApplyDataHook);
		}, out);

		/*batch.Add({ XOR("RPE"), XOR("E8 ? ? ? ? ? ? ? ? F6 C3 02 74 15") }, [](Ptr ptr) {
			patterns::receive_presence_event = ptr.call().as<uint64_t>();
			//return hooking::detour("RPE", patterns::receive_presence_event, &receivePresenceEvent, &ogReceivePresenceEvent);
		}, out);*/

		/*batch.Add({XOR("WGSITEM"), XOR(48 89 5C 24 ? ? 48 89 74 24 ? ? 57 48 81 EC ? ? ? ? ? ? ? ? 48 8B 02" }, [](Ptr ptr) {
			patterns::write_gs_item = ptr.as<uint64_t>();
		//	return hooking::detour("WGSITEM", patterns::write_gs_item, &writeGSItemHook, &ogWriteGSItemHook);
		}, out);*/

		batch.Add({ XOR("SPGS"), XOR("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 30 0F B7 81") }, [](Ptr ptr) {
			patterns::write_player_game_state_data_node = ptr.as<uint64_t>();
			return hooking::detour("SPGS", patterns::write_player_game_state_data_node, &syncPlayerGameStateHook, &ogSyncPlayerGameStateHook);
			}, out);

		batch.Add({ XOR("SPH"), XOR("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 83 EC 20 48 8B B9 ? ? ? ? 4C 8D B1") }, [](Ptr ptr) {
			patterns::write_ped_health_data_node = ptr.as<uint64_t>();
			return hooking::detour("SPH", patterns::write_ped_health_data_node, &syncPedHealthHook, &ogSyncPedHealthHook);
			}, out);

		/*batch.Add({ XOR("RAB"), XOR(48 89 5C 24 10 55 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 83 EC 30 48 8B 05" }, [](Ptr ptr) {
			patterns::receive_array_broadcast = ptr.call().as<uint64_t>();
			return hooking::detour("RAB", patterns::receive_array_broadcast, &receiveArrayBroadcastHook, &ogReceiveArrayBroadcastHook);
		}, out);*/

		batch.Add({ XOR("APPI"), XOR("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 20 41 8A E8") }, [](Ptr ptr) {
			patterns::apply_player_physical_index = ptr.as<uint64_t>();
			return hooking::detour("APPI", patterns::apply_player_physical_index, &applyPlayerPhysicalIndexHook, &ogApplyPlayerPhysicalIndexHook);
			}, out);

		batch.Add({ XOR("UPSS"), XOR("40 53 48 83 EC 30 48 8B 05 ? ? ? ? 4C 8B D1 41 83 7A ? ? 48 8B 48 40 7D 23 48 85 C9 0F 84 ? ? ? ? 48 8B 01 4C 8D 05")}, [](Ptr ptr) {
			auto target = ptr.as<uint64_t>();
			return hooking::detour("UPSS", target, &updatePlayerScriptStatus, &ogUpdatePlayerScriptStatus);
		}, out);

		batch.Add({ XOR("STT"), XOR("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 80 B9 ? ? ? ? ? 8B FA 48 8B D9 74 05 8B 41 10 EB 7F E8 ? ? ? ? 83 25") }, [](Ptr ptr) {
			patterns::tick_script_thread = ptr.as<uint64_t>();
			//return hooking::detour("STT", patterns::tick_script_thread, &tickScriptThreadHook, &ogTickScriptThreadHook);
			}, out);

		batch.Add({ XOR("IMCP"), XOR("E8 ? ? ? ? 40 88 7C 24 ? 49 89 9C 24") }, [](Ptr ptr) {
			patterns::invalid_mods = ptr.call().as<uint64_t>();
			return hooking::detour("IMCP", patterns::invalid_mods, &invalidModsCrashHook, &ogInvalidModsCrashHook);
			}, out);

		batch.Add({ XOR("IDCP"), XOR("E8 ? ? ? ? 8B 9C 24 B8 00 00 00 4C 8B AC 24 A8 00 00 00") }, [](Ptr ptr) {
			patterns::invalid_decal = ptr.call().as<uint64_t>();
			return hooking::detour("IDCP", patterns::invalid_decal, &invalidDecalCrashHook, &ogInvalidDecalCrashHook);
			}, out);

		batch.Add({ XOR("PCP"), XOR("40 55 53 57 41 56 48 8B EC 48 83 EC 68") }, [](Ptr ptr) {
			patterns::parachute_crash_patch = ptr.as<uint64_t>();
			return hooking::detour("PCP", patterns::parachute_crash_patch, &parachuteCrashHook, &ogParachuteCrashHook);
			}, out);

		batch.Add({ XOR("PCP2"), XOR("0F 88 ? ? ? ? 75 34") }, [](Ptr ptr) {
			patterns::parachute_crash_patch2 = ptr.sub(6).as<uint64_t>();
			return hooking::detour("PCP2", patterns::parachute_crash_patch2, &parachuteCrashHook2, &ogParachuteCrashHook2);
			}, out);

		batch.Add({ XOR("FCP"), XOR("E8 ? ? ? ? 84 C0 75 0B 41 FF CF") }, [](Ptr ptr) {
			patterns::fragment_crash = ptr.call().as<uint64_t>();
			return hooking::detour("FCP", patterns::fragment_crash, &fragmentCrashHook, &ogFragmentCrashHook);
			}, out);

		batch.Add({ XOR("GNED"), XOR("53 43 52 49 50 54 5F 4E 45 54 57 4F 52 4B") }, [](Ptr ptr) {
			patterns::network_event_data = ptr.sub(0x38).as<uint64_t>();
			//return hooking::detour("GNED", patterns::network_event_data, &getNetworkEventDataHook, &ogGetNetworkEventDataHook);
			}, out);

		batch.Add({ XOR("SCM"), XOR("48 83 EC 20 48 8B F1 48 8B CA 41 8A E9") }, [](Ptr ptr) {
			patterns::send_chat_message = ptr.sub(21).as<uint64_t>();
			return hooking::detour("SCM", patterns::send_chat_message, &sendChatMessageHook, &ogSendChatMessageHook);
			}, out);

		batch.Add({ XOR("RNM"), XOR("48 83 EC 20 4C 8B 71 50 33 ED") }, [](Ptr ptr) {
			patterns::receive_net_message = ptr.sub(0x19).as<uint64_t>();
			return hooking::detour("RNM", patterns::receive_net_message, &receiveNetMessageHook, &ogReceiveNetMessageHook);
			}, out);

		batch.Add({ XOR("CCP"), XOR("E8 ? ? ? ? 83 F8 FF 75 B9") }, [](Ptr ptr) {
			patterns::chat_profanity = ptr.call().as<uint64_t>();
			return hooking::detour("CCP", patterns::chat_profanity, &checkChatProfanityHook, &ogCheckChatProfanityHook);
			}, out);

		batch.Add({ XOR("RBPH"), XOR("48 89 5C 24 08 4C 89 44 24 18 55 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 81 EC 80 00 00 00 48") }, [](Ptr ptr) {
			auto target = ptr.as<uint64_t>();
			return hooking::detour("RBPH", target, &renderBigPedHook, &ogRenderBigPedHook);
		}, out);

		batch.Add({ XOR("RPH"), XOR("48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 41 54 41 55 41 56 41 57 48 81 EC 80 00 00 00 48 8B FA") }, [](Ptr ptr) {
			auto target = ptr.as<uint64_t>();
			return hooking::detour("RPH", target, &renderPedHook, &ogRenderPedHook);
		}, out);



		batch.Add({ XOR("REH"), XOR("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 57 41 54 41 55 41 56 41 57 48 83 EC 70 0F BA") }, [](Ptr ptr) {
			auto target = ptr.as<uint64_t>();
			return hooking::detour("REH", target, &renderEntityHook, &ogRenderEntityHook);
		}, out);

		/*batch.Add({ XOR("SPTTT"), XOR("40 55 53 56 57 41 54 48 8B") }, [](Ptr ptr) {
			auto target = ptr.as<uint64_t>();
			return hooking::detour("SPTTT", target, &serialize_parachute_task, &serialize_parachute_task_t);
		}, out);*/


		batch.Add({ XOR("TAC"), XOR("48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 80 3D ? ? ? ? ? 41 8B D8 8B F2") }, [](Ptr ptr) {
			auto target = ptr.as<uint64_t>();
			//return hooking::detour("TAC", target, &task_ambient_clips, &task_ambient_clips_t);
			}, out);

		batch.Add({ XOR("RTGSDN"), XOR("48 89 5C 24 ? 57 48 83 EC 30 48 8B 02 48 8B FA") }, [](Ptr ptr) {
			patterns::read_train_data_node = ptr.as<uint64_t>();
			//return hooking::detour("RTGSDN", patterns::read_train_data_node, &readTrainGameStateHook, &ogReadTrainGameStateHook);
		}, out);

		batch.Add({ XOR("PMFR"), XOR("48 89 5C 24 08 48 89 74 24 10 57 48 81 EC F0 00 00 00 41 83") }, [](Ptr ptr) {
			uint64_t target = ptr.as<uint64_t>();
			return hooking::detour("PMFR", target, &processMatchmakingFindResponseHook, &ogProcessMatchmakingFindResponseHook);
		}, out);

		batch.Add({ XOR("PDN2"), XOR("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 30 48 8B 01 4C 8B F2 33 D2 48 8B F1 FF 90 ? ? ? ? 84 C0 0F 84") }, [](Ptr ptr) {
			uint64_t target = ptr.as<uint64_t>();
			//return hooking::detour("PDN2", target, &compressDataNodeHook2, &ogCompressDataNodeHook2);
		}, out);

		batch.Add({ XOR("SPMDN"), XOR("48 89 5C 24 18 55 56 57 48 83 EC 30 48 8B 02 48 8D 99 C0 00 00 00") }, [](Ptr ptr) {
			uint64_t target = ptr.as<uint64_t>();
			//return hooking::detour("SPMDN", target, &syncPedMovementDataNodeHook, &ogSyncPedMovementDataNodeHook);
		}, out);

		batch.Add({ XOR("VFX_UUV"), XOR("48 83 EC 18 48 8B 0D") }, [](Ptr ptr) {
			patterns::update_ui_values = ptr.as<decltype(patterns::update_ui_values)>();
			return hooking::detour("VFX_UUV", patterns::update_ui_values, &updateUIValuesHook, &ogUpdateUIValuesHook);
		}, out);


		batch.Add({ XOR("SSMA"), XOR("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 81 EC D0 00 00 00 49 8B") }, [](Ptr ptr) {
			uint64_t target = ptr.as<uint64_t>();
			//return hooking::detour("SSMA", target, &sendSessionMatchmakingAttributesHook, &ogSendSessionMatchmakingAttributesHook);
		}, out);

		batch.Add({ XOR("SGSBGH2"), XOR("E8 ? ? ? ? 84 C0 0F 84 F6 FE FF FF") }, [](Ptr ptr) {
			patterns::start_session_search = ptr.call().as<uint64_t>();
			//return hooking::detour("SGSBGH2", target, &startMatchmakingFindSessionsHook, &ogStartMatchmakingFindSessionsHook);
			}, out);

		/*
		batch.Add({ XOR("ITC"), XOR("E8 ? ? ? ? F3 44 0F 10 93 90 03 00 00") }, [](Ptr ptr) {
			patterns::infinite_train_crash = ptr.call().as<uint64_t>();
			patterns::get_next_carriage = ptr.call().add(0xF).rip().as<patterns::get_next_carriage_t>();
			//return hooking::detour("ITC", patterns::infinite_train_crash, &infiniteTrainCrashHook, &ogInfiniteTrainCrashHook);
		}, out);	*/
		

		/*batch.Add({ "RNSM", "E8 ? ? ? ? 84 C0 74 60 4C 39 77 40 74 29 48 8B 4C 24 ? 48 8B 01 FF 50 28 48 8B 4F 40 44 0F B7" }, [](Ptr ptr) {
			patterns::read_new_script_host_message = ptr.call().as<uint64_t>();
			return hooking::detour("RNSM", patterns::read_new_script_host_message - 0x6D, &readNewScriptHostMessageHook, &ogReadNewScriptHostMessageHook);
		}, out);*/
		//MUTATE_END

		//VM_TIGER_BLACK_END

		auto mod = memory::module("GTA5.exe");
		batch.run(mod);

		if (auto pat1 = mod.scan(XOR("3b 0a 0f 83 ? ? ? ? 48 ff c7"))) {
			memory::byte_patch::make(pat1.add(2).as<uint32_t*>(), 0xc9310272)->apply();
			memory::byte_patch::make(pat1.add(6).as<uint16_t*>(), 0x9090)->apply();
		}

		if (auto pat2 = mod.scan(XOR("3b 0a 0f 83 ? ? ? ? 49 03 fa"))) {
			memory::byte_patch::make(pat2.add(2).as<uint32_t*>(), 0xc9310272)->apply();
			memory::byte_patch::make(pat2.add(6).as<uint16_t*>(), 0x9090)->apply();
		}

		auto pat3 = mod.scan_all(XOR("3b 11 0f 83 ? ? ? ? 48 ff c7"));
		for (auto& handle : pat3) {
			memory::byte_patch::make(handle.add(2).as<uint32_t*>(), 0xd2310272)->apply();
			memory::byte_patch::make(handle.add(6).as<uint16_t*>(), 0x9090)->apply();
		}

		auto pat4 = mod.scan_all(XOR("3b 11 0f 83 ? ? ? ? 49 03 fa"));
		for (auto& handle : pat4) {
			memory::byte_patch::make(handle.add(2).as<uint32_t*>(), 0xd2310272)->apply();
			memory::byte_patch::make(handle.add(6).as<uint16_t*>(), 0x9090)->apply();
		}

		//MUTATE_END
	/*	memory::batch batch2;

		batch2.Add({ "PD", "48 8D 05 ? ? ? ? 48 8B F1 48 89 01 48 83 C1 08 E8 ? ? ? ? 33 ED 48 8D 8E 68 5B 00 00" }, [](Ptr ptr) {
			auto presence_data_vft = ptr.from_instruction().as<uint64_t*>();
			patterns::update_presence_attribute_int = presence_data_vft[1];
			patterns::update_presence_attribute_string = presence_data_vft[3];
			hooking::detour("UPAI", patterns::update_presence_attribute_int, &updatePresenceAttributeIntHook, &ogUpdatePresenceAttributeIntHook);
			return hooking::detour("UPAS", patterns::update_presence_attribute_string, &updatePresenceAttributeStringHook, &ogUpdatePresenceAttributeStringHook);
		}, out);

		batch2.Add({ "SGPA", "48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 54 41 56 41 57 48 83 EC 40 33 DB 41" }, [](Ptr ptr) {
			patterns::start_get_presence_attributes = ptr.as<uint64_t>();
		}, out);

		auto mod2 = memory::module("socialclub.dll");
		batch2.run(mod2);*/

		//LOG_SUCCESS(XOR("Loaded hooks"));

		return true;
	}


	void* hooks::infiniteTrainCrashHook(void* carriage) {
		void* current_carriage = carriage;
		int count = 0;
		while (patterns::get_next_carriage(current_carriage)) {
			if (++count > 20)
				return nullptr;
			current_carriage = patterns::get_next_carriage(current_carriage);
		}
		return current_carriage;
	}

	void hooks::readTrainGameStateHook(rage::netObject* player, CTrainGameStateDataNode* node) {
		if (player->m_object_id == node->m_linked_to_backward_id && player->m_object_id == node->m_linked_to_forward_id && player->m_object_id == node->m_engine_id) {
			return;
		}
		if (++node->m_carriage_config_index > 20) {
			return;
		}
		if (node->m_track_id < 0 || node->m_track_id >= 27) {
			return;
		}
		return ogReadTrainGameStateHook(player, node);
	}

	bool hooks::addItemToBasketHook(uint64_t _this, i32* items) {
		if (_this) {
			rage::netShopping::transactionNode* node = *(rage::netShopping::transactionNode**)(_this + 0x20);//m_next
			while (node) {
				if (node->m_transaction->m_category == (int)0xAE04310C) {
					LOG_WARN(XOR("Blocked Arxan Report"));
					return false;
				}
				
			}
		}
		return ogAddItemToBasketHook(_this, items);
	}

	int hooks::checkChatProfanityHook(uint64_t rcx, uint64_t input, uint64_t output) {
		if (menu::network::chat::vars::m_vars.m_bypass_profanity_filter) {
			return -1;
		}
		return ogCheckChatProfanityHook(rcx, input, output);
	}

	bool hooks::sendChatMessageHook(void* team_mgr, rage::rlGamerInfo* local_gamer_info, const char* message, bool is_team) {
		return ogSendChatMessageHook(team_mgr, local_gamer_info, message, is_team);
	}

	bool hooks::initNativeTablesHook(rage::scrProgram* program) {
		bool ret = ogInitNativeTablesHook(program);
		//menu::g_script_patcher_service->on_script_load(program);

		if (program->m_code_size && program->m_code_blocks) // ensure that we aren't hooking SHV threads
		{
			script::g_native_hooks->hook_program(program);
		}

		return ret;
	}

	LPVOID hooks::convertThreadToFiberHook(LPVOID param) {
		if (IsThreadAFiber())
			return GetCurrentFiber();
		return ogConvertThreadToFiberHook(param);
	}

	bool hooks::allowWeaponsInVehicleHook(int64_t unk, int weaponinfo_group) {
		if (menu::weapon::disables::vars::m_vars.m_vehicle_block) {
			if (weaponinfo_group == RAGE_JOAAT("GROUP_THROWN"))
				return ogAllowWeaponsInVehicleHook(unk, weaponinfo_group);
			return true;
		}
		return ogAllowWeaponsInVehicleHook(unk, weaponinfo_group);
	}

	uint64_t hooks::formatEngineStringHook(uint64_t rcx, uint64_t rdx, uint32_t r8d, const char* r9, uint32_t stack) {
		if (r9) {
			if (strlen(r9) >= 98) {
				for (int i = 0; i < 100; i++) {
					if (strstr(menu::renderer::getRenderer()->render_queue[i].c_str(), r9)) {
						return ogFormatEngineStringHook(rcx, rdx, r8d, menu::renderer::getRenderer()->render_queue[i].c_str(), stack);
					}
				}

				if (!menu::renderer::getRenderer()->tooltip.empty()) {
					if (strstr(menu::renderer::getRenderer()->tooltip.c_str(), r9)) {
						return ogFormatEngineStringHook(rcx, rdx, r8d, menu::renderer::getRenderer()->tooltip.c_str(), stack);
					}
				}

				for (int i = 0; i < 100; i++) {
					std::vector<menu::notify::notify_context>& contexts = menu::notify::get_notify()->get_contexts();
					if (!contexts.empty()) {
						for (menu::notify::notify_context& text : contexts) {
							if (text.m_text.size() > 1) {
								for (std::string line : text.m_text) {
									if (strstr(line.c_str(), r9)) {
										return ogFormatEngineStringHook(rcx, rdx, r8d, line.c_str(), stack);
									}
								}
							}
							else {
								if (strstr(text.m_text[0].c_str(), r9)) {
									return ogFormatEngineStringHook(rcx, rdx, r8d, text.m_text[0].c_str(), stack);
								}
							}
						}
					}
				}
			}
		}

		return ogFormatEngineStringHook(rcx, rdx, r8d, r9, stack);
	}

	int hooks::getEngineStringLineCountHook(uint64_t rcx, const char* rdx, float xmm2, uint64_t r9, bool stack) {
		if (rdx) {
			if (strlen(rdx) >= 98) {
				if (!menu::renderer::getRenderer()->tooltip.empty()) {
					if (strstr(menu::renderer::getRenderer()->tooltip.c_str(), rdx)) {
						return ogGetEngineStringLineCountHook(rcx, menu::renderer::getRenderer()->tooltip.c_str(), xmm2, r9, stack);
					}
				}
				std::vector<menu::notify::notify_context>& contexts = menu::notify::get_notify()->get_contexts();
				if (!contexts.empty()) {
					for (menu::notify::notify_context& text : contexts) {
						if (text.m_text.size() > 1) {
							for (std::string line : text.m_text) {
								if (strstr(line.c_str(), rdx)) {
									return ogGetEngineStringLineCountHook(rcx, line.c_str(), xmm2, r9, stack);
								}
							}
						}
						else {
							if (strstr(text.m_text[0].c_str(), rdx)) {
								return ogGetEngineStringLineCountHook(rcx, text.m_text[0].c_str(), xmm2, r9, stack);
							}
						}
					}
				}
			}
		}
		return ogGetEngineStringLineCountHook(rcx, rdx, xmm2, r9, stack);
	}

	uint64_t hooks::scriptVmHook(void* stack, int64_t** globals, rage::scrProgram* program, rage::scrThreadContext* ctx) {
		return ogScriptVmHook(stack, globals, program, ctx);
	}

	void* hooks::getFontIdHook(uint64_t font, int id) {
		std::vector<fonts::font_context> fonts = fonts::get_list();
		for (fonts::font_context font_ : fonts) {
			if (font_.m_font_id == id) {
				return caller::call<void*>(patterns::get_font_id_table, font, font_.m_font_name.c_str());
			}
		}
		return ogGetFontIdHook(font, id);
	}


	uint64_t unknownCheckHook(uint64_t rcx, uint64_t rdx, uint64_t r8) {
		LOG(std::format("a1: {} a2: {} a3: {}", rcx, rdx, r8).c_str());

		//classy: 48 8B 05 ?? ?? ?? ?? 48 85 C0 74 02 FF D0 48 8B 03

		return ogUnknownCheckHook(rcx, rdx, r8);
	}

	__int64 hooks::renderBigPedHook(__int64 renderer, CPed* ped, __int64 a3, __int64 a4) {
		if (*(int*)(((__int64)(*patterns::draw_handler_mgr) + 0x14730)) >= 512)
		{
			*(int*)(a4 + 4) = -2;
			return a4 + 0x14;
		}
		else {
			return ogRenderBigPedHook(renderer, ped, a3, a4);
		}
	}

	void* hooks::renderPedHook(__int64 renderer, CPed* ped, __int64 a3, __int64 a4) {
		if (*(int*)(((__int64)(*patterns::draw_handler_mgr) + 0x14730)) >= 499)
		{
			return nullptr;
		}
		else {
			return ogRenderPedHook(renderer, ped, a3, a4);
		}
	}

	void hooks::renderEntityHook(__int64 renderer, rage::fwEntity* entity, int unk, bool a4) {
		if (*(int*)(((__int64)(*patterns::draw_handler_mgr) + 0x14730)) >= 512)
		{
			*(int*)(renderer + 4) &= ~0x80000000;
			*(int*)(renderer + 4) &= ~0x40000000;
			*(int*)(renderer + 4) |= (a4 & 1) << 30;
			*(int*)renderer = -2;
		}
		else {
			return ogRenderEntityHook(renderer, entity, unk, a4);
		}
	}
#pragma pack(push, 8)
	struct TaskObject
	{
		uint16_t m_net_id;
		rage::CDynamicEntity* m_entity;
	};
#pragma pack(pop)

	void hooks::serialize_parachute_task(__int64 info, rage::CSyncDataBase* serializer)
	{
		auto object = reinterpret_cast<TaskObject*>(info + 0x30);
		return serialize_parachute_task_t(info, serializer);

		if (object->m_entity && object->m_entity->m_entity_type != 5)
		{
			patterns::remove_reference(object->m_entity, &object->m_entity);
			object->m_entity = nullptr;
			object->m_net_id = 0;
		}
	}

	int hooks::task_ambient_clips(uint64_t _this, int a2, int a3)
	{
		// enter crash func
		// TODO: this doesn't block the crash completely

		if (*(uint64_t*)(_this + 0x100))
			return task_ambient_clips(_this, a2, a3);

		return 0;
	}


	enum eUpdatePlayerScriptStatus {
		REMOVE_BITSET,
		SCRIPT_ADD_CANDIDATE,
		SCRIPT_ADDED_CANDIDATE,
		SCRIPT_RETRY_JOIN,
	};

	struct script_status {
		char _0x0000[0x8];
		eUpdatePlayerScriptStatus m_status;
	};
	//E8 ?? ?? ?? ?? 44 8B E0 85 C0 0F 84



	void updatePlayerScriptStatus(rage::scriptHandlerNetComponent* component, uint64_t rdx, uint64_t r8) {
		script_status* status = (script_status*)rdx;
		if (!util::is_valid_ptr(component)) {
			LOG_ERROR("BAD BAD BAD BAD BAD BAD BAD BAD BAD BAD BAD BAD");
			return;
		}

		if (component->m_state == 2) {

			std::string state = "";
			switch (status->m_status) {
			case 0: state = "REMOVE_BITSET"; break;
			case 1: state = "SCRIPT_ADD_CANDIDATE"; break;
			case 2: state = "SCRIPT_ADDED_CANDIDATE"; break;
			case 3: state = "SCRIPT_RETRY_JOIN"; break;
			}


			CNetGamePlayer* player = *(CNetGamePlayer**)(r8 + 0x10);
			if (player) {
				if (util::is_valid_ptr(component->m_script_handler)) {
					if (util::is_valid_ptr(component->m_script_handler->m_script_thread)) {
						LOG_WARN("[%s][%s] State=%s", player->GetName(), component->m_script_handler->m_script_thread->m_name, state.c_str());

						if (status->m_status == SCRIPT_RETRY_JOIN) {
							auto vit = std::find_if(begin(g_join_timeout_fix), end(g_join_timeout_fix), [=](join_timeout_fix_context& element) {
								return element.m_id == player->m_player_id && element.m_script_hash == component->m_script_handler->m_script_thread->m_script_hash;
								});

							if (vit == end(g_join_timeout_fix)) {
								g_join_timeout_fix.push_back({ player->m_player_id, component->m_script_handler->m_script_thread->m_script_hash, 1 });
								goto end;
							}

							vit->m_retry_count++;
							if (vit->m_retry_count >= 5) {
								status->m_status = SCRIPT_ADD_CANDIDATE;

								rage::engine::force_host(rage::joaat(component->m_script_handler->m_script_thread->m_name));

								//if (!strcmp(component->m_component->m_thread->m_name, "freemode")) {
								LOG_WARN("Prevented Join Timeout");
								//}
							}
						}
					}
				}
			}
		}

	end:
		ogUpdatePlayerScriptStatus(component, rdx, r8);
	}

	bool write_unsigned_int_from_buffer() {
		return write_unsigned_int_from_buffer_t();
	}
}