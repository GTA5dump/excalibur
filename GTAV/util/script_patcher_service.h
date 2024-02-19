#pragma once
#include "memory/pattern.h"
#include "script_data.h"
#include "script_patch.h"

#include "rage/classes/scrProgram.h"
#include "rage/classes/joaat.h"

namespace menu
{
	class script_patcher_service
	{
		std::vector<script_patch> m_script_patches;
		std::unordered_map<rage::joaat_t, std::unique_ptr<script_data>> m_script_data;
		script_data* get_data_for_script(rage::joaat_t script);
		bool does_script_have_patches(rage::joaat_t script);
		void create_data_for_script(rage::scrProgram* program);
		void update_all_patches_for_script(rage::joaat_t script);

	public:
		script_patcher_service();
		~script_patcher_service();

		void add_patch(script_patch&& patch);
		void on_script_load(rage::scrProgram* program);
		std::uint8_t** get_script_bytecode(rage::joaat_t script);
		void update();
	};

	inline script_patcher_service* g_script_patcher_service;
}