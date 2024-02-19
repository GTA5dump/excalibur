#pragma once
#include "submenu.h"
#include "rage/classes/joaat.h"
#include "rage/engine.h"
#include "rage/invoker/natives.h"

namespace base::gui {
	class core : public base_submenu<core> {
	public:
		explicit core(const char* name, const char* target, std::function<void(core*)> action) {
			set_name(name); set_id(rage::joaat(target)); set_action(std::move(action));
		}
	};

	class pcore : public base_submenu<pcore> {
	public:
		explicit pcore(uint32_t* player, uint32_t id, std::function<void(pcore*)> action) :
			m_selected_player(player)
		{
			set_id(id);
			set_action(std::move(action));
		}
		const char* get_name() override {
			return PLAYER::GET_PLAYER_NAME(*m_selected_player);
		}
	private:
		uint32_t* m_selected_player;
	};

	class fcore : public base_submenu<fcore> {
	public:
		explicit fcore(uint32_t* player, uint32_t id, std::function<void(fcore*)> action) :
			m_selected_friend(player),
			m_submenu(nullptr)
		{
			set_id(id);
			set_action(std::move(action));

			// Initialize the name of the submenu here
			update_name();
		}

		const char* get_name() override {
			return m_name.c_str();
		}

		void set_submenu(fcore* submenu) {
			m_submenu = submenu;
		}

		void update_friend(uint32_t friendIndex) {
			*m_selected_friend = friendIndex;
			update_name();

			// Update the name of the parent submenu if available
			if (m_submenu) {
				m_submenu->update_name();
			}
		}

	private:
		uint32_t* m_selected_friend;
		std::string m_name; // Store the name of the submenu as a string
		fcore* m_submenu; // Pointer to the parent submenu, if available

		void update_name() {
			// Update the name of the submenu based on the selected friend
			if (patterns::friend_registry && *m_selected_friend < patterns::friend_registry->m_friend_count) {
				m_name = std::string(patterns::friend_registry->get(*m_selected_friend)->m_name);
			}
			else {
				m_name = "Invalid Friend";
			}
		}
	};

	class vcore : public base_submenu<vcore> {
	public:
		explicit vcore(int* vehicle, uint32_t id, std::function<void(vcore*)> action) :
			m_selected_vehicle(vehicle)
		{
			set_id(id);
			set_action(std::move(action));
		}
		const char* get_name() override {
			return rage::engine::get_vehicle_class_name(*m_selected_vehicle);
		}
	private:
		int* m_selected_vehicle;
	};
}