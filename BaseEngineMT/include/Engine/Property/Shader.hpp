#ifndef __SHADER__
#define __SHADER__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include <iostream>
#include <fstream>

class Shader
{
private:

#pragma region private attributes
#pragma endregion

#pragma region private methods
	void CheckCompilError(unsigned int id, std::string type);
#pragma endregion

public:

	Shader() = default; // CTOR
	Shader(std::string vs, std::string fs); // CTOR
	Shader(Shader const& c) = default; // CPY CTOR
	Shader(Shader&& c) = default; // MV CTOR
	~Shader() = default; // DTOR

#pragma region public attributes
	GLuint id;
#pragma endregion

#pragma region public methods

	void Use();

#pragma endregion
};

#endif // __SHADER__