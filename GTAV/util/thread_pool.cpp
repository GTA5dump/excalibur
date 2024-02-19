#include "pch.h"
#include "thread_pool.h"

namespace util::threads {
	void threadPool::addJob(std::function<void(void*)> callback, void* argument) {
		struct thread_job {
			void* m_argument;
			std::function<void(void*)> m_callback;
		};

		thread_job* job = new thread_job();
		job->m_callback = callback;
		job->m_argument = argument;

		CreateThread(0, 0, [](void* argument) -> DWORD {
			thread_job* job = (thread_job*)argument;
			job->m_callback(job->m_argument);
			delete job;
			return 0;
			}, job, 0, 0);
	}

	void threadPool::addThread(const char* name, std::function<void(void*)> callback, void* argument) {
		threadContext* thread = new threadContext();
		thread->m_name = name;
		thread->m_callback = callback;
		thread->m_argument = argument;
		thread->m_running = true;

		thread->m_handle = CreateThread(0, 0, [](void* argument) -> DWORD {
			threadContext* thread = (threadContext*)argument;

			while (thread && g_running) {
				if (!thread->m_running) {
					break;
				}

				if (thread->m_callback) {
					thread->m_callback(thread->m_argument);
				}
			}

			if (thread) delete thread;
			return 0;
			}, thread, 0, 0);

		m_threads.push_back(thread);
	}

	void threadPool::removeThread(const char* name) {
		for (threadContext* thread : m_threads) {
			if (!strcmp(thread->m_name, name)) {
				thread->m_running = false;
			}
		}
	}

	void threadPool::Cleanup() {
		for (threadContext* thread : m_threads) {
			thread->m_running = false;
			TerminateThread(thread->m_handle, 0);
		}
	}

	threadPool* getThreadPool() {
		static threadPool instance;
		return &instance;
	}
}