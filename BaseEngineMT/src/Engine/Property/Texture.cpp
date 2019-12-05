#include "Engine/Property/Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "ExtraLibs/stb_image/stb_image.h"

void Texture::FreeImage()
{
	stbi_image_free(m_data);
}

Texture::Texture(const std::string& _path): m_data{nullptr}, m_binded{false}, id{0}
{
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), &m_width, &m_height, &m_nrChannels, 0);

	path = _path;
}
