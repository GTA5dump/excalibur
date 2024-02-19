#pragma once
#include "pch.h"
#include "rage/classes/joaat.h"

namespace features {
	union value {
		const char* str;
		bool toggle;
		float floating_point;
		int8_t i8;
		uint8_t u8;
		int16_t i16;
		uint16_t u16;
		int32_t i32;
		uint32_t u32;
		int64_t i64;
		uint64_t u64;
		value* reference;
	/*	CNetGamePlayer* game_player;
		rage::netPlayer* net_player;
		rage::rlGamerInfo* gamer_info;*/
	};
	class hotkey {
	public:
		std::vector<int> m_keys{};
		bool m_enabled{};
		void add_hotkey(int key);
		bool pressed();
	};
	enum class eFeatureType : uint8_t {
		AbstractFeature,
		ToggleFeature,
		IntFeature,
		FloatFeature,
		ToggleIntFeature,
		ToggleFloatFeature,
		ActionFeature,
		VariadicFeature,
	};
	class abstractFeature {
	public:
		abstractFeature(std::string id, std::string name, std::string description, hotkey hotkey, eFeatureType type) :
			m_id(id), m_name(name), m_description(description), m_lookupId(rage::joaat(m_id)), m_hotkey(hotkey), m_type(type)
		{}
		abstractFeature(std::string id, std::string name, std::string description, eFeatureType type) : abstractFeature(id, name, description, {}, type) {}
		abstractFeature(std::string id, std::string name, eFeatureType type) : abstractFeature(id, name, {}, type) {}
		abstractFeature(std::string id, eFeatureType type) : abstractFeature(id, {}, type) {}
		virtual ~abstractFeature() {
			deallocate();
		}
		virtual void init() {
			if (!m_looped) {
				if (m_type != eFeatureType::AbstractFeature && m_type != eFeatureType::IntFeature && m_type != eFeatureType::FloatFeature && m_type != eFeatureType::ActionFeature)
					m_looped = true;
			}
			m_intialized = true;
		}
		virtual void run() {}
		void deallocate() {
			m_values.clear();
			m_hotkey.m_keys.clear();
		}
		void push_value(value& v) {
			m_values.emplace_back(&v);
		}
		value* get_value(size_t index) {
			if (index > m_values.size() - 1) {
				throw std::runtime_error("Value index cannot be over value size!");
			}
			return m_values[index];
		}
		value* v() {
			return get_value(0);
		}
		void add_hotkey(int key) {
			m_hotkey.add_hotkey(key);
		}
	public:
		eFeatureType m_type{};
		std::string m_id{};
		std::string m_name{};
		std::string m_description{};
		uint32_t m_lookupId{};
		hotkey m_hotkey{};
		bool m_looped{};
		bool m_intialized{};
	private:
		std::vector<value*> m_values{};
	};
}