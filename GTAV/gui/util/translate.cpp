#include "pch.h"
#include "translate.h"
#include "rage/classes/joaat.h"
#include "util/log.h"
#include "util/json.h"
#include "util/util.h"

namespace base {

	using jsonf = nlohmann::json;
	jsonf g_loader;

	void translation::enable() {
		translation::get()->m_translate = true;
	}

	void translation::disbale() {
		translation::get()->m_translate = false;
	}

	void translation::push(std::string string) {
		static bool saved_once;
		using jsonf = nlohmann::json;
		static jsonf save;
		auto cheat_path = std::filesystem::path(Util::GetDocumentsPath()).append("Excalibur").append("translation.json");
		std::ofstream file(cheat_path, std::ios::out | std::ios::trunc);

		save[string.c_str()]["Replacement"] = string.c_str();

		std::ofstream json_file(cheat_path);
		json_file << std::setw(4) << save << std::endl;
		json_file.close();
	}

	std::string translation::get(std::string string) {
		if (!translation::get()->m_translate) { // enable it to push stuff
			return string;
		}
		if (auto it = translation::get()->m_translation_table.find(rage::joaat(string));  it != translation::get()->m_translation_table.end()) {
			return &(it->second)[0];
		}
		else {
			translation::push(string); // pushes each string into the file we can send this file to resellers / chat gpt to translate it into diff lang, but we still need font support
			return string;
		}
	}

	void translation::load() {
		auto config_path = std::filesystem::path(Util::GetDocumentsPath()).append("Excalibur").append("translation.json");

		std::ifstream file(config_path);

		if (file.good()) {
			file >> g_loader;
		}
		else {
			return;
		}
		for (auto& item : g_loader.items()) {
			const std::string& key = item.key();
			try {
				std::string value = g_loader[key]["Replacement"];
				translation::get()->m_translation_table.insert({ rage::joaat(key), value });
			}
			catch (const std::exception& e) { // catch any exception derived from std::exception
				LOG(e.what());
			}
		}
	//	LOG("Found {} Saved Options", g_loader.size());
	}

	std::string trans(std::string string) {
		return translation::get(string);
	}
}