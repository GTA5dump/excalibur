#include "pch.h"
#include "fwddec.h"
#include "RTTI.h"
#include "hooks/patterns.h"

#pragma pack(push, 1)
namespace rage {
	struct datBitBufferSyncInstance;
	class datBitBuffer
	{
	public:
		datBitBuffer(void* data, uint32_t size)
		{
			m_data = data;
			m_bitOffset = 0;
			m_maxBit = size * 8;
			m_bitsRead = 0;
			m_curBit = 0;
			m_highestBitsRead = 0;
			m_flagBits = 0;
		}
		uint32_t GetPosition()
		{
			return m_bitsRead;
		}
		bool Seek(uint32_t bits)
		{
			if (bits >= 0)
			{
				uint32_t length = (m_flagBits & 1) ? m_maxBit : m_curBit;
				if (bits <= length)
					m_bitsRead = bits;
			}
			return false;
		}
		bool WriteBool(bool integer)
		{
			return patterns::write_bitbuf_bool(this, integer, 1);
		}
		bool ReadBool(bool* integer)
		{
			return patterns::read_bitbuf_bool(this, integer, 1);
		}
		bool ReadPeerId(uint64_t* integer)
		{
			return this->ReadQWord(integer, 0x40);
		}
		uint64_t ReadBits(size_t numBits)
		{
			auto const totalBits = (m_flagBits & 1) ? m_maxBit : m_curBit;
			if ((m_flagBits & 2) || m_bitsRead + numBits > totalBits)
				return 0;
			auto const bufPos = m_bitsRead + m_bitOffset;
			auto const initialBitOffset = bufPos & 0b111;
			auto const start = &((uint8_t*)m_data)[bufPos / 8];
			auto const next = &start[1];
			auto result = (start[0] << initialBitOffset) & 0xff;
			for (auto i = 0; i < ((numBits - 1) / 8); i++)
			{
				result <<= 8;
				result |= next[i] << initialBitOffset;
			}
			if (initialBitOffset)
				result |= next[0] >> (8 - initialBitOffset);
			m_bitsRead += static_cast<uint32_t>(numBits);
			if (m_bitsRead > m_highestBitsRead)
				m_highestBitsRead = m_bitsRead;
			return result >> ((8 - numBits) % 8);
		}
		int GetDataLength()
		{
			int leftoverBit = (m_curBit % 8) ? 1 : 0;
			return (m_curBit / 8) + leftoverBit;
		}
		bool ReadString(char* string, int bits)
		{
			return patterns::read_bitbuf_string(this, string, bits);
		}
		bool WriteByte(uint8_t integer, int bits)
		{
			return patterns::write_bitbuf_dword(this, integer, bits);
		}
		bool ReadByte(uint8_t* integer, int bits)
		{
			uint32_t read;
			if (patterns::read_bitbuf_dword(this, &read, bits))
			{
				*integer = read;
				return true;
			}
			return false;
		}
		bool WriteWord(uint16_t integer, int bits)
		{
			return patterns::write_bitbuf_dword(this, integer, bits);
		}
		bool ReadWord(uint16_t* integer, int bits)
		{
			uint32_t read;
			if (patterns::read_bitbuf_dword(this, &read, bits))
			{
				*integer = read;
				return true;
			}
			return false;
		}
		bool WriteDword(uint32_t integer, int bits)
		{
			return patterns::write_bitbuf_dword(this, integer, bits);
		}
		bool ReadDword(uint32_t* integer, int bits)
		{
			return patterns::read_bitbuf_dword(this, integer, bits);
		}
		bool WriteInt32(int32_t integer, int bits)
		{
			return patterns::write_bitbuf_int32(this, integer, bits);
		}
		bool ReadInt32(int32_t* integer, int bits)
		{
			int32_t v8;
			int32_t v9;
			if (ReadDword((uint32_t*)&v8, 1u) && ReadDword((uint32_t*)&v9, bits - 1))
			{
				*integer = v8 + (v9 ^ -v8);
				return true;
			}
			return false;
		}
		bool WriteQWord(uint64_t integer, int bits)
		{
			return patterns::write_bitbuf_qword(this, integer, bits);
		}
		bool ReadQWord(uint64_t* integer, int bits)
		{
			if (bits <= 32)
			{
				uint32_t v10;
				if (ReadDword(&v10, bits))
				{
					*integer = v10;
					return true;
				}
			}
			else
			{
				uint32_t v10, v11;
				if (ReadDword(&v11, 32u) && ReadDword(&v10, bits - 32u))
				{
					*integer = v11 | ((uint64_t)v10 << 32);
					return true;
				}
			}
			return false;
		}
		bool WriteInt64(int64_t integer, int bits)
		{
			return patterns::write_bitbuf_int64(this, integer, bits);
		}
		bool ReadInt64(int64_t* integer, int bits)
		{
			uint32_t v8;
			uint64_t v9;
			if (ReadDword(&v8, 1u) && ReadQWord(&v9, bits - 1))
			{
				*integer = v8 + (v9 ^ -(int64_t)v8);
				return true;
			}
			return false;
		}
		bool WriteArray(void* array, int size)
		{
			return patterns::write_bitbuf_array(this, array, size, 0);
		}
		bool ReadArray(PVOID array, int size)
		{
			return patterns::read_bitbuf_array(this, array, size, 0);
		}

