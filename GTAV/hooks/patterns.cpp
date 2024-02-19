#include "pch.h"
#include "patterns.h"

namespace patterns {
	rage::scrNativeRegistrationTable* native_registration_table;
	rage::scrProgramTable* script_program;
	rage::hash_list* hash_list;
	rage::weapon_hash_list* weapon_components;
	rage::weapon_hash_list* weapon_info;
	rage::types::store_manager* store_manager;
	CPedFactory** ped_factory;
	CNetworkObjectMgr** network_object_mgr;
	rage::grcTextureStore* texture_store;
	rage::grcTextureFactory** texture_factory;
	IDXGISwapChain** swapchain;
	GenericPool** ped_pool;
	GenericPool** prop_pool;
	VehiclePool*** vehicle_pool;
	GenericPool** pickup_pool;
	std::pair<CWheelVfx*, uint8_t> vfx_wheel;
	CBlipList* blip_list;
	rage::atArray<GtaThread*>* script_threads;
	CNetworkPlayerMgr** network_player_mgr;
	Network** network;
	rage::rlGamerInfo* profile_gamer_info;
	rage::rlGamerInfo* player_info_gamer_info;
	CCommunications** communications;
	rage::netShopping::CNetworkShoppingMgr* net_shop_mgr;

	uint64_t script_vm;
	uint64_t get_font_id;
	uint64_t font_table;
	uint64_t font_memory_helper;
	uint64_t get_font_id_table;
	uint64_t construct_gfx_font;
	uint64_t destruct;
	uint64_t create_id_for_font;
	uint64_t add_font_lib;
	uint64_t get_store_module_extension;
	uint64_t register_streaming_file;
	uint64_t request_streaming_file;
	uint64_t format_game_string;
	uint64_t get_game_string_line_count;
	uint64_t allow_weapons_in_vehicle;
	uint64_t get_entity_address;
	uint64_t set_vehicle_gravity;
	uint64_t invalid_resource_check;
	uint64_t ac_patch_1;//48 8B C4 48 89 58 18 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 48 8D 8D ? ? ? ? 0F 29 70 B8 E8 ? ? ? ? 48 8D 8D ? ? ? ? E8 ? ? ? ? 4C 8D 05 (detected, has self healing vtables)
	uint64_t ac_patch_2;//48 89 5C 24 ?? 55 48 8D AC 24 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 48 8B D9 48 8D 0D 
	uint64_t integ_check_1;
	uint64_t add_event_to_list;
	uint64_t send_network_event;
	uint64_t send_http_request;
	uint64_t check_crc;
	uint64_t report_myself;
	uint64_t cash_spawn;
	uint64_t queue_dependency;
	uint64_t start_get_session_by_gamer_handle;
	uint64_t encode_session_info;
	uint64_t decode_session_info;
	uint64_t join_session_by_info;
	uint64_t generate_uuid;
	uint64_t begin_service;
	uint64_t construct_basket;
	uint64_t add_item_to_basket;
	uint64_t send_event_ack;
	uint64_t ped_orientation;
	uint64_t vehicle_orientation;
	uint64_t handle_rotation;
	uint64_t received_network_event;
	int* heap_size;
	int64_t* host_token;
	int64_t** script_globals;
	uint32_t* game_state;
	uint32_t* frame_count;
	PVOID interval_check_func;
	PVOID set_this_thread_networked;
	int* resolution_x;
	int* resolution_y;
	bool* is_session_started;
	void* jmp_rbx_register;
	rage::atArray<CTrainConfig>* train_config_array;
	PVOID* draw_handler_mgr;
	memory::byte_patch* max_wanted_level;
	memory::byte_patch* max_wanted_level_2;
	GenericPool** interior_proxy_pool;
	read_bitbuf_dword_t read_bitbuf_dword;
	read_bitbuf_string_t read_bitbuf_string;
	read_bitbuf_bool_t read_bitbuf_bool;
	read_bitbuf_array_t read_bitbuf_array;
	write_bitbuf_qword_t write_bitbuf_qword;
	write_bitbuf_dword_t write_bitbuf_dword;
	write_bitbuf_int64_t write_bitbuf_int64;
	write_bitbuf_int32_t write_bitbuf_int32;
	write_bitbuf_bool_t write_bitbuf_bool;
	write_bitbuf_array_t write_bitbuf_array;
	fix_vectors_t fix_vectors;
	handle_to_ptr_t handle_to_ptr;
	request_control_t request_control;
	get_net_game_player get_net_player;
	setup_dictionary_t setup_dictionary;
	add_texture_to_dictionary_t add_texture_to_dictionary;
	setup_store_item_t setup_store_item;
	add_dictionary_to_pool_t add_dictionary_to_pool;
	ptr_to_handle_t ptr_to_handle;
	get_native_handler_t get_native_handler;

