#pragma once
#include "util/math.h"
#include "gui/util/flags.h"
#include "gui/types.h"
#include "gui/renderer.h"
#include "menu/util/scr_global.h"

namespace menu {
    class panel {
    public:
        panel(float width, float title_height, float item_height) :
            m_width(width), m_title_height(title_height), m_item_height(item_height)
        {
        }
    public:
       
        
        void start_panel(std::string title);
        void push(std::string left, std::string right);
        void push_sprite(std::pair<std::string, std::string> texture, math::vector2<float> scale);
        void end_panel();
        void set_next();

        void setRenderTitle(bool value) { m_render_title = value; }
    private:
        float m_width;
        float m_title_height;
        float m_item_height;
        bool m_next_to = false;
        eFont m_title_font = eFont::HouseScript;
        eFont m_item_font = eFont::ChaletLondon;
        color m_back_ground = { 0, 0, 0, 180 };
        float m_title_font_scale = 0.3f;
        float m_font_scale = 0.25f;
        math::vector2<float> m_padding = { 3.1f, 2.1f };
        bool m_render_title;
    };

    inline math::vector2<float> g_panel_pos = { renderer::getRenderer()->m_position.x, renderer::getRenderer()->m_position.y - 0.006f };

    inline  float g_panel_base = 0.f;
    inline float g_panel_base_2 = 0.f;
    inline float g_panel_spacing = -0.06f;
    inline float g_test_y = -0.006f;
    inline float g_test_x = 0.f;

    inline std::string get_gs_type(int type) {
        switch (type) {
        case 0: return "Invite Only";
        case 1: return "Friends Only";
        case 2: return "Crew Only";
        case 4: return "Heist";
        case 5: return "Public";
        }

        return "Unknown";
    }

