#pragma once
#include <cstdint>

namespace rage {
	class netSyncData;
	class netObject;
	class datBitBuffer;
#pragma pack(push, 8)
	class netSyncNodeBase
	{
	public:
		virtual ~netSyncNodeBase() = default;                                                                                                            // 0x00
		virtual bool IsDataNode() { return false; };                                                                                                     // 0x08
		virtual bool IsParentNode() { return false; };                                                                                                   // 0x10
		virtual void MoveCommonDataOpsVFT() {};                                                                                                          // 0x18
		virtual void ClearChildren() {};                                                                                                                 // 0x20
		virtual void _0x28(void*, void*, void*, int* out_count) {};                                                                                      // 0x28
		virtual bool Serialize(int flags, int flags2, void*, rage::datBitBuffer* buffer, int, void*, bool, int*, int* num_serialized) { return false; }  // 0x30
		virtual bool Deserialize(int flags, int flags2, rage::datBitBuffer* buffer, void*) { return false; }                                             // 0x38
		virtual int CalculateSize(int flags, int flags2, void*) { return 0; }                                                                            // 0x40
		virtual int CalculateSize2(int flags, int flags2, bool) { return 0; }                                                                            // 0x48

		netSyncNodeBase* m_next_sibling; //0x0008
		netSyncNodeBase* m_prev_sibling; //0x0010
		netSyncNodeBase* m_root; //0x0018
		netSyncNodeBase* m_parent; //0x0020

		uint32_t m_flags1; //0x0028
		uint32_t m_flags2; //0x002C
		uint32_t m_flags3; //0x0030

		uint32_t m_pad2; //0x0034

		netSyncNodeBase* m_first_child; //0x0038
	}; //Size: 0x0040
	static_assert(sizeof(netSyncNodeBase) == 0x40);
#pragma pack(pop)
#pragma pack(push, 8)
	class netSyncDataNode : public netSyncNodeBase
	{
	public:
		uint32_t flags; //0x40
		uint32_t pad3; //0x44
		uint64_t pad4; //0x48

		netSyncDataNode* parentData; //0x50
		uint32_t childCount; //0x58
		netSyncDataNode* children[8]; //0x5C
		uint8_t syncFrequencies[8]; //0x9C
		void* commonDataOpsVFT; //0xA8 wtf
	};
	static_assert(sizeof(netSyncDataNode) == 0xB0);
#pragma pack(pop)
#pragma pack(push, 1)
	class netSyncTree
	{
	public:
		virtual ~netSyncTree() = default;

		char pad_0008[8]; //0x0008
		netSyncNodeBase* m_next_sync_node; //0x0010
		netSyncNodeBase* m_last_sync_node; //0x0018
		uint32_t m_child_node_count; //0x0020
		uint32_t m_unk_array_count; //0x0024
		char pad_0028[8]; //0x0028
		netSyncNodeBase* m_child_nodes[42]; //0x0030
		uint32_t m_child_node_max_count; //0x0180
		netSyncNodeBase* m_unk_array[32]; //0x0188
		uint32_t m_unk_array_max_count; //0x0288
		char pad_0290[560]; //0x0290
	}; //Size: 0x0030
	static_assert(sizeof(netSyncTree) == 0x4B8);
#pragma pack(pop)

	class netSyncParentNode : public netSyncNodeBase
	{
	public:
		char pad_0040[32];
	};
	static_assert(sizeof(netSyncParentNode) == 0x60);
}
class NodeCommonDataOperations
{
public:
	virtual ~NodeCommonDataOperations() = default;
	virtual void ReadFromBuffer(rage::netSyncDataNode* node) {};            // 0x08
	virtual void WriteToBuffer(rage::netSyncDataNode* node) {};             // 0x10
	virtual void Unk() {};                                                  // 0x18
	virtual int CalculateSize(rage::netSyncDataNode* node) { return 0; };   // 0x20
	virtual int CalculateSize2(rage::netSyncDataNode* node) { return 0; };  // 0x28
	virtual void LogSyncData(rage::netSyncDataNode* node) {};               // 0x30
	virtual void LogSyncData2(rage::netSyncDataNode* node) {};              // 0x38

	rage::datBitBuffer* m_buffer; // 0x8
};
static_assert(sizeof(NodeCommonDataOperations) == 0x10);
class CProjectBaseSyncDataNode : public rage::netSyncDataNode
{
public:
	virtual bool IsSyncNode() { return false; }                                 // 0x50
	virtual bool _0x58() { return false; }                                      // 0x58
	virtual bool IsGlobalFlags() { return false; }                              // 0x60
	virtual void DoPreCache(rage::netSyncData* data) {}                         // 0x68
	virtual std::uint8_t GetSyncFrequency(int index) { return 0; }              // 0x70
	virtual int GetSyncInterval(int index) { return 0; }                        // 0x78
	virtual int GetBandwidthForPlayer(int player) { return 200; }               // 0x80 (should always return 200)
	virtual void _0x88(void*) {}                                                // 0x88
	virtual bool _0x90(void*, void*, int, int, int) { return false; }           // 0x90
	virtual int CalculateSize() { return 0; }                                   // 0x98 need to verify later
	virtual bool IsPreCacheDisabled() { return false; }                         // 0xA0
	virtual bool CanApply(rage::netObject* object) { return false; }            // 0xA8
	virtual int GetPlayersInScope() { return -1; }                              // 0xB0
	virtual void DeserializeImpl() {}                                           // 0xB8 need to verify later
	virtual void SerializeImpl() {}                                             // 0xC0 need to verify later
	virtual int CalculateSize2() { return 0; }                                  // 0xC8
	virtual int _0xD0() { return 0; }                                           // 0xD0 calls NodeCommonDataOperations::Unk()
	virtual void Log() {}                                                       // 0xD8
	virtual bool CanPreCache(int) { return false; }                             // 0xE0 arg is always zero afaik
	virtual bool CanBeEmpty() { return false; }                                 // 0xE8
	virtual bool IsEmpty() { return false; }                                    // 0xF0 returns true if all data is default
	virtual void SetEmpty() {}                                                  // 0xF8 sets all data to their default values
	virtual void Log2() {}                                                      // 0x100
	virtual void ResetScriptData() {}                                           // 0x108
	virtual bool _0x110() { return false; }                                     // 0x110

private:
	NodeCommonDataOperations m_common_data_operations; // 0xB0 this is generally invalidated by MoveCommonDataOpsVFT()
};
static_assert(sizeof(CProjectBaseSyncDataNode) == 0xC0);

class CSyncDataNodeFrequent : public CProjectBaseSyncDataNode {};
class CSyncDataNodeInfrequent : public CProjectBaseSyncDataNode {};
class CProjectBaseSyncParentNode : public rage::netSyncParentNode {};


class CProjectSyncTree : public rage::netSyncTree
{
	void* m_unk_data;
	int m_unk_data_size;
	char pad_04C4[4];
};
static_assert(sizeof(CProjectSyncTree) == 0x4C8);