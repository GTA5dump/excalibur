#pragma once
#include "util/hooking/hooking.h"
#include "rage/classes/scrNativeCallContext.h"
#include "rage/classes/scrThread.h"
#include "rage/classes/scrProgram.h"
#include "rage/classes/WebConstuction.h"
#include "rage/classes/enums.h"
#include "rage/classes/netShopping.h"
#include "rage/classes/SyncTree.h"
class CPlayerGamerDataNode;
class CPlayerGameStateDataNode;
class CPedInventoryDataNode;
class CDynamicEntityGameStateDataNode;
class CVehicleGadgetDataNode;
class CPlayerCameraDataNode;
class CJoinRequestContext;
class SessionSortEntry;
class RemoteGamerInfoMsg;
class CMsgTextMessage;
class CNetGamePlayerDataMsg;
class MatchmakingAttributes;
class CNetworkIncrementStatEvent;
class CScriptedGameEvent;
class NetworkGameFilterMatchmakingComponent;
class ClonedTakeOffPedVariationInfo;
class CPlayerCardStats;
class CStatsSerializationContext;
class CPlayerCreationDataNode;
class CPlayerAppearanceDataNode;
class CFoundDevice;
class IDirectSoundCapture;
class CVehicleProximityMigrationDataNode;
class CTrainGameStateDataNode;
class CPed;
namespace rage
{
	class snSession;
	class JSONNode;
	class netArrayHandlerBase;
	class CEventNetwork;
	class CSyncDataBase;
	class rlGamerHandle;
	class rlGamerInfo;
	class netConnectionManager;
	class datBitBuffer;
	struct datBitBufferSyncInstance;
	class rlMetric;
	struct gs_session;
	class rlTaskStatus;
	class TimecycleKeyframeData;
	class fwEntity;

	namespace netConnection
	{
		class InFrame;
	}
}

namespace base::hooks {
	bool patterns();
	bool bypass();
	bool hooks();

	void stat_get_int(rage::scrNativeCallContext* context);
	void set_current_ped_weapon(rage::scrNativeCallContext* context);
	void disable_control_action(rage::scrNativeCallContext* context);
	void network_session_host(rage::scrNativeCallContext* context);
	void set_player_name(rage::scrNativeCallContext* context);
	void terminate_this_thread(rage::scrNativeCallContext* context);
	void return_true(rage::scrNativeCallContext* context);
	void return_false(rage::scrNativeCallContext* context);

	uint64_t scriptVmHook(void* stack, int64_t** globals, rage::scrProgram* program, rage::scrThreadContext* ctx);
	inline decltype(&scriptVmHook) ogScriptVmHook;

	void* getFontIdHook(uint64_t font, int id);
	inline decltype(&getFontIdHook) ogGetFontIdHook;

	int ntQueryVirtualMemoryHook(void* _this, HANDLE handle, PVOID base_addr, int info_class, MEMORY_BASIC_INFORMATION* info, int size, size_t* return_len);
	
	void queueDependencyHook(void* dependency);
	inline decltype(&queueDependencyHook) ogQueueDependencyHook;

	void sendNetworkEventHook(uint64_t net_table, uint64_t event);
	inline decltype(&sendNetworkEventHook) ogSendNetworkEventHook;

	uint64_t formatEngineStringHook(uint64_t rcx, uint64_t rdx, uint32_t r8d, const char* r9, uint32_t stack);
	inline decltype(&formatEngineStringHook) ogFormatEngineStringHook;

	int getEngineStringLineCountHook(uint64_t rcx, const char* rdx, float xmm2, uint64_t r9, bool stack);
	inline decltype(&getEngineStringLineCountHook) ogGetEngineStringLineCountHook;

	bool allowWeaponsInVehicleHook(int64_t unk, int weaponinfo_group);
	inline decltype(&allowWeaponsInVehicleHook) ogAllowWeaponsInVehicleHook;

	uint64_t addEventToListHook(uint64_t event_pool);
	inline decltype(&addEventToListHook) ogAddEventToListHook;

