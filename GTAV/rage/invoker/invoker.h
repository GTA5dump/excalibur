#pragma once
#include "pch.h"
#include "rage/classes/scrNativeCallContext.h"
#include "rage/classes/scrNativeRegistrationTable.h"
namespace invoker
{
    class invoker
    {
    public:
        invoker() = default;

    public:
        ~invoker() = default;

        static void cache_handlers()
        {
            get_instance().cache_handlers_impl();
        }

        static bool handlers_cached()
        {
            return get_instance().m_handlers_cached;
        }

        static void begin_call()
        {
            get_instance().begin_call_impl();
        }

        template<typename Args>
        static void push_arg(Args&& arg)
        {
            get_instance().m_call_context.push_arg(std::forward<Args>(arg));
        }

        static void end_call(rage::scrNativeHash hash)
        {
            get_instance().end_call_impl(hash);
        }

        template<typename T>
        static T& get_return_value()
        {
            return *get_instance().m_call_context.get_return_value<T>();
        }

        std::unordered_map<rage::scrNativeHash, rage::scrCmd> get_cache() { return m_handler_cache; }
       

    private:
        void cache_handlers_impl();

        void begin_call_impl();
        void end_call_impl(rage::scrNativeHash hash);

        static invoker& get_instance()
        {
            static invoker i{};

            return i;
        }

    private:
        struct native_context : public rage::scrNativeCallContext {
        public:
            native_context() {
                reset();
            }
        public:
            void reset() {
                Return = &m_ret_data[0];
                ArgCount = 0;
                Args = &m_arg_data[0];
                VectorSpace = rage::scrVectorSpace();
                memset(&m_ret_data, NULL, sizeof(m_ret_data));
                memset(&m_arg_data, NULL, sizeof(m_arg_data));
            }
        public:
            template <typename type>
            void push(type value) {
                static_assert(sizeof(type) <= 8);
                rage::scrValue data;
                *(type*)(&data) = value;
                m_arg_data[ArgCount++] = data;
            }
            template <>
            void push<Vector3>(Vector3 value) {
                push(value.x);
                push(value.y);
                push(value.z);
            }
        public:
            template <typename t>
            t get_return_val() {
                return *reinterpret_cast<t*>((uint64_t)Return);
            }
            template <>
            void get_return_val<void>() {
            }
        public:
            rage::scrValue m_ret_data[10]{};
            rage::scrValue m_arg_data[100]{};
        };
    private:
        native_context m_call_context;
        std::unordered_map<rage::scrNativeHash, rage::scrCmd> m_handler_cache;
        bool m_handlers_cached = false;
    };

    static invoker* getInvoker() {
        static invoker instance; 
        return &instance;
    }
}