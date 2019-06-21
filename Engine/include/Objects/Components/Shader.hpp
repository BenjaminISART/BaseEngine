#ifndef __SHADER__
#define __SHADER__

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Objects/Components/Component.hpp"

namespace Objects::Components
{
	class Shader : public Component
	{
	private:
		GLuint m_ID;

	public:
		Shader();
		Shader(Shader const& s);
		~Shader();

		Shader& operator=(Shader const& s);

		void Start() override {};
		void Update() override;
	};
}

#endif