	bool sendMetricHook(rage::rlMetric* _this, bool unk);
	inline decltype(&sendMetricHook) ogSendMetricHook;

	bool addItemToBasketHook(uint64_t _this, i32* items);
	inline decltype(&addItemToBasketHook) ogAddItemToBasketHook;

	bool sendHTTPRequestHook(CHttpRequest* request);
	inline decltype(&sendHTTPRequestHook) ogSendHTTPRequestHook;

	LPVOID convertThreadToFiberHook(LPVOID param);
	inline decltype(&convertThreadToFiberHook) ogConvertThreadToFiberHook;

	void syncPedOrientationHook(uint64_t rcx, uint64_t rdx);
	inline decltype(&syncPedOrientationHook) ogSyncPedOrientationHook;

	void syncVehicleOrientationHook(uint64_t rcx, uint64_t* rdx);
	inline decltype(&syncVehicleOrientationHook) ogsyncVehicleOrientationHook;

	void receivedNetworkEventHook(void* _this, CNetGamePlayer* sender, CNetGamePlayer* receiver, uint16_t event_id, int event_index, int event_bitset, uint32_t buffer_size, rage::datBitBuffer* buffer);
	inline decltype(&receivedNetworkEventHook) ogReceivedNetworkEventHook;

	int receiveCloneSyncHook(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eNetObjType object_type, uint16_t object_id, rage::datBitBuffer* buffer, uint16_t unk, uint32_t timestamp);
	inline decltype(&receiveCloneSyncHook) ogReceiveCloneSyncHook;

	bool receiveCloneCreateHook(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eNetObjType object_type, int32_t object_id, int32_t object_flag, rage::datBitBuffer* buffer, int32_t timestamp);
	inline decltype(&receiveCloneCreateHook) ogReceiveCloneCreateHook;

	bool receiveCloneRemoveHook(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, int32_t object_id, int32_t timestamp);
	inline decltype(&receiveCloneRemoveHook) ogReceiveCloneRemoveHook;

	void receiveCloneRemoveAckHook(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, int32_t object_id, int32_t timestamp);
	inline decltype(&receiveCloneRemoveAckHook) ogReceiveCloneRemoveAckHook;

	void receiveCloneCreateAckHook(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, uint16_t object_id, int32_t ack_code);
	inline decltype(&receiveCloneCreateAckHook) ogReceiveCloneCreateAckHook;

	void receiveCloneSyncAckHook(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, rage::datBitBuffer* buffer, uint16_t object_id, int32_t ack_code);
	inline decltype(&receiveCloneSyncAckHook) ogReceiveCloneSyncAckHook;

	bool canApplyDataHook(rage::netSyncTree* tree, rage::netObject* object);
	inline decltype(&canApplyDataHook) ogCanApplyDataHook;

	bool receiveArrayBroadcastHook(rage::netArrayHandlerBase* array, CNetGamePlayer* sender, rage::datBitBuffer* buffer, int size, std::int16_t cycle);
	inline decltype(&receiveArrayBroadcastHook) ogReceiveArrayBroadcastHook;

	bool receivePresenceEvent(uint64_t rcx, uint64_t rdx, const char** payload, uint64_t r9);
	inline decltype(&receivePresenceEvent) ogReceivePresenceEvent;

	bool updatePresenceAttributeIntHook(void* presence_data, int profile_index, char* attr, std::uint64_t value);
	inline decltype(&updatePresenceAttributeIntHook) ogUpdatePresenceAttributeIntHook;

	bool updatePresenceAttributeStringHook(void* presence_data, int profile_index, char* attr, char* value);
	inline decltype(&updatePresenceAttributeStringHook) ogUpdatePresenceAttributeStringHook;

	void writeGSItemHook(int index, rage::gs_session* data, const char* type);
	inline decltype(&writeGSItemHook) ogWriteGSItemHook;

	bool readNewScriptHostMessageHook(uint64_t rcx, uint64_t rdx);
	inline decltype(&readNewScriptHostMessageHook) ogReadNewScriptHostMessageHook;

