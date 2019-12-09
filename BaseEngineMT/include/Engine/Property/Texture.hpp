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
	unsigned char* m_data;
	int m_width{0}, m_height{0}, m_nrChannels{0};

	bool m_binded;
#pragma endregion

#pragma region private methods
	void Bind();

	void FreeImage();
#pragma endregion

public:

	Texture() = default; // CTOR
	Texture(const std::string& _path); // CTOR
	// Texture(Texture const& c); // CPY CTOR
	// Texture(Texture const && c); // MV CTOR
	~Texture() = default; // DTOR

#pragma region public attributes
	GLuint id;
	std::string type;
	std::string path;
#pragma endregion

#pragma region public methods

	void Use();

#pragma endregion
};

#endif
