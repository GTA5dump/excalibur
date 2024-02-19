#pragma once
#include "pch.h"

enum class eOptionAction {
	left_click,
	right_click,
	click
};

enum eJustify {
	JUSTIFY_LEFT,
	JUSTIFY_RIGHT,
	JUSTIFY_CENTER,
};

enum class eFont : std::int32_t {
	ChaletLondon = 0,
	HouseScript = 1,
	Monospace = 2,
	Wingdings = 3,
	ChaletComprimeCologne = 4,
	Pricedown = 7
};

enum class eOptionFlag {
	indicator = (1 << 0),
	toggle_option = (1 << 1),
	scroll_option = (1 << 2),
	number_option = (1 << 3),
	simple_option = (1 << 4),
	toggle_number_option = (1 << 5),
	keyboard_option = (1 << 6),
	break_option = (1 << 7),
	toggle_scroll_option = (1 << 8),
	vehicle_option = (1 << 9),
	color_option = (1 << 10)
};