    struct vehicle_pictures { std::string DictName; std::string PreviewName; };
    inline std::vector<vehicle_pictures> g_vehicle_pictures = {
    {"candc_heist4","alkonost"},
    {"candc_heist4","annihilator2"},
    {"candc_heist4","avisa"},
    {"sssa_dlc_heist4","brioso2"},
    {"candc_heist4","dinghy5"},
    {"lgm_dlc_heist4","italirsx"},
    {"sssa_dlc_heist4","kosatka"},
    {"dock_dlc_heist4","longfin"},
    {"candc_heist4","manchez2"},
    {"candc_heist4","patrolboat"},
    {"sssa_dlc_heist4","seasparrow2"},
    {"candc_heist4","seasparrow3"},
    {"sssa_dlc_heist4","slamtruck"},
    {"candc_heist4","squaddie"},
    {"candc_heist4","toreador"},
    {"candc_heist4","verus"},
    {"candc_heist4","vetir"},
    {"candc_heist4","veto"},
    {"candc_heist4","veto2"},
    {"candc_heist4","weevil"},
    {"candc_heist4","winky"},
    {"lgm_dlc_executive1","pfister811"},
    {"lgm_default","adder"},
    {"lgm_dlc_xmas2017","autarch_b"},
    {"lsc_jan2016","banshee2"},
    {"lgm_default","bullet"},
    {"lgm_default","cheetah"},
    {"lgm_dlc_smuggler","cyclone"},
    {"lgm_dlc_smuggler","cyclone"},
    {"lgm_dlc_arena","deveste"},
    {"lgm_dlc_stunt","sheava"},
    {"lgm_dlc_vinewood","emerus"},
    {"lgm_dlc_assault","entity2"},
    {"lgm_default","entityxf"},
    {"lgm_dlc_executive1","fmj"},
    {"lgm_dlc_casinoheist","furia"},
    {"lgm_dlc_specialraces","gp1"},
    {"sssa_default","infernus"},
    {"lsc_dlc_import_export","italigtb2"},
    {"lsc_dlc_import_export","italigtb"},
    {"lgm_dlc_vinewood","krieger"},
    {"lsc_dlc_import_export","nero2_b"},
    {"lsc_dlc_import_export","nero2_a"},
    {"lgm_dlc_luxe","Osiris"},
    {"lgm_dlc_importexport","penetrator"},
    {"lgm_dlc_stunt","le7b"},
    {"lgm_dlc_executive1","reaper"},
    {"candc_importexport","voltic2"},
    {"lgm_dlc_vinewood","s80"},
    {"lgm_dlc_xmas2017","sc1_b"},
    {"candc_battle","scramjet"},
    {"lsc_jan2016","sultan2_a"},
    {"lgm_dlc_luxe","t20"},
    {"lgm_dlc_assault","taipan"},
    {"lgm_dlc_importexport","tempesta"},
    {"lgm_dlc_assault","tezeract"},
    {"lgm_dlc_vinewood","thrax"},
    {"lgm_dlc_business","turismor"},
    {"lgm_dlc_assault","tyrant"},
    {"lgm_dlc_stunt","tyrus"},
    {"lgm_default","vacca"},
    {"lgm_dlc_gunrunning","vagner"},
    {"candc_smuggler","vigilante"},
    {"lgm_dlc_smuggler","visione"},
    {"lgm_default","voltic_tless"},
    {"lgm_dlc_executive1","prototipo"},
    {"lgm_dlc_gunrunning","xa21"},
    {"lgm_dlc_business2","zentorno"},
    {"lgm_dlc_vinewood","zorrusso"},
    {"lgm_dlc_business","alpha"},
    {"lgm_dlc_business2","banshee_tless"},
    {"sssa_dlc_mp_to_sp","blista2"},
    {"lgm_dlc_executive1","bestiagts"},
    {"sssa_dlc_hipster","buffalo"},
    {"sssa_dlc_mp_to_sp","buffalo3"},
    {"sssa_dlc_hipster","buffalo"},
    {"lgm_default","carboniz"},
    {"lsc_dlc_import_export","comet3"},
    {"sssa_default","comet2"},
    {"lgm_dlc_xmas2017","comet4_b"},
    {"lgm_dlc_xmas2017","comet5_b"},
    {"lgm_default","coquette"},
    {"lgm_dlc_vinewood","drafter"},
    {"sssa_dlc_stunt","tampa2"},
    {"lgm_default","elegy2"},
    {"lsc_dlc_import_export","elegy"},
    {"lgm_dlc_casinoheist", "formula"},
    {"lgm_dlc_casinoheist", "formula2"},
    {"lgm_dlc_assault","flashgt"},
    {"lgm_dlc_lts_creator","furore"},
    {"sssa_dlc_business2","fusilade"},
    {"sssa_dlc_battle","futo"},
    {"lgm_dlc_assault","gb200"},
    {"sssa_dlc_assault","hotring"},
    {"lgm_dlc_casinoheist","imorgon"},
    {"sssa_dlc_vinewood","issi7"},
    {"lgm_dlc_arena","italigto"},
    {"sssa_dlc_christmas_2","jester2"},
    {"lgm_dlc_assault","jester3"},
    {"lgm_dlc_business","jester"},
    {"lgm_dlc_vinewood","jugular"},
    {"lgm_dlc_casinoheist","komoda"},
    {"sssa_dlc_heist","kuruma2"},
    {"sssa_dlc_heist","kuruma"},
    {"lgm_dlc_vinewood","locust"},
    {"lgm_dlc_stunt","lynx"},
    {"sssa_dlc_christmas_2","massacro2"},
    {"lgm_dlc_business2","massacro"},
    {"lgm_dlc_vinewood","neo"},
    {"lgm_dlc_xmas2017","neon_b"},
    {"lgm_default","ninef2"},
    {"sssa_default","ninef"},
    {"sssa_dlc_stunt","omnis"},
    {"lgm_dlc_vinewood","paragon"},
    {"lgm_dlc_vinewood","paragon"},
    {"lgm_dlc_xmas2017","pariah_b"},
    {"sssa_dlc_business2","penumbra"},
    {"lgm_dlc_xmas2017","raiden_b"},
    {"lgm_default","rapidgt2"},
    {"lgm_default","rapidgt"},
    {"lgm_dlc_biker","raptor"},
    {"lgm_dlc_xmas2017","revolter_b"},
    {"lgm_dlc_specialraces","ruston"},
    {"lgm_dlc_apartments","schafter4"},
    {"lgm_dlc_apartments","schafter3"},
    {"lgm_dlc_arena","schlagen"},
    {"sssa_default","schwarze"},
    {"sssa_dlc_xmas2017","sentinel3_b"},
    {"lgm_dlc_executive1","seven70"},
    {"lsc_dlc_import_export","specter2_a"},
    {"lsc_dlc_import_export","specter2_b"},
    {"lgm_dlc_xmas2017","streiter_b"},
    {"sssa_dlc_casinoheist","sugoi"},
    {"lsc_jan2016","sultan2_a"},
    {"sssa_dlc_casinoheist","sultan2"},
    {"lgm_default","surano_convertable"},
    {"sssa_dlc_stunt","tropos"},
    {"lgm_dlc_casinoheist","vstr"},
    {"lgm_dlc_apartments","verlier"},
    {"mba_vehicles","zr3802"},
    {"mba_vehicles","zr3803"},
    {"mba_vehicles","zr3801"},
    {"candc_gunrunning","ardent"},
    {"lgm_dlc_heist","casco"},
    {"sssa_dlc_assault","cheburek"},
    {"lgm_dlc_gunrunning","cheetah2"},
    {"lgm_dlc_pilot","coquette2"},
    {"candc_xmas2017","deluxo_b"},
    {"sssa_dlc_vinewood","dynasty"},
    {"sssa_dlc_assault","fagaloa"},
    {"lgm_dlc_xmas2017","gt500_b"},
    {"lgm_dlc_specialraces","infernus2"},
    {"lgm_default","jb700"},
    {"lgm_dlc_apartments","mamba"},
    {"sssa_dlc_assault","michelli"},
    {"lgm_default","monroe"},
    {"sssa_dlc_vinewood","nebula"},
    {"sssa_dlc_hipster","pigalle"},
    {"lgm_dlc_smuggler","rapidgt3"},
    {"sssa_dlc_casinoheist","retinue2"},
    {"sssa_dlc_smuggler","retinue_b"},
    {"sssa_dlc_halloween","btype2"},
    {"lgm_dlc_valentines2","roosevelt2"},
    {"lgm_dlc_valentines","roosevelt"},
    {"lgm_dlc_xmas2017","savestra_b"},
    {"lgm_default","stingerg"},
    {"lgm_default","stinger"},
    {"lgm_dlc_luxe","feltzer3"},
    {"candc_xmas2017","stromberg_b"},
    {"lgm_dlc_battle","swinger"},
    {"lgm_dlc_gunrunning","torero"},
    {"lsc_lowrider2","tornado5_a"},
    {"sssa_dlc_biker","tornado6"},
    {"lgm_dlc_specialraces","turismo2"},
    {"lgm_dlc_xmas2017","viseris_b"},
    {"lgm_default","ztype"},
    {"lgm_dlc_xmas2017","z190_b"},
    {"sssa_dlc_vinewood","zion3"},
    {"lgm_default","cogcabri"},
    {"sssa_default","exemplar"},
    {"sssa_dlc_business2","f620"},
    {"sssa_default","felon"},
    {"sssa_default","felon2"},
    {"sssa_dlc_heist","jackal"},
    {"sssa_default","oracle"},
    {"sssa_dlc_heist","oracle1"},
    {"sssa_dlc_business2","sentinel"},
    {"sssa_dlc_business2","sentinel"},
    {"lgm_dlc_luxe","windsor"},
    {"sssa_default","zion"},
    {"sssa_default","zion2"},
    {"sssa_dlc_hipster","blade"},
    {"lsc_default","buccaneer2_b"},
    {"lsc_default","buccaneer2_a"},
    {"lsc_default","chino2_a"},
    {"lgm_dlc_luxe","chino"},
    {"lgm_dlc_arena","clique"},
    {"lgm_dlc_luxe","coquette3"},
    {"lgm_dlc_arena","deviant"},
    {"sssa_dlc_assault","dominator3"},
    {"mba_vehicles","dominato_c_1"},
    {"mba_vehicles","dominato_c_2"},
    {"mba_vehicles","dominato_c_3"},
    {"sssa_dlc_business2","dominato"},
    {"candc_default","dukes"},
    {"sssa_dlc_mp_to_sp","dukes"},
    {"sssa_dlc_assault","ellie"},
    {"lsc_lowrider2","faction3_b"},
    {"lsc_lowrider2","faction3_a"},
    {"lsc_default","faction2_a"},
    {"sssa_dlc_mp_to_sp","gauntlet2"},
    {"sssa_dlc_vinewood","gauntlet3"},
    {"sssa_dlc_vinewood","gauntlet4"},
    {"sssa_default","gauntlet"},
    {"sssa_dlc_xmas2017","hermes_b"},
    {"lgm_default","hotknife"},
    {"lgm_dlc_xmas2017","hustler_b"},
    {"mba_vehicles","impaler"},
    {"sssa_dlc_vinewood","impaler"},
    {"mba_vehicles","impaler_c_1"},
    {"mba_vehicles","impaler_c_2"},
    {"mba_vehicles","impaler_c_3"},
    {"mba_vehicles","imperator2"},
    {"mba_vehicles","imperator3"},
    {"mba_vehicles","imperator1"},
    {"sssa_dlc_halloween","lurcher"},
    {"lsc_default","moonbeam2"},
    {"lgm_dlc_apartments","niteshad"},
    {"sssa_dlc_vinewood","peyote2"},
    {"sssa_dlc_hipster","picador"},
    {"sssa_dlc_mp_to_sp","dominator2"},
    {"sssa_dlc_valentines","rloader"},
    {"sssa_dlc_christmas_2","rloader2"},
    {"candc_importexport","ruiner2"},
    {"sssa_dlc_battle","ruiner"},
    {"lsc_lowrider2","sabregt2_a"},
    {"lsc_lowrider2","slamvan3_b"},
    {"mba_vehicles","slamvan_c_1"},
    {"mba_vehicles","slamvan_c_2"},
    {"mba_vehicles","slamvan_c_3"},
    {"sssa_dlc_christmas_2","slamvan"},
    {"sssa_dlc_mp_to_sp","stalion2"},
    {"sssa_dlc_mp_to_sp","stallion"},
    {"candc_gunrunning","tampa3"},
    {"sssa_dlc_christmas_3","tampa"},
    {"sssa_dlc_arena","tulip"},
    {"sssa_dlc_arena","vamos"},
    {"sssa_default","vigero"},
    {"lsc_lowrider2","virgo2_a"},
    {"lsc_lowrider2","virgo2_b"},
    {"lgm_dlc_luxe","virgo"},
    {"lsc_default","voodoo_b"},
    {"lsc_default","voodoo_a"},
    {"sssa_dlc_xmas2017","yosemite_b"},
    {"sssa_dlc_casinoheist","yosemite2"},
    {"sssa_default","bfinject"},
    {"sssa_default","bifta"},
    {"sssa_dlc_hipster","blazer3"},
    {"candc_importexport","blazer5"},
    {"sssa_default","blazer"},
    {"sssa_dlc_biker","blazer4"},
    {"sssa_default","bodhi2"},
    {"lgm_dlc_luxe","brawler"},
    {"mba_vehicles","bruiser_c_2"},
    {"mba_vehicles","bruiser_c_3"},
    {"mba_vehicles","bruiser_c_1"},
    {"mba_vehicles","brutus2"},
    {"mba_vehicles","brutus3"},
    {"mba_vehicles","brutus1"},
    {"sssa_dlc_vinewood","caracara2"},
    {"candc_assault","caracara"},
    {"candc_default","dubsta3"},
    {"candc_gunrunning","dune3"},
    {"sssa_default","dune"},
    {"sssa_dlc_casinoheist","everon"},
    {"lgm_dlc_battle","freecrawler"},
    {"sssa_dlc_vinewood","hellion"},
    {"ua_generic","ua_unlock_11"},
    {"candc_default","insurgent"},
    {"candc_default","insurgent"},
    {"sssa_default","kalahari"},
    {"sssa_dlc_xmas2017","kamacho_b"},
    {"candc_default","marshall"},
    {"candc_battle","menacer"},
    {"candc_default","mesa3"},
    {"mba_vehicles","monster_c_1"},
    {"mba_vehicles","monster_c_2"},
    {"mba_vehicles","monster_c_3"},
    {"candc_gunrunning","nightshark"},
    {"sssa_dlc_casinoheist","outlaw"},
    {"candc_importexport","dune5"},
    {"sssa_dlc_business","rancherx"},
    {"sssa_dlc_arena","rcbandito"},
    {"sssa_dlc_hipster","rebel2"},
    {"sssa_default","rebel"},
    {"sssa_dlc_xmas2017","riata_b"},
    {"sssa_default","sandking_b"},
    {"sssa_default","sandkin_2b"},
    {"candc_importexport","technical2"},
    {"ua_generic","ua_unlock_15"},
    {"candc_default","technical"},
    {"candc_default","monster"},
    {"sssa_dlc_stunt","trophy2"},
    {"sssa_dlc_stunt","trophy"},
    {"sssa_dlc_casinoheist","vagrant"},
    {"sssa_default","akuma"},
    {"sssa_dlc_biker","avarus"},
    {"sssa_dlc_stunt","bf400"},
    {"sssa_dlc_biker","bagger"},
    {"sssa_default","bati2"},
    {"sssa_default","bati"},
    {"lgm_default","carbon"},
    {"sssa_dlc_biker","chimera"},
    {"sssa_dlc_stunt","cliffhanger"},
    {"sssa_dlc_biker","daemon2"},
    {"mba_vehicles","deathbike_c_2"},
    {"mba_vehicles","deathbike_c_3"},
    {"mba_vehicles","deathbike_c_1"},
    {"sssa_dlc_biker","defiler"},
    {"lsc_dlc_import_export","diablous2"},
    {"sssa_default","double"},
    {"sssa_dlc_heist","enduro"},
    {"sssa_dlc_biker","esskey"},
    {"lsc_dlc_import_export","fcr2_b"},
    {"lsc_dlc_import_export","fcr2_a"},
    {"sssa_dlc_biker","faggio3"},
    {"sssa_default","faggio"},
    {"sssa_dlc_biker","faggion"},
    {"sssa_dlc_stunt","gargoyle"},
    {"lgm_dlc_biker","hakuchou2"},
    {"sssa_dlc_lts_creator","hakuchou"},
    {"sssa_default","hexer"},
    {"sssa_dlc_lts_creator","innovation"},
    {"lgm_dlc_heist","lectro"},
    {"sssa_dlc_biker","manchez"},
    {"sssa_dlc_heist","nemesis"},
    {"sssa_dlc_biker","nightblade"},
    {"candc_battle","oppressor2"},
    {"candc_gunrunning","oppressor"},
    {"sssa_default","pcj"},
    {"sssa_dlc_biker","ratbike"},
    {"lgm_dlc_vinewood","rrocket"},
    {"sssa_default","ruffian"},
    {"sssa_default","sanchez2"},
    {"sssa_default","sanchez"},
    {"sssa_dlc_biker","sanctus"},
    {"lgm_dlc_biker","shotaro"},
    {"lgm_dlc_casinoheist","stryder"},
    {"lgm_dlc_business2","thrust"},
    {"sssa_default","vader"},
    {"lgm_dlc_luxe","vindicator"},
    {"sssa_dlc_biker","vortex"},
    {"sssa_dlc_biker","wolfsbane"},
    {"sssa_dlc_biker","zombieb"},
    {"sssa_dlc_biker","zombiea"},
    {"candc_gunrunning","apc"},
    {"candc_gunrunning","trsmall2"},
    {"candc_default","barracks"},
    {"candc_xmas2017","barrage_b"},
    {"candc_xmas2017","chernobog_b"},
    {"candc_default","crusader"},
    {"candc_gunrunning","halftrack"},
    {"candc_xmas2017","khanjali_b"},
    {"candc_default","rhino"},
    {"mba_vehicles","scarab2"},
    {"mba_vehicles","scarab3"},
    {"mba_vehicles","scarab1"},
    {"candc_xmas2017","thruster_b"},
    {"candc_default","pbus"},
    {"candc_xmas2017","riot2_b"},
    {"candc_default","airbus"},
    {"candc_executive1","brickade"},
    {"candc_default","bus"},
    {"candc_default","coach"},
    {"sssa_dlc_stunt","rallytruck"},
    {"sssa_dlc_battle","pbus2"},
    {"candc_default","rentbus"},
    {"candc_importexport","wastlndr"},
    {"sssa_dlc_business","asea"},
    {"sssa_dlc_business","astrope"},
    {"lgm_dlc_apartments","cognosc"},
    {"sssa_dlc_business","premier"},
    {"sssa_default","superd"},
    {"sssa_default","fugitive"},
    {"sssa_dlc_hipster","glendale"},
    {"sssa_dlc_business","intruder"},
    {"sssa_default","stretch"},
    {"sssa_dlc_hipster","primo"},
    {"sssa_dlc_hipster","regina"},
    {"sssa_dlc_battle","Romero"},
    {"lgm_dlc_apartments","schafter3"},
    {"lgm_dlc_apartments","schafter4"},
    {"sssa_dlc_heist","schafter2"},
    {"lgm_dlc_battle","stafford"},
    {"sssa_dlc_business","stanier"},
    {"sssa_dlc_business","stratum"},
    {"sssa_dlc_heist","surge"},
    {"sssa_dlc_hipster","tailgater"},
    {"sssa_dlc_business","ingot"},
    {"sssa_dlc_hipster","warrener"},
    {"sssa_dlc_business","washingt"},
    {"candc_default","dump"},
    {"sssa_dlc_heist","guardian"},
    {"sssa_dlc_casinoheist","asbo"},
    {"sssa_default","dilettan"},
    {"sssa_dlc_stunt","brioso"},
    {"sssa_dlc_assault","issi3"},
    {"mba_vehicles","issi3_c_1"},
    {"mba_vehicles","issi3_c_2"},
    {"mba_vehicles","issi3_c_3"},
    {"sssa_dlc_casinoheist","kanjo"},
    {"sssa_dlc_hipster","panto"},
    {"sssa_dlc_battle","prairie"},
    {"sssa_dlc_hipster","rhapsody"},
    {"sssa_default","issi2"},
    {"mba_vehicles","cerberus2"},
    {"mba_vehicles","cerberus3"},
    {"mba_vehicles","cerberus1"},
    {"candc_truck","cab_1"},
    {"candc_default","mule3"},
    {"candc_battle","mule4"},
    {"candc_default","mule"},
    {"candc_truck","cab_0"},
    {"candc_importexport","phantom2"},
    {"candc_battle","pounder2"},
    {"elt_dlc_smuggler","alphaz1"},
    {"candc_chopper","banner_5"},
    {"candc_chopper","banner_4"},
    {"elt_dlc_pilot","besra"},
    {"elt_dlc_battle","blimp3"},
    {"candc_smuggler","bombushka"},
    {"elt_default","cuban800"},
    {"elt_default","dodo"},
    {"elt_default","duster"},
    {"elt_dlc_smuggler","howard"},
    {"candc_default","hydra"},
    {"elt_dlc_executive1","luxor2"},
    {"elt_default","luxor"},
    {"elt_default","mammatus"},
    {"elt_dlc_smuggler","microlight"},
    {"elt_dlc_pilot","miljet"},
    {"candc_smuggler","mogu"},
    {"candc_smuggler","molotok_b"},
    {"elt_dlc_executive1","nimbus"},
    {"candc_smuggler","nokota"},
    {"candc_smuggler","lazer"},
    {"candc_smuggler","pyro"},
    {"candc_smuggler","rogue"},
    {"elt_dlc_smuggler","seabreeze"},
    {"elt_default","shama"},
    {"candc_smuggler","starling"},
    {"candc_battle","strikeforce"},
    {"elt_default","stunt"},
    {"elt_default","titan"},
    {"candc_smuggler","tula"},
    {"elt_default","velum2"},
    {"elt_default","velum"},
    {"candc_xmas2017","volatol_b"},
    {"foreclosures_bunker","transportation_2"},
    {"foreclosures_bunker","transportation_1"},
    {"candc_truck","banner_2"},
    {"sssa_default","sadler"},
    {"candc_xmas2017","akula_b"},
    {"elt_default","annih"},
    {"candc_default","buzzard"},
    {"candc_default","cargobob"},
    {"elt_default","frogger"},
    {"elt_dlc_smuggler","havok"},
    {"candc_smuggler","hunter"},
    {"elt_default","maverick"},
    {"candc_default","savage"},
    {"elt_dlc_assault","sparrow"},
    {"elt_dlc_executive1","swift2"},
    {"elt_dlc_pilot","swift"},
    {"candc_default","valkyrie"},
    {"elt_dlc_executive1","volatus"},
    {"sssa_dlc_hipster","surfer"},
    {"sssa_default","bison"},
    {"sssa_dlc_business","bobcatx"},
    {"candc_importexport","boxville5"},
    {"candc_default","boxville4"},
    {"sssa_dlc_heist","gburrito2"},
    {"candc_default","journey"},
    {"lsc_lowrider2","minivan2_b"},
    {"sssa_dlc_business","minivan"},
    {"sssa_default","paradise"},
    {"sssa_dlc_executive_1","rumpo3_b"},
    {"sssa_dlc_heist","rumpo"},
    {"sssa_dlc_biker","youga2"},
    {"sssa_dlc_hipster","youga"},
    {"dock_default","dinghy3"},
    {"dock_default","jetmax"},
    {"dock_default","marquis"},
    {"dock_default","seashark"},
    {"dock_default","squalo"},
    {"dock_default","sub2"},
    {"dock_default","suntrap"},
    {"dock_default","toro"},
    {"dock_default","tropic"},
    {"pandm_default","bmx"},
    {"pandm_default","cruiser"},
    {"pandm_default","tribike2"},
    {"pandm_default","scorcher"},
    {"pandm_default","tribike3"},
    {"pandm_default","tribike"},
    {"sssa_default","baller2"},
    {"lgm_dlc_apartments","baller4"},
    {"lgm_dlc_apartments","baller3"},
    {"sssa_dlc_battle","bjx"},
    {"sssa_dlc_heist","seminole"},
    {"sssa_dlc_business","cavcade2"},
    {"sssa_default","cavcade"},
    {"sssa_dlc_stunt","contender"},
    {"sssa_dlc_battle","habanero"},
    {"lgm_dlc_business2","huntley"},
    {"sssa_dlc_battle","fq2"},
    {"sssa_dlc_business","granger"},
    {"sssa_dlc_heist","gresley"},
    {"sssa_dlc_heist","landstalker"},
    {"sssa_dlc_battle","patriot"},
    {"candc_default","mesa"},
    {"lgm_dlc_vinewood","novak"},
    {"sssa_dlc_battle","patriot2"},
    {"sssa_dlc_business","radi"},
    {"lgm_dlc_casinoheist","rebla"},
    {"sssa_default","rocoto"},
    {"sssa_dlc_battle","serrano"},
    {"lgm_dlc_arena","toros"},
    {"lgm_dlc_executive1","xls"},
    {"lgm_dlc_tuner","zr350" },
    {"lgm_dlc_tuner","growler" },
    {"lgm_dlc_tuner","cypher" },
    {"lgm_dlc_tuner","comet6" },
    {"lgm_dlc_tuner","jester4" },
    {"lgm_dlc_tuner","tailgater2" },
    {"lgm_dlc_tuner","vectre" },
    {"lgm_dlc_tuner","euros" },
    {"sssa_dlc_tuner","calico" },
    {"sssa_dlc_tuner","dominator7" },
    {"sssa_dlc_tuner","dominator8" },
    {"sssa_dlc_tuner","futo2" },
    {"sssa_dlc_tuner","previon" },
    {"sssa_dlc_tuner","remus" },
    {"sssa_dlc_tuner","rt3000" },
    {"sssa_dlc_tuner","sultan3" },
    {"sssa_dlc_tuner","warrener2" },
    {"sssa_dlc_xmas2022","boor" },
    {"candc_xmas2022","brickade2" },
    {"lgm_dlc_xmas2022","broadway" },
    {"sssa_dlc_xmas2022","cargoplane2" },
    {"lgm_dlc_xmas2022","entity3" },
    {"sssa_dlc_xmas2022","eudora" },
    {"sssa_dlc_xmas2022","everon2" },
    {"sssa_dlc_xmas2022","issi8" },
    {"sssa_dlc_xmas2022","journey2" },
    {"sssa_dlc_xmas2022","manchez3" },
    {"lgm_dlc_xmas2022","panthere" },
    {"lgm_dlc_xmas2022","powersurge" },
    {"lgm_dlc_xmas2022","r300" },
    {"sssa_dlc_xmas2022","surfer3" },
    {"sssa_dlc_xmas2022","tahoma" },
    {"sssa_dlc_xmas2022","tulip2" },
    {"lgm_dlc_xmas2022","virtue" }
    };