	bool initNativeTablesHook(rage::scrProgram* program);
	inline decltype(&initNativeTablesHook) ogInitNativeTablesHook;

	bool sendChatMessageHook(void* team_mgr, rage::rlGamerInfo* local_gamer_info, const char* message, bool is_team);
	inline decltype(&sendChatMessageHook) ogSendChatMessageHook;

	bool receiveNetMessageHook(void* netConnectionManager, void* a2, rage::netConnection::InFrame* frame);
	inline decltype(&receiveNetMessageHook) ogReceiveNetMessageHook;

	int checkChatProfanityHook(uint64_t rcx, uint64_t input, uint64_t output);
	inline decltype(&checkChatProfanityHook) ogCheckChatProfanityHook;

	//48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 20 48 8D B1 08 23 00 00

	uint64_t unknownCheckHook(uint64_t rcx, uint64_t rdx, uint64_t r8);
	inline decltype(&unknownCheckHook) ogUnknownCheckHook;

	void getNetworkEventDataHook(int64_t unk, rage::CEventNetwork* net_event);
	inline decltype(&getNetworkEventDataHook) ogGetNetworkEventDataHook;

	//crashy crashy patchy patchy
	eThreadState tickScriptThreadHook(GtaThread* thread, uint32_t count);
	inline decltype(&tickScriptThreadHook) ogTickScriptThreadHook;

	uint64_t invalidDecalCrashHook(uintptr_t rcx, int rdx);
	inline decltype(&invalidDecalCrashHook) ogInvalidDecalCrashHook;

	void invalidModsCrashHook(int64_t  rcx, int64_t  rdx, int r8, char r9);
	inline decltype(&invalidModsCrashHook) ogInvalidModsCrashHook;

	void parachuteCrashHook(ClonedTakeOffPedVariationInfo* info, rage::CSyncDataBase* serializer);
	inline decltype(&parachuteCrashHook) ogParachuteCrashHook;

	uint64_t parachuteCrashHook2(uint64_t rcx, int rdx, int r8);
	inline decltype(&parachuteCrashHook2) ogParachuteCrashHook2;

	bool fragmentCrashHook(float* rcx, float* rdx);
	inline decltype(&fragmentCrashHook) ogFragmentCrashHook;

	//48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 20 41 8A E8
	void* applyPlayerPhysicalIndexHook(CNetworkPlayerMgr* netPlayerMgr, CNetGamePlayer* player, uint8_t new_index);
	inline decltype(&applyPlayerPhysicalIndexHook) ogApplyPlayerPhysicalIndexHook;

	bool syncPlayerGameStateHook(uint64_t rcx, CPlayerGameStateDataNode* node);
	inline decltype(&syncPlayerGameStateHook) ogSyncPlayerGameStateHook;

	void syncPedHealthHook(uint64_t rcx, uint64_t rdx);
	inline decltype(&syncPedHealthHook) ogSyncPedHealthHook;

	/*void syncPlayerAppearanceDataNodeHook(rage::netObject* player, CPlayerAppearanceDataNode* node);//first arg is incorrect
	inline decltype(&syncPlayerAppearanceDataNodeHook) ogSyncPlayerAppearanceDataNodeHook;*/

	void readTrainGameStateHook(rage::netObject* player, CTrainGameStateDataNode* node);
	inline decltype(&readTrainGameStateHook) ogReadTrainGameStateHook;

	void* infiniteTrainCrashHook(void* carriage);
	inline decltype(&infiniteTrainCrashHook) ogInfiniteTrainCrashHook;

	void* renderPedHook(__int64 renderer, CPed* ped, __int64 a3, __int64 a4);
	inline decltype(&renderPedHook) ogRenderPedHook;

	void renderEntityHook(__int64 renderer, rage::fwEntity* entity, int unk, bool a4);
	inline decltype(&renderEntityHook) ogRenderEntityHook;

	__int64 renderBigPedHook(__int64 renderer, CPed* ped, __int64 a3, __int64 a4);
	inline decltype(&renderBigPedHook) ogRenderBigPedHook;

