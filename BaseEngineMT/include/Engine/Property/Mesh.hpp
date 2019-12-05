#ifndef __MESH__
#define __MESH__

#include "Engine/Property/Property.hpp"
#include "Engine/Property/Texture.hpp"
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Core
{
	struct Mesh : public Property
	{
		std::vector<float> vertex;
		std::vector<unsigned int> index;
		std::vector<Texture> textures;

		GLuint VAO;
		GLuint VBO;
		GLuint EBO;

		void SetBuffers()
		{
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(0);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(float), &vertex.front(), GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(unsigned int), &index.front(), GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<GLvoid*>(0));
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<GLvoid*>(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<GLvoid*>(6 * sizeof(float)));
			glEnableVertexAttribArray(2);
			glBindVertexArray(0);
		}

		void Draw(/*objects::Components::Shader s*/) {};

		Mesh() : VAO{ 0 }, VBO{ 0 }, EBO{ 0 } {}
	};
}

#endif // __MESH__