    inline void vehicle_info_panel(uint32_t hash) {
        panel panel(0.14f, 0, 0.03f);
        panel.start_panel("");

        if (hash != 0) {
            std::string model = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(hash);
            std::string text = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(model.c_str());

            std::string VehiclePreviewDictName, VehiclePreviewName;
            std::transform(model.begin(), model.end(), model.begin(), tolower);
            for (auto& Vector : g_vehicle_pictures) {
                std::string PreviewName = Vector.PreviewName;
                std::transform(PreviewName.begin(), PreviewName.end(), PreviewName.begin(), tolower);
                if (PreviewName == model) {
                    VehiclePreviewDictName = Vector.DictName;
                    VehiclePreviewName = Vector.PreviewName;
                    break;
                }
            }

            auto maxSpeed = VEHICLE::GET_VEHICLE_MODEL_ESTIMATED_MAX_SPEED(hash) * 2.236936f;
            auto seats = VEHICLE::GET_VEHICLE_MODEL_NUMBER_OF_SEATS(hash);
            auto maxBraking = VEHICLE::GET_VEHICLE_MODEL_MAX_BRAKING(hash);
            auto maxTraction = VEHICLE::GET_VEHICLE_MODEL_MAX_TRACTION(hash);

            if (strlen(VehiclePreviewDictName.c_str()) > 0 && strlen(VehiclePreviewName.c_str()) > 0) {
                if (VehiclePreviewName == "P-996 LAZER") {
                    VehiclePreviewName = "lazer";
                }
                panel.push_sprite({ VehiclePreviewDictName, VehiclePreviewName }, { 0.135f, 0.14f });
                panel.push("Max Speed", std::format("{} KMH", std::roundf(maxSpeed)));
                panel.push("Max Traction", std::format("{}", maxTraction));
                panel.push("Max Braking", std::format("{}", maxBraking));
                panel.push("Seats", std::format("{}", seats));
            }
            else {
                panel.push("Max Speed", std::format("{} KMH", std::roundf(maxSpeed)));
                panel.push("Max Traction", std::format("{}", maxTraction));
                panel.push("Max Braking", std::format("{}", maxBraking));
                panel.push("Seats", std::format("{}", seats));
            }

        }    

        panel.end_panel();
    }

