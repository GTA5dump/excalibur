#pragma once
#include "option.h"
#include "util/util.h"
#include "util/log.h"
#include "gui/renderer.h"
#include "gui/util/translate.h"

namespace base::gui {
	class colorOption : public base_option<colorOption> {
	private:
		std::uint32_t m_sub_id{};
	public:
		explicit colorOption(const char* text, color color) {
			set_left_text(text);
			set_color(color);
		}

		colorOption& setTarget(const const char* id) {
			m_sub_id = rage::joaat(id);
			return *this;
		}

		colorOption& addTranslate() {
			//set_left_text(translation);
			return *this;
		}


		void handle_action(eOptionAction action) override {
			if (action == eOptionAction::click) {
				menu::renderer::getRenderer()->switch_to_submenu(m_sub_id);
			}
			base_option::handle_action(action);
		}

		bool get_flag(eOptionFlag flag) override {
			if (flag == eOptionFlag::color_option) {
				return true;
			}
			return base_option::get_flag(flag);
		}
	};

}