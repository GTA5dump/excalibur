#include "pch.h"
#include "fwddec.h"
#include "vector.h"
#include "rage/invoker/types.h"
#include "RTTI.h"

#pragma pack(push, 1)
namespace rage {
	namespace netConnection
	{


		enum class eNetMessage : uint32_t
		{
			MsgInvalid = 0xFFFFF,
			MsgSessionAcceptChat = 0x62,
			MsgStartMatchCmd = 0x2D,
			MsgSetInvitableCmd = 0x1F,
			MsgSessionMemberIds = 0x23,
			MsgRequestGamerInfo = 0x54,
			MsgRemoveGamersFromSessionCmd = 0x53,
			MsgNotMigrating = 0x35,
			MsgMigrateHostResponse = 0x12,
			MsgMigrateHostRequest = 0x66,
			MsgJoinResponse = 0x2A,
			MsgJoinRequest = 0x41,
			MsgHostLeftWhilstJoiningCmd = 0x58,
			MsgConfigResponse = 0x5F,
			MsgConfigRequest = 0x48,
			MsgChangeSessionAttributesCmd = 0x5A,
			MsgAddGamerToSessionCmd = 0x64,// this is where send net info to lobby is called, among other things
			MsgReassignResponse = 0x10,
			MsgReassignNegotiate = 0x01,
			MsgReassignConfirm = 0x26,
			MsgPlayerData = 0x18,
			MsgPackedReliables = 0x30,
			MsgPackedCloneSyncACKs = 0x3B,
			MsgNonPhysicalData = 0x16,
			MsgNetArrayMgrUpdateAck = 0x5D,
			MsgNetArrayMgrUpdate = 0x60,
			MsgNetArrayMgrSplitUpdateAck = 0x25,
			MsgScriptVerifyHostAck = 0x0B,
			MsgScriptVerifyHost = 0x3E,
			MsgScriptNewHost = 0x0E,
			MsgScriptMigrateHostFailAck = 0x1A,
			MsgScriptMigrateHost = 0x33,
			MsgScriptLeaveAck = 0x40,
			MsgScriptLeave = 0x17,
			MsgScriptJoinHostAck = 0x4D,
			MsgScriptJoinAck = 0x43,
			MsgScriptJoin = 0x5C,
			MsgScriptHostRequest = 0x67,
			MsgScriptHandshakeAck = 0x5B,
			MsgScriptHandshake = 0x57,
			MsgScriptBotLeave = 0x2B,// unused?
			MsgScriptBotJoinAck = 0x63,// unused?
			MsgScriptBotJoin = 0x1C,// unused?
			MsgScriptBotHandshakeAck = 0x31,// unused?
			MsgScriptBotHandshake = 0x4B,// unused?
			MsgPartyLeaveGame = 0x3D,
			MsgPartyEnterGame = 0x1E,
			MsgCloneSync = 0x4E,// aka clone_create, clone_sync etc.
			MsgActivateNetworkBot = 0x65,// unused?
			MsgRequestObjectIds = 0x29,
			MsgInformObjectIds = 0x09,
			MsgTextMessage = 0x24,// this one is for chat
			MsgPlayerIsTyping = 0x61,
			MsgPackedEvents = 0x4F,// aka received_event
			MsgPackedEventReliablesMsgs = 0x20,
			MsgRequestKickFromHost = 0x0D,
			MsgTransitionToGameStart = 0x50,
			MsgTransitionToGameNotify = 0x02,
			MsgTransitionToActivityStart = 0x06,
			MsgTransitionToActivityFinish = 0x36,
			MsgTransitionParameters = 0x3C,
			MsgTransitionParameterString = 0x37,
			MsgTransitionLaunchNotify = 0x1B,
			MsgTransitionLaunch = 0x19,
			MsgTransitionGamerInstruction = 0x14,
			MsgTextMessage2 = 0x0A,// this one is for phone message
			MsgSessionEstablishedRequest = 0x52,
			MsgSessionEstablished = 0x07,
			MsgRequestTransitionParameters = 0x42,
			MsgRadioStationSyncRequest = 0x47,
			MsgRadioStationSync = 0x46,
			MsgPlayerCardSync = 0x3A,
			MsgPlayerCardRequest = 0x6A,
			MsgLostConnectionToHost = 0x81,
			MsgKickPlayer = 0x34,// host kick
			MsgDebugStall = 0x7E,// unused?
			MsgCheckQueuedJoinRequestReply = 0x59,
			MsgCheckQueuedJoinRequest = 0x51,
			MsgBlacklist = 0x0C,
			MsgRoamingRequestBubbleRequiredResponse = 0x83,
			MsgRoamingRequestBubbleRequiredCheck = 0x82,
			MsgRoamingRequestBubble = 0x2E,
			MsgRoamingJoinBubble = 0x4C,
			MsgRoamingJoinBubbleAck = 0x3F,
			MsgRoamingInitialBubble = 0x32,
			MsgVoiceStatus = 0x03,
			MsgTextChatStatus = 0x00,
			MsgJoinResponse2 = 0x08,
			MsgJoinRequest2 = 0x68,
			MsgNetTimeSync = 0x38,// ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 37
			MsgNetComplaint = 0x55,// ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 54
			MsgNetLagPing = 0x27,// unused? ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 26
			MsgSearchResponse = 0x6B,// unused? ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 6A
			MsgSearchRequest = 0x05,// unused?
			MsgQosProbeResponse = 0x2C,// ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 2B
			MsgQosProbeRequest = 0x1D,// ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 1C
			MsgCxnRelayAddressChanged = 0x49,// ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 48
			MsgCxnRequestRemoteTimeout = 0x2F,// ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 2E
			MsgSessionDetailRequest = 0x22,// ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 21
			MsgSessionDetailResponse = 0x13,// ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 12
			MsgKeyExchangeOffer = 0x0F,// ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 0E (last result)
			MsgKeyExchangeAnswer = 0x44,// ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 43
			Msg_0x87 = 0x87,
			Msg_0x88 = 0x88,
			Msg_0x80 = 0x80,
			Msg_0x28 = 0x28,
			Msg_0x11 = 0x11,
			Msg_0x45 = 0x45,
			Msg_0x89 = 0x89,
			Msg_0x86 = 0x86,
		};


