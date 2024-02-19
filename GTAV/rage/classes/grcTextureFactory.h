#pragma once
#include <cstdint>
#include "grcTexture.h"
#include "grcRenderTarget.h"

namespace rage {
    class grcTextureFactory {
    public:
        virtual ~grcTextureFactory() = default;
        virtual grcTexture* unk_0008() = NULL;
        virtual grcTexture* CreateManualTexture() = NULL;
        virtual grcTexture* unk_0018() = NULL;
        virtual grcTexture* CreateTexture(const char* name, int32_t id) = NULL;
        virtual void unk_0028() = NULL;
        virtual void unk_0030() = NULL;
        virtual int TranslateFormatToParamFormat(int32_t format) = NULL;
        virtual void unk_0040() = NULL;
        virtual void unk_0048() = NULL;
        virtual void unk_0050() = NULL;
        virtual void unk_0058() = NULL;
        virtual void unk_0060() = NULL;
        virtual void unk_0068() = NULL;
        virtual void unk_0070() = NULL;
        virtual void unk_0078() = NULL;
        virtual void unk_0080() = NULL;
        virtual void unk_0088() = NULL;
        virtual grcTexture* CreateFromNativeTexture(const char* name, ID3D11Resource* nativeResource, void* a3) = NULL;
        virtual void unk_00A0() = NULL;
        virtual void PushRenderTarget(void* a1, grcRenderTarget* target, void* a3, int a4, bool a5, bool a6) = NULL;
        virtual void PopRenderTarget(void* a1, grcRenderTarget* target) = NULL;
    public:
        char pad_0008[8]; //0x0008
    }; //Size: 0x0010
    static_assert(sizeof(grcTextureFactory) == 0x10);
}