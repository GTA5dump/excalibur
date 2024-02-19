#pragma once
#include "joaat.h"

namespace rage
{
    class rlMetric
    {
    public:
        virtual ~rlMetric() = default;

        virtual int get_type() { return 0; }; 

        virtual int get_sub_type() { return 0; }; 

        virtual int _0x18() { return 0; };

        virtual const char* get_name() { return ""; };

        virtual bool serialize(void* serializer) { return false; };

        virtual int get_size() { return 0; };

        virtual joaat_t get_name_hash() { return 0; };
    };
};