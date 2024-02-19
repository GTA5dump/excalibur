#include "pch.h"
#include "invoker.h"
#include "crossmap.h"

#include "util/log.h"
#include "hooks/patterns.h"
#include "spoof_call.h"
namespace invoker
{
    void invoker::cache_handlers_impl()
    {
        if (auto regTbl = patterns::native_registration_table; regTbl) {
            for (auto& entry : g_crossmap) {
                m_handler_cache.emplace(entry.hash, regTbl->get_handler(entry.translated_hash));
            }
        }

        m_handlers_cached = true;
    }

    void invoker::begin_call_impl()
    {
        m_call_context.reset();
    }

    void invoker::end_call_impl(rage::scrNativeHash hash)
    {
        if (auto val = m_handler_cache.find(hash); val != m_handler_cache.end()) {
            if (!val->second) {
            }
            spoof_call(patterns::jmp_rbx_register, val->second, dynamic_cast<rage::scrNativeCallContext*>(&m_call_context));
            patterns::fix_vectors(&m_call_context);
          //  m_call_context.VectorSpace.CopyReferencedParametersOut();
 
        }
        else
        {
            [hash]() { LOG_WARN(std::format("[Ntve] Failed to Invoke: 0x{:X}", hash).c_str()); }();
        }
    }
}