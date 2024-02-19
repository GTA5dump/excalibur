#pragma once
#include "pch.h"
#include "util/log.h"
#include "rage/invoker/natives.h"
#include "renderer.h"
#include "util/math.h"
#include "types.h"
namespace menu::render {
	inline float get_accurate_font_scale(int font, float scale) {
		switch (font) {
		case 0: return (scale * 1.0f);
		case 1: return (scale * 1.3f);
		case 2: return (scale * 1.11f);
		case 4: return (scale * 1.11f);
		case 7: return (scale * 1.29f);
		}
		return scale;
	}

	inline float get_text_width(std::string string, int font, float scale) {
		HUD::BEGIN_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(string.c_str());
		HUD::SET_TEXT_SCALE(0.f, scale);
		return HUD::END_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT(font);
	}

	inline float get_text_height(int font, float size) {
		return HUD::GET_RENDERED_CHARACTER_HEIGHT(size, font);
	}

	inline void draw_rect(math::vector2<float> position, math::vector2<float> scale, color color, bool alligned = false) {
		if (alligned) {
			GRAPHICS::DRAW_RECT({ position.x + (scale.x * 0.5f), position.y + (scale.y * 0.5f) }, scale.x, scale.y, color.r, color.g, color.b, color.a, 0);
		}
		else {
			GRAPHICS::DRAW_RECT({ position.x, position.y }, scale.x, scale.y, color.r, color.g, color.b, color.a, 0);
		}
	}

	inline void draw_outlined_rect(math::vector2<float> position, math::vector2<float> scale, float thickness, color box_color, color border_color) {
		draw_rect({ position.x, position.y }, { scale.x, scale.y }, box_color); // bg
		draw_rect({ position.x, position.y - thickness }, { scale.x, thickness }, border_color); // top
		draw_rect({ position.x, position.y + scale.y }, { scale.x, thickness }, border_color); // bottom

		draw_rect({ position.x - (thickness * 0.60f), position.y - thickness }, { (thickness * 0.60f), scale.y + (thickness * 2.f) }, border_color); // left
		draw_rect({ position.x + scale.x, position.y - thickness }, { (thickness * 0.60f), scale.y + (thickness * 2.f) }, border_color); // right
	}

	inline float get_rect_base(float rect_height, float draw_base = renderer::getRenderer()->m_draw_base_y) {
		return draw_base + (rect_height / 2.f);
	}

	inline void draw_text(const char* text, eJustify justify, math::vector2<float> position, float size, int font, math::vector2<float> padding, color color = { 255, 255, 255, 255 }, bool half = false, bool outline = false, bool shadow = false) {
		if (justify == eJustify::JUSTIFY_CENTER) {
			HUD::SET_TEXT_CENTRE(true);
			position.x = position.x;
		}
		if (justify == eJustify::JUSTIFY_RIGHT) {
			HUD::SET_TEXT_WRAP(0.f, position.x);
			HUD::SET_TEXT_RIGHT_JUSTIFY(true);
			position.x = position.x + (renderer::getRenderer()->m_width / padding.y);
		}
		if (justify == eJustify::JUSTIFY_LEFT) {
			position.x = position.x - (renderer::getRenderer()->m_width / padding.x);
		}
		if (half) {
			position.y -= get_text_height(font, size) / 2.f;
		}
		else {
			position.y -= get_text_height(font, size) / 1.5f;
		}
		HUD::SET_TEXT_SCALE(size, size);
		HUD::SET_TEXT_FONT(static_cast<int>(font));
		HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
		if (outline)
			HUD::SET_TEXT_OUTLINE();
		if (shadow)
			HUD::SET_TEXT_DROP_SHADOW();

	/*	if (text.length() >= 98) {
			renderer::getRenderer()->render_queue[renderer::getRenderer()->render_queue_index] = text;
			renderer::getRenderer()->render_queue_index++;
			renderer::getRenderer()->render_queue_index %= 100;
		}*/

		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT({ position.x, position.y }, 0);
	}

