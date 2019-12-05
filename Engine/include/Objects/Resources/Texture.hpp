#ifndef __TEXTURE__
#define __TEXTURE__

#include <string>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Objects::Resources
{
	class Texture
	{
	private:

	public:
		Texture() = default;
		Texture(Texture const& t) = default;
		explicit Texture(const std::string& path);
		~Texture() = default;

		GLuint m_ID{};
		std::string type;
		std::string path;

		void Use() const;

		Texture& operator=(Texture const& t) = default;
	};
}

#endif