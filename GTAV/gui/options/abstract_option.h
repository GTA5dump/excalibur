#pragma once
#include "pch.h"
#include "../util/flags.h"
#include "gui/types.h"
#include "gui/util/translate.h"

namespace base::gui {
	class abstract_option {
	public:
		virtual const char* get_left_text() = 0;
		virtual const char* get_right_text() = 0;
		virtual const char* get_description() = 0;

		virtual color get_color() = 0;
		virtual void handle_action(eOptionAction action) = 0;
		virtual void set_value(double text) = 0;
		virtual void set_value(std::string text) = 0;
		virtual bool get_flag(eOptionFlag flag) = 0;
		virtual std::function<void()> get_action() = 0;
		virtual bool* get_bool_pointer() = 0;

	
	};
}