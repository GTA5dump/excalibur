#pragma once
#include "pch.h"

union vector_coord {
	int16_t i16;
	uint16_t u16;
	int32_t i32;
	uint32_t u32;
	float f_point;
};
struct vec2 {
	vector_coord x{}, y{};
};
struct image { unsigned char* data{}; vec2 size{}; };
struct image_data { unsigned char* bytes{}; int size{}; uint32_t delay{}; };
struct shader_data { ID3D11Resource* resource{}; ID3D11ShaderResourceView* resource_view{}; };
struct frame_data { uint32_t delay{}; shader_data shader{}; };
struct gif { unsigned char* bytes{}; image_data data{}; int* delays{}; int frame_count{}; vec2 size{}; int comp{}; };

namespace stb {
	namespace memory {
		extern image_data write(vec2& size, int comp, const void* data, int strideBytes, uint32_t delay);
		extern image read(image_data data);
		extern gif read_gif(image_data data);
	}
	namespace file {
		extern image read_image(std::filesystem::path path);
		extern gif read_gif(std::filesystem::path path);
	}
	extern std::vector<image_data> split_gif(std::filesystem::path path);
}

class d3d {
public:
	d3d();

	static std::pair<shader_data, vec2> create_texture(std::filesystem::path path);
	static std::vector<frame_data> create_gif_texture(std::filesystem::path path);
	static shader_data create_shader_data(image image);

	Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapchain;
	Microsoft::WRL::ComPtr<ID3D11Device> m_device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context;

	static d3d* get()
	{
		static d3d i{};

		return &i;
	}

	static void initialize() {
		get();
	}
};