#pragma once
#include "pch.h"
#include "util/math.h"
#include "rage/classes/atArray.h"
namespace rage {

    struct waypoint_data {
        rage::vector4* m_points;
        char _0x0008[0x3C];
        uint32_t m_count;
    };

    struct CVisualVfx {//didnt i give you this
        char pad_0000[0x2874];
        float m_shadow_light;
        float m_reflection;
        float m_gamma;
        float m_blur;
        float m_blur2;
        float m_sky_intensity;
        float m_saturation;
    };

    struct vfx_liquid {
        float m_duration_foot;
        float m_duration_wheel_in;
        float m_life_foot;
        float m_life_wheel;
        char _0x0010[0x48];
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
        char _0x005C[0x4];
    };

    struct ocean_wave_quad {
        math::vector2<short> m_min;
        math::vector2<short> m_max;
        short m_amplitude;
        math::vector2<uint8_t> m_direction;
    };

    struct ocean_calming_quad {
        math::vector2<short> m_min;
        math::vector2<short> m_max;
        float m_dampening;
    };

    struct ocean_quad {
        math::vector2<short> m_min;
        math::vector2<short> m_max;
        uint32_t m_alpha;
        char _0x000C[0x8];
        float m_height;
        char _0x0024[0x4];
    };

    struct ocean_quad_info {
        uint64_t m_quad_pool;
        short m_quad_count;
    };

    struct ocean_quads {
        ocean_quad_info* m_ocean;
        ocean_quad_info* m_wave;
        ocean_quad_info* m_calming;
    };

    struct water_tune {
        int m_water_color;
        float m_ripple_scale;
        float m_ocean_foam_scale;
        float m_specular_falloff;
        float m_fog_pierce_intensity;
        float m_refraction_blend;
        float m_refraction_exponent;
        float m_water_cycle_depth;
        float m_water_cycle_fade;
        float m_water_lightning_depth;
        float m_water_lightning_fade;
        float m_deep_water_mod_depth;
        float m_deep_water_mod_fade;
        float m_god_rays_lerp_start;
        float m_god_rays_lerp_end;
        float m_disturb_foam_scale;
        math::vector2<float> m_fog_min;
        math::vector2<float> m_fog_max;
    };
    class CGameVisuals
    {
    public:
        float m_fog_level; //0x0000
        float m_unk_0x4; //0x0004
        float m_unk_0x8; //0x0008
        float m_fov; //0x000C
    }; //Size: 0x0010
   // static_assert(sizeof(CGameVisuals) == 0x10);

    struct CWeatherVfx {//didnt i give you this
        uint32_t m_name_hash;
        char pad_1[4];
        float m_velocity;
        float m_gravity;
        char pad_2[16];
        math::vector4<float> m_box_centre_offset;
        math::vector4<float> m_box_size;
        math::vector4<float> m_life_min_max;
        math::vector4<float> m_velocity_min;
        math::vector4<float> m_velocity_max;
        char pad_3[32];
        rage::grcTexture* m_texture_1;
        rage::grcTexture* m_texture_2;
        math::vector4<float> m_texture_rows_cols_start_end;
        math::vector4<float> m_texture_anim_rate_scale_over_life_start_2_end_2;
        math::vector4<float> m_size_min_max;
        math::vector4<float> m_color;
        math::vector2<float> m_fade_in_out;
        math::vector2<float> m_fade_near_far;
        math::vector4<float> m_fade_grd_off_lo_hi;
        math::vector4<float> m_rot_speed_min_max;
        math::vector4<float> m_directional_z_offset_min_max;
        math::vector4<float> m_dir_vel_add_cam_speed_min_max_mult;
        float m_edge_softness;
        char pad_4[8];
        float m_particle_color_percentage;
        float m_background_distortion_visibility_percentage;
        float m_background_distortion_alpha_booster;
        float m_background_distortion_amount;
        uint32_t m_background_distortion_blur_level;
        float m_local_lights_multiplier;
        char pad_5[12];
    };

    class CUIElementColor {
    public:
        int m_index; //0x0000
        char pad_0004[12]; //0x0004
        rage::vector4 m_value; //0x0010
    }; //Size: 0x0020
    static_assert(sizeof(CUIElementColor) == 0x20);

    class CUIElementColorConstant {
    public:
        rage::vector4 m_value; //0x0000
        char pad_0010[12]; //0x0010
        int m_index; //0x001C
    }; //Size: 0x0020
    static_assert(sizeof(CUIElementColorConstant) == 0x20);

    class CUIIndex {
    public:
        int m_index; //0x0000
    }; //Size: 0x0004
    static_assert(sizeof(CUIIndex) == 0x4);

    class CUIElementInt {
    public:
        CUIIndex m_index; //0x0000
        int m_value; //0x0004
    }; //Size: 0x0008
    static_assert(sizeof(CUIElementInt) == 0x8);

