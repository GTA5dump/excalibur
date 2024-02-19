#include "pch.h"
#include "log.h"
#include "Util.h"
#include "util/fiber.h"
namespace util::log {

	void log::Load() {
		AllocConsole();
		SetConsoleTitleA("Excalibur | 1.2.0");

		FILE* stream;
		freopen_s(&stream, "CONOUT$", "w", stdout);

		m_console.open("CONOUT$");
		SetConsoleMode(GetStdHandle(-11), ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

		m_path.append(Util::GetDocumentsPath());
		m_path.append("Excalibur");

		if (!std::filesystem::exists(m_path)) {
			std::filesystem::create_directory(m_path);
		}
		m_path.append("log.txt");

		m_file.open(m_path, std::ios_base::out | std::ios_base::trunc);
		m_file.clear();
	}

	void log::Cleanup() {
		LOG("Goodbye <3");
		util::fiber::sleep(5000);
		fclose(stdout);
		FreeConsole();
		m_console.clear();
		m_path.clear();
		m_console.close();
		m_file.close();
	}

	void set_color(int color) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
	}

	void log::Log(int color, const char* type, const char* message, ...) {
		va_list args;
		va_start(args, message);

		std::size_t log_size = std::vsnprintf(nullptr, 0, message, args) + 1;
		auto buffer = std::make_unique<char[]>(log_size);

		std::uninitialized_fill_n(buffer.get(), log_size, '\0');
		std::vsnprintf(buffer.get(), log_size, message, args);

		va_end(args);

		auto time = std::time(nullptr);
		auto tm = std::localtime(&time);

		char tag[64] = {};
		snprintf(tag, sizeof(tag) - 1, "[%s] ", type);

		std::cout << background_color::code2(color) << " " << background_color::Default << forgound_color::Code(color) << " " << tag << buffer.get() << std::endl;

		m_file << tag << buffer.get() << std::endl;
		//m_console << forgound_color::Code(color) << tag << buffer.get() << std::endl;
	}
}