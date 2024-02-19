#include "pch.h"
#include "notify.h"
#include "rage/invoker/natives.h"
#include "gui/renderer.h"
#include "util/log.h"
#include "util/util.h"
#include "gui/render.h"
namespace menu::notify {


    void notify::update() {
        float padding = 0.004f; // Padding value
        float cumulativeHeight = 0.01f; // Move the starting position by 0.01

        for (auto context = m_context.begin(); context != m_context.end(); context++) {
            float x_offset = 0.003f;
            float text_height = 0.25f;
            float height = (text_height / 10.f) + ((text_height * 0.7f) / 10.f);
            bool death = false;

            float scaled_body_height = (render::get_normalized_font_scale(0, text_height) * 1.1);

            uint32_t end_time = context->m_start_time + context->m_time_limit;
            if (end_time < GetTickCount() || end_time - GetTickCount() < 1000) {
                death = true;
                context->x = math::lerp(context->x, 1.2f, 5.f * renderer::getRenderer()->m_delta);

                if (context->m_alpha_start == 0) context->m_alpha_start = GetTickCount();
                context->m_alpha = 255 - (((GetTickCount() - context->m_alpha_start) * 255) / 1000);
            }

            context->m_max_width = render::calculate_string_width(context->m_text[0], 0, scaled_body_height) + (x_offset * 2.f);
            context->m_lines = 1;
            context->m_rendering_text = context->m_text[0];

            float current = -((context->m_lines * HUD::GET_RENDERED_CHARACTER_HEIGHT(scaled_body_height, 0)) + (context->m_lines * x_offset) + (x_offset * 3.f) + padding);
            context->m_y = math::lerp(context->m_y, cumulativeHeight, 5.f * renderer::getRenderer()->m_delta);

            if (context->m_y + height + padding > 0.7f) {
                context->m_time_limit = 0;
            }

            if (context->m_y <= 1.f) {
                HUD::CLEAR_HELP(true);
                HUD::CLEAR_ALL_HELP_MESSAGES();

                int rect_alpha = context->m_alpha >= 35 ? context->m_alpha - 35 : 0;
                std::pair<std::string, std::string> texture = { "re", "re" };

                // Move the notification to the left based on its width
                float x_position = context->x - context->m_max_width - padding;

                render::draw_sprite_aligned(texture, { x_position, context->m_y }, { context->m_max_width, height }, 0.f, m_notify_background.opacity(rect_alpha));

                std::pair<std::string, std::string> texture2 = { "rerer", "reerer" };
                render::draw_sprite_aligned(texture2, { x_position, context->m_y }, { 0.002f, height }, 0.f, context->m_color.opacity(rect_alpha));

                render::draw_text2(context->m_rendering_text, { x_position + x_offset, context->m_y + 0.012f }, scaled_body_height, 0, { 255, 255, 255, 255 }, JUSTIFY_LEFT);
                cumulativeHeight += height + padding;
            }
        }

        for (auto context = m_context.begin(); context != m_context.end();) {
            if (context->m_start_time + context->m_time_limit < GetTickCount()) {
                context = m_context.erase(context);
                continue;
            }

            context++;
        }
    }


	void notify::stacked(std::string text, color color, uint32_t timeout) {
		for (auto& context : m_context) {
			if (context.m_text.size() == 1 && context.m_text[0] == text) {
				context.m_start_time = GetTickCount();
				return;
			}
		}

		notify_context context;
		context.m_text.push_back(text);
		context.m_color = color;
		context.m_start_time = GetTickCount();
		context.m_time_limit = timeout;

		LOG(text.c_str());

		m_context.push_back(context);
	}


	void notify::subtitle(const char* msg) {
        HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP("STRING");
        HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(msg);
        HUD::END_TEXT_COMMAND_DISPLAY_HELP(0, 0, 1, -1);
	}

	notify* get_notify() {
		static notify instance;
		return &instance;
	}
}