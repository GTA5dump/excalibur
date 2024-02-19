#include "pch.h"
#include "util/log.h"
#include "pattern.h"
namespace memory {
	void batch::Add(std::pair<const char*, pattern> entry, std::function<void(Ptr)> callback, bool& out) {
		m_entries.emplace_back(entry.first, std::move(entry.second), std::move(callback), std::move(out));
	}
	std::string bytesToString(const std::vector<std::optional<std::uint8_t>>& m_bytes) {
		std::ostringstream oss;
		for (const auto& byte : m_bytes) {
			if (byte.has_value()) {
				oss << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(*byte);
			}
		}
		return oss.str();
	}
	void batch::run(range region) {
		bool all_found = true;
		for (auto& entry : m_entries) {
			if (auto result = region.scan(entry.m_pattern)) {
				if (entry.m_callback) {
					std::invoke(std::move(entry.m_callback), result);

					if (entry.m_out) {
						LOG_CUSTOM_SUCCESS("Found", "%s", entry.m_name.c_str());
					}

				}
				else {
					entry.m_out = false;
					all_found = false;
					LOG_ERROR(std::format(("Failed To Find {}"), entry.m_name).c_str());
				}
			}
			else {
				entry.m_out = false;
				all_found = false;
				LOG_ERROR(std::format(("Failed To Find {}"), entry.m_name).c_str());
			}
		}

		m_entries.clear();
		if (!all_found) {
			throw std::runtime_error("Failed to find some patterns.");
		}
	}
}