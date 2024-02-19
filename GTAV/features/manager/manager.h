#pragma once
#include "features/manager/types.h"
#define ONCE(a) do a while (false)

namespace features {
	class manager {
	public:
		template<typename t>
		void add(t feature) {
			m_features.push_back(new t(feature));
		}
		void remove(uint32_t id);
		void init();
		void tick();
		void clear();
		template <typename t>
		t* getFeature(uint32_t id) {
			for (auto& f : m_features) {
				if (f->m_lookupId == id) {
					return (t*)f;
				}
			}
			return nullptr;
		}
		template <typename t>
		t* getFeature(const char* id) {
			for (auto& f : m_features) {
				if (f->m_id == id) {
					return (t*)f;
				}
			}
			return nullptr;
		}
	private:
		std::vector<abstractFeature*> m_features{};
	};
	inline manager g_manager{};
}
inline features::abstractFeature* operator ""_ABF(const char* str, size_t) {
	return features::g_manager.getFeature<features::abstractFeature>(str);
}
inline features::toggleFeature* operator ""_TF(const char* str, size_t) {
	return features::g_manager.getFeature<features::toggleFeature>(str);
}
inline features::intFeature* operator ""_IF(const char* str, size_t) {
	return features::g_manager.getFeature<features::intFeature>(str);
}
inline features::toggleIntFeature* operator ""_TIF(const char* str, size_t) {
	return features::g_manager.getFeature<features::toggleIntFeature>(str);
}
inline features::floatFeature* operator ""_FF(const char* str, size_t) {
	return features::g_manager.getFeature<features::floatFeature>(str);
}
inline features::toggleFloatFeature* operator ""_TFF(const char* str, size_t) {
	return features::g_manager.getFeature<features::toggleFloatFeature>(str);
}
inline features::actionFeature* operator ""_AF(const char* str, size_t) {
	return features::g_manager.getFeature<features::actionFeature>(str);
}