		template<typename T>
		inline T Read(int length)
		{
			static_assert(sizeof(T) <= 4, "maximum of 32 bit read");

			uint32_t val = 0;
			ReadDword(&val, length);

			return T(val);
		}

		template<typename T>
		inline T ReadSigned(int length)
		{
			static_assert(sizeof(T) <= 4, "maximum of 32 bit read");

			int val = 0;
			ReadInt32(&val, length);

			return T(val);
		}

		template<typename T>
		inline void Write(T data, int length)
		{
			static_assert(sizeof(T) <= 8, "maximum of 64 bit write");

			WriteQWord((uint64_t)data, length);
		}

		template<typename T>
		inline void WriteSigned(int length, T data)
		{
			int sign = data < 0;
			int signEx = (data < 0) ? 0xFFFFFFFF : 0;
			int d = (data ^ signEx);

			Write<int>(1, sign);
			Write<int>(length - 1, d);
		}

		inline float ReadFloat(int length, float divisor)
		{
			auto integer = Read<int>(length);

			float max = (1 << length) - 1;
			return ((float)integer / max) * divisor;
		}

		inline void WriteFloat(int length, float divisor, float value)
		{
			float max = (1 << length) - 1;
			int integer = (int)((value / divisor) * max);

			Write<int>(length, integer);
		}

		inline float ReadSignedFloat(int length, float divisor)
		{
			auto integer = ReadSigned<int>(length);

			float max = (1 << (length - 1)) - 1;
			return ((float)integer / max) * divisor;
		}

		inline void WriteSignedFloat(int length, float divisor, float value)
		{
			float max = (1 << (length - 1)) - 1;
			int integer = (int)((value / divisor) * max);

			WriteSigned<int>(length, integer);
		}

	public:
		void* m_data;              //0x0000
		uint32_t m_bitOffset;      //0x0008
		uint32_t m_maxBit;         //0x000C
		uint32_t m_bitsRead;       //0x0010
		uint32_t m_curBit;         //0x0014
		uint32_t m_highestBitsRead;//0x0018
		uint8_t m_flagBits;        //0x001C
	};

	struct datBitBufferSyncInstance {
		uint64_t m_VTable;
		uint8_t m_type; // 1 = reader, 2 = writer, 3 = calculator, 4 = logger
		char _0x0009[0x7];
		uint64_t m_sub_type; // 0 = reader, 2 = writer, 3 = calculator, 4 = logger
		datBitBuffer* m_buffer;
	};
}
#pragma pop