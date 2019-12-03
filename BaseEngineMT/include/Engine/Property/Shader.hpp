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
	void CheckCompilError(unsigned int id, std::string type)
	{
		GLint success;
		GLchar infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(id, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(id, 1024, nullptr, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog
					<< "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(id, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(id, 1024, nullptr, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog
					<< "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
#pragma endregion

public:

	Shader() = default; // CTOR
	Shader(std::string vs, std::string fs)
	{
		std::string vscode, fscode;
		std::ifstream vsfile(vs);
		std::ifstream fsfile(fs);

		std::stringstream vsss, fsss;

		vsss << vsfile.rdbuf();
		fsss << fsfile.rdbuf();

		vsfile.close();
		fsfile.close();

		vscode = vsss.str();
		fscode = fsss.str();

		const char* vscodechar = vscode.c_str();
		const char* fscodechar = fscode.c_str();

		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vscodechar, nullptr);
		glCompileShader(vertex);
		CheckCompilError(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fscodechar, nullptr);
		glCompileShader(fragment);
		CheckCompilError(fragment, "FRAGMENT");

		id = glCreateProgram();
		glAttachShader(id, vertex);
		glAttachShader(id, fragment);
		glLinkProgram(id);
		CheckCompilError(id, "PROGRAM");

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}// CTOR
	// Shader(Shader const& c); // CPY CTOR
	// Shader(Shader const && c); // MV CTOR
	~Shader() = default; // DTOR

#pragma region public attributes
	GLuint id;
#pragma endregion

#pragma region public methods

	void Use()
	{
		glUseProgram(id);
	}

#pragma endregion
};

#endif // __SHADER__