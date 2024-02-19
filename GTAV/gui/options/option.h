#pragma once
#include "pch.h"
#include "abstract_option.h"
#include "gui/types.h"
#include "gui/util/translate.h"
namespace base::gui {
	template <typename T>
	class base_option : public abstract_option {
	public:
		const char* get_left_text() override {
			return &m_left_text[0];
		}
		const char* get_right_text() override {
			return &m_right_text[0];
		}
		const char* get_description() override {
			return &m_description[0];
		}

		color get_color() override {
			return m_color;
		}



		void handle_action(eOptionAction action) override {
			if (action == eOptionAction::click) {
				if (m_action) {
					std::invoke(m_action);
				}
			}
		}
		bool get_flag(eOptionFlag) override {
			return false;
		}
		std::function<void()> get_action() override {
			return m_action;
		}

		bool* get_bool_pointer() override {
			return nullptr;
		}

		void set_value(double text) override {}
		void set_value(std::string text) {}

		T& handle_hover() {
			return static_cast<T&>(*this);
		}

		T& set_left_text(const char* text) {
			std::strncpy(&m_left_text[0], text, sizeof(m_left_text) - 1);
			return static_cast<T&>(*this);
		}
		T& set_right_text(const char* text) {
			std::strncpy(&m_right_text[0], text, sizeof(m_right_text) - 1);
			return static_cast<T&>(*this);
		}

		T& set_tooltip(const char* text) {
			if (text)
				std::strncpy(&m_description[0], trans(text).c_str(), sizeof(m_description) - 1);
			return static_cast<T&>(*this);
		}
		T& set_action(std::function<void()> action) {
			m_action = std::move(action);
			return static_cast<T&>(*this);
		}

		T& set_color(color col) {
			m_color = col;
			return static_cast<T&>(*this);
		}



	protected:
		std::function<void()> m_action;
		char m_left_text[128] = {};
		char m_right_text[128] = {};
		char m_description[1024] = {};
		color m_color;
	};
}