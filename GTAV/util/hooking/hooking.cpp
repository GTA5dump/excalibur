#include "pch.h"
#include "hooking.h"
#include "hooks/patterns.h"
#include "rage/invoker/invoker.h"
#include "util/caller.h"
#include "rage/invoker/crossmap.h"
#include "hooks/hooks.h"
#include "rage/classes/scrProgram.h"
#include "rage/classes/joaat.h"
namespace hooking {
	

	void restoreIRC()
	{
		// Patch bytes for the "IRC" pattern
		std::vector<BYTE> patchBytes = {
			0x80, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x85, 0xA7, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x05
		};

		// Restore the "IRC" patch
		memory::restorePatch(patterns::invalid_resource_check, patchBytes);
	}

	void restoreICP1()
	{
		// Patch bytes for the "ICP-1" pattern
		std::vector<BYTE> patchBytes = {
			0x48, 0x83, 0xEC, 0x48, 0x48, 0x83, 0x64, 0x24, 0x00, 0x00, 0x83, 0x4C, 0x24
		};

		// Restore the "ICP-1" patch
		memory::restorePatch(patterns::integ_check_1, patchBytes);
	}

	void Detour::remove_detour() {
		for (DetourContext& detour : m_detours) {
			MH_QueueDisableHook((void*)detour.m_address);
			LOG_CUSTOM_SUCCESS("Hook", "Unhooked %s", detour.m_name);
		}
		MH_ApplyQueued();
		MH_Uninitialize();

	}

	void vmtHook::remove_vmt() {
		for (virtual_context& vmt : m_vmts) {
			write(vmt.m_address, vmt.m_original);
			LOG_CUSTOM_SUCCESS("Hook", "Unhooked %s", vmt.m_name);
		}
	}

	vmt_hook::vmt_hook(void* obj, std::size_t num_funcs) :
		m_object(static_cast<void***>(obj)),
		m_num_funcs(num_funcs),
		m_original_table(*m_object),
		m_new_table(std::make_unique<void* []>(m_num_funcs))
	{
		std::copy_n(m_original_table, m_num_funcs, m_new_table.get());
	}

	vmt_hook::~vmt_hook() {
		disable();
	}

	void vmt_hook::hook(std::size_t index, void* func) {
		m_new_table[index] = func;
	}

	void vmt_hook::unhook(std::size_t index) {
		m_new_table[index] = m_original_table[index];
	}

	void vmt_hook::enable() {
		*m_object = m_new_table.get();
	}

	void vmt_hook::disable() {
		*m_object = m_original_table;
	}

	static bool map_native(rage::scrNativeHash* hash) {
		for (auto const& mapping : g_crossmap) {
			if (mapping.hash == *hash) {
				*hash = mapping.translated_hash;
				return true;
			}
		}

		return false;
	}
}

