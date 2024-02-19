#include "pch.h"
#include "panels.h"
#include "gui/render.h"
#include "gui/renderer.h"

namespace menu {

    void panel::start_panel(std::string title) {
        auto menu = renderer::getRenderer();

        g_panel_base_2 = g_panel_pos.y;

        if (!m_next_to) {
            g_panel_pos.x = menu->m_position.x + (menu->m_width / 2.f) + (m_width + g_panel_spacing);
        }
        else {
            g_panel_pos.x = menu->m_position.x + (menu->m_width / 2.f) + (m_width + g_panel_spacing);
            //g_panel_base = g_panel_base_2;
        }

        g_panel_base = g_panel_pos.y;

        if (m_title_height != 0) {
            g_panel_pos.y = renderer::getRenderer()->m_position.y - 0.006f;
        }
        else {
            g_panel_pos.y = renderer::getRenderer()->m_position.y - g_test_y;
        }   
        
        if (m_title_height != 0) {
            render::draw_rect({ g_panel_pos.x, render::get_rect_base(m_title_height, g_panel_base + 0.01f) }, { m_width, m_title_height + 0.001f }, m_back_ground);
            render::draw_rect({ g_panel_pos.x, render::get_rect_base(m_title_height, g_panel_base - 0.004f) }, { m_width, 0.004f }, menu->m_header.m_color);
            render::draw_text(title.c_str(), eJustify::JUSTIFY_LEFT, { g_panel_pos.x, render::get_rect_base(m_title_height, g_panel_base + 0.013f) }, m_title_font_scale, (int)m_title_font, m_padding);
            g_panel_base += m_title_height + 0.001;
        }
        else {
            render::draw_rect({ g_panel_pos.x, render::get_rect_base(m_title_height, g_panel_base - 0.004f) }, { m_width, 0.004f }, menu->m_header.m_color);     
            g_panel_base += 0.f;
        }
    }

    void panel::push(std::string left, std::string right) {
        if (m_title_height != 0) {
            render::draw_rect({ g_panel_pos.x, render::get_rect_base(m_item_height, g_panel_base + 0.01f) }, { m_width, m_title_height + 0.001f }, m_back_ground);
            render::draw_text(left.c_str(), eJustify::JUSTIFY_LEFT, { g_panel_pos.x, render::get_rect_base(m_item_height, g_panel_base + 0.01f) }, m_font_scale, (int)m_item_font, m_padding);
            render::draw_text(right.c_str(), eJustify::JUSTIFY_RIGHT, { g_panel_pos.x + (m_width / 2.f) - 0.003f, render::get_rect_base(m_item_height, g_panel_base + 0.01f) }, m_font_scale, (int)m_item_font, m_padding);
            g_panel_base += m_title_height + 0.001;
        }
        else {
            render::draw_rect({ g_panel_pos.x, render::get_rect_base(m_item_height, g_panel_base - 0.002f) }, { m_width, m_item_height }, m_back_ground);
            render::draw_text(left.c_str(), eJustify::JUSTIFY_LEFT, { g_panel_pos.x, render::get_rect_base(m_item_height, g_panel_base - 0.002f) }, m_font_scale, (int)m_item_font, m_padding);
            render::draw_text(right.c_str(), eJustify::JUSTIFY_RIGHT, { g_panel_pos.x + (m_width / 2.f) - 0.003f, render::get_rect_base(m_item_height, g_panel_base - 0.002f) }, m_font_scale, (int)m_item_font, m_padding);
            g_panel_base += m_item_height;
        }
    }

    void panel::push_sprite(std::pair<std::string, std::string> texture, math::vector2<float> scale) {
        render::draw_rect({ g_panel_pos.x, render::get_rect_base(scale.y, g_panel_base ) }, { m_width, scale.y + 0.004f }, m_back_ground);
        render::draw_sprite(texture, { g_panel_pos.x, render::get_rect_base(scale.y, g_panel_base) }, { scale.x, scale.y });
        g_panel_base += scale.y + 0.004f;
    }

    void panel::end_panel() {
        g_panel_base += g_panel_spacing;
    }

    void panel::set_next() {
        m_next_to = true;
    }


}