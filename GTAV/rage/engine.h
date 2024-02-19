#pragma once
#include "pch.h"
#include "hooks/patterns.h"
#include "util/caller.h"
#include "rage/invoker/natives.h"
#include "util/fiber.h"
#include "util/fiber_pool.h"
#include "menu/util/globals.h"
#include "menu/util/scr_global.h"

#include "rage/classes/script_handler.h"
#include "rage/classes/CNetworkPlayerMgr.h"
#include "rage/classes/CNetGamePlayer.h"
#include "rage/classes/CPlayerInfo.h"
#include "rage/classes/netShopping.h"
#include "util/log.h"
#include "util/math.h"

#include <vector>
#include <array>

#include "rage/classes/enums.h"
namespace rage::engine {
	inline rage::types::store_module* get_store_module_extension(const char* extension) {
		return caller::call<rage::types::store_module*>(patterns::get_store_module_extension, &patterns::store_manager->m_module, extension);
	}

	inline uint64_t construct_gfx_font(uint64_t allocation) {
		return caller::call<uint64_t>(patterns::construct_gfx_font, allocation);
	}

	inline void destruct(uint64_t allocation) {
		caller::call<void>(patterns::destruct, allocation);
	}

	inline int create_id_for_font(const char* asset_name) {
		static uint8_t junk[2][0x100];
		memset(junk, 0, sizeof(junk));

		return caller::call<int>(patterns::create_id_for_font, asset_name, junk[0], junk[1], 0, -1, -1, 1, 2, 0, 0);
	}

	inline void add_font_lib(uint64_t allocation, int index) {
		rage::types::store_module* store = get_store_module_extension("gfx");
		caller::call<void>(patterns::add_font_lib, store, allocation, index - store->m_base_index);
	}


	inline void request_streaming_file(int index) {
		caller::call<void>(patterns::request_streaming_file, patterns::store_manager, index, 7);
	}

	inline int register_streaming_file(const char* file_path, const char* asset_name) {
		int index = -1;
		caller::call<void>(patterns::register_streaming_file, &index, file_path, true, asset_name, false);

		return index;
	}

	inline const char* get_vehicle_class_name(int id) {
		std::stringstream ss; ss << "VEH_CLASS_" << id;
		return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(ss.str().c_str()) == "NULL" ? "Unknown Class" : HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(ss.str().c_str());
	}

	inline uint64_t get_entity_address(Entity entity) {
		if (entity <= 0) return 0;
		return caller::call<uint64_t>(patterns::get_entity_address, entity);
	}

	inline void set_vehicle_gravity(uint64_t address, float gravity) {
		caller::call<void>(patterns::set_vehicle_gravity, address, gravity);
	}

	inline void handle_rotation_values_from_order(math::matrix<float>* matrix, math::vector3_<float>* rotation, int order) {
		caller::call<void>(patterns::handle_rotation, matrix, rotation, order);
	}

	inline float deg_to_rad(float degs) {
		return degs * 3.141592653589793f / 180.f;
	}


	inline void request_model(std::uint32_t hash) {
		STREAMING::REQUEST_MODEL(hash);
		while (!STREAMING::HAS_MODEL_LOADED(hash)) {
			util::fiber::go_to_main();
		}
	}

	inline std::vector<uint32_t> get_hash_list_from_hash_table(uint32_t count, uint64_t table) {
		std::vector<uint32_t> hashes;

		if (count && table) {
			uint64_t* ptr = (uint64_t*)table;

			for (uint32_t i = 0; i < count; i++) {
				if (ptr[i]) {
					uint32_t hash = *(uint32_t*)(ptr[i] + 0x10);

					if (hash) {
						hashes.push_back(hash);
					}
				}
			}
		}

		return hashes;
	}

	inline void request_bullshark_testosterone() {
		*menu::script_global(2672505).at(3689).as<int*>() = 1;
	}

	inline void request_ballistic_armor() {
		*menu::script_global(menu::scr_globals::mechanic_global).at(896).as<int*>() = 1;
	}

	inline void request_ammo_drop() {
		*menu::script_global(menu::scr_globals::mechanic_global).at(891).as<int*>() = 1;
	}