		class InFrame
		{
		public:
			enum class EventType
			{
				ConnectionClosed = 3,
				FrameReceived = 4,
				BandwidthExceeded = 6,
				OutOfMemory = 7
			};

			virtual ~InFrame() = default;

			virtual void destroy() = 0;
			virtual EventType get_event_type() = 0;
			virtual uint32_t _0x18() = 0;

			uint32_t m_timestamp;            //0x0008
			char pad_0008[52];               //0x000C
			uint32_t m_msg_id;               //0x0040
			uint32_t m_connection_identifier;//0x0044
			InFrame* m_this;                 //0x0048
			uint32_t m_peer_id;              //0x0050
			char pad_0050[44];               //0x0058
			uint32_t m_length;               //0x0080
			char pad_007C[4];                //0x0084
			void* m_data;                    //0x0088
		};
		static_assert(sizeof(rage::netConnection::InFrame) == 0x90);
	}

	enum class eEventNetworkType : int64_t
	{
		CEventNetworkPlayerJoinScript = 153,
		CEventNetworkPlayerLeftScript = 154,
		CEventNetworkStorePlayerLeft = 155,
		CEventNetworkStartSession = 156,
		CEventNetworkEndSession = 157,
		CEventNetworkStartMatch = 158,
		CEventNetworkRemovedFromSessionDueToStall = 160,
		CEventNetworkRemovedFromSessionDueToComplaints = 161,
		CEventNetworkConnectionTimeout = 162,
		CEventNetworkPedDroppedWeapon = 163,
		CEventNetworkPlayerSpawn = 164,
		CEventNetworkPlayerCollectedPickup = 165,
		CEventNetworkPlayerCollectedAmbientPickup = 166,
		CEventNetworkPlayerCollectedPortablePickup = 167,
		CEventNetworkPlayerDroppedPortablePickup = 168,
		CEventNetworkInviteAccepted = 170,
		CEventNetworkInviteConfirmed = 171,
		CEventNetworkInviteRejected = 172,
		CEventNetworkSummo = 173,
		CEventNetworkScriptEvent = 174,
		CEventNetworkSignInStateChanged = 176,
		CEventNetworkSignInChangeActioned = 177,
		CEventNetworkRosChanged = 178,
		CEventNetworkBail = 179,
		CEventNetworkHostMigration = 180,
		CEventNetworkFindSession = 181,
		EventNetworkHostSession = 182,
		CEventNetworkJoinSession = 183,
		CEventNetworkJoinSessionResponse = 184,
		CEventNetworkCheatTriggered = 185,
		CEventNetworkEntityDamage = 186,
		CEventNetworkPlayerArrest = 187,
		CEventNetworkTimedExplosion = 188,
		CEventNetworkPrimaryClanChanged = 189,
		CEventNetworkClanJoined = 190,
		CEventNetworkClanLeft = 191,
		CEventNetworkClanInviteReceived = 192,
		CEventNetworkVoiceSessionStarted = 193,
		CEventNetworkVoiceSessionEnded = 194,
		CEventNetworkVoiceConnectionRequested = 195,
		CEventNetworkVoiceConnectionResponse = 196,
		CEventNetworkVoiceConnectionTerminated = 197,
		CEventNetworkTextMessageReceived = 198,
		CEventNetworkCloudFileResponse = 199,
		CEventNetworkPickupRespawned = 200,
		CEventNetworkPresence_StatUpdate = 201,
		CEventNetworkPedLeftBehind = 202,
		CEventNetwork_InboxMsgReceived = 203,
		CEventNetworkAttemptHostMigration = 204,
		CEventNetworkIncrementStat = 205,
		CEventNetworkSessionEvent = 206,
		CEventNetworkTransitionStarted = 207,
		CEventNetworkTransitionEvent = 208,
		CEventNetworkTransitionMemberJoined = 209,
		CEventNetworkTransitionMemberLeft = 210,
		CEventNetworkTransitionParameterChanged = 211,
		CEventNetworkClanKicked = 212,
		CEventNetworkTransitionStringChanged = 213,
		EventNetworkTransitionGamerInstruction = 214,
		CEventNetworkPresenceInvite = 215,
		EventNetworkPresenceInviteRemoved = 216,
		EventNetworkPresenceInviteReply = 217,
		CEventNetworkCashTransactionLog = 218,
		CEventNetworkClanRankChanged = 219,
		CEventNetworkVehicleUndrivable = 220,
		CEventNetworkPresenceTriggerEvent = 221,
		CEventNetworkEmailReceivedEvent = 222,
		CEventNetworkFollowInviteReceived = 223,
		CEventNetworkSpectateLocal = 225,
		CEventNetworkCloudEvent = 226,
		CEventNetworkShopTransaction = 227,
		CEventNetworkOnlinePermissionsUpdated = 230,
		CEventNetworkSystemServiceEvent = 231,
		CEventNetworkRequestDelay = 232,
		CEventNetworkSocialClubAccountLinked = 233,
		CEventNetworkScAdminPlayerUpdated = 234,
		CEventNetworkScAdminReceivedCash = 235,
		CEventNetworkClanInviteRequestReceived = 236,
		CEventNetworkMarketingEmailReceivedEvent = 237,
		CEventNetworkStuntPerformed = 238,
		CEventNetworkFiredDummyProjectile = 239,
		CEventNetworkPlayerEnteredVehicle = 240,
		CEventNetworkPlayerActivatedSpecialAbility = 241,
		CEventNetworkPlayerDeactivatedSpecialAbility = 242,
		CEventNetworkPlayerSpecialAbilityFailedActivation = 243,
		CEventNetworkFiredVehicleProjectile = 244,
	};

