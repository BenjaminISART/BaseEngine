#include "Engine/Property/Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "ExtraLibs/stb_image/stb_image.h"

#include "Engine/Manager/LogManager.hpp"

#include <sstream>
#include <sys/stat.h>


Texture::Texture(const std::string& _path) : m_data{ nullptr }, m_binded{ false }, id{ 0 }
{
	path = _path;

	stbi_set_flip_vertically_on_load(true);
	m_data = stbi_load(path.c_str(), &m_width, &m_height, &m_nrChannels, 0);
}



void Texture::Bind()
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (m_data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_data);
#ifdef MIPMAP
		glGenerateMipmap(GL_TEXTURE_2D);
#endif
	}
	else
		EngineLog("Failed to load texture " + path);

	FreeImage();
	m_binded = true;
}



void Texture::Use()
{
	if (!m_binded)
		Bind();

	glBindTexture(GL_TEXTURE_2D, id);
}



void Texture::FreeImage()
{
	stbi_image_free(m_data);
}