	inline void request_boat_pickup() {
		*menu::script_global(menu::scr_globals::mechanic_global).at(892).as<int*>() = 1;
	}

	inline void request_helicopter_pickup() {
		*menu::script_global(menu::scr_globals::mechanic_global).at(893).as<int*>() = 1;
	}

	inline void request_backup_helicopter() {
		*menu::script_global(menu::scr_globals::mechanic_global).at(4491).as<int*>() = 1;
	}

	inline void request_airstrike() {
		*menu::script_global(menu::scr_globals::mechanic_global).at(4492).as<int*>() = 1;
	}

	inline rage::scrThread* m_mission_creator_thread = nullptr;

	inline void clear_bit(int* address, int pos) {
		*address &= ~(1 << pos);
	}

	inline void clear_bits(int* address, int bits) {
		*address &= ~(bits);
	}

	inline bool has_bit_set(int* address, int pos) {
		return *address & 1 << pos;
	}

	template<typename T>
	inline bool has_bits_set(T* address, T bits) {
		return (*address & bits) == bits;
	}

	inline bool has_bits_set(int* address, int bits) {
		return (*address & bits) == bits;
	}

	inline void set_bit(int* address, int pos) {
		*address |= 1 << pos;
	}

	inline void set_bits(int* address, int bits) {
		*address |= bits;
	}

	template<typename T>
	inline constexpr void SetBit(T* value, T bit) {
		*value |= (1 << bit);
	}


	template<typename T, typename ...T2>
	inline constexpr void set_bits(T* value, T2... bit) {
		(SetBit<T>(value, std::forward<T>(bit)), ...);
	}


	template<typename F, typename... Args>
	void execute_as_script(rage::scrThread* thread, F&& callback, Args&&... args) {
		auto tls_ctx = rage::tlsContext::get();
		auto og_thread = tls_ctx->m_script_thread;

		tls_ctx->m_script_thread = thread;
		tls_ctx->m_is_script_thread_active = true;

		std::invoke(std::forward<F>(callback), std::forward<Args>(args)...);

		tls_ctx->m_script_thread = og_thread;
		tls_ctx->m_is_script_thread_active = og_thread != nullptr;
	}

	template<typename F, typename... Args>
	void execute_as_script(rage::joaat_t script_hash, F&& callback, Args&&... args) {
		for (auto thread : *patterns::script_threads) {
			if (!thread || !thread->m_context.m_thread_id || thread->m_context.m_script_hash != script_hash)
				continue;

			execute_as_script(thread, callback, args...);
			return;
		}
	}

	inline GtaThread* find_script_thread(rage::joaat_t hash) {
		for (auto thread : *patterns::script_threads) {
			if (thread && thread->m_context.m_thread_id && thread->m_handler && thread->m_script_hash == hash) {
				return thread;
			}
		}

		return nullptr;
	}

	inline GtaThread* find_script_thread_by_id(std::uint32_t id) {
		for (auto thread : *patterns::script_threads) {
			if (thread && thread->m_handler && thread->m_context.m_thread_id == id) {
				return thread;
			}
		}

		return nullptr;
	}

	inline rage::scrProgram* find_script_program(rage::joaat_t hash) {
		for (auto& script : *patterns::script_program) {
			if (script.m_program && script.m_program->m_name_hash == hash)
				return script.m_program;
		}

		return nullptr;
	}

	inline bool force_host(rage::joaat_t hash) {
		if (auto launcher = find_script_thread(hash); launcher && launcher->m_net_component) {
			for (int i = 0; !((CGameScriptHandlerNetComponent*)launcher->m_net_component)->is_local_player_host(); i++) {
				if (i > 200)
					return false;

				((CGameScriptHandlerNetComponent*)launcher->m_net_component)->send_host_migration_event((*patterns::network_player_mgr)->m_local_net_player);
				util::fiber::go_to_main();

				if (!launcher->m_stack || !launcher->m_net_component)
					return false;
			}
		}

		return true;
	}

