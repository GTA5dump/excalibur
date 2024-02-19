#pragma once
#include <cstdint>

#pragma pack(push, 1)
class FriendInfo
{
public:
    char m_name[20]; //0x0000
    char pad_0014[36]; //0x0014
    uint64_t m_rockstar_id; //0x0038
    uint8_t unk; //0x0040
    char pad_0041[3]; //0x0041
    uint32_t m_friend_state; //0x0044
    char pad_0048[304]; //0x0048
    uint32_t m_is_joinable; //0x0178
    char pad_017C[4]; //0x017C
}; //Size: 0x0180
static_assert(sizeof(FriendInfo) == 0x180);
#pragma pack(pop)

#pragma pack(push, 4)
class FriendRegistry
{
public:
    uint32_t m_friend_count; //0x0000
    char pad_0004[8]; //0x0004
    FriendInfo(*m_friends)[250]; //0x000C

    inline FriendInfo* get(std::uint32_t idx)
    {
        return &(*m_friends)[idx];
    }
}; //Size: 0x0014
static_assert(sizeof(FriendRegistry) == 0x14);
#pragma pack(pop)

#pragma pack(push, 1)
class ScInfo
{
public:
    char m_ticket[208]; //0x0000
    char pad_00D0[304]; //0x00D0
    char m_session_ticket[88]; //0x0200 - rlSessionInfo base64 serialized?
    char pad_0258[40]; //0x0258
    uint32_t m_nonce; //0x0280
    char pad_0284[4]; //0x0284
    uint32_t m_account_id; //0x0288
    char pad_028C[16]; //0x028C
    char m_profile_pic[128]; //0x029C
    char pad_031C[32]; //0x031C
    char m_country_code[4]; //0x033C
    char pad_0340[31]; //0x0340
    char m_email_address[96]; //0x035F
    char pad_03BF[6]; //0x03BF
    char m_language_subtag[8]; //0x03C5
    char pad_03CD[2]; //0x03CD
    char m_sc_name[20]; //0x03CF
    char pad_03E3[533]; //0x03E3
    char m_session_key[16]; //0x05F8
    char pad_0608[2296]; //0x0608
}; //Size: 0x0F00
static_assert(sizeof(ScInfo) == 0xF00);
#pragma pack(pop)