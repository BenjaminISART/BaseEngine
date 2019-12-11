#ifndef __TEXTURE__
#define __TEXTURE__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>



class Texture
{
private:

#pragma region private attributes
	unsigned char* m_data = nullptr;
	int m_width{0}, m_height{0}, m_nrChannels{0};

	bool m_binded = false;
#pragma endregion

#pragma region private methods
	void Bind();

	void FreeImage();
#pragma endregion

public:

	Texture() = default; // CTOR
	Texture(const std::string& _path); // CTOR
	Texture(Texture const& c) = default; // CPY CTOR
	Texture(Texture&& c) = default; // MV CTOR
	~Texture() = default; // DTOR

	Texture& operator=(Texture const& t) = default;
	Texture& operator=(Texture&& t) = default;

#pragma region public attributes
	GLuint id = 0;
	std::string type = "texture_diffuse";
	std::string path = "";
#pragma endregion

#pragma region public methods

	void Use();

#pragma endregion
};

#endif
