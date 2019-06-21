#ifndef __ENGINE__
#define __ENGINE__

#include <iostream>
#include <memory>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Engine/IUpdatable.hpp"
#include "DataStructure/Graph.hpp"
#include "Objects/GameObject.hpp"

namespace Core
{
	class Engine
	{
	private:
		GLFWwindow* m_window;

		Objects::GameObject gO;

		static std::unique_ptr<Engine> m_instance;

		static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
		void TestExit();

		friend std::unique_ptr<Engine> std::make_unique<Engine>();
		Engine();

	public:

		Engine(Engine const& e) = delete;
		~Engine();

		[[nodiscard]]
		static Engine* Instance();
		void Load();
		void Run();
		void Unload();

		[[ nodiscard ]]
		GLFWwindow* GetWindow() const { return m_window; }

		Engine& operator=(const Engine& e) = delete;
	};

	constexpr unsigned int SCREEN_LENGTH = 1600;
	constexpr unsigned int SCREEN_WIDTH = 900;

}

#define EngineInst Core::Engine::Instance()

#endif