#pragma once
#include "gui/options/core.h"
#include "gui/options/submenu.h"
#include "gui/options/option.h"
#include "gui/options/button.h"
#include "gui/options/submenu_option.h"
#include "gui/options/number.h"
#include "gui/options/toggle.h"
#include "gui/options/scroll.h"

namespace menu {
	class network_menu {
	public:
		void render();
		void update();
	};

	static network_menu* getNetworkMenu() {
		static network_menu instance;
		return &instance;
	}

	namespace network::vars {
		struct variables {
			bool m_bst;
			bool m_toggle_ping;
			bool m_esp_box;
			bool m_esp_line;
			bool m_esp_name;

			color m_3d_box_color = color(255, 0, 255, 255);
			color m_snapline_color = color(255, 255, 0, 255);
			color m_name_text_color = color(255, 255, 255, 255);
			color m_name_bg_color = color(0, 0, 0, 180);

			int m_box_red{ 255 };
			int m_box_green{ 0 };
			int m_box_blue{ 0 };

			int m_line_red{ 0 };
			int m_line_green{ 0 };
			int m_line_blue{ 255 };

			int m_name_red{ 255 };
			int m_name_green{ 255 };
			int m_name_blue{ 255 };
		};

		extern variables m_vars;
	}

}