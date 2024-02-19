#pragma once
#include "pch.h"
#include "rage/classes/scrNativeRegistrationTable.h"
#include "rage/classes/scrProgram.h"
#include "rage/classes/scrNativeCallContext.h"
#include "rage/classes/pgDictionary.h"
#include "rage/classes/grcTextureStore.h"
#include "rage/classes/grcTextureFactory.h"
#include "rage/classes/CPedFactory.h"
#include "rage/invoker/types.h"
#include "memory/pattern.h"
#include "rage/classes/vfx.h"
#include "rage/classes/CBlipList.h"
#include "rage/classes/atArray.h"
#include "rage/classes/CNetworkPlayerMgr.h"
#include "rage/classes/scrThread.h"
#include "rage/classes/Network.h"
#include "rage/classes/CCommunications.h"
#include "rage/classes/netShopping.h"
#include "rage/classes/HashTable.h"
#include "rage/classes/CBaseModelInfo.h"
#include "rage/classes/CEntity.h"
#include "rage/classes/ros.h"
#include "rage/classes/chatData.h"
#include "rage/classes/CReplayInterface.h"
class GenericPool;
class VehiclePool;
namespace patterns {
	extern rage::scrNativeRegistrationTable* native_registration_table;
	extern rage::scrProgramTable* script_program;
	extern rage::hash_list* hash_list;
	extern rage::weapon_hash_list* weapon_components;
	extern rage::weapon_hash_list* weapon_info;
	extern rage::types::store_manager* store_manager;
	extern CPedFactory** ped_factory;
	extern CNetworkObjectMgr** network_object_mgr;
	extern rage::grcTextureStore* texture_store;
	extern rage::grcTextureFactory** texture_factory;
	extern IDXGISwapChain** swapchain;
	extern GenericPool** ped_pool;
	extern GenericPool** prop_pool;
	extern GenericPool** pickup_pool;
	extern VehiclePool*** vehicle_pool;
	extern std::pair<CWheelVfx*, uint8_t> vfx_wheel;
	extern CBlipList* blip_list;
	extern rage::atArray<GtaThread*>* script_threads;
	extern CNetworkPlayerMgr** network_player_mgr;
	extern Network** network;
	extern rage::rlGamerInfo* profile_gamer_info;
	extern rage::rlGamerInfo* player_info_gamer_info;
	extern CCommunications** communications;
	extern rage::netShopping::CNetworkShoppingMgr* net_shop_mgr;

	extern uint64_t script_vm;
	extern uint64_t get_font_id;
	extern uint64_t font_table;
	extern uint64_t font_memory_helper;
	extern uint64_t get_font_id_table;
	extern uint64_t construct_gfx_font;
	extern uint64_t destruct;
	extern uint64_t create_id_for_font;
	extern uint64_t add_font_lib;
	extern uint64_t get_store_module_extension;
	extern uint64_t register_streaming_file;
	extern uint64_t request_streaming_file;	
	extern uint64_t format_game_string;
	extern uint64_t get_game_string_line_count;
	extern uint64_t allow_weapons_in_vehicle;
	extern uint64_t get_entity_address;
	extern uint64_t set_vehicle_gravity;
	extern uint64_t invalid_resource_check;
	extern uint64_t ac_patch_1;//48 8B C4 48 89 58 18 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 48 8D 8D ? ? ? ? 0F 29 70 B8 E8 ? ? ? ? 48 8D 8D ? ? ? ? E8 ? ? ? ? 4C 8D 05 (detected, has self healing vtables)
	extern uint64_t ac_patch_2;//48 89 5C 24 ?? 55 48 8D AC 24 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 48 8B D9 48 8D 0D 
	extern uint64_t integ_check_1;
	extern uint64_t add_event_to_list;
	extern uint64_t send_network_event;
	extern uint64_t send_http_request;
	extern uint64_t check_crc;
	extern uint64_t report_myself;
	extern uint64_t cash_spawn;
	extern uint64_t queue_dependency;
	extern uint64_t start_get_session_by_gamer_handle;	
	extern uint64_t encode_session_info;
	extern uint64_t decode_session_info;
	extern uint64_t join_session_by_info;
	extern uint64_t generate_uuid;
	extern uint64_t begin_service;
	extern uint64_t construct_basket;
	extern uint64_t add_item_to_basket;
	extern uint64_t send_event_ack;
	extern uint64_t ped_orientation;
	extern uint64_t vehicle_orientation;
	extern uint64_t handle_rotation;
	extern uint64_t received_network_event;
	extern int* heap_size;
	extern int64_t* host_token;
	extern int64_t** script_globals;
	extern uint32_t* game_state;
	extern uint32_t* frame_count;
	extern PVOID interval_check_func;
	extern PVOID set_this_thread_networked;
	extern int* resolution_x;
	extern int* resolution_y;
	extern bool* is_session_started;
	extern void* jmp_rbx_register;

