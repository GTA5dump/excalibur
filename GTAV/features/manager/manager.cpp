#include "pch.h"
#include "manager.h"
#include "gui/util/notify.h"
namespace features {
	void hotkey::add_hotkey(int key) {
		m_keys.emplace_back(key);
	}
	bool hotkey::pressed() {
		if (m_enabled)
			return false;
		bool pressed{};
		for (auto& k : m_keys) {
			if (GetAsyncKeyState(k)) {
				pressed = true;
			}
		}
		return pressed;
	}
	void manager::remove(uint32_t id) {
		for (size_t i{}; i != m_features.size(); ++i) {
			auto& f{ m_features[i] };
			if (f->m_lookupId == id) {
				delete f;
				m_features.erase(m_features.begin() + i);
			}
		}
	}
	void manager::init() {
		for (auto& f : m_features) {
			f->init();
		}
	}
	void manager::tick() {
		for (auto& f : m_features) {
			if (f->m_looped) {
				f->run();
			}
			else if (f->m_hotkey.pressed()) {
				ONCE({
					f->run();
				});
			}
		}
	}
	void manager::clear() {
		for (auto& f : m_features) {
			f->~abstractFeature();
			delete f;
		}
	}
}