#pragma once
#include "pch.h"
#include "util/math.h"

struct color {
	int r;
	int g;
	int b;
	int a = 255;

	color()
		: r(0), g(0), b(0), a(0) {}

	color(int red, int green, int blue, int alpha = 255)
		: r(red), g(green), b(blue), a(alpha) {}

	color(uint32_t hex)
		: r(hex >> 24), g(((hex >> 16) & 0x00FF)), b(((hex >> 8) & 0x0000FF)), a(hex & 0xFF) {}

	color opacity(int opacity) {
		return color(r, g, b, opacity);
	}

	math::vector3_<int> as_vector() {
		return { r, g, b };
	}

	std::initializer_list<int> as_initializer_list() {
		return std::initializer_list<int> { r, g, b, a };
	}

	uint32_t to_argb() {
		uint8_t val[4];
		val[0] = a;
		val[1] = r;
		val[2] = g;
		val[3] = b;

		return *(uint32_t*)&val;
	}
};

