#pragma once
#include "option.h"
#include "gui/render.h"
namespace base::gui {
	class breakOption : public base_option<breakOption> {
	public:
		explicit breakOption(const char* text) {
			set_left_text(trans(text).c_str());
		}
		bool get_flag(eOptionFlag flag) override {
			if (flag == eOptionFlag::break_option) {
				return true;
			}
			return base_option::get_flag(flag);
		}
	};
}