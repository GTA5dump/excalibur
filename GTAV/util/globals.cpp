#include "pch.h"
#include "globals.h"
#include "hooks/patterns.h"
#include "rage/classes/scrThread.h"

namespace menu
{
	script_global::script_global(std::size_t index) :
		m_index(index)
	{
	}

	script_global script_global::at(std::ptrdiff_t index)
	{
		return script_global(m_index + index);
	}

	script_global script_global::at(std::ptrdiff_t index, std::size_t size)
	{
		return script_global(m_index + 1 + (index * size));
	}

	void* script_global::get()
	{
		return patterns::script_globals[m_index >> 0x12 & 0x3F] + (m_index & 0x3FFFF);
	}

	script_local::script_local(rage::scrThread* thread, std::size_t index) :
		m_index(index),
		m_stack(thread->m_stack)
	{
	}
	script_local::script_local(PVOID stack, std::size_t index) :
		m_index(index),
		m_stack(stack)
	{
	}

	script_local script_local::at(std::ptrdiff_t index) {
		return script_local(m_stack, m_index + index);
	}

	script_local script_local::at(std::ptrdiff_t index, std::size_t size) {
		return script_local(m_stack, m_index + 1 + (index * size));
	}

	void* script_local::get() {
		return reinterpret_cast<uintptr_t*>((uintptr_t)m_stack + (m_index * sizeof(uintptr_t)));
	}
}
