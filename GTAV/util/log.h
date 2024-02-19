#pragma once

#define LOG(fmt, ...) util::log::Log(util::log::forgound_color::Code::Generic, "Inf", fmt, ##__VA_ARGS__);
#define LOG_WARN(fmt, ...) util::log::Log(util::log::forgound_color::Code::Developer, "Wrn", fmt, ##__VA_ARGS__);
#define LOG_ERROR(fmt, ...) util::log::Log(util::log::forgound_color::Code::Error, "Err", fmt, ##__VA_ARGS__);
#define LOG_SUCCESS(fmt, ...) util::log::Log(util::log::forgound_color::Code::Success, "Suc", fmt, ##__VA_ARGS__);

#define LOG_CUSTOM(tag, fmt, ...) util::log::Log(util::log::forgound_color::Code::Generic, tag, fmt, ##__VA_ARGS__);
#define LOG_CUSTOM_WARN(tag, fmt, ...) util::log::Log(util::log::forgound_color::Code::Warning, tag, fmt, ##__VA_ARGS__);
#define LOG_CUSTOM_ERROR(tag, fmt, ...) util::log::Log(util::log::forgound_color::Code::Error, tag, fmt, ##__VA_ARGS__);
#define LOG_CUSTOM_SUCCESS(tag, fmt, ...) util::log::Log(util::log::forgound_color::Code::Success, tag, fmt, ##__VA_ARGS__);

namespace util::log {
	namespace foreground {
		enum {
			BLACK = 0,
			DARKBLUE = FOREGROUND_BLUE,
			DARKGREEN = FOREGROUND_GREEN,
			DARKCYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
			DARKRED = FOREGROUND_RED,
			DARKMAGENTA = FOREGROUND_RED | FOREGROUND_BLUE,
			DARKYELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
			DARKGRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
			GRAY = FOREGROUND_INTENSITY,
			BLUE = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
			GREEN = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
			CYAN = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
			RED = FOREGROUND_INTENSITY | FOREGROUND_RED,
			MAGENTA = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
			YELLOW = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
			WHITE = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		};
	};

	namespace background {
		enum {
			BLACK = 0,
			DARKBLUE = BACKGROUND_BLUE,
			DARKGREEN = BACKGROUND_GREEN,
			DARKCYAN = BACKGROUND_GREEN | BACKGROUND_BLUE,
			DARKRED = BACKGROUND_RED,
			DARKMAGENTA = BACKGROUND_RED | BACKGROUND_BLUE,
			DARKYELLOW = BACKGROUND_RED | BACKGROUND_GREEN,
			DARKGRAY = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
			GRAY = BACKGROUND_INTENSITY,
			BLUE = BACKGROUND_INTENSITY | BACKGROUND_BLUE,
			GREEN = BACKGROUND_INTENSITY | BACKGROUND_GREEN,
			CYAN = BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE,
			RED = BACKGROUND_INTENSITY | BACKGROUND_RED,
			MAGENTA = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
			YELLOW = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
			WHITE = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
		};
	};

	namespace forgound_color
	{
		enum Code
		{
			Default = 0,
			Generic = 243,
			Success = 84,
			Error = 196,
			Warning = 3,
			Developer = 26,
		};

		inline std::ostream& operator<<(std::ostream& os, Code code)
		{
			return os << "\033[38;5;" << static_cast<int>(code) << "m";
		}
	}

	namespace background_color
	{
		enum code2
		{
			Default = 0,
			Generic = 243,
			Success = 84,
			Error = 196,
			Warning = 3,
			Developer = 26,
		};

		inline std::ostream& operator<<(std::ostream& os, code2 code)
		{
			return os << "\033[48;5;" << static_cast<int>(code) << "m";
		}
	}

	void Load();
	void Log(int color, const char* type, const char* message, ...);
	void Cleanup();

	inline std::filesystem::path m_path{};
	inline std::filesystem::path m_backup_path{};
	inline std::ofstream m_file{};
	inline std::ofstream m_console{};
}