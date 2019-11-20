#include "Objects/Components/Shader.hpp"

namespace Objects::Components
{
	Shader::Shader() :
		m_ID(0)
	{
	}

	Shader::Shader(std::string vs, std::string fs)
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
		CheckCompileErrors(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fscodechar, nullptr);
		glCompileShader(fragment);
		CheckCompileErrors(fragment, "FRAGMENT");

		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertex);
		glAttachShader(m_ID, fragment);
		glLinkProgram(m_ID);
		CheckCompileErrors(m_ID, "PROGRAM");

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void Shader::CheckCompileErrors(unsigned id, std::string type)
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

	Shader::Shader(Shader const& s) :
		m_ID(s.m_ID)
	{
	}

	Shader::~Shader()
	= default;

	Shader& Shader::operator=(Shader const& s)
	{
		m_ID = s.m_ID;
		return *this;
	}

	void Shader::Update()
	{
		//std::cout << "update Shader\n";
	}

	void Shader::Use() const
	{
		glUseProgram(m_ID);
	}
}
