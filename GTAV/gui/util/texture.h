#pragma once
#include "pch.h"
#include "rage/classes/sysMemAllocator.h"
#include "rage/classes/grcTexture.h"
#include "rage/classes/grcTextureFactory.h"
#include "rage/classes/grcTextureStore.h"
#include "rage/classes/pgDictionary.h"
#include "util/util.h"

namespace menu {
    struct texture_context {
        std::string m_name;
        rage::grcTexture* m_texture;
    };

    class textures {
    public:
        textures();
        static void tick();
        void load_image(std::filesystem::path path);
        texture_context get(std::string name);
        bool exists(std::string name) {
            texture_context texture{ get(name) };
            if (!texture.m_name.empty()) {
                return true;
            }
            return false;
        }
    private:
        static textures* get()
        {
            static textures i{};

            return &i;
        }
    public:
        static void initialize() {
            get();
        }
    private:
        std::filesystem::path m_path{ Util::GetDocumentsPath() };
        rage::pgDictionary* m_dictionary{};
        std::vector<std::string> m_files{};
        std::vector<texture_context> m_textures{};
    };
}