	extern memory::byte_patch* max_wanted_level;
	extern memory::byte_patch* max_wanted_level_2;

	using setup_dictionary_t = rage::pgDictionary* (*)(rage::pgDictionary* dict, int size);
	using add_texture_to_dictionary_t = void(*)(rage::pgDictionary* dict, uint32_t hash, rage::grcTexture* texture);
	using setup_store_item_t = uint32_t * (*)(rage::grcTextureStore* store, uint32_t* out, uint32_t* dictHash);
	using add_dictionary_to_pool_t = void(*)(rage::grcTextureStore* store, uint32_t slot, rage::pgDictionary* dict);
	using add_text_component_t = void(*)(const char* string);
	using get_net_game_player = CNetGamePlayer * (*) (uint32_t player);
	using read_bitbuf_dword_t = bool (*)(rage::datBitBuffer* buffer, PVOID read, int bits);
	using read_bitbuf_string_t = bool (*)(rage::datBitBuffer* buffer, char* read, int bits);
	using read_bitbuf_bool_t = bool (*)(rage::datBitBuffer* buffer, bool* read, int bits);
	using read_bitbuf_array_t = bool (*)(rage::datBitBuffer* buffer, PVOID read, int bits, int unk);
	using write_bitbuf_qword_t = bool (*)(rage::datBitBuffer* buffer, uint64_t val, int bits);
	using write_bitbuf_dword_t = bool (*)(rage::datBitBuffer* buffer, uint32_t val, int bits);
	using write_bitbuf_int64_t = bool (*)(rage::datBitBuffer* buffer, int64_t val, int bits);
	using write_bitbuf_int32_t = bool (*)(rage::datBitBuffer* buffer, int32_t val, int bits);
	using write_bitbuf_bool_t = bool (*)(rage::datBitBuffer* buffer, bool val, int bits);
	using write_bitbuf_array_t = bool (*)(rage::datBitBuffer* buffer, void* val, int bits, int unk);
	using fix_vectors_t = void(*)(rage::scrNativeCallContext* call_ctx);
	using handle_to_ptr_t = rage::CDynamicEntity* (*)(Entity);
	using request_control_t = void (*)(rage::netObject* net_object);
	using ptr_to_handle_t = Entity(*)(void*);
	using get_native_handler_t = rage::scrNativeHandler(*)(rage::scrNativeRegistrationTable* registration_table, rage::scrNativeHash hash);

	extern read_bitbuf_dword_t read_bitbuf_dword;
	extern read_bitbuf_string_t read_bitbuf_string;
	extern read_bitbuf_bool_t read_bitbuf_bool;
	extern read_bitbuf_array_t read_bitbuf_array;
	extern write_bitbuf_qword_t write_bitbuf_qword;
	extern write_bitbuf_dword_t write_bitbuf_dword;
	extern write_bitbuf_int64_t write_bitbuf_int64;
	extern write_bitbuf_int32_t write_bitbuf_int32;
	extern write_bitbuf_bool_t write_bitbuf_bool;
	extern write_bitbuf_array_t write_bitbuf_array;
	extern fix_vectors_t fix_vectors;
	extern handle_to_ptr_t handle_to_ptr;
	extern request_control_t request_control;
	extern get_net_game_player get_net_player;
	extern setup_dictionary_t setup_dictionary;
	extern add_texture_to_dictionary_t add_texture_to_dictionary;
	extern setup_store_item_t setup_store_item;
	extern add_dictionary_to_pool_t add_dictionary_to_pool;
	extern ptr_to_handle_t ptr_to_handle;
	extern get_native_handler_t get_native_handler;

	extern PVOID* draw_handler_mgr;
	extern rage::types::memory_heap_pt* memory_heap_pool;


	using get_sync_type_info_t = const char* (*)(uint16_t sync_type, char a2);

	using get_sync_tree_for_type_t = rage::netSyncTree* (*)(CNetworkObjectMgr* mgr, uint16_t sync_type);

	using get_net_object_t = rage::netObject* (*)(CNetworkObjectMgr* mgr, int16_t id, bool can_delete_be_pending);

	using get_net_object_for_player_t = rage::netObject* (*)(CNetworkObjectMgr*, int16_t, CNetGamePlayer*, bool);

	using read_bitbuffer_into_sync_tree_t = void (*)(rage::netSyncTree* tree, uint64_t flag, uint32_t flag2, rage::datBitBuffer* buffer, uint64_t netLogStub);