	inline void set_fm_event_index(int index)
	{
		int idx = index / 32;
		int bit = index % 32;
		set_bit(menu::scr_globals::gsbd_fm_events.at(11).at(361).at(idx, 1).as<int*>(), bit);
		set_bit(menu::scr_globals::gsbd_fm_events.at(11).at(353).at(idx, 1).as<int*>(), bit);
		set_bit((int*)&menu::scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[PLAYER::PLAYER_ID()].BossGoon.ActiveFreemodeEvents[idx], bit);
	}

	inline void clear_fm_event_index(int index)
	{
		int idx = index / 32;
		int bit = index % 32;
		clear_bit(menu::scr_globals::gsbd_fm_events.at(11).at(361).at(idx, 1).as<int*>(), bit);
		clear_bit(menu::scr_globals::gsbd_fm_events.at(11).at(353).at(idx, 1).as<int*>(), bit);
		clear_bit((int*)&menu::scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[PLAYER::PLAYER_ID()].BossGoon.ActiveFreemodeEvents[idx], bit);
	}

	inline void session_script(int script_id) {
		util::fiber::pool::add([=] {
			static auto check_players_in_state = [](GtaThread* launcher, int state) -> bool {
				bool set = false;

				if (!launcher->m_net_component)
					return false;

				for (uint32_t i = 0; i < 32; i++) {
					if (patterns::get_net_player(i)) {
						auto plyr = patterns::get_net_player(i);
						if (((CGameScriptHandlerNetComponent*)launcher->m_net_component)->is_player_a_participant(plyr)) {
							if (*menu::script_local(launcher->m_stack, 232).at(plyr->m_player_id, 3).at(2).as<int*>() == state) {
								set = true;
								break;
							}
						}
					}
					
				}

				return set;
			};

			if (auto launcher = find_script_thread(RAGE_JOAAT("am_launcher"))) {
				if (!force_host(RAGE_JOAAT("am_launcher"))) {
					return;
				}

				launcher->m_context.m_state = eThreadState::unk_3;

				if (check_players_in_state(launcher, 5)) {
					for (int i = 0; check_players_in_state(launcher, 5); i++) {
						if (i > 200)
							break;

						*menu::scr_globals::launcher_global.at(3).at(1).as<int*>() = 0;
						*menu::scr_globals::launcher_global.at(2).as<int*>() = 6;
						util::fiber::go_to_main();
					}
				}


				if (check_players_in_state(launcher, 6))
				{
					for (int i = 0; check_players_in_state(launcher, 6); i++)
					{
						if (i > 200)
							break;

						*menu::scr_globals::launcher_global.at(3).at(1).as<int*>() = 0;
						*menu::scr_globals::launcher_global.at(2).as<int*>() = 7;
						util::fiber::go_to_main();
					}
				}

				if (check_players_in_state(launcher, 7))
				{
					for (int i = 0; check_players_in_state(launcher, 7); i++)
					{
						if (i > 200)
							break;

						*menu::scr_globals::launcher_global.at(2).as<int*>() = 0;
						util::fiber::go_to_main();
					}
				}

				set_bit(menu::scr_globals::launcher_global.at(1).as<int*>(), 1);
				*menu::scr_globals::launcher_global.at(2).as<int*>() = 6;
				*menu::script_local(launcher->m_stack, 232).at(PLAYER::PLAYER_ID(), 3).at(2).as<int*>() = 6;
				*menu::scr_globals::launcher_global.at(3).at(1).as<int*>() = script_id;

				launcher->m_context.m_state = eThreadState::running;
			}
			else {
			}
		});
	}

	inline const std::optional<uint32_t> get_code_location_by_pattern(rage::scrProgram* program, const memory::pattern& pattern) {
		std::uint32_t code_size = program->m_code_size;
		for (std::uint32_t i = 0; i < (code_size - pattern.m_bytes.size()); i++)
		{
			for (std::uint32_t j = 0; j < pattern.m_bytes.size(); j++)
				if (pattern.m_bytes[j].has_value())
					if (pattern.m_bytes[j].value() != *program->get_code_address(i + j))
						goto incorrect;

			return i;
		incorrect:
			continue;
		}

		return std::nullopt;
	}

