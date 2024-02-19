#pragma once
#include "rage/invoker/natives.h"
#include "hooks/patterns.h"


template<typename T>
class pool_iterator
{
public:
	T* pool = nullptr;
	uint32_t index = 0;

	explicit pool_iterator(T* pool, int32_t index = 0)
	{
		this->pool = pool;
		this->index = index;
	}

	pool_iterator& operator++()
	{
		for (index++; index < pool->m_size; index++)
		{
			if (pool->is_valid(index))
			{
				return *this;
			}
		}

		index = pool->m_size;
		return *this;
	}

	rage::CEntity* operator*()
	{
		auto addr = pool->get_address(index);
		return (rage::CEntity*)addr;
	}

	bool operator!=(const pool_iterator& other) const
	{
		return this->index != other.index;
	}
};

// Common functions for VehiclePool and GenericPool
template<typename T>
class PoolUtils
{
public:
	inline auto to_array()
	{
		std::vector<Entity> arr;
		for (auto entity : *static_cast<T*>(this))
		{
			arr.push_back(patterns::ptr_to_handle(entity));
		}

		return arr;
	}

	auto begin()
	{
		return ++pool_iterator<T>(static_cast<T*>(this), -1);
	}

	auto end()
	{
		return ++pool_iterator<T>(static_cast<T*>(this), static_cast<T*>(this)->m_size);
	}
};

class VehiclePool : public PoolUtils<VehiclePool>
{
public:
	UINT64* m_pool_address;
	UINT32 m_size;
	char _Padding2[36];
	UINT32* m_bit_array;
	char _Padding3[40];
	UINT32 m_item_count;

	inline bool is_valid(UINT32 i)
	{
		return (m_bit_array[i >> 5] >> (i & 0x1F)) & 1;
	}

	inline UINT64 get_address(UINT32 i)
	{
		return m_pool_address[i];
	}
};

class GenericPool : public PoolUtils<GenericPool>
{
public:
	UINT64 m_pool_address;
	BYTE* m_bit_array;
	UINT32 m_size;
	UINT32 m_item_size;

	inline bool is_valid(UINT32 i)
	{
		return mask(i) != 0;
	}

	inline UINT64 get_address(UINT32 i)
	{
		return mask(i) & (m_pool_address + i * m_item_size);
	}

private:
	inline long long mask(UINT32 i)
	{
		long long num1 = m_bit_array[i] & 0x80;
		return ~((num1 | -num1) >> 63);
	}
};