    inline void recent_info_panel(Player player) {
        panel panel(0.14f, 0.03f, 0.03f);
        panel.start_panel(PLAYER::GET_PLAYER_NAME(player));

        auto plyr = patterns::get_net_player(player);

        bool in_session = false;
        bool online = false;

        for (uint32_t i = 0; i < 32; i++) {
            if (patterns::get_net_player(i)) {
                if (patterns::get_net_player(i)->m_player_info) {
                    if (patterns::get_net_player(i)->GetGamerInfo()->m_gamer_handle.m_rockstar_id == plyr->GetGamerInfo()->m_gamer_handle.m_rockstar_id) {
                        in_session = true;
                    }
                }
            }
        }

        std::string online_display = in_session ? "Yes" : "No";

        int rank = *script_global(scr_globals::gpbd_fm_1).at(player, scr_globals::size::gpbd_fm_1).at(205).at(6).as<int*>();
        int cash = *script_global(scr_globals::gpbd_fm_1).at(player, scr_globals::size::gpbd_fm_1).at(205).at(3).as<int*>();
        int bank = *script_global(scr_globals::gpbd_fm_1).at(player, scr_globals::size::gpbd_fm_1).at(205).at(56).as<int*>() - *script_global(scr_globals::gpbd_fm_1).at(player, scr_globals::size::gpbd_fm_1).at(205).at(3).as<int*>();

        float kd_ratio = *script_global(scr_globals::gpbd_fm_1)
            .at(player, scr_globals::size::gpbd_fm_1)
            .at(205)
            .at(26)
            .as<float*>();

        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << kd_ratio;
        std::string kd_ratio_str = oss.str();

        panel.push("Rockstar ID", std::to_string(plyr->GetGamerInfo()->m_gamer_handle.m_rockstar_id));
        panel.push("Online", online_display);
        panel.push("In Session", online_display);
        panel.push("Rank", std::to_string(rank));
        panel.push("Cash", std::format("${}", std::to_string(cash)));
        panel.push("Bank", std::format("${}", std::to_string(bank)));
        panel.push("K/D Ratio", kd_ratio_str);

        panel.end_panel();
    }