	inline void patch_script(rage::scrProgram* program, std::optional<std::uint32_t> location, std::vector<std::uint8_t> patch, int offset) {
		std::uint8_t* bytearray = patch.data();
		if (location)
			memcpy(program->get_code_address(location.value() + offset), bytearray, patch.size());
	}


	inline void start_creator_script(rage::joaat_t hash) {
		util::fiber::pool::add([=] {
			static auto read_uint24_t = [](uint8_t* arr) {
				return arr[0] + (arr[1] << 8) + (arr[2] << 16);
			};

			if (m_mission_creator_thread || SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(RAGE_JOAAT("creator")) != 0 || SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(RAGE_JOAAT("maintransition")) != 0 || STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS() || CUTSCENE::IS_CUTSCENE_ACTIVE()) {
				return;
			}

			if (MISC::GET_NUMBER_OF_FREE_STACKS_OF_THIS_SIZE(54000) == 0) {
			}


			while (!SCRIPT::HAS_SCRIPT_WITH_NAME_HASH_LOADED(hash)) {
				SCRIPT::REQUEST_SCRIPT_WITH_NAME_HASH(hash);
				util::fiber::go_to_main();
			}

			*menu::scr_globals::terminate_creator.as<bool*>() = false;
			*menu::scr_globals::mission_creator_exited.as<bool*>() = false;
			*menu::scr_globals::mission_creator_radar_follows_camera.as<bool*>() = true;

			if (SYSTEM::START_NEW_SCRIPT_WITH_NAME_HASH(hash, 54000)) {
				m_mission_creator_thread = find_script_thread(hash);
			}

			if (auto program = find_script_program(hash)) {
				patch_script(program,
					get_code_location_by_pattern(program, ("2D 02 04 00 ? 38 01 38 00 42 13")),
					{
						0x72,// PUSH_CONST_1
						0x00 // NOP
					},
					5);// place anywhere

				patch_script(program, get_code_location_by_pattern(program, ("71 08 2A 56 ? ? 2C ? ? ? 1F 56 ? ? 72")), { 0x00, 0x00, 0x00, 0x00, 0x00 }, 0xE);// don't bail on network mode

				if (auto loc = get_code_location_by_pattern(program, ("39 04 5D ? ? ? 71"))) {
					patch_script(program,
						read_uint24_t(program->get_code_address(loc.value() + 3)),
						{
							0x73,// PUSH_CONST_2 0 = mp, 2 = creator, 999 = singleplayer
							0x2E,
							0x00,
							0x01// LEAVE 0 1
						},
						5);// allow fast zoom in mp
				}
			}

			SCRIPT::SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED(hash);
		});
	}


	inline void send_basket_transaction(rage::joaat_t category, rage::joaat_t item_hash, rage::joaat_t action_type_hash, int value, int flag) {
		execute_as_script(rage::joaat("shop_controller"), [&] {
			if (NETSHOPPING::NET_GAMESERVER_BASKET_IS_ACTIVE()) {
				NETSHOPPING::NET_GAMESERVER_BASKET_END();
			}
			int transaction_id{};

			if (caller::call<bool>(patterns::begin_service, patterns::net_shop_mgr, &transaction_id, 0xBC537E0D, category, item_hash, action_type_hash, value, flag)) {
				NETSHOPPING::NET_GAMESERVER_CHECKOUT_START(transaction_id);
			}
		});
	}

	inline void add_basket_transaction(rage::joaat_t category, rage::joaat_t action_type_hash, int flag, std::vector<std::array<int, 5>> items) {
		execute_as_script(rage::joaat("shop_controller"), [&] {
			if (NETSHOPPING::NET_GAMESERVER_BASKET_IS_ACTIVE()) {
				NETSHOPPING::NET_GAMESERVER_BASKET_END();
			}

			int transaction_id = -1;
			if (caller::call<bool>(patterns::construct_basket, patterns::net_shop_mgr, &transaction_id, category, action_type_hash, flag)) {
				for (auto& item : items) {
					caller::call<void>(patterns::add_item_to_basket, patterns::net_shop_mgr, (int*)&item);
				}
				NETSHOPPING::NET_GAMESERVER_CHECKOUT_START(transaction_id);
			}
		});
	}

}