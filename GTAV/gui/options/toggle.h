#pragma once
#include "pch.h"
#include "option.h"
#include "gui/renderer.h"
#include "gui/util/translate.h"

namespace base::gui {
	class toggleOption : public base_option<toggleOption> {
	private:
		bool* m_Bool = nullptr;
		bool m_DisplayInverted = false;
		std::function<void()> m_action = [] {};
		std::string m_name = "";
	public:
		explicit toggleOption(const char* const text) {
			m_name = text;
			base_option::set_left_text(m_name.c_str());
		}

		toggleOption& addTooltip(const char* const text) {
			base_option::set_tooltip(text);
			return *this;
		}

		toggleOption& addClick(std::function<void()> action = [] {}) {
			m_action = action;
			base_option::set_action(std::move(m_action));
			return *this;
		}

		toggleOption& addToggle(bool* const b00l) {
			m_Bool = b00l;
			return *this;
		}

		toggleOption& addHotkey() {
			addTooltip("Hotkeys Supported. Press F8 to bind");
			return *this;
		}

		toggleOption& addTranslate() {
			//set_left_text(translation);
			return *this;
		}


		void handle_action(eOptionAction action) override {
			if (action == eOptionAction::click) {
				*m_Bool = !*m_Bool;
			}
			base_option::handle_action(action);
		}

		bool* get_bool_pointer() override {
			return m_Bool;
		}


		bool get_flag(eOptionFlag flag) override {
			if (flag == eOptionFlag::toggle_option) {
				menu::renderer::getRenderer()->m_toggled_on = *m_Bool;
				return true;
			}
			return base_option::get_flag(flag);
		}
	};

	template <typename Type, typename = std::enable_if_t<std::is_arithmetic_v<Type>>>
	class toggleNumberOption : public base_option<toggleNumberOption<Type>> {
	private:
		Type* m_number = nullptr;
		bool* m_bool = nullptr;
		Type m_min = 0;
		Type m_max = 1;
		Type m_step = 1;
		std::size_t m_precision = 3;
		std::function<void()> m_function;
		using base = base_option<toggleNumberOption<Type>>;
		using display_type = std::conditional_t<sizeof(Type) == 1, std::uint32_t, Type>;
	public:
		explicit toggleNumberOption(const char* text) {
			base::set_left_text(text);
		}

		toggleNumberOption& addTooltip(const char* const text)
		{
			base::set_tooltip(text);
			return *this;
		}

		toggleNumberOption& addClick(std::function<void()> action = [] {}) {
			base::set_action(std::move(action));
			return *this;
		}

		toggleNumberOption& addToggle(bool* const b00l) {
			m_bool = b00l;
			return *this;
		}

		toggleNumberOption& addNumber(Type* number) {
			m_number = number;
			return *this;
		}

		toggleNumberOption& addMin(Type min) {
			m_min = min;
			return *this;
		}

		toggleNumberOption& addMax(Type max) {
			m_max = max;
			return *this;
		}

		toggleNumberOption& addStep(Type step) {
			m_step = step;
			return *this;
		}

		toggleNumberOption& setPrecision(Type precision) {
			m_precision = precision;
			return *this;
		}

		const char* get_right_text() {
			MemoryStringStream stream(base::m_right_text);
			stream
				<< std::setprecision(m_precision)
				<< std::fixed
				<< static_cast<display_type>(*m_number);
			return base::get_right_text();
		}

		void handle_action(eOptionAction action) override {
			if (action == eOptionAction::left_click) {
				if (*m_number - m_step < m_min)
					*m_number = m_max;
				else
					*m_number -= m_step;
				if (base::m_action)
					std::invoke(base::m_action);
			}
			else if (action == eOptionAction::right_click) {
				if (*m_number + m_step > m_max)
					*m_number = m_min;
				else
					*m_number += m_step;
				if (base::m_action)
					std::invoke(base::m_action);
			}
			else if (action == eOptionAction::click) {
				*m_bool = !*m_bool;
			}
			base::handle_action(action);
		}

		bool get_flag(eOptionFlag flag) override {
			if (flag == eOptionFlag::toggle_number_option) {
				menu::renderer::getRenderer()->m_toggled_on = *m_bool;
				return true;
			}
			return base::get_flag(flag);
		}
	};

	template <typename DataType, typename PositionType>
	class toggleScrollOption : public base_option<toggleScrollOption<DataType, PositionType>>
	{
	private:
		const DataType* m_data{};
		PositionType m_data_size{};
		PositionType* m_position{};
		std::function<void()> m_function;
		bool* m_Bool = nullptr;
		using base = base_option<toggleScrollOption<DataType, PositionType>>;
	public:
		explicit toggleScrollOption(const char* text) {
			base::set_left_text(text);
		}
		template <PositionType N>
		toggleScrollOption& addScroll(DataType(*array)[N]) {
			m_data = *array;
			m_data_size = N;
			return *this;
		}

		toggleScrollOption& setPosition(PositionType* position) {
			m_position = position;
			return *this;
		}

		toggleScrollOption& addToggle(bool* const b00l) {
			m_Bool = b00l;
			return *this;
		}

		toggleScrollOption& addClick(std::function<void()>&& function) {
			m_function = std::move(function);
			return *this;
		}

		const char* get_right_text() override {
			MemoryStringStream stream(base::m_right_text);
			if (m_data) {
				stream << m_data[*m_position];
				stream << " ~c~[" << *m_position + 1 << "/" << m_data_size << "]";
			}
			else {
				stream << "Unknown ~c~[0 / 0]";
			}
			return base::get_right_text();
		}

		void handle_action(eOptionAction action) override {
			if (action == eOptionAction::left_click) {

				if (m_data) {
					if (*m_position > 0)
						--(*m_position);
					else
						*m_position = static_cast<PositionType>(m_data_size - 1);
					if (base::m_action)
						std::invoke(base::m_action);
				}
			}
			else if (action == eOptionAction::right_click) {
				if (m_data) {
					if (*m_position < m_data_size - 1)
						++(*m_position);
					else
						*m_position = 0;
					if (base::m_action)
						std::invoke(base::m_action);
				}
			}
			else if (action == eOptionAction::click) {
				*m_Bool = !*m_Bool;
			}
			if (m_data) {
				base::handle_action(action);
			}
		}
		bool get_flag(eOptionFlag flag) override {
			if (flag == eOptionFlag::toggle_scroll_option) {
				menu::renderer::getRenderer()->m_toggled_on = *m_Bool;
				return true;
			}
			return base::get_flag(flag);
		}
	};
}