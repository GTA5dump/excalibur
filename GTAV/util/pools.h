#pragma once
#include "rage/classes/pools.h"
namespace menu::pools {
	inline auto& get_all_peds()
	{
		return **patterns::ped_pool;
	}

	inline auto& get_all_vehicles()
	{
		return ***patterns::vehicle_pool;
	}

	inline auto& get_all_props()
	{
		return **patterns::prop_pool;
	}

	inline auto get_all_peds_array()
	{
		return get_all_peds().to_array();
	}

	inline auto get_all_vehicles_array()
	{
		return get_all_vehicles().to_array();
	}

	inline auto get_all_props_array()
	{
		return get_all_props().to_array();
	}
}