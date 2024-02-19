#pragma once
#include "option.h"
#include "util/util.h"
#include "util/log.h"
#include "gui/renderer.h"
#include "gui/util/translate.h"

namespace base::gui {
	class buttonOption : public base_option<buttonOption> {
	private:
		std::function<void()> m_function;
		struct Keyboard {
			bool m_enabled = false;
			bool m_is_active = false;
			int m_max_chars = 0;
			std::function<void(buttonOption*, const char*)> m_callback = {};
			std::string m_title = "";
			std::string m_default_text = "";
		};

		Keyboard m_keyboard;
	public:

		explicit buttonOption(const char* text) {
			set_left_text(text);
		}

		buttonOption& addTooltip(const char* description) {
			base_option::set_tooltip(description);
			return *this;
		}

		buttonOption& addRightText(const char* const text) {
			base_option::set_right_text(text);
			return *this;
		}

		buttonOption& addClick(std::function<void()> function) {
			set_action(std::move(function));
			return *this;
		}

		buttonOption& addHotkey() {
			addTooltip("Hotkeys Supported. Press F8 to bind");
			return *this;
		}

		buttonOption& addTranslate() {

			//set_left_text(translation);
			return *this;
		}


		bool get_flag(eOptionFlag flag) override {
			if (flag == eOptionFlag::simple_option) {
				return true;
			}
			return base_option::get_flag(flag);
		}
	};

	class vehicleOption : public base_option<vehicleOption> {
	private:
		std::function<void()> m_function;
	public:
		explicit vehicleOption(const char* text) {
			set_left_text(text);
		}

		vehicleOption& addToolTip(const char* description) {
			base_option::set_tooltip(description);
			return *this;
		}

		vehicleOption& addRightText(const char* text) {
			base_option::set_right_text(text);
			return *this;
		}

		vehicleOption& addClick(std::function<void()>&& function) {
			set_action(std::move(function));
			return *this;
		}

		bool get_flag(eOptionFlag flag) override {
			if (flag == eOptionFlag::vehicle_option) {
				return true;
			}
			return base_option::get_flag(flag);
		}
	};

	class keyboardOption : public base_option<keyboardOption> {
	private:
		std::function<void()> m_function;
	public:
		explicit keyboardOption(const char* text) {
			set_left_text(text);
		}

		keyboardOption& addToolTip(const char* description) {
			base_option::set_tooltip(description);
			return *this;
		}

		keyboardOption& addRightText(const char* text) {
			base_option::set_right_text(text);
			return *this;
		}

		keyboardOption& addClick(std::function<void()>&& function) {
			set_action(std::move(function));
			return *this;
		}

		bool get_flag(eOptionFlag flag) override {
			if (flag == eOptionFlag::keyboard_option) {
				return true;
			}
			return base_option::get_flag(flag);
		}
	};
}