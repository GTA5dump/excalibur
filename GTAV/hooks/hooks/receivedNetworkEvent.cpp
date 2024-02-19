#include "pch.h"
#include "hooks/hooks.h"
#include "hooks/patterns.h"
#include "util/caller.h"
#include "menu/submenus/main/protections.h"
#include "menu/submenus/main/protections/protection_network_events.h"
#include "menu/submenus/main/protections/protection_script_events.h"
#include "menu/submenus/main/protections/protection_reports.h"
#include "gui/util/notify.h"
#include "rage/classes/datBitBuffer.h"
#include "rage/classes/script_id.h"
#include "rage/classes/CPed.h"
#include "rage/classes/netGameEvent.h"
#include "rage/classes/CPlayerInfo.h"
#include "rage/classes/CNetGamePlayer.h"

namespace base::hooks {
	void sendEventAck(void* _this, CNetGamePlayer* target, CNetGamePlayer* receiver, int index, int bitset) {
		caller::call<void>(patterns::send_event_ack, _this, target, receiver, index, bitset);
	}

	static void getScriptId(CGameScriptId& id, rage::datBitBuffer& buffer) {
		id.m_hash = buffer.Read<uint32_t>(32);
		id.m_timestamp = buffer.Read<uint32_t>(32);

		if (buffer.Read<bool>(1))
			id.m_position_hash = buffer.Read<uint32_t>(32);

		if (buffer.Read<bool>(1))
			id.m_instance_id = buffer.Read<int32_t>(8);
	}

	std::string getReportNameFromHash(uint32_t hash, bool* is_report) {
		*is_report = false;

		switch (hash) {
		case 0x9C6A0C42: *is_report = true; return "Griefing";
		case 0xCBFD04A4: *is_report = true; return "Game Exploits";
		case 0x9F79BA0B: *is_report = true; return "Exploits";
		case 0xEC3CE96A: *is_report = true; return "Cheating";
		case 0x62EB8C5A: *is_report = true; return "Annoying in VC";
		case 0x0E7072CD: *is_report = true; return "Hateful in VC";
		case 0x762F9994: *is_report = true; return "Annoying in Chat";
		case 0xB722D6C0: *is_report = true; return "Hateful in Chat";
		case 0xDAFB10F9: return "Being Friendly";
		case 0x893E1390: return "Being Helpful";
		}

		std::stringstream stream;
		stream << "0x" << std::hex << hash;
		return stream.str();
	}

	void handleScriptEvent(std::string name, std::string type, bool notify) {
		if (notify)
			menu::notify::stacked(std::format("Blocked {} From {}", type, name).c_str());
	}

	bool isPlayerDriverOfLocalVehicle(Player sender) {
		if (!patterns::get_net_player(sender)->m_player_id || !patterns::get_net_player(sender)->m_player_info->m_ped->m_vehicle || !(*patterns::network_player_mgr)->m_local_net_player)
			return false;

		return (*patterns::network_player_mgr)->m_local_net_player->m_player_info->m_ped->m_vehicle->m_driver == (*patterns::network_player_mgr)->m_local_net_player->m_player_info->m_ped;
	}

	bool isPlayerGoon(Player sender) {
		auto& boss_goon = menu::scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[PLAYER::PLAYER_ID()].BossGoon;

		if (boss_goon.Boss != PLAYER::PLAYER_ID())
			return false;

		for (int i = 0; i < boss_goon.Goons.Size; i++) {
			if (boss_goon.Goons[i] == sender) {
				return true;
			}
		}

		return false;
	}

