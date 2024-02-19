#include "pch.h"
#include "spawner_settings.h"

using namespace base::gui;

using namespace menu::spawner::settings::vars;

namespace menu::spawner::settings::vars {
	variables m_vars;

}

namespace menu {

	void spawner_settings_menu::render() {
		renderer::addSubmenu("Spawner Settings", "Spawner Settings", [](core* core) {
			core->addOption(toggleOption("Notification")
				.addToggle(&m_vars.m_notification));

			core->addOption(toggleOption("Blip")
				.addToggle(&m_vars.m_blip));

			core->addOption(toggleOption("Particle FX")
				.addToggle(&m_vars.m_particle_fx));

			core->addOption(toggleOption("Teleport Inside")
				.addToggle(&m_vars.m_teleport_inside));

			core->addOption(toggleOption("Godmode")
				.addToggle(&m_vars.m_godmode));

			core->addOption(toggleOption("Fade")
				.addToggle(&m_vars.m_fade));

			core->addOption(toggleOption("Air Vehicles In Air")
				.addToggle(&m_vars.m_air_vehicles_in_air));

			core->addOption(numberOption<float>("Air Vehicles Height")
				.addNumber(&m_vars.m_spawn_height).addStep(1.f).setPrecision(0)
				.addMin(0.f).addMax(1000.f));

			core->addOption(toggleOption("Delete Current")
				.addToggle(&m_vars.m_delete_current));
		});
	}

	void spawner_settings_menu::update() {
		render();
	}
};

