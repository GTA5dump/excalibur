#pragma once
#include "pch.h"
#include "options/submenu.h"
#include "types.h"
#include "gui/options/core.h"


struct bool_hotkey {
	int m_key;
	bool* m_pointer;
	std::string m_name;
};

namespace menu::renderer {


	struct header {
		float m_height = 0.092f, m_font_scale = 1.1f;
		int m_font = 7;

		color m_color = { 0, 0, 0 };
		color m_text_color = { 255, 255, 255 };
	};

	struct title {
		float m_height = 0.0295f, m_font_scale = 0.28f;
		int m_font = (int)eFont::ChaletLondon;
		math::vector2<float> m_padding = { 2.05f, 2.05f };

		color m_color = { 0, 0, 0, 255 };
		color m_text_color = { 255, 255, 255, 255 };
	};

	struct option {
		float m_height = 0.032f, m_font_scale = 0.29f;
		int m_font = 0;
		math::vector2<float> m_padding = { 2.05f, 2.05f };


		color m_color = { 0, 0, 0, 160 };
		color m_text_color = { 220, 220, 220, 220 };
		color m_selected_text_color = { 0, 0, 0, 255 };
		color g_ToggleOnColor = { 130, 214, 157, 255 };
		color g_ToggleOffColor = { 200, 55, 80, 255 };

	};

	

	struct footer {
		float m_height = 0.0295, m_font_scale = 0.28f;
		int m_font = (int)eFont::ChaletLondon;
		math::vector2<float> m_padding = { 2.05f, 2.05f };

		color m_color = { 0,0,0,255 };
		color m_text_color = { 255,255,255,255 };
	};

	class renderer {
	public:
		void render();

		base::gui::abstract_option* get_option_pointer(u32 id);
		void push_options();

		std::vector<std::unique_ptr<base::gui::abstract_submenu>>& get_all_subs() { return m_all_subs; }
		std::unordered_map<u32, base::gui::abstract_option*>& get_all_options() { return m_all_options; }
		std::stack<base::gui::abstract_submenu*, std::vector<base::gui::abstract_submenu*>>& get_submenu_stack() { return m_submenu_stack; }

	public:
		bool m_opened{};
		bool m_toggled_on{};
		bool m_smooth_scroll = true;
		math::vector2<float> m_position = { 0.13f, 0.05f };
		float m_draw_base_y{};
		float m_width = 0.21f;

		std::string tooltip;

		float test = 0.0935f;

		std::size_t m_max_vis_options = 12;

		float m_alpha = 0.0f; // Current alpha value for fade animation
		bool m_fadeIn = false; // Flag to indicate if fade-in animation is in progress


		float m_target = { 0.f };
		float m_current = { 0.f };
		float m_speed = { 0.2281f };

		float m_fadespeed = { 0.4281f };

		float m_bg_target = { 0.f };
		float m_bg_current = { 0.f };

		color m_scroller_color = { 255, 255, 255, 220 };

		std::string render_queue[100];
		int render_queue_index = 0;

		header m_header;
		title m_title;
		option m_option;
		footer m_footer;
		float m_wrap = -0.1f;

		bool m_color_opt = false;

		float m_delta = 0.f;
		float m_tooltip_x = 0.0985f;

		bool full_theme;

		std::int32_t m_open_delay = 200, m_close_delay = 300, m_back_delay = 300, m_enter_delay = 300, m_vertical_delay = 120, m_horizontal_delay = 110;
		bool m_open_key; bool m_back_key; bool m_enter_key; bool m_up_key; bool m_down_key; bool m_left_key; bool m_right_key;
		void reset_keys();
		void check_keys();
		void handle_keys();

		void update_scroller();
		void draw_scroller();

		void render_color_preview(base::gui::abstract_option* option);
		void render_tooltip();
		void draw_header();
		void draw_title(base::gui::abstract_submenu* sub);
		void draw_background(base::gui::abstract_submenu* sub);

		bool m_hotkey;
		bool m_hotkey_pressed;

		void drawOverlay();
		bool m_IsOverlayEnabled = true;
		float m_OverlayX = 0.11f;
		float m_OverlayY = 0.03f;
		float m_OverlayHeight = 0.035f;
		float m_OverlayLineHeight = 0.0035f;
		float m_OverlayPadding = 2.1f;
		float m_OverlayWidth = 0.20f;
		color m_OverlayColor = color(27, 28, 31, 220 );
		color m_OverlayTextColor = color( 255, 255, 255, 255 );
		color m_OverlayLineColor = m_header.m_color;

		void draw_option(base::gui::abstract_option* option, bool selected);
		void draw_footer();
		void draw_vehicle_preview(uint32_t hash);


		float test_x = 0.0260;
		float test_y = 0.120;