	bool scriptedGameEvent(rage::CScriptedGameEvent* event, CNetGamePlayer* player) {
		const auto args = event->m_args;

		const auto hash = static_cast<eRemoteEvent>(args[0]);
		const auto player_name = player->GetName();
		const auto var = menu::protections::script_events::vars::m_vars;

		switch (hash) {
		case eRemoteEvent::Bounty:
			switch (var.block_bounty_id) {
			case 0:
				break;
			case 1:
				if (args[2] == PLAYER::PLAYER_ID()) {
					return true;
				}
				break; 
			case 2:
				if (args[2] == PLAYER::PLAYER_ID()) {
					handleScriptEvent(player_name, "Bounty", true);
					return true;
				}
				break;
			}
			break;
		case eRemoteEvent::CeoKick:
			switch (var.block_ceo_kick_id) {
			case 0:
				break;
			case 1:
				if (player->m_player_id != menu::scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[PLAYER::PLAYER_ID()].BossGoon.Boss) {
					return true;
				}
				break;
			case 2:
				if (player->m_player_id != menu::scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[PLAYER::PLAYER_ID()].BossGoon.Boss) {
					handleScriptEvent(player_name, "Ceo Kick", true);
					return true;
				}
				break;
			}
			break;
		case eRemoteEvent::CeoMoney:
			switch (var.block_ceo_money_id) {
			case 0:
				break;
			case 1:
				if (player->m_player_id != menu::scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[PLAYER::PLAYER_ID()].BossGoon.Boss) {
					return true;
				}
				break;
			case 2:
				if (player->m_player_id != menu::scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[PLAYER::PLAYER_ID()].BossGoon.Boss) {
					handleScriptEvent(player_name, "Ceo Money", true);
					return true;
				}
				break;
			}
			break;
		case eRemoteEvent::ClearWantedLevel:
			switch (var.block_clear_wanted_level_id) {
			case 0:
				break;
			case 1:
				if (!isPlayerDriverOfLocalVehicle(player->m_player_id)) {
					return true;
				}
				break;
			case 2:
				if (!isPlayerDriverOfLocalVehicle(player->m_player_id)) {
					handleScriptEvent(player_name, "Clear Wanted Level", true);
					return true;
				}
				break;
			}
			break;
		case eRemoteEvent::Crash: return true;
		case eRemoteEvent::Crash2:
			switch (var.block_script_crashes_id) {
			case 0:
				break;
			case 1:
				if (args[2] > 32) {
					return true;
				}
				break;
			case 2:
				if (args[2] > 32) {
					handleScriptEvent(player_name, "Script Crash", true);
					return true;
				}
				break;
			}
			break;
		case eRemoteEvent::Crash3:
			switch (var.block_script_crashes_id) {
			case 0:
				break;
			case 1:
				if (isnan(*(float*)&args[3]) || isnan(*(float*)&args[4])){
					return true;
				}
				break;
			case 2:
				if (isnan(*(float*)&args[3]) || isnan(*(float*)&args[4])) {
					handleScriptEvent(player_name, "Script Crash", true);
					return true;
				}
				break;
			}
			break;
		case eRemoteEvent::Notification:
			switch (static_cast<eRemoteEvent>(args[2]))
			{
			case eRemoteEvent::NotificationMoneyBanked:
			case eRemoteEvent::NotificationMoneyRemoved:
			case eRemoteEvent::NotificationMoneyStolen:
				switch (var.block_notifications_id) {
				case 0: break;
				case 1:  return true; break;
				case 2: handleScriptEvent(player_name, "Notification", true); return true; break;
				}
				break;
			case eRemoteEvent::NotificationCrash1:                             // this isn't used by the game
				return true;
			case eRemoteEvent::NotificationCrash2:
				if (!rage::engine::find_script_thread(RAGE_JOAAT("gb_salvage")))
				{
					return true;
				}
				break;
			}
			break;
		case eRemoteEvent::ForceMission:
			switch (var.block_force_to_mission_id) {
			case 0: break;
			case 1:  return true; break;
			case 2: handleScriptEvent(player_name, "Force to Mission", true); return true; break;
			}
			break;
		case eRemoteEvent::GiveCollectible:
			switch (var.block_give_collectible_id) {
			case 0: break;
			case 1:  return true; break;
			case 2: handleScriptEvent(player_name, "Give Collectible", true); return true; break;
			}
			break;
		case eRemoteEvent::GtaBanner:
			switch (var.block_gta_banner_id) {
			case 0: break;
			case 1:  return true; break;
			case 2: handleScriptEvent(player_name, "GTA Banner", true); return true; break;
			}
			break;
		case eRemoteEvent::MCTeleport:
			if (args[3] <= 32) {
				for (int i = 0; i < 32; i++)
				{
					if (args[4 + i] == NETWORK::NETWORK_HASH_FROM_PLAYER_HANDLE(PLAYER::PLAYER_ID()))
					{
						switch (var.block_force_teleport_id) {
						case 0: break;
						case 1:  return true; break;
						case 2: handleScriptEvent(player_name, "Force Teleport", true); return true; break;
						}
					}
				}
			}
			else if (args[3] > 32) {
				return true;
			}
			break;
		case eRemoteEvent::PersonalVehicleDestroyed:
			switch (var.block_insurance_message_id) {
			case 0: break;
			case 1:  return true; break;
			case 2: handleScriptEvent(player_name, "Insurance Message", true); return true; break;
			}
			break;
		case eRemoteEvent::RemoteOffradar:
			if (player->m_player_id != menu::scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[PLAYER::PLAYER_ID()].BossGoon.Boss) {
				switch (var.block_remote_off_radar_id) {
				case 0: break;
				case 1:  return true; break;
				case 2: handleScriptEvent(player_name, "Remote Off the Radar", true); return true; break;
				}
			}
			break;
		case eRemoteEvent::TSECommand:
			if (static_cast<eRemoteEvent>(args[2]) == eRemoteEvent::TSECommandRotateCam && !(*patterns::network)->m_is_activity_session) {
				switch (var.block_rotate_cam_id) {
				case 0: break;
				case 1:  return true; break;
				case 2: handleScriptEvent(player_name, "Rotate Camera", true); return true; break;
				}
			}
			break;
		case eRemoteEvent::SendToCayoPerico:
			if (args[3] == 0) {
				switch (var.block_force_to_cayo_id) {
				case 0: break;
				case 1:  return true; break;
				case 2: handleScriptEvent(player_name, "Force to Cayo", true); return true; break;
				}
			}
			break;
		case eRemoteEvent::SendToCutscene:
			if (player->m_player_id != menu::scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[PLAYER::PLAYER_ID()].BossGoon.Boss) {
				switch (var.block_force_to_cutscene_id) {
				case 0: break;
				case 1:  return true; break;
				case 2: handleScriptEvent(player_name, "Force to Cutscene", true); return true; break;
				}
			}
			break;
		case eRemoteEvent::SendToLocation: {
			bool known_location = false;

			if (args[2] == 0 && args[3] == 0) {
				if (args[4] == 4 && args[5] == 0) {
					known_location = true;

					switch (var.block_force_teleport_id) {
					case 0: break;
					case 1:  return true; break;
					case 2: handleScriptEvent(player_name, "Force Teleport", true); return true; break;
					}
				}
				else if ((args[4] == 3 || args[4] == 4) && args[5] == 1) {
					known_location = true;

					switch (var.block_force_teleport_id) {
					case 0: break;
					case 1:  return true; break;
					case 2: handleScriptEvent(player_name, "Force Teleport", true); return true; break;
					}
				}
			}

			if (!known_location) {
				return true;
			}
			break;
		}
		case eRemoteEvent::SoundSpam:
			switch (var.block_script_sound_spam_id) {
			case 0: break;
			case 1:  return true; break;
			case 2: handleScriptEvent(player_name, "Sound Spam", true); return true; break;
			}
			break;
		case eRemoteEvent::Spectate:
			switch (var.block_spectate_message_id) {
			case 0: break;
			case 1:  return true; break;
			case 2: handleScriptEvent(player_name, "Spectate Message", true); return true; break;
			}
			break;
		case eRemoteEvent::Teleport:		
			switch (var.block_force_teleport_id) {
			case 0: break;
			case 1:  return true; break;
			case 2: handleScriptEvent(player_name, "Force Teleport", true); return true; break;
			}			
			break;
		case eRemoteEvent::TransactionError: return true;
		case eRemoteEvent::VehicleKick:
			switch (var.block_vehicle_kick_id) {
			case 0: break;
			case 1:  return true; break;
			case 2: handleScriptEvent(player_name, "Vehicle Kick", true); return true; break;
			}
			break;
		case eRemoteEvent::NetworkBail:
			return true;
		case eRemoteEvent::TeleportToWarehouse:
			switch (var.block_force_teleport_id) {
			case 0: break;
			case 1:  return true; break;
			case 2: handleScriptEvent(player_name, "Force Teleport", true); return true; break;
			}
			break;
		case eRemoteEvent::StartActivity:
		{
			eActivityType activity = static_cast<eActivityType>(args[2]);
			if (activity == eActivityType::Survival || activity == eActivityType::Mission || activity == eActivityType::Deathmatch || activity == eActivityType::BaseJump || activity == eActivityType::Race) {
				return true;
			}
			else if (activity == eActivityType::Darts) {
				return true;
			}
			else if (activity == eActivityType::PilotSchool) {
				return true;
			}
			else if (activity == eActivityType::ImpromptuDeathmatch) {
				return true;
			}
			else if (activity == eActivityType::DefendSpecialCargo || activity == eActivityType::GunrunningDefend || activity == eActivityType::BikerDefend || args[2] == 238) {
				return true;
			}
			else if (activity == eActivityType::Tennis)
			{
				return true;
			}
			switch (var.block_force_to_activity_id) {
			case 0: break;
			case 1:  return true; break;
			case 2: handleScriptEvent(player_name, "Force to Activity", true); return true; break;
			}
			break;
		}
		case eRemoteEvent::InteriorControl:
		{
			int interior = (int)args[2];
			if (interior < 0 || interior > 161) {
				return true;
			}
			break;
		}
		case eRemoteEvent::KickFromInterior:
			if (menu::scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[PLAYER::PLAYER_ID()].SimpleInteriorData.Owner != player->m_player_id)
			{
				handleScriptEvent(player_name, "Kick from Interior", true);
				return true;
			}
			break;
		case eRemoteEvent::TriggerCEORaid:
		{
			if (auto script = rage::engine::find_script_thread(RAGE_JOAAT("freemode")))
			{
				if (script->m_net_component && ((CGameScriptHandlerNetComponent*)script->m_net_component)->m_host && ((CGameScriptHandlerNetComponent*)script->m_net_component)->m_host->m_net_game_player != player)
				{
					handleScriptEvent(player_name, "Trigger CEO Raid", true);
				}
			}

			return true;
		}
		}

		if (*(int*)&args[1] != player->m_player_id && player->m_player_id != -1) {
			return true;
		}

		if (menu::protections::vars::m_vars.m_block_all_script_events) {
			return true;
		}

		return false;
	}

