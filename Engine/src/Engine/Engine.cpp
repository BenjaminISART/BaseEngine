#include "Engine/Engine.hpp"
#include "Engine/Render/Render.hpp"
#include "Objects/Components/Shader.hpp"
#include "Objects/Components/Transform.hpp"
#include "Objects/Components/Model.hpp"
#include "Managers/InputManager.hpp"
#include "Managers/ResourceManager.hpp"
#include "Engine/UpdateHandler.hpp"
#include "DataStructure/Graph.hpp"
#include "Engine/SceneLoader.hpp"

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
		glfwSetCursorPosCallback(m_window, Managers::InputManager::MouseCallback);
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}

		glEnable(GL_DEPTH_TEST);
		/*glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
	}

	void Engine::Run()
	{
		// mainScene load
		// --------------
		Core::SceneLoader::LoadScene("Data/Scenes/Scene1.xml");

		SGraph->m_mainCamera = SGraph->FindGameObjectWithScript<Objects::Components::Camera>()->GetComponent<Objects::Components::Camera>();

		// render loop
		// -----------
		while (!glfwWindowShouldClose(m_window))
		{
			// update
			// ------
			Core::UpdateHandler::Instance()->UpdateAll();

			if (Input->IsKeyDown(GLFW_KEY_T))
			{
				std::cout << "" << std::endl;
				std::cout << SGraph->FindGameObject("benji")->GetComponent<Objects::Components::Transform>()->translation << std::endl;
				std::cout << "" << std::endl;
			}

			if (Input->IsKeyDown(GLFW_KEY_Y))
			{
				std::cout << "" << std::endl;
				std::cout << SGraph->FindGameObject("adel")->GetComponent<Objects::Components::Transform>()->translation << std::endl;
				std::cout << "" << std::endl;
			}

			if (Input->IsKeyDown(GLFW_KEY_U))
			{
				std::cout << "" << std::endl;
				std::cout << SGraph->m_mainCamera->position << std::endl;
				std::cout << "" << std::endl;
			}

			if (Input->IsKeyDown(GLFW_KEY_P))
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			if (Input->IsKeyDown(GLFW_KEY_O))
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);


			// render
			// ------
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			Renderer::Render::Instance()->RendScene();


			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			// -------------------------------------------------------------------------------
			glfwSwapBuffers(m_window);
			glfwPollEvents();

			// input
			// -----
			TestExit();
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

	void Engine::MouseMotionCallback(GLFWwindow* w, double x, double y)
	{

	}

	void Engine::TestExit()
	{
		if (Input->IsPressingKey(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(m_window, true);
	}
}
