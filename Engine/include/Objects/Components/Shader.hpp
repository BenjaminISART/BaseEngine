#ifndef __SHADER__
#define __SHADER__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Objects/Components/Component.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Objects::Components
{
	class Shader final : public Component
	{
	private:
		GLuint m_ID;

		void CheckCompileErrors(unsigned int id, std::string type);

	public:
		Shader();
		Shader(std::string vs, std::string fs);
		Shader(Shader const& s);
		~Shader();

		Shader& operator=(Shader const& s);

		void Start() override {};
		void Update() override;

		void Use() const;

		[[nodiscard]] GLuint ID() const { return m_ID; }
	};
}

#endif
