#include "pch.h"
#include "script.h"
#include "rage/classes/scrNativeCallContext.h"
#include "rage/classes/scrNativeRegistration.h"
#include "rage/classes/scrNativeRegistrationTable.h"
#include "rage/classes/joaat.h"
#include "rage/invoker/crossmap.h"
#include "hooks/patterns.h"
#include "hooks/hooks.h"

namespace script {
	static bool map_native(rage::scrNativeHash* hash) {
		for (auto const& mapping : g_crossmap) {
			if (mapping.hash == *hash) {
				*hash = mapping.translated_hash;
				return true;
			}
		}

		return false;
	}

	native_hook::native_hook(rage::scrProgram* program, const std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler>& native_replacements) {
		hook_instance(program, native_replacements);
	}

	native_hook::~native_hook() {
		if (m_handler_hook) {
			m_handler_hook->disable();
			m_handler_hook.reset();
		}

		if (m_vmt_hook)	{
			m_vmt_hook->disable();
			m_vmt_hook.reset();
		}
	}

	void native_hook::hook_instance(rage::scrProgram* program, const std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler>& native_replacements) {
		m_program = program;
		m_vmt_hook = std::make_unique<hooking::vmt_hook>(m_program, 9);
		m_vmt_hook->hook(6, &scrprogram_dtor);
		m_vmt_hook->enable();

		m_handler_hook = std::make_unique<hooking::vmt_hook>(&m_program->m_native_entrypoints, m_program->m_native_count);
		m_handler_hook->enable();

		std::unordered_map<rage::scrNativeHandler, rage::scrNativeHandler> handler_replacements;

		for (auto& [replacement_hash, replacement_handler] : native_replacements) {
			auto native = replacement_hash;
			map_native(&native);

			auto og_handler = patterns::get_native_handler(patterns::native_registration_table, native);
			if (!og_handler)
				continue;

			handler_replacements[og_handler] = replacement_handler;
		}

		for (int i = 0; i < m_program->m_native_count; i++) {
			if (auto it = handler_replacements.find((rage::scrNativeHandler)program->m_native_entrypoints[i]);
				it != handler_replacements.end())
			{
				m_handler_hook->hook(i, it->second);
			}
		}
	}

	void native_hook::scrprogram_dtor(rage::scrProgram* this_, char free_memory) {
		if (auto it = g_native_hooks->m_native_hooks.find(this_); it != g_native_hooks->m_native_hooks.end()) {
			auto og_func = it->second->m_vmt_hook->get_original<decltype(&native_hook::scrprogram_dtor)>(6);
			it->second->m_vmt_hook->disable();
			it->second->m_vmt_hook.reset();
			it->second->m_handler_hook->disable();
			it->second->m_handler_hook.reset();
			g_native_hooks->m_native_hooks.erase(it);
			og_func(this_, free_memory);
		}
		else
		{
			LOG_ERROR("Cannot find hook for program");
		}
	}

	constexpr auto ALL_SCRIPT_HASH = "ALL_SCRIPTS"_joaat;

	native_hooks::native_hooks() {
		add_native_detour("main_persistent"_joaat, 0x767FBC2AC802EF3D, base::hooks::stat_get_int);
		add_native_detour(0xADF692B254977C0C, base::hooks::set_current_ped_weapon);
		add_native_detour(0xFE99B66D079CF6BC, base::hooks::disable_control_action);
		add_native_detour(0x6D0DE6A7B5DA71F8, base::hooks::set_player_name);
		add_native_detour(0x158C16F5E4CF41F8, base::hooks::return_true);

		add_native_detour(RAGE_JOAAT("shop_controller"), 0x34616828CD07F1A1, base::hooks::return_false);
		add_native_detour(RAGE_JOAAT("maintransition"), 0x6F3D4ED9BEE4E61D, base::hooks::network_session_host);
		add_native_detour("freemode"_joaat, 0x1090044AD1DA76FA, base::hooks::terminate_this_thread);


		for (auto& entry : *patterns::script_program)
			if (entry.m_program)
				hook_program(entry.m_program);

		g_native_hooks = this;
	}

	native_hooks::~native_hooks() {
		m_native_hooks.clear();
		g_native_hooks = nullptr;
	}

	void native_hooks::add_native_detour(rage::scrNativeHash hash, rage::scrNativeHandler detour) {
		add_native_detour(ALL_SCRIPT_HASH, hash, detour);
	}

	void native_hooks::add_native_detour(rage::joaat_t script_hash, rage::scrNativeHash hash, rage::scrNativeHandler detour) {
		if (const auto& it = m_native_registrations.find(script_hash); it != m_native_registrations.end()) {
			it->second.emplace_back(hash, detour);
			return;
		}

		m_native_registrations.emplace(script_hash, std::vector<native_detour>({ {hash, detour} }));
	}

	void native_hooks::hook_program(rage::scrProgram* program) {
		std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler> native_replacements;
		const auto script_hash = program->m_name_hash;

		// Functions that need to be detoured for all scripts
		if (const auto& pair = m_native_registrations.find(ALL_SCRIPT_HASH); pair != m_native_registrations.end())
			for (const auto& native_hook_reg : pair->second)
				native_replacements.insert(native_hook_reg);

		// Functions that only need to be detoured for a specific script
		if (const auto& pair = m_native_registrations.find(script_hash); pair != m_native_registrations.end())
			for (const auto& native_hook_reg : pair->second)
				native_replacements.insert(native_hook_reg);

		if (!native_replacements.empty()) {
			m_native_hooks.emplace(program, std::make_unique<native_hook>(program, native_replacements));
		}
	}
}