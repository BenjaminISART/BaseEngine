#include "Engine/Engine.hpp"
#include "Engine/Tools/EngineStructure.hpp"


// tmp
#include "Engine/Property/Shader.hpp"

namespace Core
{
	std::unique_ptr<Engine> Engine::m_instance = nullptr;
 
	Engine::Engine()
	{
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(1000, 800, "EngineMT", nullptr, nullptr);

		if (m_window == nullptr)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(m_window);
		//glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);
		//glfwSetCursorPosCallback(m_window, Managers::InputManager::MouseCallback);
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



	Engine* Engine::GetEngine()
	{
		{
			if (m_instance == nullptr)
				m_instance = std::make_unique<Engine>();
		}

		return m_instance.get();
	}



	void Engine::Run()
	{
		// mainScene load
		// --------------
		m_renderer.m_scene.push_back(Core::SceneLoader::LoadScene("Data/Scenes/Scene1.xml"));

		Shader s("Resources/Shaders/object.vs", "Resources/Shaders/object.fs");
		s.Use();

		//SGraph->m_mainCamera = SGraph->FindGameObjectWithScript<Objects::Components::Camera>()->GetComponent<Objects::Components::Camera>();

		// render loop
		// -----------
		while (!glfwWindowShouldClose(m_window))
		{
			// update
			// ------
			//Core::UpdateHandler::Instance()->UpdateAll();
			for (auto& s : m_renderer.GetActualScene()->GetSGraph().m_objects)
			{
				s.second.Draw();
			}

			//m_rm.CheckRequestQueue();

			// render
			// ------
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//Renderer::Render::Instance()->RendScene();


			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			// -------------------------------------------------------------------------------
			glfwSwapBuffers(m_window);
			glfwPollEvents();

			// input
			// -----
			if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(m_window, true);
		}
	}
}