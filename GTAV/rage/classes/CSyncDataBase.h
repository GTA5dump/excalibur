#include "pch.h"
#include "fwddec.h"
#include "vector.h"

#pragma pack(push, 1)
namespace rage {
	class CSyncDataBase
	{
	public:
		virtual ~CSyncDataBase() = default;
		virtual bool SerializeDword(uint32_t* dword, int size) = 0;
		virtual bool SerializeWord(uint16_t* word, int size) = 0;
		virtual bool SerializeByte(uint8_t* byte, int size) = 0;
		virtual bool SerializeInt32(int32_t* i, int size) = 0;
		virtual bool SerializeInt16(int16_t* i, int size) = 0;
		virtual bool SerializeSignedByte(int8_t* byte, int size) = 0;
		virtual bool SerializeBool(bool* flag) = 0;
		virtual bool SerializeInt64(int64_t* i, int size) = 0;
		virtual bool SerializeInt32Alt(int32_t* i, int size) = 0;
		virtual bool SerializeInt16Alt(int16_t* i, int size) = 0;
		virtual bool SerializeSignedByteAlt(int8_t* byte, int size) = 0;
		virtual bool SerializeQword(uint64_t* qword, int size) = 0;
		virtual bool SerializeDwordAlt(uint32_t* dword, int size) = 0;
		virtual bool SerializeWordAlt(uint16_t* word, int size) = 0;
		virtual bool SerializeByteAlt(uint8_t* byte, int size) = 0;
		virtual bool SerializeSignedFloat(float* flt, float divisor, int size) = 0;
		virtual bool SerializeFloat(float* flt, float divisor, int size) = 0;
		virtual bool SerializeNetworkId(uint16_t* net_id) = 0;
		virtual bool SerializeVector3(rage::vector3* vec3, float divisor, int size) = 0;
		virtual bool SerializeQuaternion(void* unk) = 0;// i have no clue what that is
		virtual bool SerializeVector3SignedZComponent(rage::vector3* vec3, float divisor, int size) = 0;
		virtual bool SerializeOrientation(rage::vector4* vec4, float size) = 0;// yes, the size is a float
		virtual bool SerializeArray(void* array, int size) = 0;
		virtual bool SerializeString(char* str, int max_length) = 0;
		virtual bool IsSizeCalculator() = 0;
		virtual bool IsSizeCalculator2() = 0;

		void* unk_0x8;
		void* syncLog;
		datBitBuffer* buffer;
	};

}
#pragma pop