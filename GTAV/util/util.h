#pragma once
#include "pch.h"
#include "hooks/patterns.h"

namespace Util {
	inline std::string GetDocumentsPath() {
		wchar_t folder[1024];
		HRESULT result = SHGetFolderPathW(0, CSIDL_MYDOCUMENTS, 0, 0, folder);
		if (SUCCEEDED(result)) {
			char string[1024];
			wcstombs(string, folder, 1023);
			return string;
		}
		else return "";
	}

	inline bool is_key_pressed(std::uint16_t key) {
		if (GetForegroundWindow() == g_window) {
			if (GetAsyncKeyState(key) & 0x8000) {
				return true;
			}
		}
		return false;
	}

	inline std::string mock_string(std::string str) {
		auto is_char = [](char c) {
			return c >= 0x41 && c <= 0x7A;
		};

		auto is_capital = [](char c) {
			return c >= 0x41 && c <= 0x5A;
		};

		auto get_capital = [](char c) {
			return c - 0x20;
		};

		auto get_lower = [](char c) {
			return c + 0x20;
		};

		bool capital = true;
		for (char& c : str) {
			if (is_char(c)) {
				if (capital) {
					if (!is_capital(c)) {
						c = get_capital(c);
					}
				}
				else {
					if (is_capital(c)) {
						c = get_lower(c);
					}
				}

				capital ^= true;
			}
		}

		return str;
	}


	inline const char* create_random_string(size_t Length) {
		auto randchar = []() -> char {
			const char charset[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";
			const size_t max_index = (sizeof(charset) - 1);
			return charset[rand() % max_index];
		};

		std::string str(Length, 0);
		std::generate_n(str.begin(), Length, randchar);
		return str.c_str();
	}
}