	bool processMatchmakingFindResponseHook(void* _this, void* rdx, rage::JSONNode* node, int* unk);
	inline decltype(&processMatchmakingFindResponseHook) ogProcessMatchmakingFindResponseHook;
	
	//pdn2: 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC 30 48 8B 01 4C 8B F2 33 D2 48 8B F1 FF 90 ? ? ? ? 84 C0 0F 84
	bool compressDataNodeHook2(rage::netSyncDataNode* node, rage::netObject* object);
	inline decltype(&compressDataNodeHook2) ogCompressDataNodeHook2;

	uint64_t updateUIValuesHook(int64_t _this, rage::TimecycleKeyframeData* data);
	inline decltype(&updateUIValuesHook) ogUpdateUIValuesHook;
	//uint64_t syncPedMovementDataNodeHook(CPedMovementDataNode* node, rage::netObject* player);
	//inline decltype(&syncPedMovementDataNodeHook) ogSyncPedMovementDataNodeHook;
	//bool sendSessionMatchmakingAttributesHook(void* a1, rage::rlSessionInfo* info, std::uint64_t session_id, bool use_session_id, MatchmakingAttributes* attributes);
	//inline decltype(&sendSessionMatchmakingAttributesHook) ogSendSessionMatchmakingAttributesHook;



	bool read_unsigned_int_from_buffer(rage::datBitBufferSyncInstance* _this, uint32_t* output, int count);
	inline decltype(&read_unsigned_int_from_buffer) read_unsigned_int_from_buffer_t;

	bool read_unsigned_short_from_buffer(rage::datBitBufferSyncInstance* _this, uint16_t* output, int count);
	inline decltype(&read_unsigned_short_from_buffer) read_unsigned_short_from_buffer_t;

	bool read_unsigned_char_from_buffer(rage::datBitBufferSyncInstance* _this, uint8_t* output, int count);
	inline decltype(&read_unsigned_char_from_buffer) read_unsigned_char_from_buffer_t;

	bool read_int_from_buffer(rage::datBitBufferSyncInstance* _this, int* output, int count);
	inline decltype(&read_int_from_buffer) read_int_from_buffer_t;

	bool read_short_from_buffer(rage::datBitBufferSyncInstance* _this, short* output, int count);
	inline decltype(&read_short_from_buffer) read_short_from_buffer_t;

	bool read_char_from_buffer(rage::datBitBufferSyncInstance* _this, char* output, int count);
	inline decltype(&read_char_from_buffer) read_char_from_buffer_t;

	bool read_bool_from_buffer(rage::datBitBufferSyncInstance* _this, bool* output);
	inline decltype(&read_bool_from_buffer) read_bool_from_buffer_t;

	bool read_long_long_from_buffer(rage::datBitBufferSyncInstance* _this, long long* output, int count);
	inline decltype(&read_long_long_from_buffer) read_long_long_from_buffer_t;

	bool read_unsigned_long_long_from_buffer(rage::datBitBufferSyncInstance* _this, uint64_t* output, int count);
	inline decltype(&read_unsigned_long_long_from_buffer) read_unsigned_long_long_from_buffer_t;

	bool read_float_from_buffer(rage::datBitBufferSyncInstance* _this, float* output, float mod, int count);
	inline decltype(&read_float_from_buffer) read_float_from_buffer_t;

	bool read_unsigned_float_from_buffer(rage::datBitBufferSyncInstance* _this, float* output, float mod, int count);
	inline decltype(&read_unsigned_float_from_buffer) read_unsigned_float_from_buffer_t;

	bool read_network_id_from_buffer(rage::datBitBufferSyncInstance* _this, short* output);
	inline decltype(&read_network_id_from_buffer) read_network_id_from_buffer_t;

	bool read_array_from_buffer(rage::datBitBufferSyncInstance* _this, int* output, int count, int unk);
	inline decltype(&read_array_from_buffer) read_array_from_buffer_t;

	bool read_string_from_buffer(rage::datBitBufferSyncInstance* _this, char* output, int length);
	inline decltype(&read_string_from_buffer) read_string_from_buffer_t;

