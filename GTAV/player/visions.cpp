#include "pch.h"
#include "visions.h"
#include "features/manager/manager.h"
#include "menu/util/globals.h"
#include "gui/options/option.h"
#include "gui/util/panels.h"
#include "rage/classes/CPed.h"
#include "menu/util/control.h"
using namespace base::gui;
using namespace menu::player::visions::vars;

namespace menu::player::visions::vars {

	variables m_vars;

	struct vision_display { const char* display_name; const char* real_name; };
	inline std::vector<vision_display> visions{
		{ "None", "" },
		{ "Sunglasses", "sunglasses" },
		{ "Camera BW", "CAMERA_BW" },
		{ "Hint Cam", "Hint_cam" },
		{ "UFO", "ufo" },
		{ "UFO Deathray", "ufo_deathray" },
		{ "Dying", "dying" },
		{ "Underwater", "underwater" },
		{ "Spectator", "spectator1" },
		{ "Cops Splash", "CopsSPLASH" },
		{ "Crane Cam", "crane_cam" },
		{ "Secret Camera", "secret_camera" },
		{ "Graveyard Shootout", "graveyard_shootout" },
		{ "Cops", "cops" },
		{ "Damage", "damage" },
		{ "Bikers Splash", "BikersSPLASH" },
		{ "Bikers", "Bikers" },
		{ "Prologue Shootout", "prologue_shootout" },
		{ "Vagos", "vagos" },
		{ "Sniper", "sniper" }
	};


}

namespace menu {
	void player_visions_menu::render() {
		renderer::addSubmenu("Visions", "Player Visions", [](core* core) {
			for (int i = 0; i < visions.size(); i++) {
				core->addOption(buttonOption(visions[i].display_name)
					.addClick([=] { if (i == 0) { GRAPHICS::POP_TIMECYCLE_MODIFIER(); } else { GRAPHICS::SET_TIMECYCLE_MODIFIER(visions[i].real_name); }  }));
			}
		});
	}

	void player_visions_menu::update() {
		render();

	
	}
}