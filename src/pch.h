#ifndef PCH_H
#define PCH_H

#include "framework.h"
#pragma warning(disable : 4996)
extern bool g_running;
inline bool g_input_disabled{};
extern bool g_freemode_terminated;
extern std::uint64_t g_vehicle_info;
extern HWND g_window;
inline HMODULE g_module{};

inline static uint64_t g_timeout_fix_funcs[5];
struct join_timeout_fix_context {
    int32_t m_id;
    uint32_t m_script_hash;
    int m_retry_count;
};
inline std::vector<join_timeout_fix_context> g_join_timeout_fix;
inline 	std::pair<uint64_t, uint32_t> g_game_address;
//define namespaces
using namespace std::chrono;
using namespace std::chrono_literals;

//defines
using u64 = uint64_t;
using i64 = int64_t;
using u32 = uint32_t;
using i32 = int32_t;
using u16 = uint16_t;
using i16 = int16_t;
using u8 = uint8_t;
using i8 = int8_t;
using cc = const char;
using ccp = cc*;
using fp = float_t;
using db = double_t;

template <typename t>
	requires std::is_function_v<t>
using fnptr = std::add_pointer_t<t>;

template<typename T, int N>
constexpr int NUMOF(T(&)[N]) { return N; }

struct alignment_test {
    bool m_monitor;
    bool m_block;
    uint32_t m_thread_id;
};
inline std::unordered_map<std::string, alignment_test> g_alignment_tests;
inline std::unordered_map<uint64_t, std::pair<uint32_t, uint32_t>> g_raw_buffer_translations;
inline std::vector<std::pair<uint64_t, int>> g_return_address_node_iterations;

struct protectionContext {
    int m_var = 0;

    bool block() {
        return m_var == 2 || m_var == 3 || m_var == 5 || m_var == 7;
    }

    bool notify() {
        return m_var == 1 || m_var == 3 || m_var == 6 || m_var == 7;
    }

    bool redirect() {
        return m_var >= 4;
    }

    bool enabled() {
        return m_var > 0;
    }
};

namespace rage::types {
   
    struct memory_heap_pt {
        virtual ~memory_heap_pt();
        virtual void _0x1();
        virtual void _0x2();
        virtual void _0x3();
        virtual void _0x4();
        virtual void _0x5();
        virtual void _0x6();
        virtual void _0x7();
        virtual void _0x8();
        virtual void _0x9();
        virtual uint64_t allocate(uint32_t size);
    };

    struct guid_pool {
    public:
        char* m_data;
        int8_t* m_flags;
        uint32_t m_max;
        uint32_t m_size;
        uint32_t m_count;

        template<typename T>
        T* get(int index) {
            if (m_flags[index] < 0) return nullptr;
            return (T*)(m_data + (index * m_size));
        }
    };

    struct store_entry {
        uint32_t m_handle;
        uint32_t m_flag;
    };

    struct store_module {
        char _0x0000[0x8];
        uint32_t m_base_index;
        char _0x000C[0x2C];
        guid_pool m_pool;
    };

    struct store_module_manager {};

    struct store_manager {
        store_entry* m_entries;
        char _0x0008[0x1B0];
        store_module_manager m_module;
    };

}

namespace rage {



#pragma pack(push, 1)
    class hash_list
    {
    public:
        std::uint64_t* list; //0x0000
        std::int32_t capacity; //0x0008
        char pad_000C[4]; //0x000C
        std::int32_t free; //0x0010
        char pad_0014[4]; //0x0014
        std::uint64_t item_size; //0x0018
        char pad_0020[16]; //0x0020
        std::uint32_t* data; //0x0030
        char pad_0038[16]; //0x0038
        std::int32_t occupied; //0x0048
        const std::uint64_t get(std::int32_t index) const {
            if ((this->data[index >> 5] >> (index & 0x1F)) & 1)
                return this->list[index];
            return NULL;
        }
    }; // Size: 0x004C
#pragma pack(pop)

  
}

namespace rage {
    struct weapon_hash_list {
        uint64_t m_count;
        uint64_t m_list;
    };
}


namespace util {
    template<typename T>
    inline bool is_valid_ptr(T ptr) {
        uint64_t address = (uint64_t)ptr;
        if (address < 0x5000) return false;
        if ((address & 0xFFFFFFFF) == 0xFFFFFFFF) return false;
        if ((address & 0xFFFFFFFF) <= 0xFF) return false;

        if (*(uint8_t*)((uint64_t)&address + 6) != 0 || *(uint8_t*)((uint64_t)&address + 7) != 0) return false;

        return true;
    }
}



#endif 

