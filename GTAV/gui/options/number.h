#pragma once
#include "option.h"
#include "gui/renderer.h"
#include "gui/util/char_mem_stream.h"
#include "rage/invoker/natives.h"
#include "gui/util/translate.h"

namespace base::gui {
	template <typename Type, typename = std::enable_if_t<std::is_arithmetic_v<Type>>>
	class numberOption : public base_option<numberOption<Type>> {
	private:
		Type* m_number = nullptr;
		Type m_min = 0;
		Type m_max = 1;
		Type m_step = 1;
		std::size_t m_precision = 3;
		using base = base_option<numberOption<Type>>;
		using display_type = std::conditional_t<sizeof(Type) == 1, std::uint32_t, Type>;
		std::function<void()> m_function;
		std::function<void()> m_on_hover = []() {};
		std::string m_name = "";
	public:
		explicit numberOption(const char* text) {
			m_name = text;
			base::set_left_text(m_name.c_str());
		}

		numberOption& addTooltip(const char* const text)
		{
			base::set_tooltip(text);
			return *this;
		}

		numberOption& addClick(std::function<void()> action = [] {}) {
			base::set_action(std::move(action));
			return *this;
		}

		numberOption& addHover(std::function<void()> function) {
			m_on_hover = function;
			return *this;
		}

		numberOption& addNumber(Type* number) {
			m_number = number;
			return *this;
		}

		numberOption& addMin(Type min) {
			m_min = min;
			return *this;
		}

		numberOption& addMax(Type max) {
			m_max = max;
			return *this;
		}

		numberOption& addStep(Type step) {
			m_step = step;
			return *this;
		}

		numberOption& setPrecision(Type precision) {
			m_precision = precision;
			return *this;
		}

		numberOption& addTranslate() {
			const char* translation = TRANSLATE(base_option::get_left_text());
			//base::set_left_text(translation);
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
			m_on_hover();
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
				static bool active = false;
					MISC::DISPLAY_ONSCREEN_KEYBOARD(true, (char*)"Input", (char*)"", (char*)"", (char*)"", (char*)"", (char*)"", 20);
					while (MISC::UPDATE_ONSCREEN_KEYBOARD() == 0) {
						active = true;
						menu::renderer::getRenderer()->reset_keys();
						util::fiber::go_to_main();
					}
					active = false;
					if (!MISC::GET_ONSCREEN_KEYBOARD_RESULT())
						return;

					*m_number = std::atoi(MISC::GET_ONSCREEN_KEYBOARD_RESULT());
					if (base::m_action)
						std::invoke(base::m_action);
			}
			base::handle_action(action);
		}

		bool get_flag(eOptionFlag flag) override {
			if (flag == eOptionFlag::number_option) {
				return true;
			}
			return base::get_flag(flag);
		}
	};

}