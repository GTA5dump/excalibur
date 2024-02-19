#pragma once
#include "option.h"
#include "gui/renderer.h"
#include "gui/util/char_mem_stream.h"
#include "gui/util/flags.h"
#include "gui/util/translate.h"

namespace base::gui
{
	template <typename DataType, typename PositionType>
	class scrollOption : public base_option<scrollOption<DataType, PositionType>>
	{
	private:
		const DataType* m_data{};
		PositionType m_data_size{};
		PositionType* m_position{};
		std::function<void()> m_function;
		std::function<void()> m_on_hover = []() {};
		using base = base_option<scrollOption<DataType, PositionType>>;
	public:
		explicit scrollOption(const char* text) {
			base::set_left_text(text);
		}
		template <PositionType N>
		scrollOption& addScroll(DataType(*array)[N]) {
			m_data = *array;
			m_data_size = N;
			return *this;
		}

		scrollOption& setPosition(PositionType* position) {
			m_position = position;
			return *this;
		}

		scrollOption& addClick(std::function<void()> action = [] {}) {
			base::set_action(std::move(action));
			return *this;
		}

		scrollOption& addHover(std::function<void()> function) {
			m_on_hover = function;
			return *this;
		}

		scrollOption& addTranslate() {
			//base::set_left_text(translation);
			return *this;
		}

		const char* get_right_text() override {
			MemoryStringStream stream(base::m_right_text);
			if (m_data) {
				stream << m_data[*m_position];
				stream << " ~c~[" << *m_position + 1 << "/" << m_data_size << "]";
			}
			else {
				stream << "Unknown ~c~[0/0]";
			}
			return base::get_right_text();
		}

		void handle_action(eOptionAction action) override {
			m_on_hover();
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
				if (base::m_action)
					std::invoke(base::m_action);
			}
			if (m_data) {
				base::handle_action(action);
			}
		}
		bool get_flag(eOptionFlag flag) override {
			if (flag == eOptionFlag::scroll_option) {
				return true;
			}
			return base::get_flag(flag);
		}
	};
}