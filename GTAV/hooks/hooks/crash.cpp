#include "pch.h"
#include "hooks/hooks.h"
#include "rage/classes/enums.h"
#include "rage/classes/script_handler.h"
#include "rage/classes/dataNodes.h"
#include "rage/classes/CSyncDataBase.h"
namespace base::hooks {
	eThreadState hooks::tickScriptThreadHook(GtaThread* thread, uint32_t count) {
		//if (thread->m_is_paused)
		//	return thread->m_context.m_state;

		eThreadState state = thread->m_context.m_state;

		static uint8_t stack_backup[0xFFFF];
		static uint8_t thread_backup[sizeof(GtaThread)];
		static uint8_t handler_backup[sizeof(CGameScriptHandler)];

		if (state == eThreadState::running && !g_freemode_terminated && thread->m_script_hash == rage::joaat("freemode")) {
			memcpy(thread_backup, thread, sizeof(GtaThread));
			memcpy(stack_backup, thread->m_stack, thread->m_context.m_stack_size);

			if (thread->m_context.m_stack_size >= 0xFFFF) {
				//LOG("BAD STACK SIZE: %i", thread->m_context.m_stack_size);
			}

			if (thread->m_handler) {
				memcpy(handler_backup, thread->m_handler, sizeof(CGameScriptHandler));
			}
		}

		eThreadState tick_state = ogTickScriptThreadHook(thread, count);

		if (tick_state == eThreadState::killed && state == eThreadState::running && thread->m_script_hash == rage::joaat("freemode")) {
			if (!g_freemode_terminated) {
				tick_state = eThreadState::running;

				memcpy(thread, thread_backup, sizeof(GtaThread));
				memcpy(thread->m_stack, stack_backup, thread->m_context.m_stack_size);

				if (thread->m_handler) {
					memcpy(thread->m_handler, handler_backup, sizeof(CGameScriptHandler));
				}
			}
			else {
				g_freemode_terminated = false;
			}
		}

		return tick_state;
	}

	uint64_t hooks::invalidDecalCrashHook(uintptr_t rcx, int rdx) {
		if (rcx && rdx == 2)
			//*(*(*(a1 + 0x48) + 0x30) + 0x2C8)
			if (const auto ptr = *reinterpret_cast<uintptr_t*>((rcx + 0x48)); ptr)
				if (const auto ptr2 = *reinterpret_cast<uintptr_t*>((ptr + 0x30)); ptr2)
					if (*reinterpret_cast<uintptr_t*>(ptr2 + 0x2C8) == 0)
						return 0;

		return ogInvalidDecalCrashHook(rcx, rdx);
	}

	void hooks::invalidModsCrashHook(int64_t  rcx, int64_t  rdx, int r8, char r9) {
		if (!*(int64_t*)(rcx + 0xD8))
			return;
		
		ogInvalidModsCrashHook(rcx, rdx, r8, r9);
	}

	constexpr uint32_t valid_parachute_models[] = {
		RAGE_JOAAT("p_parachute_s"),
		RAGE_JOAAT("vw_p_para_bag_vine_s"),
		RAGE_JOAAT("reh_p_para_bag_reh_s_01a"),
		RAGE_JOAAT("xm_prop_x17_scuba_tank"),
		RAGE_JOAAT("lts_p_para_bag_pilot2_s"),
		RAGE_JOAAT("lts_p_para_bag_lts_s"),
		RAGE_JOAAT("p_para_bag_tr_s_01a"),
		RAGE_JOAAT("p_para_bag_xmas_s"),
	};

	bool is_valid_parachute_model(rage::joaat_t hash)
	{
		for (auto& model : valid_parachute_models)
			if (model == hash)
				return true;

		return false;
	}


	void hooks::parachuteCrashHook(ClonedTakeOffPedVariationInfo* info, rage::CSyncDataBase* serializer) {
		ogParachuteCrashHook(info, serializer);

		if (!is_valid_parachute_model(info->m_prop_hash)) {
			info->m_prop_hash = 0;
		}
	}


	uint64_t hooks::parachuteCrashHook2(uint64_t rcx, int rdx, int r8) {
		if (rdx == 1 && r8 == 1) {
			if (auto ptr = *(uint64_t*)(rcx + 16))
				if (auto ptr2 = *(uint64_t*)(ptr + 80))
					if (auto ptr3 = *(uint64_t*)(ptr2 + 64))
						return ogParachuteCrashHook2(rcx, rdx, r8);
			return 0;
		}
		return ogParachuteCrashHook2(rcx, rdx, r8);
	}

	bool hooks::fragmentCrashHook(float* rcx, float* rdx) {

		if (!rcx || !rdx)
			return false;

		return ogFragmentCrashHook(rcx, rdx);
	}


}