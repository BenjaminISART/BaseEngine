#include "Engine/Engine.hpp"
#include "Managers/InputManager.hpp"

namespace Core
{
	std::unique_ptr<Engine> Engine::m_instance = nullptr;

	Engine::Engine()
	{
		m_window = nullptr;
	}

	Engine::~Engine()
	= default;

	Engine* Engine::Instance()
	{
		if (m_instance == nullptr)
			m_instance = std::make_unique<Engine>();

		return m_instance.get();
	}

	void Engine::Load()
	{
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(SCREEN_LENGTH, SCREEN_WIDTH, "Engine", 
									 nullptr, nullptr);

		if (m_window == nullptr)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(m_window);
		glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);

		if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}
	}

	void Engine::Run()
	{
		// render loop
		// -----------
		while (!glfwWindowShouldClose(m_window))
		{
			// input
			// -----
			TestExit();

			// render
			// ------
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			// -------------------------------------------------------------------------------
			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}
	}

	void Engine::Unload()
	{
		glfwTerminate();
		m_window = nullptr;
	}

	void Engine::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	}

	void Engine::TestExit()
	{
		if (Input->IsKeyDown(GLFW_KEY_A))
			glfwSetWindowShouldClose(m_window, true);

		if (Input->IsKeyDown(Managers::Key::B))
			std::cout << "Hello World !" << std::endl;

	}
}
