#ifndef __MESH__
#define __MESH__

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Objects/Resources/Texture.hpp"

namespace Objects::Components
{
	class Shader;
}

namespace Objects::Resources
{

	struct Mesh
	{
		std::vector<Texture> textures;
		std::vector<float> vertex;
		std::vector<unsigned int> index;

		GLuint VAO;
		GLuint VBO;
		GLuint EBO;

		void SetBuffers();
		void Draw(Objects::Components::Shader s);

		Mesh() = default;
	};
}

#endif