		void save_theme(const char* name);
		void load_theme(const char* name);
		void reset_theme();
		std::vector<std::string> m_cached_themes;
	public:
		std::vector<std::unique_ptr<base::gui::abstract_submenu>> m_all_subs;
		std::stack<base::gui::abstract_submenu*, std::vector<base::gui::abstract_submenu*>> m_submenu_stack;
		std::unordered_map<u32, base::gui::abstract_option*> m_all_options;
	public:
		std::unordered_map<u32, bool_hotkey> m_bool_hotkeys;
		void update_hotkeys();
		void save_hotkeys();
		void load_hotkeys();
	public:
		template <typename sub_type, typename ...TArgs>
		void add_submenu(TArgs&&... args) {
			auto sub = std::make_unique<sub_type>(std::forward<TArgs>(args)...);
			if (m_submenu_stack.empty()) {
				m_submenu_stack.push(sub.get());
			}
			m_all_subs.push_back(std::move(sub));
		}

		void switch_to_submenu(std::uint32_t id) {
			for (auto&& sub : m_all_subs) {
				if (sub->get_id() == id) {
					m_submenu_stack.push(sub.get());
					return;
				}
			}
		}

	};

	inline renderer* getRenderer() {
		static renderer instance;
		return &instance;
	}
	
	inline void addSubmenu(const char* name, const char* target, std::function<void(base::gui::core*)> action) {
		getRenderer()->add_submenu<base::gui::core>(name, target, action);
	}

	inline void addVehicleSubmenu(int* vehicle, uint32_t id, std::function<void(base::gui::vcore*)> action) {
		getRenderer()->add_submenu<base::gui::vcore>(vehicle, id, action);
	}

	inline void addPlayerSubmenu(uint32_t* player, uint32_t id, std::function<void(base::gui::pcore*)> action) {
		getRenderer()->add_submenu<base::gui::pcore>(player, id, action);
	}

	inline void addFriendSubmenu(uint32_t* player, uint32_t id, std::function<void(base::gui::fcore*)> action) {
		getRenderer()->add_submenu<base::gui::fcore>(player, id, action);
	}
}


inline int m_last_key_pressed = 86;
inline const char* g_key_names[254] = {
"",
"F10",
"F10",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"BACKSPACE",
"TAB",
"TAB",
"TAB",
"NUM 5",
"ENTER",
"ENTER",
"ENTER",
"SHIFT",
"CTRL",
"ALT",
"ALT",
"CAPSLOCK",
"CAPSLOCK",
"CAPSLOCK",
"CAPSLOCK",
"CAPSLOCK",
"CAPSLOCK",
"CAPSLOCK",
"ESC",
"ESC",
"ESC",
"ESC",
"ESC",
"SPACE",
"NUM 9",
"NUM 3",
"NUM 1",
"NUM 7",
"LEFT",
"UP",
"RIGHT",
"DOWN",
"NUM 2",
"NUM 2",
"NUM 2",
"NUM 2",
"NUM 0",
"DELETE",
"NUM DECIMAL",
"0",
"1",
"2",
"3",
"4",
"5",
"6",
"7",
"8",
"9",
"9",
"9",
"9",
"9",
"9",
"9",
"9",
"A",
"B",
"C",
"D",
"E",
"F",
"G",
"H",
"I",
"J",
"K",
"L",
"M",
"N",
"O",
"P",
"Q",
"R",
"S",
"T",
"U",
"V",
"W",
"X",
"Y",
"Z",
"Z",
"Z",
"Z",
"Z",
"Z",
"NUM 0",
"NUM 1",
"NUM 2",
"NUM 3",
"NUM 4",
"NUM 5",
"NUM 6",
"NUM 7",
"NUM 8",
"NUM 9",
"*",
"NUM PLUS",
"NUM PLUS",
"NUM SUB",
"NUM DECIMAL",
"/",
"F1",
"F2",
"F3",
"F4",
"F5",
"F6",
"F7",
"F8",
"F9",
"F10",
"F11",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"F12",
"Pause",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SCROLL LOCK",
"SHIFT",
"RIGHT SHIFT",
"CTRL",
"CTRL",
"ALT",
"ALT",
"ALT",
"ALT",
"ALT",
"ALT",
"ALT",
"ALT",
"M",
"D",
"C",
"B",
"P",
"Q",
"J",
"G",
"G",
"G",
"G",
"F",
"F",
"F",
";",
"=",
",",
"-",
".",
"/",
"GRAVE",
"GRAVE",
"GRAVE",
"GRAVE",
"GRAVE",
"GRAVE",
"GRAVE",
"GRAVE",
"GRAVE",
"A",
"B",
"X",
"Y",
"Left Button",
"Right Button",
"Left Trigger",
"Right Trigger",
"Left Stick",
"Right Stick",
"GRAVE",
"GRAVE",
"GRAVE",
"GRAVE",
"GRAVE",
"GRAVE",
"GRAVE",
"GRAVE",
"[",
"null",
"]",
"ACUTE/CEDILLA",
"ACUTE/CEDILLA",
"ACUTE/CEDILLA",
"ACUTE/CEDILLA",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null",
"null"
};