	class CEventNetwork
	{
	public:
		DEFINE_AT_RTTI(rage::CEventNetwork);
		virtual void unk_0008() = 0;      //0x0008 (1)
		virtual void unk_0010() = 0;      //0x0010 (2)
		virtual eEventNetworkType get_type() = 0;      //0x0018 (3)
		virtual void unk_0020() = 0;      //0x0020 (4)
		virtual void unk_0028() = 0;      //0x0028 (5)
		virtual bool get_extra_information(void* info_array, int check) = 0;      //0x0030 (6)
		virtual void unk_0038() = 0;      //0x0038 (7)
	};                                                                            //Size: 0x0008

	class sEntityDamagedData
	{
	public:
		alignas(8) Entity m_victim_index;              //0x0000
		alignas(8) Entity m_damager_index;             //0x0008
		alignas(8) float m_damage;                     //0x0010
		alignas(8) float m_endurance_damage;           //0x0018
		alignas(8) bool m_victim_incapacitated;        //0x0020
		alignas(8) bool m_victim_destroyed;            //0x0028
		alignas(8) int m_weapon_used;                  //0x0030
		alignas(8) float m_victim_speed;               //0x0038
		alignas(8) float m_damager_speed;              //0x0040
		alignas(8) bool m_is_responsible_for_collision;//0x0048
		alignas(8) bool m_is_headshot;                 //0x0050
		alignas(8) bool m_is_with_melee_weapon;        //0x0058
		alignas(8) int m_hit_material;                 //0x0060
	};                                                 //Size: 0x0068
	static_assert(sizeof(sEntityDamagedData) == 0x68);

