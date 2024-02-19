#pragma once
#include "pch.h"
#include "gui/types.h"

namespace menu {
	class rainbow {
	public:
		rainbow(int min = 25, int max = 250, int steps = 80);

		void add(color* color);
		void remove(color* col);
		void run();
		void start();
		void stop();
		void toggle(bool toggle);

		color get_default(color* color);

		bool m_enabled = false;
		int m_increment = 0;
		int m_min = 0;
		int m_max = 0;
		int m_steps = 0;
		color m_color;
	private:
		std::vector<color*> m_colors;
		std::vector<std::pair<color*, color>> m_default_colors;
	};
}