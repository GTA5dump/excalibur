#include "pch.h"
#include "hooks/hooks.h"
#include "rage/classes/datBitBuffer.h"
#include "util/caller.h"
#include "menu/submenus/main/network/players/network_player_removals.h"
namespace base{

	bool hooks::read_unsigned_int_from_buffer(rage::datBitBufferSyncInstance* _this, uint32_t* output, int count) {
		if (_this->m_buffer->m_bitOffset == 1234) return false;

		bool _return = read_unsigned_int_from_buffer_t(_this, output, count);
		if (!_return) {
			for (auto& [name, alignment] : g_alignment_tests) {
				if (alignment.m_monitor) {
					if (alignment.m_thread_id == GetCurrentThreadId()) {
						alignment.m_block = true;
					}
				}
			}

			LOG_ERROR("[%s] failed! %s", __FUNCTION__);
			_this->m_buffer->m_bitOffset = 1234;
			return false;
		}

		uint64_t return_address = (uint64_t)_ReturnAddress();
		for (auto& [address, count] : g_return_address_node_iterations) {
			if (return_address == address) {
				if (*output > (uint32_t)count) {
					for (auto& [name, alignment] : g_alignment_tests) {
						if (alignment.m_monitor) {
							if (alignment.m_thread_id == GetCurrentThreadId()) {
								alignment.m_block = true;
							}
						}
					}

					*output = 0;
					LOG_ERROR("[%s] iteration failed! %s", __FUNCTION__);
					_this->m_buffer->m_bitOffset = 1234;
					return false;
				}
			}
		}

		return _return;
	}

	bool hooks::read_unsigned_short_from_buffer(rage::datBitBufferSyncInstance* _this, uint16_t* output, int count) {
		if (_this->m_buffer->m_bitOffset == 1234) return false;

		bool _return = read_unsigned_short_from_buffer_t(_this, output, count);
		if (!_return) {
			for (auto& [name, alignment] : g_alignment_tests) {
				if (alignment.m_monitor) {
					if (alignment.m_thread_id == GetCurrentThreadId()) {
						alignment.m_block = true;
					}
				}
			}

			LOG_ERROR("[%s] failed! %s", __FUNCTION__);
			_this->m_buffer->m_bitOffset = 1234;
			return false;
		}

		return _return;
	}

	bool hooks::read_unsigned_char_from_buffer(rage::datBitBufferSyncInstance* _this, uint8_t* output, int count) {
		if (_this->m_buffer->m_bitOffset == 1234) return false;

		bool _return = read_unsigned_char_from_buffer_t(_this, output, count);
		if (!_return) {
			for (auto& [name, alignment] : g_alignment_tests) {
				if (alignment.m_monitor) {
					if (alignment.m_thread_id == GetCurrentThreadId()) {
						alignment.m_block = true;
					}
				}
			}

			LOG_ERROR("[%s] failed! %s", __FUNCTION__);
			_this->m_buffer->m_bitOffset = 1234;
			return false;
		}

		return _return;
	}

	bool hooks::read_int_from_buffer(rage::datBitBufferSyncInstance* _this, int* output, int count) {
		if (_this->m_buffer->m_bitOffset == 1234) return false;

		bool _return = read_int_from_buffer_t(_this, output, count);
		if (!_return) {
			for (auto& [name, alignment] : g_alignment_tests) {
				if (alignment.m_monitor) {
					if (alignment.m_thread_id == GetCurrentThreadId()) {
						alignment.m_block = true;
					}
				}
			}

			LOG_ERROR("[%s] failed! %s", __FUNCTION__);
			_this->m_buffer->m_bitOffset = 1234;
			return false;
		}

		return _return;
	}

