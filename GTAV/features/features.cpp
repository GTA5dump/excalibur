#include "pch.h"
#include "features.h"
#include "features/manager/manager.h"
#include "rage/invoker/natives.h"
#include "util/fiber.h"
#include "menu/util/script_patcher_service.h"
#include "hooks/patterns.h"
namespace features {
	void run() {
		

		while (true) {
			util::fiber::go_to_main();
		}
	}
}