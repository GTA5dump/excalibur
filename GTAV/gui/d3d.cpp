#include "pch.h"
#include "d3d.h"
#include "hooks/patterns.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../includes/STB/STBImage.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../includes/STB/STBImageWrite.hpp"



d3d::d3d() :
	m_swapchain(*patterns::swapchain)
{
	if (FAILED(m_swapchain->GetDevice(__uuidof(ID3D11Device), (void**)m_device.GetAddressOf())))
		throw std::runtime_error("Failed to create a ID3D11Device");
	m_device->GetImmediateContext(m_context.GetAddressOf());
}


namespace stb {
	namespace memory {
		image_data write(vec2& size, int comp, const void* data, int strideBytes, uint32_t delay) {
			int imageSize;
			stbi_uc* image{ stbi_write_png_to_mem((const unsigned char*)data, strideBytes, size.x.i32, size.y.i32, comp, &imageSize) };
			if (!image) {
				// equivalent to RETURN_DEFAULT
				return {};
			}
			else {
				// equivalent to RETURN(...)
				return { image, imageSize, delay };
			}
		}
		image read(image_data data) {
			vec2 size{};
			stbi_uc* image{ stbi_load_from_memory(data.bytes, data.size, &size.x.i32, &size.y.i32, NULL, 0) };
			if (!image) {
				// equivalent to RETURN_DEFAULT
				return {};
			}
			else {
				// equivalent to RETURN(...)
				return { image, size };
			}
		}
		gif read_gif(image_data data) {
			vec2 size{};
			int* delays{};
			int frameCount{}, comp{};
			stbi_uc* image{ stbi_load_gif_from_memory(data.bytes, data.size, &delays, &size.x.i32, &size.y.i32, &frameCount, &comp, NULL) };
			if (!image) {
				// equivalent to RETURN_DEFAULT
				return {};
			}
			else {
				// equivalent to RETURN(...)
				return { image, data, delays,frameCount,size,comp };
			}
		}
	}

	namespace file {
		image read_image(std::filesystem::path path) {
			vec2 size{};
			stbi_uc* image{ stbi_load(path.string().c_str(), &size.x.i32, &size.y.i32, NULL, 4) };
			if (!image) {
				// equivalent to RETURN_DEFAULT
				return {};
			}
			else {
				// equivalent to RETURN(...)
				return { image, size };
			}
		}

		gif read_gif(std::filesystem::path path) {
			FILE* f{ stbi__fopen(path.string().c_str(), "rb") };
			if (!f) {
				// equivalent to RETURN_DEFAULT
				return {};
			}

			image_data data{};
			fseek(f, 0L, SEEK_END);
			data.size = ftell(f);
			fseek(f, 0L, SEEK_SET);
			data.bytes = decltype(data.bytes)(malloc(data.size));
			fread(data.bytes, data.size, 1, f);
			fclose(f);

			gif gif_result = memory::read_gif(data);
			free(data.bytes);

			if (!gif_result.bytes) {
				return {};
			}
			else {
				return gif_result;
			}

		}
	}

	std::vector<image_data> split_gif(std::filesystem::path path) {
		gif gif{ file::read_gif(path) };
		std::vector<image_data> frames{};
		size_t bytes{ size_t(gif.size.x.i32 * gif.comp) };
		for (size_t i{}; i != gif.frame_count; ++i)
			frames.push_back(memory::write(gif.size, gif.comp, gif.bytes + bytes * gif.size.y.i32 * i, 0, gif.delays[i]));
		stbi_image_free(gif.bytes);
		return frames;
	}
}

std::pair<shader_data, vec2> d3d::create_texture(std::filesystem::path path) {
	image image{ stb::file::read_image(path) };
	return std::make_pair(d3d::create_shader_data(image), image.size);
}

std::vector<frame_data> d3d::create_gif_texture(std::filesystem::path path) {
	std::vector<frame_data> frames{};
	std::vector<image_data> gif{ stb::split_gif(path) };
	for (auto& fr : gif) {
		image image{ stb::memory::read(fr) };
		frames.push_back({ fr.delay, d3d::create_shader_data(image) });
	}
	return frames;
}

shader_data d3d::create_shader_data(image image) {
	if (!image.data) {
		// equivalent to RETURN_DEFAULT
		return {};
	}

	ID3D11ShaderResourceView* resourceView{};
	ID3D11Texture2D* texture{};
	D3D11_TEXTURE2D_DESC desc{ image.size.x.u32, image.size.y.u32, 1, 1, DXGI_FORMAT_R8G8B8A8_UNORM, { 1 }, D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0 };
	D3D11_SUBRESOURCE_DATA subResource{ image.data, desc.Width * 4, 0 };
	get()->m_device->CreateTexture2D(&desc, &subResource, &texture);

	if (!texture) {
		// equivalent to RETURN_DEFAULT
		return {};
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{ DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_SRV_DIMENSION_TEXTURE2D, { 0, desc.MipLevels } };
	get()->m_device->CreateShaderResourceView(texture, &srvDesc, std::add_pointer_t<decltype(resourceView)>(&resourceView));

	// equivalent to RETURN_IF_VALID(texture, resourceView)
	if (!texture || !resourceView) {
		return {};
	}
	else {
		return { texture, resourceView };
	}
}