	extern uint64_t receive_clone_sync;
	extern uint64_t receive_clone_create;
	extern uint64_t receive_clone_remove;
	extern uint64_t receive_clone_remove_ack;
	extern uint64_t receive_clone_create_ack;
	extern uint64_t receive_clone_sync_ack;
	extern uint64_t can_apply_data;
	extern get_sync_tree_for_type_t get_sync_tree_for_type;
	extern get_sync_type_info_t get_sync_type_info;
	extern get_net_object_t get_net_object;
	extern read_bitbuffer_into_sync_tree_t read_bitbuffer_into_sync_tree;
	extern uint64_t get_entity_attached_to;
	extern HashTable<CBaseModelInfo*>* model_table;

	extern uint64_t arxanCheckFunction;

	extern uint64_t tick_script_thread;

	using increment_stat_t = void (*) (Hash hash, unsigned int value, CNetGamePlayer* player);
	extern increment_stat_t remote_increment_stat;

	using give_pickup_rewards_t = void(*)(int players, uint32_t hash);
	extern give_pickup_rewards_t give_pickup_rewards;

	using trigger_script_event_t = void(*)(int event_group, int64_t* args, int arg_count, int player_bits);
	extern trigger_script_event_t trigger_script_event;

	extern uint64_t invalid_decal;
	extern uint64_t invalid_mods;
	extern uint64_t parachute_crash_patch;
	extern uint64_t parachute_crash_patch2;
	extern uint64_t fragment_crash;

	extern uint64_t network_event_data;
	extern uint64_t read_new_script_host_message;
	extern uint64_t apply_player_physical_index;

	extern uint64_t receive_array_broadcast;

	inline CNetGamePlayer* g_syncing_player;
	inline eNetObjType g_syncing_object_type = (eNetObjType)-1;

	extern uint64_t write_player_game_state_data_node;
	extern uint64_t write_ped_health_data_node;

	extern uint64_t receive_presence_event;

	extern uint64_t update_presence_attribute_int;
	extern uint64_t update_presence_attribute_string;
	extern uint64_t start_get_presence_attributes;
	extern uint64_t write_gs_item;

	using clear_ped_tasks_network_t = void (*)(CPed* ped, bool immediately);
	extern clear_ped_tasks_network_t clear_ped_tasks_network;

	extern PVOID world_model_spawn_bypass;
	using request_ragdoll_t = void (*)(uint16_t object_id);
	extern request_ragdoll_t request_ragdoll;

	extern memory::byte_patch* blame_explode;

	extern ScInfo* sc_info;
	extern FriendRegistry* friend_registry;
	extern uint64_t init_native_tables;

	extern ChatData** chat_data;
	extern int64_t** chat_ptr;

	//using send_chat_message_t = bool (*)(int64_t* send_chat_ptr, rage::rlGamerInfo* gamer_info, const char* message, bool is_team);
	extern uint64_t send_chat_message;
	extern uint64_t receive_net_message;
	extern uint64_t chat_profanity;

	using get_model_info_t = uint64_t(*)(rage::joaat_t hash, uint32_t* ctx);
	extern get_model_info_t get_model_info;

	using remove_reference_t = void (*)(rage::fwRefAwareBase* object, void* reference);
	extern remove_reference_t remove_reference;

	extern uint64_t dispatch_table;

	extern rage::ocean_quads ocean_quads;
	extern rage::water_tune* water_tune;

	extern rage::TimecycleKeyframeData* ui_weather;

	inline bool m_disable_sky = true;

	extern uint64_t send_metric;

	extern uint64_t update_ui_values;
	extern uint64_t update_ui_values_2;

	extern uint64_t sync_data_reader_vtable;
	extern uint64_t sync_data_writer_vtable;
	extern rage::waypoint_data* waypoint_data;

	extern uint64_t set_seethrough;

	extern rage::CWeatherVfx* weather_fx;
	extern rage::CGameVisuals* game_visuals;
	extern rage::CVisualVfx* visual_settings;

	extern rage::replay::CReplayInterface** replay_interface;

	extern uint64_t mobile_radio;

	extern uint64_t read_train_data_node;
	extern uint64_t infinite_train_crash;

	using get_next_carriage_t = void* (*)(void* carriage);
	extern get_next_carriage_t get_next_carriage;
	extern uint64_t attach_crash_patch;

	extern uint64_t start_session_search;

	inline void test() {
		ui_weather->set_sky(m_disable_sky);

	}
	extern rage::atArray<CTrainConfig>* train_config_array;
	using check_event_queue_t = bool (*)(rage::netEventMgr* mgr, bool free);
	using get_new_pool_item_t = void* (*)(GenericPool* pool);
	using queue_network_event_t = void (*)(rage::netEventMgr* mgr, rage::netGameEvent* event);
	extern rage::netEventMgr** m_net_event_manager;
	extern GenericPool** m_net_event_pool;
	extern check_event_queue_t m_check_event_queue;
	extern get_new_pool_item_t m_get_new_pool_item;
	extern queue_network_event_t m_queue_network_event;

	extern GenericPool** interior_proxy_pool;

	extern rage::vfx_liquid* vfx_liquid;
}