	rage::types::memory_heap_pt* memory_heap_pool;
	uint64_t receive_clone_sync;
	get_sync_tree_for_type_t get_sync_tree_for_type;
	get_sync_type_info_t get_sync_type_info;
	get_net_object_t get_net_object;
	read_bitbuffer_into_sync_tree_t read_bitbuffer_into_sync_tree;
	uint64_t get_entity_attached_to;
	HashTable<CBaseModelInfo*>* model_table;

	uint64_t receive_clone_create;

	uint64_t arxanCheckFunction;
	uint64_t tick_script_thread;
	increment_stat_t remote_increment_stat;
	trigger_script_event_t trigger_script_event;

	give_pickup_rewards_t give_pickup_rewards;

	uint64_t invalid_decal;
	uint64_t invalid_mods;
	uint64_t parachute_crash_patch;
	uint64_t parachute_crash_patch2;
	uint64_t fragment_crash;

	uint64_t network_event_data;
	uint64_t read_new_script_host_message;

	uint64_t receive_clone_remove;
	uint64_t receive_clone_remove_ack;
	uint64_t receive_clone_sync_ack;
	uint64_t can_apply_data;
	uint64_t apply_player_physical_index;
	uint64_t receive_array_broadcast;

	uint64_t write_player_game_state_data_node;
	uint64_t write_ped_health_data_node;

	uint64_t receive_presence_event;
	uint64_t update_presence_attribute_int;
	uint64_t update_presence_attribute_string;
	uint64_t start_get_presence_attributes;
	uint64_t write_gs_item;
	uint64_t receive_clone_create_ack;

	clear_ped_tasks_network_t clear_ped_tasks_network;
	PVOID world_model_spawn_bypass;
	request_ragdoll_t request_ragdoll;

	memory::byte_patch* blame_explode;
	ScInfo* sc_info;
	FriendRegistry* friend_registry;
	uint64_t init_native_tables;

	ChatData** chat_data;
	int64_t** chat_ptr;
	uint64_t send_chat_message;
	uint64_t receive_net_message;
	uint64_t chat_profanity;
	get_model_info_t get_model_info;
	uint64_t dispatch_table;
	rage::TimecycleKeyframeData* ui_weather;

	uint64_t update_ui_values;
	uint64_t update_ui_values_2;
	rage::waypoint_data* waypoint_data;
	uint64_t set_seethrough;
	uint64_t sync_data_reader_vtable;
	uint64_t sync_data_writer_vtable;
	remove_reference_t remove_reference;
	rage::ocean_quads ocean_quads;
	rage::water_tune* water_tune;

	rage::netEventMgr** m_net_event_manager;
	GenericPool** m_net_event_pool;
	check_event_queue_t m_check_event_queue;
	get_new_pool_item_t m_get_new_pool_item;
	queue_network_event_t m_queue_network_event;
	rage::vfx_liquid* vfx_liquid;
	uint64_t send_metric;
	rage::CWeatherVfx* weather_fx;
	rage::CGameVisuals* game_visuals;
	rage::CVisualVfx* visual_settings;
	rage::replay::CReplayInterface** replay_interface;
	uint64_t read_train_data_node;
	uint64_t infinite_train_crash;
	get_next_carriage_t get_next_carriage;
	uint64_t attach_crash_patch;
	uint64_t start_session_search;
	uint64_t mobile_radio;
}