	bool hooks::read_short_from_buffer(rage::datBitBufferSyncInstance* _this, short* output, int count) {
		if (_this->m_buffer->m_bitOffset == 1234) return false;

		bool _return = read_short_from_buffer_t(_this, output, count);
		if (!_return) {
			for (auto& [name, alignment] : g_alignment_tests) {
				if (alignment.m_monitor) {
					if (alignment.m_thread_id == GetCurrentThreadId()) {
						alignment.m_block = true;
					}
				}
			}

			LOG_ERROR("[%s] failed! %s", __FUNCTION__);
			_this->m_buffer->m_bitOffset = 1234;
			return false;
		}

		return _return;
	}

	bool hooks::read_char_from_buffer(rage::datBitBufferSyncInstance* _this, char* output, int count) {
		if (_this->m_buffer->m_bitOffset == 1234) return false;

		bool _return = read_char_from_buffer_t(_this, output, count);
		if (!_return) {
			for (auto& [name, alignment] : g_alignment_tests) {
				if (alignment.m_monitor) {
					if (alignment.m_thread_id == GetCurrentThreadId()) {
						alignment.m_block = true;
					}
				}
			}

			LOG_ERROR("[%s] failed! %s", __FUNCTION__);
			_this->m_buffer->m_bitOffset = 1234;
			return false;
		}

		return _return;
	}

	bool hooks::read_bool_from_buffer(rage::datBitBufferSyncInstance* _this, bool* output) {
		if (_this->m_buffer->m_bitOffset == 1234) return false;

		bool _return = read_bool_from_buffer_t(_this, output);
		if (!_return) {
			for (auto& [name, alignment] : g_alignment_tests) {
				if (alignment.m_monitor) {
					if (alignment.m_thread_id == GetCurrentThreadId()) {
						alignment.m_block = true;
					}
				}
			}

			LOG_ERROR("[%s] failed! %s", __FUNCTION__);
			_this->m_buffer->m_bitOffset = 1234;
			return false;
		}

		return _return;
	}

	bool hooks::read_long_long_from_buffer(rage::datBitBufferSyncInstance* _this, long long* output, int count) {
		if (_this->m_buffer->m_bitOffset == 1234) return false;

		bool _return = read_long_long_from_buffer_t(_this, output, count);
		if (!_return) {
			for (auto& [name, alignment] : g_alignment_tests) {
				if (alignment.m_monitor) {
					if (alignment.m_thread_id == GetCurrentThreadId()) {
						alignment.m_block = true;
					}
				}
			}

			LOG_ERROR("[%s] failed! %s", __FUNCTION__);
			_this->m_buffer->m_bitOffset = 1234;
			return false;
		}

		return _return;
	}

	bool hooks::read_unsigned_long_long_from_buffer(rage::datBitBufferSyncInstance* _this, uint64_t* output, int count) {
		if (_this->m_buffer->m_bitOffset == 1234) return false;

		bool _return = read_unsigned_long_long_from_buffer_t(_this, output, count);
		if (!_return) {
			for (auto& [name, alignment] : g_alignment_tests) {
				if (alignment.m_monitor) {
					if (alignment.m_thread_id == GetCurrentThreadId()) {
						alignment.m_block = true;
					}
				}
			}

			LOG_ERROR("[%s] failed! %s", __FUNCTION__);
			_this->m_buffer->m_bitOffset = 1234;
			return false;
		}

		return _return;
	}

	bool hooks::read_float_from_buffer(rage::datBitBufferSyncInstance* _this, float* output, float mod, int count) {
		if (_this->m_buffer->m_bitOffset == 1234) return false;

		bool _return = read_float_from_buffer_t(_this, output, mod, count);
		if (!_return) {
			for (auto& [name, alignment] : g_alignment_tests) {
				if (alignment.m_monitor) {
					if (alignment.m_thread_id == GetCurrentThreadId()) {
						alignment.m_block = true;
					}
				}
			}

			LOG_ERROR("[%s] failed! %s", __FUNCTION__);
			_this->m_buffer->m_bitOffset = 1234;
			return false;
		}

		return _return;
	}