	inline void draw_text2(std::string text, math::vector2<float> position, float scale, int font, color color,eJustify justification = JUSTIFY_LEFT, math::vector2<float> wrap = { 0.f, 5.f }) {
		HUD::SET_TEXT_WRAP(wrap.x, wrap.y);

		if (justification != JUSTIFY_LEFT) {
		  //  HUD::SET_TEXT_JUSTIFICATION(justification = JUSTIFY_CENTER ? 0 : 2);
		}

		HUD::SET_TEXT_CENTRE(justification == JUSTIFY_CENTER);
		HUD::SET_TEXT_SCALE(0.f, scale);
		HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
		HUD::SET_TEXT_FONT(font);

		if (text.length() >= 98) {
			renderer::getRenderer()->render_queue[renderer::getRenderer()->render_queue_index] = text;
			renderer::getRenderer()->render_queue_index++;
			renderer::getRenderer()->render_queue_index %= 100;
		}

		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT({ position.x, position.y }, 0);
	}

	inline void draw_left_text(const char* text, float x, float y, float size, int font, color color, bool outline, bool shadow) {
		HUD::SET_TEXT_SCALE(size, size);
		HUD::SET_TEXT_FONT(static_cast<int>(font));
		HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
		if (outline)
			HUD::SET_TEXT_OUTLINE();
		if (shadow)
			HUD::SET_TEXT_DROP_SHADOW();
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT({ x, y }, 0);
	}

	inline void draw_right_text(const char* text, float x, float y, float size, int font, color color, bool outline, bool shadow) {
		HUD::SET_TEXT_WRAP(0.f, x);
		HUD::SET_TEXT_RIGHT_JUSTIFY(true);
		draw_left_text(text, x, y, size, font, color, outline, shadow);
	}

	inline void draw_sprite(std::pair<std::string, std::string> asset, math::vector2<float> position, math::vector2<float> scale, color color = { 255, 255, 255, 255 }, float rotation = 0.f, bool alligned = false) {
		if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(asset.first.c_str()) && asset.first != "Excalibur") {
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(asset.first.c_str(), true);
		}
		if (alligned) {
			GRAPHICS::DRAW_SPRITE(asset.first.c_str(), asset.second.c_str(), { position.x + (scale.x * 0.5f), position.y + (scale.y * 0.5f) }, scale.x, scale.y, rotation, color.r, color.g, color.b, color.a, TRUE, TRUE);
		}
		else {
			GRAPHICS::DRAW_SPRITE(asset.first.c_str(), asset.second.c_str(), { position.x, position.y }, scale.x, scale.y, rotation, color.r, color.g, color.b, color.a, 0, TRUE);
		}
	}

	inline math::vector2<float> get_sprite_scale(float size) {
		int x, y;
		GRAPHICS::GET_ACTUAL_SCREEN_RESOLUTION(&x, &y);
		return { (static_cast<float>(y) / static_cast<float>(x)) * size, size };
	}

	inline float calculate_string_width(std::string string, int font, float scale) {
		HUD::BEGIN_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(string.c_str());
		HUD::SET_TEXT_SCALE(0.f, scale);
		return HUD::END_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT(font);
	}

	inline float get_normalized_font_scale(int font, float scale) {
		switch (font) {
		case 0: return (scale * 1.0f);
		case 1: return (scale * 1.3f);
		case 2: return (scale * 1.11f);
		case 4: return (scale * 1.11f);
		case 7: return (scale * 1.29f);
		}

		return scale;
	}

	inline void draw_sprite_aligned(std::pair<std::string, std::string> asset, math::vector2<float> position, math::vector2<float> scale, float rotation, color color) {

		if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(asset.first.c_str()) && asset.first != "Excaliburtextures") {
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(asset.first.c_str(), true);
		}

		GRAPHICS::DRAW_SPRITE(asset.first.c_str(), asset.second.c_str(), { position.x + (scale.x * 0.5f), position.y + (scale.y * 0.5f) }, scale.x, scale.y, rotation, color.r, color.g, color.b, color.a, TRUE, TRUE);
	}
}