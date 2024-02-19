#pragma once
#include <cstdint>
#include <d3d11.h>
#include "grcLockedTexture.h"
#include "gui/d3d.h"

namespace rage {
    struct grcTextureStored {
        char* m_name;
        ID3D11Resource* m_texture;
        ID3D11ShaderResourceView* m_shader;
        uint16_t m_width;
        uint16_t m_height;
        uint16_t m_depth;
    };
    class grcTexture {
    public:
        virtual ~grcTexture() = NULL;
        virtual bool unk_0008() = NULL;
        virtual int unk_0010() = NULL;
        virtual void unk_0018() = NULL;
        virtual int unk_0020() = NULL;
        virtual uint16_t GetWidth() = NULL;
        virtual uint16_t GetHeight() = NULL;
        virtual uint16_t GetDepth() = NULL;
        virtual uint8_t GetLevels() = NULL;
        virtual void unk_0048() = NULL;
        virtual bool unk_0050() = NULL;
        virtual void unk_0058(int64_t) = NULL;
        virtual void unk_0060(void*) = NULL;
        virtual void unk_0068(void*) = NULL;
        virtual void unk_0070() = NULL;
        virtual rage::grcTexture* unk_0078() = NULL;
        virtual rage::grcTexture* unk_0080() = NULL;
        virtual bool unk_0088() = NULL;
        virtual int unk_0090() = NULL;
        virtual int unk_0098() = NULL;
        virtual int unk_00A0() = NULL;
        virtual int unk_00A8() = NULL;
        virtual int unk_00B0() = NULL;
        virtual int unk_00B8() = NULL;
        virtual int unk_00C0() = NULL;
        virtual bool Map(int numSubLevels, int subLevel, grcLockedTexture* lockedTexture, grcLockFlags flags) = NULL;

        char pad_0008[32]; //0x0008
        char* m_name; //0x0028
        uint16_t m_ref_count; //0x0030
        uint8_t m_resource_type; //0x0032
        uint8_t m_layers; //0x0033
        char pad_0034[4]; //0x0034
        ID3D11Resource* m_texture; //0x0038
        uint32_t m_physical_size; //0x0040
        uint32_t m_handle; //0x0044
        uint32_t m_flags; //0x0048
        char pad_004C[4]; //0x004C
        uint16_t m_width; //0x0050
        uint16_t m_height; //0x0052
        uint16_t m_depth; //0x0054
        uint16_t m_mip_stride; //0x0056
        uint32_t m_format; //0x0058
        uint8_t m_image_type; //0x005C
        uint8_t m_mip_count; //0x005D
        uint8_t m_cut_mip_levels; //0x005E
        bool m_is_srgb; //0x005F
        grcTexture* m_previous; //0x0060
        grcTexture* m_next; //0x0068
        void* m_backing; //0x0070
        ID3D11ShaderResourceView* m_shader; //0x0078
        char pad_0080[32]; //0x0080
    public:
        void Set(std::string file, std::pair<shader_data, vec2> data) {
            m_name = new char[file.length() + 1];
            strcpy(m_name, file.c_str());
            m_texture = data.first.resource;
            m_shader = data.first.resource_view;
            m_width = data.second.x.u16;
            m_height = data.second.y.u16;
            m_depth = 1;
        }
        void Swap(grcTexture* texure, bool retainOrginialSizes = false) {
            m_texture = texure->m_texture;
            m_shader = texure->m_shader;
            if (!retainOrginialSizes) {
                m_width = texure->m_width;
                m_height = texure->m_height;
                m_depth = texure->m_depth;
            }
        }
        void Swap(grcTextureStored texure, bool retainOrginialSizes = false) {
            m_texture = texure.m_texture;
            m_shader = texure.m_shader;
            m_width = texure.m_width;
            m_height = texure.m_height;
            m_depth = texure.m_depth;
        }
        grcTextureStored CreateCopy() {
            grcTextureStored data{};
            data.m_name = m_name;
            data.m_texture = m_texture;
            data.m_shader = m_shader;
            data.m_width = m_width;
            data.m_height = m_height;
            data.m_depth = m_depth;
            return data;
        }
        void Erase() {
            *(void**)this = nullptr;
        }
    }; //Size: 0x00A0
    static_assert(sizeof(grcTexture) == 0xA0);
}