    class CUIElementShader {
    public:
        uint64_t m_raw_element; //0x0000
        rage::grcTexture* m_shader; //0x0008
    }; //Size: 0x0010
    static_assert(sizeof(CUIElementShader) == 0x10);

    class TimecycleKeyframeData
    {
    public:
        char pad_0000[32]; //0x0000
        math::vector4<float> m_azimuth_east; //0x0020
        float m_azimuth_east_intensity; //0x0030
        char pad_0034[28]; //0x0034
        rage::vector4 m_azimuth_west; //0x0050
        float m_azimuth_west_intensity; //0x0060
        char pad_0064[28]; //0x0064
        rage::vector4 m_azimuth_transition; //0x0080
        float m_azimuth_transition_intensity; //0x0090
        char pad_0094[4]; //0x0094
        float m_azimuth_transition_position; //0x0098
        char pad_009C[20]; //0x009C
        rage::vector4 m_zenith; //0x00B0
        float m_zenith_intensity; //0x00C0
        char pad_00C4[28]; //0x00C4
        rage::vector4 m_zenith_transition; //0x00E0
        float m_zenith_transition_intensity; //0x00F0
        float m_zenith_transition_position; //0x00F4
        float m_zenith_transition_east_blend; //0x00F8
        float m_zenith_transition_west_blend; //0x00FC
        float m_zenith_blend_start; //0x0100
        char pad_0104[60]; //0x0104
        rage::vector3 m_plane; //0x0140
        float m_plane_intensity; //0x014C
        char pad_0150[52]; //0x0150
        float m_hdr; //0x0184
        float m_unk_188; //0x0188
        bool m_update_sky_attributes; //0x018C
        char pad_018D[3]; //0x018D
        uint32_t m_unk_190; //0x0190
        uint32_t m_unk_194; //0x0194
        char pad_0198[8]; //0x0198
        rage::vector4 m_unk_1A0; //0x01A0
        char pad_01AC[16]; //0x01AC
        rage::vector4 m_sun; //0x01C0
        char pad_01CC[32]; //0x01CC
        rage::vector4 m_sun_disc; //0x01F0
        char pad_01FC[32]; //0x01FC
        float m_sun_disc_size; //0x0220
        float m_sun_hdr; //0x0224
        float m_sun_miephase; //0x0228
        float m_sun_miescatter; //0x022C
        float m_sun_mie_intensity_mult; //0x0230
        char pad_0234[28]; //0x0234
        rage::vector4 m_unk_250; //0x0250
        char pad_025C[16]; //0x025C
        float m_cloud_shadow_strength; //0x0270
        float m_cloud_density_mult; //0x0274
        float m_cloud_density_bias; //0x0278
        float m_cloud_fadeout; //0x027C
        char pad_0280[32]; //0x0280
        float m_unk_2A0; //0x02A0
        float m_cloud_offset; //0x02A4
        float m_cloud_overall_color; //0x02A8
        float m_cloud_hdr; //0x02AC
        char pad_02B0[32]; //0x02B0
        float m_cloud_dither_strength; //0x02D0
        char pad_02D4[44]; //0x02D4
        float m_cloud_edge_strength; //0x0300
        char pad_0304[4]; //0x0304
        float m_cloud_overall_strength; //0x0308
        char pad_030C[16]; //0x030C
        rage::vector4 m_unk_320; //0x031C
        rage::vector4 m_cloud_base; //0x032C
        rage::vector4 m_unk_340; //0x033C
        char pad_0348[16]; //0x0348
        rage::vector4 m_cloud_1; //0x035C
        char pad_0368[20]; //0x0368
        rage::vector4 m_cloud_mid; //0x0380
        char pad_038C[32]; //0x038C
        float m_unk_380; //0x03B0
        float m_small_cloud_detail_strength; //0x03B4
        float m_small_cloud_density_mult; //0x03B8
        float m_unk_3BC; //0x03BC
        char pad_03C0[32]; //0x03C0
        rage::vector4 m_small_cloud; //0x03E0
        char pad_03EC[32]; //0x03EC
        float m_sun_influence_radius; //0x0410
        float m_sun_scatter_inten; //0x0414
        float m_moon_influence_radius; //0x0418
        float m_moon_scatter_inten; //0x041C
        char pad_0420[212]; //0x0420
        float m_stars_iten; //0x04F4
        char pad_04F8[60]; //0x04F8
        float m_moon_disc_size; //0x0534
        char pad_0538[24]; //0x0538
        rage::vector4 m_moon; //0x0550
        float m_moon_intensity; //0x0560
        char pad_0564[140]; //0x0564

