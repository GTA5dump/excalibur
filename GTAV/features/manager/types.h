#pragma once
#include "abstract.h"

namespace features {
	class toggleFeature : public abstractFeature {
	public:
		toggleFeature(std::string id, std::string name, std::string description, hotkey hotkey, fnptr<void(toggleFeature*, bool&)> callback) :
			abstractFeature(id, name, description, hotkey, eFeatureType::ToggleFeature),
			m_callback(callback) {
		}
		toggleFeature(std::string id, std::string name, std::string description, fnptr<void(toggleFeature*, bool&)> callback) :
			toggleFeature(id, name, description, {}, callback) {
		}
		toggleFeature(std::string id, std::string name, fnptr<void(toggleFeature*, bool&)> callback) :
			toggleFeature(id, name, {}, callback) {
		}
		toggleFeature(std::string id, fnptr<void(toggleFeature*, bool&)> callback) :
			toggleFeature(id, {}, callback) {
		}
		~toggleFeature() {
			abstractFeature::~abstractFeature();
		}
		void init() override {
			m_looped = true;
			push_value(m_value);
			abstractFeature::init();
		}
		void run() override {
			if (m_hotkey.pressed()) {
				m_value.toggle ^= true;
			}
			m_callback(this, m_value.toggle);
			abstractFeature::run();
		}
	public:
		value m_value{};
	private:
		fnptr<void(toggleFeature*, bool&)> m_callback{};
	};
	class intFeature : public abstractFeature {
	public:
		intFeature(std::string id, std::string name, std::string description, hotkey hotkey, fnptr<void(intFeature*, int&)> callback) :
			abstractFeature(id, name, description, hotkey, eFeatureType::IntFeature),
			m_callback(callback) {
		}
		intFeature(std::string id, std::string name, std::string description, fnptr<void(intFeature*, int&)> callback) :
			intFeature(id, name, description, {}, callback) {
		}
		intFeature(std::string id, std::string name, fnptr<void(intFeature*, int&)> callback) :
			intFeature(id, name, {}, callback) {
		}
		intFeature(std::string id, fnptr<void(intFeature*, int&)> callback) :
			intFeature(id, {}, callback) {
		}
		~intFeature() {
			abstractFeature::~abstractFeature();
		}
	public:
		void init() override {
			m_looped = false;
			push_value(m_value);
			abstractFeature::init();
		}
		void run() override {
			m_callback(this, m_value.i32);
			abstractFeature::run();
		}
	public:
		value m_value{};
	private:
		fnptr<void(intFeature*, int&)> m_callback{};
	};
	class toggleIntFeature : public abstractFeature {
	public:
		toggleIntFeature(std::string id, std::string name, std::string description, hotkey hotkey, fnptr<void(toggleIntFeature*, bool&, int&)> callback) :
			abstractFeature(id, name, description, hotkey, eFeatureType::ToggleIntFeature),
			m_callback(callback) {
		}
		toggleIntFeature(std::string id, std::string name, std::string description, fnptr<void(toggleIntFeature*, bool&, int&)> callback) :
			toggleIntFeature(id, name, description, {}, callback) {
		}
		toggleIntFeature(std::string id, std::string name, fnptr<void(toggleIntFeature*, bool&, int&)> callback) :
			toggleIntFeature(id, name, {}, callback) {
		}
		toggleIntFeature(std::string id, fnptr<void(toggleIntFeature*, bool&, int&)> callback) :
			toggleIntFeature(id, {}, callback) {
		}
		~toggleIntFeature() {
			abstractFeature::~abstractFeature();
		}
	public:
		void init() override {
			m_looped = true;
			push_value(m_toggleValue);
			push_value(m_numberValue);
			abstractFeature::init();
		}
		void run() override {
			if (m_hotkey.pressed()) {
				m_toggleValue.toggle ^= true;
			}
			m_callback(this, m_toggleValue.toggle, m_numberValue.i32);
			abstractFeature::run();
		}
	public:
		value m_toggleValue{};
		value m_numberValue{};
	private:
		fnptr<void(toggleIntFeature*, bool&, int&)> m_callback{};
	};
	class floatFeature : public abstractFeature {
	public:
		floatFeature(std::string id, std::string name, std::string description, hotkey hotkey, fnptr<void(floatFeature*, float&)> callback) :
			abstractFeature(id, name, description, hotkey, eFeatureType::FloatFeature),
			m_callback(callback) {
		}
		floatFeature(std::string id, std::string name, std::string description, fnptr<void(floatFeature*, float&)> callback) :
			floatFeature(id, name, description, {}, callback) {
		}
		floatFeature(std::string id, std::string name, fnptr<void(floatFeature*, float&)> callback) :
			floatFeature(id, name, {}, callback) {
		}
		floatFeature(std::string id, fnptr<void(floatFeature*, float&)> callback) :
			floatFeature(id, {}, callback) {
		}
		~floatFeature() {
			abstractFeature::~abstractFeature();
		}
	public:
		void init() override {
			m_looped = false;
			push_value(m_value);
			abstractFeature::init();
		}
		void run() override {
			m_callback(this, m_value.floating_point);
			abstractFeature::run();
		}
	public:
		value m_value{};
	private:
		fnptr<void(floatFeature*, float&)> m_callback{};
	};
	class toggleFloatFeature : public abstractFeature {
	public:
		toggleFloatFeature(std::string id, std::string name, std::string description, hotkey hotkey, fnptr<void(toggleFloatFeature*, bool&, float&)> callback) :
			abstractFeature(id, name, description, hotkey, eFeatureType::ToggleFloatFeature),
			m_callback(callback) {
		}
		toggleFloatFeature(std::string id, std::string name, std::string description, fnptr<void(toggleFloatFeature*, bool&, float&)> callback) :
			toggleFloatFeature(id, name, description, {}, callback) {
		}
		toggleFloatFeature(std::string id, std::string name, fnptr<void(toggleFloatFeature*, bool&, float&)> callback) :
			toggleFloatFeature(id, name, {}, callback) {
		}
		toggleFloatFeature(std::string id, fnptr<void(toggleFloatFeature*, bool&, float&)> callback) :
			toggleFloatFeature(id, {}, callback) {
		}
		~toggleFloatFeature() {
			abstractFeature::~abstractFeature();
		}
	public:
		void init() override {
			m_looped = true;
			push_value(m_toggleValue);
			push_value(m_numberValue);
			abstractFeature::init();
		}
		void run() override {
			if (m_hotkey.pressed()) {
				m_toggleValue.toggle ^= true;
			}
			m_callback(this, m_toggleValue.toggle, m_numberValue.floating_point);
			abstractFeature::run();
		}
	public:
		value m_toggleValue{};
		value m_numberValue{};
	private:
		fnptr<void(toggleFloatFeature*, bool&, float&)> m_callback{};
	};
	class actionFeature : public abstractFeature {
	public:
		actionFeature(std::string id, std::string name, std::string description, hotkey hotkey, fnptr<void(actionFeature*)> callback) :
			abstractFeature(id, name, description, hotkey, eFeatureType::ActionFeature),
			m_callback(callback) {
		}
		actionFeature(std::string id, std::string name, std::string description, fnptr<void(actionFeature*)> callback) :
			actionFeature(id, name, description, {}, callback) {
		}
		actionFeature(std::string id, std::string name, fnptr<void(actionFeature*)> callback) :
			actionFeature(id, name, {}, callback) {
		}
		actionFeature(std::string id, fnptr<void(actionFeature*)> callback) :
			actionFeature(id, {}, callback) {
		}
		~actionFeature() {
			abstractFeature::~abstractFeature();
		}
	public:
		void init() override {
			m_looped = false;
			abstractFeature::init();
		}
		void run() override {
			m_callback(this);
			abstractFeature::run();
		}
	private:
		fnptr<void(actionFeature*)> m_callback{};
	};
}