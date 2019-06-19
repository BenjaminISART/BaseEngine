#ifndef __ENGINE__
#define __ENGINE__

#include <iostream>
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Core
{
	class Engine
	{
	public:
		GLFWwindow* m_window;

		static std::unique_ptr<Engine> m_instance;

		static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
		void TestExit();

		Engine();

	public:

		Engine(Engine const& e) = delete;
		~Engine();

		static Engine* Instance();
		void Load();
		void Run();
		void Unload();

		[[ nodiscard ]]
		GLFWwindow* GetWindow() const { return m_window; }
	};

	constexpr unsigned int SCREEN_LENGTH = 1600;
	constexpr unsigned int SCREEN_WIDTH = 900;

}

#endif