	class netGameEvent
	{
	public:
		virtual ~netGameEvent() = default;

		virtual const char* get_name()
		{
			return 0;
		};
		virtual bool is_in_scope(netPlayer* player)
		{
			return 0;
		};
		virtual bool time_to_resend(std::uint32_t time)
		{
			return 0;
		};
		virtual bool can_change_scope()
		{
			return 0;
		};

		virtual void prepare_data(datBitBuffer* buffer, netPlayer* source_player, netPlayer* target_player) {};
		virtual void handle_data(datBitBuffer* buffer, netPlayer* source_player, netPlayer* target_player) {};

		virtual bool decide(netPlayer* source_player, netPlayer* target_player)
		{
			return 0;
		};

		virtual void prepare_reply(datBitBuffer* buffer, netPlayer* reply_player) {};
		virtual void handle_reply(datBitBuffer* buffer, netPlayer* souce_player) {};

		virtual void prepare_extra_data(datBitBuffer* buffer, bool is_reply, netPlayer* player, netPlayer* player2) {};
		virtual void handle_extra_data(datBitBuffer* buffer, bool is_reply, netPlayer* player, netPlayer* player2) {};

	private:
		virtual void unk_0x60() {};
		virtual void unk_0x68() {};
		virtual void unk_0x70() {};
		virtual void unk_0x78() {};

	public:
		virtual bool operator==(netGameEvent const& other)
		{
			return 0;
		};
		virtual bool operator!=(netGameEvent const& other)
		{
			return 0;
		};

		virtual bool must_persist()
		{
			return 0;
		};
		virtual bool must_persist_when_out_of_scope()
		{
			return 0;
		};
		virtual bool has_timed_out()
		{
			return 0;
		};

	public:
		std::uint16_t m_id;   // 0x08
		bool m_requires_reply;// 0x0A
	private:
		char m_padding1[0x05];// 0x0B
	public:
		netPlayer* m_source_player; // 0x10
		netPlayer* m_target_player; // 0x18
		std::uint32_t m_resend_time;// 0x20
	private:
		std::uint16_t m_0x24;// 0x24
		std::uint8_t m_0x26; // 0x26
		std::uint8_t m_0x27; // 0x27
		std::uint32_t m_0x28;// 0x28
		char m_padding2[0x04];
	};

	class CScriptedGameEvent : public rage::netGameEvent
	{
	public:
		char m_padding[0x40];     // 0x30
		std::int64_t m_args[54];  // 0x70
		std::uint32_t m_bitset;   // 0x220
		std::uint32_t m_args_size;// 0x224
	};

	class CNetworkIncrementStatEvent : public rage::netGameEvent
	{
	public:
		Hash m_stat;           // 0x30
		std::uint32_t m_amount;// 0x34
	};

}
#pragma pop