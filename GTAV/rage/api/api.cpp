#include "pch.h"
#include "api.h"
#include "util/fiber.h"
#include "util/fiber_pool.h"
#include "util/json.h"
#include "util/log.h"
#include "util/util.h"
#include "rage/invoker/natives.h"
#include "security/xor.h"
#include "hooks/patterns.h"
#include <fstream>



namespace rage::api {
	void social_club::update() {
		if (m_clear_queue) {
			m_clear_queue = false;
			m_queue.clear();
			return;
		}

		if (!m_queue.empty()) {
			queue_item& item = m_queue.front();
			LOG("URL: %s", item.m_endpoint.c_str());

			struct curl_slist* headers = nullptr;
			std::string userAgent = Util::create_random_string(10);
			headers = curl_slist_append(headers, ("User-Agent: " + userAgent).c_str());
			headers = curl_slist_append(headers, "X-Requested-With: XMLHttpRequest");
			headers = curl_slist_append(headers, ("Authorization: SCAUTH val=\"" + std::string(patterns::sc_info->m_ticket) + "\"").c_str());
			headers = curl_slist_append(headers, "Content-Type: application/json; charset=utf-8");
			headers = curl_slist_append(headers, ("Content-Length: " + std::to_string(item.m_data.size())).c_str());

			CURL* curl = curl_easy_init();
			if (curl) {
				curl_easy_setopt(curl, CURLOPT_URL, item.m_endpoint.c_str());
				curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, item.m_data.c_str());
				curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, item.m_data.size());

				CURLcode code = curl_easy_perform(curl);
				if (code == CURLE_OK) {
					if (item.m_callback) {
						item.m_callback(nullptr, item.m_custom);
					}
					else {
						LOG("No callback!");
					}
				}
				else {
					LOG("CURL Error: %i", code);
				}

				curl_slist_free_all(headers);
				curl_easy_cleanup(curl);
			}

			m_queue.erase(m_queue.begin());

			Sleep(1000);
		}
		else {
			LOG("QUEUE EMPTY");
		}
	}

	void social_club::send(std::string endpoint, std::string data, std::function<void(const char*, void*)> callback, void* custom_data) {
		LOG("Adding request to api pool...");
		m_queue.push_back({ endpoint, data, callback, custom_data, 0 });
	}

	void social_club::get_profiles_from_rid(uint64_t rockstar_id, std::function<void(bool, std::vector<rockstar_account>, void*)> callback, void* custom_data) {
		if (rockstar_id < 0x1000) {
			util::fiber::pool::add([=] {
				callback(false, {}, custom_data);
				});

			return;
		}

		send("https://scui.rockstargames.com/api/friend/getprofile",
			nlohmann::json({ { "RockstarId", rockstar_id } }).dump(), [=](const char* jresponse, void* data) {
				if (!nlohmann::json::accept(jresponse)) {
					LOG("BAD JSON");
					util::fiber::pool::add([=] {
						callback(false, {}, data);
						});

					return;
				}

				try {
					nlohmann::json json = nlohmann::json::parse(jresponse);
					if ((json["Status"].is_null() || !json["Status"].get<bool>()) || (json["Accounts"].is_null() || json["Accounts"].get<nlohmann::json::array_t>().size() == 0)) {
						LOG("BAD STATUS");

						util::fiber::pool::add([=] {
							callback(false, {}, data);
							});

						return;
					}

					std::vector<rockstar_account> accounts;

					int total = json["Total"].is_null() ? 1 : json["Total"].get<int>();
					for (int i = 0; i < total; i++) {
						accounts.push_back({ json["Accounts"][i]["RockstarAccount"]["Name"], json["Accounts"][i]["RockstarAccount"]["RockstarId"] });
					}

					util::fiber::pool::add([=] {
						callback(true, accounts, data);
						});
				}
				catch (std::exception& e) {
					LOG_WARN("[Json] %s", e.what());

					util::fiber::pool::add([=] {
						callback(false, {}, data);
						});
				}
			}, custom_data);
	}

	void social_club::get_profiles_from_name(std::string name, std::function<void(bool, std::vector<rockstar_account>, result_info*)> callback, void* custom_data, int page_offset) {
		send("https://scui.rockstargames.com/api/friend/accountsearch",
			nlohmann::json({
				{ "env", "prod" },
				{ "title", "gta5" },
				{ "version", 11 },
				{ "searchNickname", name },
				{ "pageIndex", page_offset }
				}).dump(), [=](const char* jresponse, void* data) {
					if (!nlohmann::json::accept(jresponse)) {
						util::fiber::pool::add([=] {
							callback(false, {}, nullptr);
							});

						return;
					}

					try {
						nlohmann::json json = nlohmann::json::parse(jresponse);
						if ((json["Status"].is_null() || !json["Status"].get<bool>()) || (json["Accounts"].is_null() || json["Accounts"].get<nlohmann::json::array_t>().size() == 0)) {
							util::fiber::pool::add([=] {
								callback(false, {}, nullptr);
								});

							return;
						}

						std::vector<rockstar_account> accounts;

						for (nlohmann::json& account : json["Accounts"]) {
							accounts.push_back({ account["Nickname"], account["RockstarId"] });
						}

						result_info* out_info = new result_info();
						out_info->m_next_offset = json["NextOffset"];
						out_info->m_total = json["Total"];

						util::fiber::pool::add([=] {
							callback(true, accounts, out_info);
							});
					}
					catch (std::exception& e) {
						LOG_WARN("[Json] %s", e.what());

						util::fiber::pool::add([=] {
							callback(false, {}, nullptr);
							});
					}
			}, custom_data);
	}

	social_club* get_social_club() {
		static social_club instance;
		return &instance;
	}
}