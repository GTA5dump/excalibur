#pragma once
#include "pch.h"

namespace base {
	class translation {
	public:
		static void enable();
		static void disbale();
		static void load();
	public:
		static std::string get(std::string string);
		static void push(std::string string);
	public:
		static translation* get() {
			static translation i{};
			return &i;
		}
	public:
		std::unordered_map<u32, std::string> m_translation_table;
		std::vector<std::string> m_files{};
		bool m_translate;
	};

	extern std::string trans(std::string string);
}