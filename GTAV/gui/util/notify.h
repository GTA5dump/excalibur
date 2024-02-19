#pragma once
#include "pch.h"
#include "gui/renderer.h"
namespace menu::notify {
	struct notify_context {
		std::vector<std::string> m_text = {};
		std::string m_rendering_text = "";
		int m_lines = 1;
		color m_color = { 255, 0, 0 };
		float m_max_width = 0.20f;
		float m_max_height = 0.f; // Add the m_max_height variable here
		float x = 1.f;
		float m_y = 0.0f;
		uint32_t m_start_time = 0;
		uint32_t m_time_limit = 5000;
		bool m_has_calculated = false;
		bool m_has_init = false;
		uint32_t m_alpha_start = 0;
		int m_alpha = 255;
		float m_title_width = 0.f;
	};

	class notify {
	public:
		void update();
		void stacked(std::string text, color color = { 255, 0, 0, } , uint32_t timeout = 6000);
		void subtitle(const char* msg);

		color m_notify_background = color(31, 30, 31, 255);

		std::vector<notify_context>& get_contexts() { return m_context; }


	private:
		std::vector<notify_context> m_context;
		std::unordered_map<uint32_t, uint32_t> m_protection_spam;
	};

	notify* get_notify();

	inline void update() {
		get_notify()->update();
	}

	inline void subtitle(const char* msg) {
		get_notify()->subtitle(msg);
	}

	inline void stacked(std::string text, color color = renderer::getRenderer()->m_header.m_color, uint32_t timeout = 6000) {
		get_notify()->stacked(text, color, timeout);
	}


	inline std::vector<notify_context>& get_contexts() {
		return get_notify()->get_contexts();
	}

	inline float test = 0.f;
}