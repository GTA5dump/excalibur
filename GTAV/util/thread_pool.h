#pragma once
#include "pch.h"
#include <functional>

namespace util::threads {
	struct threadContext {
		const char* m_name = "";
		HANDLE m_handle = 0;
		bool m_running = true;
		void* m_argument = nullptr;
		std::function<void(void*)> m_callback = {};
	};

	class threadPool {
	public:
		void addJob(std::function<void(void*)> callback, void* argument = nullptr);
		void addThread(const char* name, std::function<void(void*)> callback, void* argument = nullptr);
		void removeThread(const char* name);
		void Cleanup();
	private:
		std::vector<threadContext*> m_threads;
	};

	threadPool* getThreadPool();
}