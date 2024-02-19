#pragma once
#include "fwddec.h"
#include "vector.h"
#include "CEntity.h"
#include "NetPlayer.h"
#include "Vehicle.h"

class CPedFactory {
public:
    enum class PedCreateFlags {
        IS_NETWORKED = (1 << 0),
        IS_PLAYER = (1 << 1)
    };
    virtual ~CPedFactory() = default; //0x0000 (0)
    virtual CPed* CreatePed(uint8_t* flags, uint16_t* model_index, rage::matrix44* matrix, bool default_component_variation, bool register_network_object, bool give_default_loadout, bool, bool) = 0; //0x0008 (1)
    virtual CPed* CreateClone(uint8_t* flags, uint16_t* model_index, rage::matrix44* matrix, bool default_component_variation, bool, bool register_network_object, bool) = 0; //0x0010 (2)
    virtual CPed* ClonePed(CPed* ped, bool register_network_object, bool link_blends, bool clone_compressed_damage) = 0; //0x0018 (3)
    virtual CPed* ClonePedToTarget(CPed* source, CPed* target, bool clone_compressed_damage) = 0; //0x0020 (4)
    virtual CPed* CreatePlayer(uint8_t* flags, uint16_t model_index, rage::matrix44* matrix, CPlayerInfo* player_info) = 0; //0x0028 (5)
    virtual void DestroyPed(CPed* ped) = 0; //0x0030 (6)

    class CPed* m_local_ped; //0x0008
}; //Size: 0x0010
static_assert(sizeof(CPedFactory) == 0x10);