	void hooks::receivedNetworkEventHook(void* _this, CNetGamePlayer* sender, CNetGamePlayer* receiver, uint16_t event_id, int event_index, int event_bitset, uint32_t buffer_size, rage::datBitBuffer* buffer) {

		if (event_id > 91u) {
			sendEventAck(_this, sender, receiver, event_index, event_bitset);
			return;
		}

		const auto eventName = *(char**)((DWORD64)_this + 8i64 * event_id + 243376);
		if (eventName == nullptr || sender == nullptr || sender->m_player_id < 0 || sender->m_player_id >= 32) {
			sendEventAck(_this, sender, receiver, event_index, event_bitset);
			return;
		}

		const auto var = menu::protections::network_events::vars::m_vars;

		switch (static_cast<eNetworkEvents>(event_id)) {
		case eNetworkEvents::SCRIPTED_GAME_EVENT:
		{
			const auto scripted_game_event = std::make_unique<rage::CScriptedGameEvent>();
			buffer->ReadDword(&scripted_game_event->m_args_size, 32);
			if (scripted_game_event->m_args_size - 1 <= 0x1AF)
				buffer->ReadArray(&scripted_game_event->m_args, 8 * scripted_game_event->m_args_size);

			if (scriptedGameEvent(scripted_game_event.get(), sender))
			{
				sendEventAck(_this, sender, receiver, event_index, event_bitset);
				return;
			}
			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::NETWORK_INCREMENT_STAT_EVENT:
		{
			const auto increment_stat_event = std::make_unique<rage::CNetworkIncrementStatEvent>();
			buffer->ReadDword(&increment_stat_event->m_stat, 0x20);
			buffer->ReadDword(&increment_stat_event->m_amount, 0x20);

			bool is_report = false;
			std::string hash_string = getReportNameFromHash(increment_stat_event->m_stat, &is_report);
			const auto& Var = menu::protections::reports::vars::m_vars;
			switch (Var.block_reports_id) {
			case 0:
				break;
			case 1:
				if (is_report) {
					sendEventAck(_this, sender, receiver, event_index, event_bitset);
					buffer->Seek(0);
					return;
				}
				break;
			case 2:
				if (is_report) {
					sendEventAck(_this, sender, receiver, event_index, event_bitset);
					menu::notify::stacked(std::format("Blocked {} Report from {}", hash_string, sender->GetName()).c_str());
					buffer->Seek(0);
					return;
				}
				break;
			}

			buffer->Seek(0);
			break;
		}
		//EVENTS
		case eNetworkEvents::EXPLOSION_EVENT: {
			uint16_t f186;
			uint16_t f208;
			int ownerNetId;
			uint16_t f214;
			eExplosionTag explosionType;
			float damageScale;

			float posX;
			float posY;
			float posZ;

			bool f242;
			uint16_t f104;
			float cameraShake;

			bool isAudible;
			bool f189;
			bool isInvisible;
			bool f126;
			bool f241;
			bool f243;

			uint16_t f210;

			float unkX;
			float unkY;
			float unkZ;

			bool f190;
			bool f191;

			uint32_t f164;

			float posX224;
			float posY224;
			float posZ224;

			bool f240;
			uint16_t f218;
			bool f216;

			// clang-format off

			f186 = buffer->Read<uint16_t>(16);
			f208 = buffer->Read<uint16_t>(13);
			ownerNetId = buffer->Read<uint16_t>(13);
			f214 = buffer->Read<uint16_t>(13);               // 1604+
			explosionType = (eExplosionTag)buffer->ReadSigned<int>(8);// 1604+ bit size
			damageScale = buffer->Read<int>(8) / 255.0f;

			posX = buffer->ReadSignedFloat(22, 27648.0f);
			posY = buffer->ReadSignedFloat(22, 27648.0f);
			posZ = buffer->ReadFloat(22, 4416.0f) - 1700.0f;

			f242 = buffer->Read<uint8_t>(1);
			f104 = buffer->Read<uint16_t>(16);
			cameraShake = buffer->Read<int>(8) / 127.0f;

			isAudible = buffer->Read<uint8_t>(1);
			f189 = buffer->Read<uint8_t>(1);
			isInvisible = buffer->Read<uint8_t>(1);
			f126 = buffer->Read<uint8_t>(1);
			f241 = buffer->Read<uint8_t>(1);
			f243 = buffer->Read<uint8_t>(1);// 1604+

			f210 = buffer->Read<uint16_t>(13);

			unkX = buffer->ReadSignedFloat(16, 1.1f);
			unkY = buffer->ReadSignedFloat(16, 1.1f);
			unkZ = buffer->ReadSignedFloat(16, 1.1f);

			f190 = buffer->Read<uint8_t>(1);
			f191 = buffer->Read<uint8_t>(1);
			f164 = buffer->Read<uint32_t>(32);

			if (f242)
			{
				posX224 = buffer->ReadSignedFloat(31, 27648.0f);
				posY224 = buffer->ReadSignedFloat(31, 27648.0f);
				posZ224 = buffer->ReadFloat(31, 4416.0f) - 1700.0f;
			}
			else
			{
				posX224 = 0;
				posY224 = 0;
				posZ224 = 0;
			}

			auto f168 = buffer->Read<uint32_t>(32);// >= 1868: f_168


			f240 = buffer->Read<uint8_t>(1);
			if (f240)
			{
				f218 = buffer->Read<uint16_t>(16);

				if (f191)
				{
					f216 = buffer->Read<uint8_t>(8);
				}
			}

			buffer->Seek(0);

			switch (var.block_explosion_id) {
			case 0:
				break;
			case 1:
				sendEventAck(_this, sender, receiver, event_index, event_bitset);
				buffer->Seek(0);
				return;
				break;
			case 2:
				menu::notify::stacked(std::format("Blocked Explosion From {}", sender->GetName()).c_str());
				sendEventAck(_this, sender, receiver, event_index, event_bitset);
				buffer->Seek(0);
				return;
				break;
			default:
				break;
			}
			break;
		}
		case eNetworkEvents::GIVE_WEAPON_EVENT: {
			if (sender->m_player_id < 32) {
				switch (var.block_give_weapons_id) {
				case 0: break;
				case 1: sendEventAck(_this, sender, receiver, event_index, event_bitset); buffer->Seek(0); return; break;
				case 2: menu::notify::stacked(std::format("Blocked remove weapons from {}", sender->GetName()).c_str()); sendEventAck(_this, sender, receiver, event_index, event_bitset); buffer->Seek(0); return; break;
				default: break;
				}
			}
			break;
		}
		case eNetworkEvents::REMOVE_ALL_WEAPONS_EVENT: {
			if (sender->m_player_id < 32) {
				switch (var.block_remove_weapons_id) {
				case 0: break;
				case 1: sendEventAck(_this, sender, receiver, event_index, event_bitset); buffer->Seek(0); return; break;
				case 2: menu::notify::stacked(std::format("Blocked remove weapons from {}", sender->GetName()).c_str()); sendEventAck(_this, sender, receiver, event_index, event_bitset); buffer->Seek(0); return; break;
				default: break;
				}
			}
			break;
		}
		case eNetworkEvents::NETWORK_CHECK_CATALOG_CRC:
		case eNetworkEvents::NETWORK_CHECK_CODE_CRCS_EVENT:
		case eNetworkEvents::NETWORK_CRC_HASH_CHECK_EVENT:
		{
			LOG_ERROR(std::format("{} Triggered a CRC Check", sender->GetName()).c_str());
			break;
		}
		case eNetworkEvents::REMOVE_WEAPON_EVENT: {
			int net_id = buffer->Read<int>(13);
			uint32_t hash = buffer->Read<uint32_t>(32);
			if (hash == RAGE_JOAAT("WEAPON_UNARMED")) {
				sendEventAck(_this, sender, receiver, event_index, event_bitset);
				menu::notify::stacked(std::format("{} Sent a crash event", sender->GetName()).c_str());
				buffer->Seek(0);
				return;
			}
			if (sender->m_player_id < 32) {
				switch (var.block_remove_weapons_id) {
				case 0: break;
				case 1: sendEventAck(_this, sender, receiver, event_index, event_bitset); buffer->Seek(0); return; break;
				case 2: menu::notify::stacked(std::format("Blocked remove weapons from {}", sender->GetName()).c_str()); sendEventAck(_this, sender, receiver, event_index, event_bitset); buffer->Seek(0); return; break;
				default: break;
				}
			}
			break;
		}
		case eNetworkEvents::NETWORK_CLEAR_PED_TASKS_EVENT: {
			int net_id = buffer->Read<int>(13);

			switch (var.block_clear_tasks_id) {
			case 0:
				break;
			case 1:
				if ((*patterns::ped_factory)->m_local_ped && (*patterns::ped_factory)->m_local_ped->m_net_object && (*patterns::ped_factory)->m_local_ped->m_net_object->m_object_id == net_id) {
					sendEventAck(_this, sender, receiver, event_index, event_bitset);
					buffer->Seek(0);
					return;
				}
				break;
			case 2:
				if ((*patterns::ped_factory)->m_local_ped && (*patterns::ped_factory)->m_local_ped->m_net_object && (*patterns::ped_factory)->m_local_ped->m_net_object->m_object_id == net_id) {
					sendEventAck(_this, sender, receiver, event_index, event_bitset);
					menu::notify::stacked(std::format("Blocked Freeze From {}", sender->GetName()).c_str());
					buffer->Seek(0);
					return;
				}
				break;
			}
			break;
		}
		case eNetworkEvents::REQUEST_CONTROL_EVENT: {
			if (sender->m_player_id < 32) {
				switch (var.block_request_control_id) {
				case 0:
					break;
				case 1:
					sendEventAck(_this, sender, receiver, event_index, event_bitset);
					buffer->Seek(0);
					return;
					break;
				case 2:
					sendEventAck(_this, sender, receiver, event_index, event_bitset);
					buffer->Seek(0);
					return;
					break;
				}
			}
			break;
		}
		case eNetworkEvents::NETWORK_PTFX_EVENT: {
			if (sender->m_player_id < 32) {
				switch (var.block_ptfx_id) {
				case 0: break;
				case 1:  sendEventAck(_this, sender, receiver, event_index, event_bitset); buffer->Seek(0); return; break;
				case 2:  menu::notify::stacked(std::format("Blocked PTFX From {}", sender->GetName()).c_str()); sendEventAck(_this, sender, receiver, event_index, event_bitset); buffer->Seek(0); return; break;
				default: break;
				}
			}
			buffer->Seek(0);
			break;
		}
		case eNetworkEvents::RAGDOLL_REQUEST_EVENT: {
			if (sender->m_player_id < 32) {
				switch (var.block_ragdoll_id) {
				case 0: break;
				case 1: sendEventAck(_this, sender, receiver, event_index, event_bitset); return; buffer->Seek(0); break;
				case 2: menu::notify::stacked(std::format("Blocked Ragdoll From {}", sender->GetName()).c_str()); sendEventAck(_this, sender, receiver, event_index, event_bitset);  buffer->Seek(0); return; break;
				default: break;
				}
			}
			break;
		}
		//CRASHES
		case eNetworkEvents::GIVE_CONTROL_EVENT:
			switch (var.block_network_crashes_id) {
			case 0:
				break;
			case 1:
			{
				uint32_t timestamp = buffer->Read<uint32_t>(32);
				int count = buffer->Read<int>(2);
				bool all_objects_migrate_together = buffer->Read<bool>(1);
				eNetObjType sync_type;

				if (count > 3)
				{
					count = 3;
				}

				for (int i = 0; i < count; i++)
				{
					int net_id = buffer->Read<int>(13);
					eNetObjType object_type = buffer->Read<eNetObjType>(4);
					int migration_type = buffer->Read<int>(3);

					if (object_type < eNetObjType::NET_OBJ_TYPE_AUTOMOBILE || object_type > eNetObjType::NET_OBJ_TYPE_TRAIN)
					{
						menu::notify::stacked(std::format("{} Sent a crash event", sender->GetName()).c_str());
						sendEventAck(_this, sender, receiver, event_index, event_bitset);
						return;
					}

					sync_type = object_type;
				}

				buffer->Seek(0);

				if (count)
				{
					patterns::g_syncing_player = sender;
					patterns::g_syncing_object_type = sync_type;
				}

				break;
			}
			case 2: 
			{
				uint32_t timestamp = buffer->Read<uint32_t>(32);
				int count = buffer->Read<int>(2);
				bool all_objects_migrate_together = buffer->Read<bool>(1);

				if (count > 3)
				{
					count = 3;
				}

				for (int i = 0; i < count; i++)
				{
					int net_id = buffer->Read<int>(13);
					eNetObjType object_type = buffer->Read<eNetObjType>(4);
					int migration_type = buffer->Read<int>(3);

					if (object_type < eNetObjType::NET_OBJ_TYPE_AUTOMOBILE || object_type > eNetObjType::NET_OBJ_TYPE_TRAIN)
					{
						menu::notify::stacked(std::format("{} Sent a crash event", sender->GetName()).c_str());
						sendEventAck(_this, sender, receiver, event_index, event_bitset);
						return;
					}
				}

				buffer->Seek(0);
				break;
			}
			default: break;
			}
			break;
		case eNetworkEvents::SCRIPT_ENTITY_STATE_CHANGE_EVENT:
			switch (var.block_network_crashes_id) {
			case 0:
				break;
			case 1:
			{
				uint16_t entity = buffer->Read<uint16_t>(13);
				auto type = buffer->Read<ScriptEntityChangeType>(4);
				uint32_t unk = buffer->Read<uint32_t>(32);
				if (type == ScriptEntityChangeType::SettingOfTaskVehicleTempAction)
				{
					uint16_t ped_id = buffer->Read<uint16_t>(13);
					uint32_t action = buffer->Read<uint32_t>(8);

					if ((action >= 15 && action <= 18) || action == 33)
					{
						sendEventAck(_this, sender, receiver, event_index, event_bitset);
						return;
					}
				}
				else if (type > ScriptEntityChangeType::SetVehicleExclusiveDriver || type < ScriptEntityChangeType::BlockingOfNonTemporaryEvents)
				{
					sendEventAck(_this, sender, receiver, event_index, event_bitset);
					return;
				}
				buffer->Seek(0);
				break;
			}
			case 2:
			{
				uint16_t entity = buffer->Read<uint16_t>(13);
				auto type = buffer->Read<ScriptEntityChangeType>(4);
				uint32_t unk = buffer->Read<uint32_t>(32);
				if (type == ScriptEntityChangeType::SettingOfTaskVehicleTempAction)
				{
					uint16_t ped_id = buffer->Read<uint16_t>(13);
					uint32_t action = buffer->Read<uint32_t>(8);

					if ((action >= 15 && action <= 18) || action == 33)
					{
						sendEventAck(_this, sender, receiver, event_index, event_bitset);
						menu::notify::stacked(std::format("{} Sent a crash event", sender->GetName()).c_str());
						return;
					}
				}
				else if (type > ScriptEntityChangeType::SetVehicleExclusiveDriver || type < ScriptEntityChangeType::BlockingOfNonTemporaryEvents)
				{
					menu::notify::stacked(std::format("{} Sent a crash event", sender->GetName()).c_str());
					sendEventAck(_this, sender, receiver, event_index, event_bitset);
					return;
				}
				buffer->Seek(0);
				break;
			}
			default:
				break;
			}
			break;
		case eNetworkEvents::SCRIPT_WORLD_STATE_EVENT:
			switch (var.block_network_crashes_id) {
			case 0:
				break;
			case 1:
			{
				auto type = buffer->Read<WorldStateDataType>(4);
				buffer->Read<bool>(1);
				CGameScriptId id;
				getScriptId(id, *buffer);

				if (type == WorldStateDataType::Rope)
				{
					buffer->Read<int>(9);    // network rope id
					buffer->Read<float>(19); // pos x
					buffer->Read<float>(19); // pos y
					buffer->Read<float>(19); // pos z
					buffer->Read<float>(19); // rot x
					buffer->Read<float>(19); // rot y
					buffer->Read<float>(19); // rot z
					buffer->Read<float>(16); // length
					int type = buffer->Read<int>(4);
					float initial_length = buffer->Read<float>(16);
					float min_length = buffer->Read<float>(16);

					if (type == 0 || initial_length < min_length) // https://docs.fivem.net/natives/?_0xE832D760399EB220
					{
						sendEventAck(_this, sender, receiver, event_index, event_bitset);
						return;
					}
				}
				else if (type == WorldStateDataType::PopGroupOverride) {
					int pop_schedule = buffer->ReadSigned<int>(8); // Pop Schedule
					int pop_group = buffer->Read<int>(32);      // Pop Group
					int percentage = buffer->Read<int>(7);       // Percentage

					if (pop_group == 0 && (percentage == 0 || percentage == 103)) {
						sendEventAck(_this, sender, receiver, event_index, event_bitset);
						return;
					}
				}
				else if (type > WorldStateDataType::VehiclePlayerLocking || type < WorldStateDataType::CarGen) {
					sendEventAck(_this, sender, receiver, event_index, event_bitset);
					return;
				}

				buffer->Seek(0);
				break;
			}
			case 2:
			{
				auto type = buffer->Read<WorldStateDataType>(4);
				buffer->Read<bool>(1);
				CGameScriptId id;
				getScriptId(id, *buffer);

				if (type == WorldStateDataType::Rope)
				{
					buffer->Read<int>(9);    // network rope id
					buffer->Read<float>(19); // pos x
					buffer->Read<float>(19); // pos y
					buffer->Read<float>(19); // pos z
					buffer->Read<float>(19); // rot x
					buffer->Read<float>(19); // rot y
					buffer->Read<float>(19); // rot z
					buffer->Read<float>(16); // length
					int type = buffer->Read<int>(4);
					float initial_length = buffer->Read<float>(16);
					float min_length = buffer->Read<float>(16);

					if (type == 0 || initial_length < min_length) // https://docs.fivem.net/natives/?_0xE832D760399EB220
					{
						menu::notify::stacked(std::format("{} Sent a crash event", sender->GetName()).c_str());
						sendEventAck(_this, sender, receiver, event_index, event_bitset);
						return;
					}
				}
				else if (type == WorldStateDataType::PopGroupOverride) {
					int pop_schedule = buffer->ReadSigned<int>(8); // Pop Schedule
					int pop_group = buffer->Read<int>(32);      // Pop Group
					int percentage = buffer->Read<int>(7);       // Percentage

					if (pop_group == 0 && (percentage == 0 || percentage == 103)) {
						menu::notify::stacked(std::format("{} Sent a crash event", sender->GetName()).c_str());
						sendEventAck(_this, sender, receiver, event_index, event_bitset);
						return;
					}
				}
				else if (type > WorldStateDataType::VehiclePlayerLocking || type < WorldStateDataType::CarGen) {
					menu::notify::stacked(std::format("{} Sent a crash event", sender->GetName()).c_str());
					sendEventAck(_this, sender, receiver, event_index, event_bitset);
					return;
				}

				buffer->Seek(0);
				break;
			}
			default:
				break;
			}
			break;

		case eNetworkEvents::REPORT_CASH_SPAWN_EVENT:
			uint32_t money;

			buffer->Seek(64);
			buffer->ReadDword(&money, 32);
			buffer->Seek(0);

			if (money >= 2000)
				menu::notify::stacked(std::format("{} Triggered RAC", sender->GetName()).c_str());

			break;

		case eNetworkEvents::REPORT_MYSELF_EVENT:
			menu::notify::stacked(std::format("{} Triggered RAC", sender->GetName()).c_str());
			LOG_ERROR(std::format("{} Triggered RAC", sender->GetName()).c_str());
			break;

		case eNetworkEvents::REMOTE_SCRIPT_LEAVE_EVENT:
		case eNetworkEvents::BLOW_UP_VEHICLE_EVENT:
		case eNetworkEvents::NETWORK_PED_SEEN_DEAD_PED_EVENT:
		case eNetworkEvents::NETWORK_START_SYNCED_SCENE_EVENT:
		case eNetworkEvents::GIVE_PICKUP_REWARDS_EVENT:
		case eNetworkEvents::FIRE_EVENT:
		case eNetworkEvents::KICK_VOTES_EVENT: {
			return sendEventAck(_this, sender, receiver, event_index, event_bitset);
		}
		default:
			break;
		}


		ogReceivedNetworkEventHook(_this, sender, receiver, event_id, event_index, event_bitset, buffer_size, buffer);
	}
}