        void set_sky(bool enabled) {
            *(bool*)((uint64_t)this - 0x60) = enabled;
        }
    }; //Size: 0x05F0
    static_assert(sizeof(TimecycleKeyframeData) == 0x5F0);
}
struct CWheelVfx {
    float m_slip_min; //0x0004
    float m_slip_max; //0x0008
    float m_pressure_min; //0x000C
    float m_pressure_max; //0x0010
    int m_type1; //0x0014
    BOOL m_unk1; //0x0018
    int m_type2; //0x001c
    BOOL m_unk2; //0x0010
    int m_type3; //0x0024
    BOOL m_unk3; //0x0028
    int m_type4; //0x002c
    BOOL m_unk4; //0x0030
    uint8_t m_r; //0x0034
    uint8_t m_g; //0x0035
    uint8_t m_b; //0x0036
    char _0x0037[1]; //0x0037
    float m_friction_thresh_min; //0x0038
    float m_friction_thresh_max; //0x003C
    uint32_t m_friction_fx1; //0x0040
    uint32_t m_friction_fx2; //0x0044
    uint32_t m_friction_fx3; //0x0048
    float m_disp_thresh_min; //0x004C
    float m_disp_thresh_max; //0x0050
    uint32_t m_displacement_fx1; //0x0054
    uint32_t m_displacement_fx2; //0x0058
    uint32_t m_displacement_fx3; //0x005C
    uint32_t m_displacement_fx_lod; //0x0060
    float m_burn_friction_evo_min; //0x0064
    float m_burn_friction_evo_max; //0x0068
    float m_burn_temp_evo_min; //0x006C
    float m_burn_temp_evo_max; //0x0070
    uint32_t m_burnout_fx1; //0x0074
    uint32_t m_burnout_fx2; //0x0078
    uint32_t m_burnout_fx3; //0x007C
    bool m_lights_on; //0x0080
    uint8_t m_lights_col_min_r; //0x0081
    uint8_t m_lights_col_min_g; //0x0082
    uint8_t m_lights_col_min_b; //0x0083
    uint8_t m_lights_col_max_r; //0x0084
    uint8_t m_lights_col_max_g; //0x0085
    uint8_t m_lights_col_max_b; //0x0086
    char _0x0087[1]; //0x0087
    float m_lights_intensity_min; //0x0088
    float m_lights_intensity_max; //0x008C
    float m_lights_range_min; //0x0090
    float m_lights_range_max; //0x0094
    float m_lights_falloff_min; //0x0098
    float m_lights_falloff_max; //0x009C
};

class CVehicleStreamRender {
public:
    char _0x0000[0x8]; // unk
    float m_tire_height; // unk
    char _0x000C[0xB94]; // unk
    float m_tire_width; // 0x08
};  
static_assert(sizeof(CVehicleStreamRender) == 0xBA4);


struct CCloudBurstCommonSettings {
    float IntensityMin;
    float IntensityMax;
    float IntensityMinClamp;
    float WidthMin;
    float WidthMax;
    float WidthMinClamp;
    float IntensityFlickerMin;
    float IntensityFlickerMax;
    float IntensityFlickerFrequency;
    float IntensityLevelDecayMin;
    float IntensityLevelDecayMax;
    float WidthLevelDecayMin;
    float WidthLevelDecayMax;
    float NoiseTexScale;
    float NoiseAmplitude;
    float NoiseAmpMinDistLerp;
    float NoiseAmpMaxDistLerp;
    unsigned char SubdivisionCount;
    float OrbitDirXVariance;
    float OrbitDirYVarianceMin;
    float OrbitDirYVarianceMax;
    float MaxDistanceForExposureReset;
    float AngularWidthFactor;
    float MaxHeightForStrike;
    float CoronaIntensityMult;
    float BaseCoronaSize;
    unsigned int BaseColor;
    unsigned int FogColor;
    float CloudLightIntensityMult;
    float CloudLightDeltaPos;
    float CloudLightRadius;
    float CloudLightFallOffExponent;
    float MaxDistanceForBurst;
    float BurstThresholdIntensity;
    float LightningFadeWidth;
    float LightningFadeWidthFalloffExp;
};


#pragma pack(push, 4)
class CCarriageConfig
{
    uint32_t m_name_hash;                      // 0x00
    int m_max_peds_per_carriage;               // 0x04
    char m_pad[4];                             // 0x08
    bool m_flip_model_dir;                     // 0x0C
    bool m_do_interior_lights;                 // 0x0D
    float m_carriage_vert_offset;              // 0x10
};
static_assert(sizeof(CCarriageConfig) == 0x14);

class CTrainConfig
{
public:
    uint32_t m_name_hash;                              // 0x00
    float m_populate_train_dist;                       // 0x04
    int m_unk1;                                        // 0x08
    int m_unk2;                                        // 0x0C
    int m_unk3;                                        // 0x10
    bool m_announce_stations;                          // 0x14
    bool m_doors_beep;                                 // 0x15
    bool m_carriages_hang;                             // 0x16
    bool m_carriages_swing;                            // 0x17
    bool m_no_carriage_gap;                            // 0x18
    bool m_link_tracks_with_adjacent_stations;         // 0x19
    bool m_no_random_spawn;                            // 0x1A
    float m_carriage_gap;                              // 0x1C
    rage::atArray<CCarriageConfig> m_carraige_configs; // 0x20
};
static_assert(sizeof(CTrainConfig) == 0x30);
#pragma pack(pop)