	int task_ambient_clips(uint64_t _this, int a2, int a3);
	inline decltype(&task_ambient_clips) task_ambient_clips_t;

	void serialize_parachute_task(__int64 info, rage::CSyncDataBase* serializer);
	inline decltype(&serialize_parachute_task) serialize_parachute_task_t;

	bool read_bitbuf_dword(rage::datBitBuffer * buffer, PVOID read, int bits);
	inline decltype(&read_bitbuf_dword) read_bitbuf_dword_t;

	bool read_bitbuf_string(rage::datBitBuffer* buffer, char* read, int bits);
	inline decltype(&read_bitbuf_string) read_bitbuf_string_t;

	bool read_bitbuf_bool(rage::datBitBuffer* buffer, bool* read, int bits);
	inline decltype(&read_bitbuf_bool) read_bitbuf_bool_t;

	bool read_bitbuf_array(rage::datBitBuffer* buffer, PVOID read, int bits, int unk);
	inline decltype(&read_bitbuf_array) read_bitbuf_array_t;


	bool write_unsigned_int_from_buffer();
	inline decltype(&write_unsigned_int_from_buffer) write_unsigned_int_from_buffer_t;

	bool write_unsigned_short_from_buffer(rage::datBitBufferSyncInstance* _this, uint16_t* output, int count);
	inline decltype(&write_unsigned_short_from_buffer) write_unsigned_short_from_buffer_t;

	bool write_unsigned_char_from_buffer(rage::datBitBufferSyncInstance* _this, uint8_t* output, int count);
	inline decltype(&write_unsigned_char_from_buffer) write_unsigned_char_from_buffer_t;

	bool write_int_from_buffer(rage::datBitBufferSyncInstance* _this, int* output, int count);
	inline decltype(&write_int_from_buffer) write_int_from_buffer_t;

	bool write_short_from_buffer(rage::datBitBufferSyncInstance* _this, short* output, int count);
	inline decltype(&write_short_from_buffer) write_short_from_buffer_t;

	bool write_char_from_buffer(rage::datBitBufferSyncInstance* _this, char* output, int count);
	inline decltype(&write_char_from_buffer) write_char_from_buffer_t;

	bool write_bool_from_buffer(rage::datBitBufferSyncInstance* _this, bool* output);
	inline decltype(&write_bool_from_buffer) write_bool_from_buffer_t;

	bool write_long_long_from_buffer(rage::datBitBufferSyncInstance* _this, long long* output, int count);
	inline decltype(&write_long_long_from_buffer) write_long_long_from_buffer_t;

	bool write_unsigned_long_long_from_buffer(rage::datBitBufferSyncInstance* _this, uint64_t* output, int count);
	inline decltype(&write_unsigned_long_long_from_buffer) write_unsigned_long_long_from_buffer_t;

	bool write_float_from_buffer(rage::datBitBufferSyncInstance* _this, float* output, float mod, int count);
	inline decltype(&write_float_from_buffer) write_float_from_buffer_t;

	bool write_unsigned_float_from_buffer(rage::datBitBufferSyncInstance* _this, float* output, float mod, int count);
	inline decltype(&write_unsigned_float_from_buffer) write_unsigned_float_from_buffer_t;

	bool write_network_id_from_buffer(rage::datBitBufferSyncInstance* _this, short* output);
	inline decltype(&write_network_id_from_buffer) write_network_id_from_buffer_t;

	bool write_array_from_buffer(rage::datBitBufferSyncInstance* _this, int* output, int count, int unk);
	inline decltype(&write_array_from_buffer) write_array_from_buffer_t;

	bool write_string_from_buffer(rage::datBitBufferSyncInstance* _this, char* output, int length);
	inline decltype(&write_string_from_buffer) write_string_from_buffer_t;


	void updatePlayerScriptStatus(rage::scriptHandlerNetComponent* component, uint64_t rdx, uint64_t r8);
	inline decltype(&updatePlayerScriptStatus) ogUpdatePlayerScriptStatus;
}