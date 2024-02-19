#pragma once
#include "pch.h"
#include "rage/classes/NetObject.h"
#include "util/fiber.h"
#include "rage/invoker/natives.h"
#include "pools.h"
#include "rage/classes/CPed.h"
#include "rage/classes/Vehicle.h"
namespace menu::control {
	inline bool network_has_control_of_entity(rage::netObject* net_object) {
		return !net_object || !net_object->m_next_owner_id && (net_object->m_control_id == -1);
	}

	inline bool request_control(Entity ent, int timeout = 300) {
		if (!*patterns::is_session_started)
			return true;

		auto hnd = patterns::handle_to_ptr(ent);

		if (!hnd || !hnd->m_net_object || !*patterns::is_session_started)
			return false;

		if (network_has_control_of_entity(hnd->m_net_object))
			return true;

		for (int i = 0; i < timeout; i++)
		{
			patterns::request_control(hnd->m_net_object);

			if (network_has_control_of_entity(hnd->m_net_object))
				return true;

			if (timeout != 0)
				util::fiber::go_to_main();
		}

		return false;
	}

	inline void requestWeapon(uint32_t model) {
		int tries = 0;
		while (!WEAPON::HAS_WEAPON_ASSET_LOADED(model) && tries < 30) {
			WEAPON::REQUEST_WEAPON_ASSET(model, 31, 0);
			tries++;
			util::fiber::go_to_main();
		}
	}

	inline void requestModel(uint32_t model) {
		int tries = 0;
		while (!STREAMING::HAS_MODEL_LOADED(model) && tries < 25) {
			STREAMING::REQUEST_MODEL(model);
			tries++;
			util::fiber::go_to_main();
		}
	}

	inline std::vector<Entity> get_entities(bool vehicles, bool peds)
	{
		std::vector<Entity> target_entities;
		target_entities.clear();

		if (vehicles)
		{
			for (auto vehicle : pools::get_all_vehicles())
			{
				if (vehicle == (*patterns::ped_factory)->m_local_ped->m_vehicle)
					continue;

				target_entities.push_back(patterns::ptr_to_handle(vehicle));
			}
		}

		if (peds)
		{
			for (auto ped : pools::get_all_peds())
			{
				if (ped == (*patterns::ped_factory)->m_local_ped)
					continue;

				target_entities.push_back(patterns::ptr_to_handle(ped));
			}
		}
		return target_entities;
	}

	inline bool load_ground_at_3dcoord(Vector3& location)
	{
		float groundZ;
		const uint8_t attempts = 10;

		for (uint8_t i = 0; i < attempts; i++)
		{
			// Only request a collision after the first try failed because the location might already be loaded on first attempt.
			for (uint16_t z = 0; i && z < 1000; z += 100)
			{
				STREAMING::REQUEST_COLLISION_AT_COORD({ location.x, location.y, (float)z });

				util::fiber::go_to_main();
			}

			if (MISC::GET_GROUND_Z_FOR_3D_COORD({ location.x, location.y, 1000.f }, &groundZ, false, false))
			{
				location.z = groundZ + 1.f;

				return true;
			}

			util::fiber::go_to_main();
		}

		location.z = 1000.f;

		return false;
	}

	inline double distance_to_middle_of_screen(const math::vector2<float>& screen_pos)
	{
		double cumulative_distance{};

		if (screen_pos.x > 0.5)
			cumulative_distance += screen_pos.x - 0.5;
		else
			cumulative_distance += 0.5 - screen_pos.x;

		if (screen_pos.y > 0.5)
			cumulative_distance += screen_pos.y - 0.5;
		else
			cumulative_distance += 0.5 - screen_pos.y;

		return cumulative_distance;
	}

	inline Entity get_entity_closest_to_middle_of_screen(rage::fwEntity** pointer = nullptr, std::vector<Entity> ignore_entities = {}, bool include_veh = true, bool include_ped = true, bool include_prop = true, bool include_players = true)
	{
		Entity closest_entity{};
		rage::fwEntity* closest_entity_ptr = nullptr;
		float distance = 1;

		auto ignored_entity = [=](Entity handle) -> bool {
			if (handle == PLAYER::PLAYER_PED_ID())
				return true;

			for (auto ent : ignore_entities)
			{
				if (handle == ent)
					return true;
			}

			return false;
		};

		auto update_closest_entity = [&](Entity handle, rage::fwEntity* entity_ptr) {
			Vector3 pos = ENTITY::GET_ENTITY_COORDS(handle, 1);
			math::vector2<float> screenpos;
			HUD::GET_HUD_SCREEN_POSITION_FROM_WORLD_POSITION(pos, &screenpos.x, &screenpos.y);

			if (distance_to_middle_of_screen(screenpos) < distance && ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(PLAYER::PLAYER_PED_ID(), handle, 17) && !ignored_entity(handle))
			{
				closest_entity = handle;
				closest_entity_ptr = entity_ptr;
				distance = distance_to_middle_of_screen(screenpos);
			}
		};

		auto include_pool = [&](auto& pool) {
			for (const auto ptr : pool())
				if (ptr)
					update_closest_entity(patterns::ptr_to_handle(ptr), ptr);
		};

		if (include_veh)
			include_pool(pools::get_all_vehicles);

		if (include_ped)
			include_pool(pools::get_all_peds);

		if (include_prop)
			include_pool(pools::get_all_props);

		if (include_players)
		{
			for (uint32_t i = 0; i < 32; i++) {
				if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i)) {
					Ped handle = patterns::ptr_to_handle(&ped);
					update_closest_entity(handle, patterns::get_net_player(i)->m_player_info->m_ped);
				}
			}
		}

		if (pointer)
			*pointer = closest_entity_ptr;

		return closest_entity;
	}

}