	bool hooks::read_unsigned_float_from_buffer(rage::datBitBufferSyncInstance* _this, float* output, float mod, int count) {
		if (_this->m_buffer->m_bitOffset == 1234) return false;

		bool _return = read_unsigned_float_from_buffer_t(_this, output, mod, count);
		if (!_return) {
			for (auto& [name, alignment] : g_alignment_tests) {
				if (alignment.m_monitor) {
					if (alignment.m_thread_id == GetCurrentThreadId()) {
						alignment.m_block = true;
					}
				}
			}

			LOG_ERROR("[%s] failed! %s", __FUNCTION__);
			_this->m_buffer->m_bitOffset = 1234;
			return false;
		}

		return _return;
	}

	bool hooks::read_network_id_from_buffer(rage::datBitBufferSyncInstance* _this, short* output) {
		if (_this->m_buffer->m_bitOffset == 1234) return false;

		bool _return = read_network_id_from_buffer_t(_this, output);
		if (!_return) {
			for (auto& [name, alignment] : g_alignment_tests) {
				if (alignment.m_monitor) {
					if (alignment.m_thread_id == GetCurrentThreadId()) {
						alignment.m_block = true;
					}
				}
			}

			LOG_ERROR("[%s] failed! %s", __FUNCTION__);
			_this->m_buffer->m_bitOffset = 1234;
			return false;
		}

		return _return;
	}

	bool hooks::read_array_from_buffer(rage::datBitBufferSyncInstance* _this, int* output, int count, int unk) {
		if (_this->m_buffer->m_bitOffset == 1234) return false;

		bool _return = read_array_from_buffer_t(_this, output, count, unk);
		if (!_return) {
			for (auto& [name, alignment] : g_alignment_tests) {
				if (alignment.m_monitor) {
					if (alignment.m_thread_id == GetCurrentThreadId()) {
						alignment.m_block = true;
					}
				}
			}

			LOG_ERROR("[%s] failed! %s", __FUNCTION__);
			_this->m_buffer->m_bitOffset = 1234;
			return false;
		}

		return _return;
	}

	bool hooks::read_string_from_buffer(rage::datBitBufferSyncInstance* _this, char* output, int length) {
		if (_this->m_buffer->m_bitOffset == 1234) return false;

		bool _return = read_string_from_buffer_t(_this, output, length);
		if (!_return) {
			for (auto& [name, alignment] : g_alignment_tests) {
				if (alignment.m_monitor) {
					if (alignment.m_thread_id == GetCurrentThreadId()) {
						alignment.m_block = true;
					}
				}
			}

			LOG_ERROR("[%s] failed! %s", __FUNCTION__);
			_this->m_buffer->m_bitOffset = 1234;
			return false;
		}

		return _return;
	}


	bool hooks::read_bitbuf_dword(rage::datBitBuffer* buffer, PVOID read, int bits) {
		__try {
			return read_bitbuf_dword_t(buffer, read, bits);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			LOG_ERROR("BUFFER OVERFLOW DWORD");
			return false;
		}

	}

	bool hooks::read_bitbuf_string(rage::datBitBuffer* buffer, char* read, int bits) {
		__try {
			return read_bitbuf_string_t(buffer, read, bits);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			LOG_ERROR("BUFFER OVERFLOW STRING");
			return false;
		}
	}

	bool hooks::read_bitbuf_bool(rage::datBitBuffer* buffer, bool* read, int bits) {
		__try {
			return read_bitbuf_bool_t(buffer, read, bits);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			LOG_ERROR("BUFFER OVERFLOW BOOL");
			return false;
		}
	}

	bool hooks::read_bitbuf_array(rage::datBitBuffer* buffer, PVOID read, int bits, int unk) {
		__try {
			return read_bitbuf_array_t(buffer, read, bits, unk);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			LOG_ERROR("BUFFER OVERFLOW ARRAY");
			return false;
		}
	}



	
}