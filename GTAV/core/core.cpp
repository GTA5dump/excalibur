#include "pch.h"
#include "core.h"
#include "util/thread_pool.h"
#include "util/Log.h"
#include "hooks/hooks.h"
#include "util/hooking/hooking.h"
#include "features/manager/manager.h"
#include "hooks/patterns.h"
#include "rage/invoker/invoker.h"
#include "exception.h"
#include "rage/invoker/natives.h"
#include "util/hooking/script.h"
#include "util/fiber.h"
#include "util/dirs.h"
#include "gui/d3d.h"
#include "gui/util/translate.h"
#include "gui/util/notify.h"
#include "memory/pattern.h"
#include "gui/util/translate.h"
#include "rage/api/api.h"
#include "menu/util/script_patcher_service.h"
#include "features/features.h"
#include "security/security.h"
#include "auth/auth.h"
#include "auth/vars.h"
#include "security/themdia/secure_engine.h"
#include "util/util.h"
#include "menu/util/matchmaking_service.h"
namespace base::core {


	DWORD WINAPI unload(LPVOID handle) {
		g_alignment_tests.clear();
		hooking::cleanup();
		hooking::getVmt()->remove_vmt();
		util::threads::getThreadPool()->Cleanup();
		util::fiber::cleanup();
		features::g_manager.clear();
		exceptions::uninitExceptionHandler();
		util::log::Cleanup();

		FreeLibraryAndExitThread(static_cast<HMODULE>(handle), 0);
	}

	void download_files() {
		std::string MenuFolderPath = Util::GetDocumentsPath() + "\\Excalibur\\textures\\";
//exmaple		auth::download(XOR("https://color.png"), MenuFolderPath + "color.png");
	}


	DWORD WINAPI load(LPVOID handle) {

		util::log::Load();
		exceptions::initExceptionHandler();

		if (!util::dirs::load()) {
			unload(handle);
		}


		LOG(XOR("Welcome to Excalibur Beta"));

		if (!(g_window = FindWindowA(("grcWindow"), NULL))) {
			int timeout = 0;
			while (!g_window) {
				if (timeout >= 20) {
					LOG_ERROR(XOR("Failed to find game window"));
					unload(handle);
					return 0;
				}

				g_window = FindWindowA(XOR("grcWindow"), NULL);
				timeout++;
				Sleep(1000);
			}
		}

		if (!base::hooks::patterns()) {
			LOG_WARN(XOR("Failed to load patterns, unloading..."));
			std::this_thread::sleep_for(6s);
			unload(handle);
		}

		if (!base::hooks::bypass()) {
			LOG_WARN(XOR("Failed to load bypasses, unloading..."));
			std::this_thread::sleep_for(6s);
			unload(handle);
		}


		while (*patterns::game_state != 0) {
			std::this_thread::sleep_for(3s);
			std::this_thread::yield();
		}


		if (!invoker::invoker::handlers_cached()) {
			invoker::invoker::cache_handlers();
		}

		d3d::initialize();

		auto matchmaing_service = std::make_unique<menu::matchmaking_service>();

		if (!base::hooks::hooks()) {
			LOG_WARN(XOR("Failed to load hooks, unloading..."));
			std::this_thread::sleep_for(6s);
			unload(handle);
		}

		auto script_hooks = std::make_unique<script::native_hooks>();



		g_running = true;


		translation::get()->load();

		while (g_running) {

			if (GetAsyncKeyState(VK_END)) {
				g_running = false;
			}
		}

		matchmaing_service.reset();
		script_hooks.reset();
		unload(handle);

	}
}