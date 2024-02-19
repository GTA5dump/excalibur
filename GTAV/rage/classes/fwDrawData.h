#pragma once
#include <cstdint>
#include "grcTexture.h"
#include "vfx.h"
namespace rage {
	class fwShaderEffect {
	public:
		char pad_0000[224]; //0x0000
		rage::grcTexture* m_unk_texture; //0x00E0
		char pad_00E8[56]; //0x00E8
		rage::grcTexture* m_texture; //0x0120
		rage::grcTexture* m_texture_2; //0x0128
	}; //Size: 0x0130
	static_assert(sizeof(fwShaderEffect) == 0x130);
#pragma pack(push, 4)
	class fwDrawData {
	public:
		fwShaderEffect* unk_000; //0x0000
		fwShaderEffect* unk_008; //0x0008
		char pad_0010[8]; //0x0010
		uint32_t dword18; //0x0018
		uint32_t unk_001C; //0x0028
		fwShaderEffect* m_damaged_shader_effect; //0x0028
		uint32_t unk_0028; //0x0028
		uint32_t unk_002C; //0x002C
		fwShaderEffect* m_shader_effect; //0x0030
		char _0x0038[0x338]; //0x0000
		CVehicleStreamRender* m_vehicle_stream_render; //0x0370
		char _0x0378[0x8B0]; //0x0378
	}; //Size: 0x0038
	//static_assert(sizeof(fwDrawData) == 0xBF2);
#pragma pack(pop)
}