    inline void friend_info_panel(Player player) {
        panel panel(0.14f, 0.03f, 0.03f);
        panel.start_panel(patterns::friend_registry->get(player)->m_name);

        auto plyr = patterns::friend_registry->get(player);

        bool in_session = false;
        bool online = false;


        std::string online_display = in_session ? "Yes" : "No";
        std::string joinable = plyr->m_is_joinable ? "Yes" : "No";
        std::string session_type = get_gs_type(-1);

        panel.push("Rockstar ID", std::to_string(plyr->m_rockstar_id));
        panel.push("Online", online_display);
        panel.push("In Session", online_display);
        panel.push("Joinable", joinable);
        panel.push("Session Type", session_type);

        panel.end_panel();
    }

    inline void player_info_panel(Player player) {
        if (*patterns::is_session_started) {
            panel info(0.14f, 0.03f, 0.03f);
            info.start_panel(PLAYER::GET_PLAYER_NAME(player));

            auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
            if (ped) {
                int rank = *script_global(scr_globals::gpbd_fm_1).at(player, scr_globals::size::gpbd_fm_1).at(205).at(6).as<int*>();
                int cash = *script_global(scr_globals::gpbd_fm_1).at(player, scr_globals::size::gpbd_fm_1).at(205).at(3).as<int*>();
                int bank = *script_global(scr_globals::gpbd_fm_1).at(player, scr_globals::size::gpbd_fm_1).at(205).at(56).as<int*>() - *script_global(scr_globals::gpbd_fm_1).at(player, scr_globals::size::gpbd_fm_1).at(205).at(3).as<int*>();

                int health = (int)ENTITY::GET_ENTITY_HEALTH(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player));
                int armor = (int)PED::GET_PED_ARMOUR(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player));
                float kd_ratio = *script_global(scr_globals::gpbd_fm_1).at(player, scr_globals::size::gpbd_fm_1).at(205).at(26).as<float*>();

                std::ostringstream oss;
                oss << std::fixed << std::setprecision(2) << kd_ratio;
                std::string kd_ratio_str = oss.str();
                std::string wanted = std::format("{}/5", PLAYER::GET_PLAYER_WANTED_LEVEL(ped));
                std::string ip = std::format("{}.{}.{}.{}", patterns::get_net_player(player)->GetGamerInfo()->m_internal_ip.m_field1, patterns::get_net_player(player)->GetGamerInfo()->m_internal_ip.m_field2, patterns::get_net_player(player)->GetGamerInfo()->m_internal_ip.m_field3, patterns::get_net_player(player)->GetGamerInfo()->m_internal_ip.m_field4);
                std::string device = *script_global(scr_globals::gpbd_fm_1).at(player, scr_globals::size::gpbd_fm_1).at(96).at(29).as<int*>() == 2 ? "Controller" : "Keyboard";

                std::ostringstream oss2;
                oss2 << "0x" << std::hex << patterns::get_net_player(player)->GetGamerInfo()->m_host_token;
                std::string hexAddress = oss2.str();

                info.push("Rank", std::to_string(rank));
                info.push("Health", std::to_string(health));
                info.push("Cash", std::format("${}", std::to_string(cash)));
                info.push("Armor", std::to_string(armor));
                info.push("Bank", std::format("${}", std::to_string(bank)));
                info.push("Wanted Level", wanted);
                info.push("K/D Ratio", kd_ratio_str);
                info.push("Rockstar ID", std::to_string(patterns::get_net_player(player)->GetGamerInfo()->m_gamer_handle.m_rockstar_id));
                info.push("IP", ip);
                info.push("Host Token", hexAddress);
                info.push("Device", device);
                info.push("Ping", "0");
            }
            info.end_panel();

        
        }
    }


    inline void vehicle_info_panel() {
        panel panel(0.14f, 0.f, 0.02f);
        panel.setRenderTitle(false);

    

        panel.end_panel();

    }
}