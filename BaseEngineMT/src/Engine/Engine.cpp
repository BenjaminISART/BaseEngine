#include "Engine/Engine.hpp"
#include "Engine/Tools/EngineStructure.hpp"
#include "Engine/Manager/InputManager.hpp"


// tmp
#include "Engine/Property/Shader.hpp"

namespace Core
{
	std::unique_ptr<Engine> Engine::m_instance = nullptr;
 
	Engine::Engine() :
		overviewCamera{ ptm::Vec3(0.0f, 0.0f, 0.0f), ptm::Vec3(0.0f, 0.0f, 1000.0f), ptm::Vec3(0.0f, 1.0f, 0.0f) }
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
		glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);
		glfwSetCursorPosCallback(m_window, Managers::InputManager::MouseCallback);
		//glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		if (!gladLoadGL())
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
		// TMP IN+MGUI IMPLEMENTATION

		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(m_window, true);
		ImGui::StyleColorsDark();
		
		// mainScene load
		// --------------
		m_renderer.GetScenes()->push_back(Core::SceneLoader::LoadScene("Data/Scenes/Scene1.xml"));

		Shader s("Resources/Shaders/object.vs", "Resources/Shaders/object.fs");
		s.Use();

		overviewCamera.ProcessMouseMovement(0.0f, 0.0f);
		
		// render loop
		// -----------
		while (!glfwWindowShouldClose(m_window))
		{
			glfwPollEvents();
			
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			// update
			// ------
			//Core::UpdateHandler::Instance()->UpdateAll();

			//m_rm.CheckRequestQueue();

			// render
			// ------
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			overviewCamera.Update();
			m_renderer.RendActualScene(s.id);
			
			{
				ImGui::Begin("Scene");
				for (auto& object : *m_renderer.GetActualScene()->GetSGraph().GetObjects())
				{
					ImGui::SetWindowPos({0,0});

					if (ImGui::BeginMenu(std::string(object.first + " :").c_str()))
					{
						ImGui::InputFloat(std::string(object.first + " pos x").c_str(), &object.second.transform.position.x); ImGui::SameLine();
						ImGui::InputFloat(std::string(object.first + " pos y").c_str(), &object.second.transform.position.y); ImGui::SameLine();
						ImGui::InputFloat(std::string(object.first + " pos z").c_str(), &object.second.transform.position.z);
						ImGui::SliderFloat(std::string(object.first + "pos x").c_str(), &object.second.transform.position.x, -100.0f, 100.0f);
						ImGui::SliderFloat(std::string(object.first + "pos y").c_str(), &object.second.transform.position.y, -100.0f, 100.0f);
						ImGui::SliderFloat(std::string(object.first + "pos z").c_str(), &object.second.transform.position.z, -100.0f, 100.0f);
						ImGui::EndMenu();
					}

					object.second.transform.UpdateMatrix();
				}
				ImGui::End();

				ImGui::Begin("Ressource Manager");
				for (auto& model : *m_rm.GetLoadedsModel())
				{
					if (ImGui::BeginMenu(std::string(model.first + " :").c_str()))
					{
						ImGui::Text("path : "); ImGui::SameLine();
						ImGui::Text(model.second.GetPath());
						ImGui::EndMenu();
					}
				}

				ImGui::Separator();

				if (ImGui::BeginMenu("Load Model"))
				{
					static char path[80] = {};
					static char name[80] = {};

					ImGui::InputText("name", name, 80);
					ImGui::InputText("path", path, 80);

					if (ImGui::Button("Confirm", {100, 20}))
					{
						std::cout << "run time load : " << path << std::endl;
						m_rm.RequestLoad(std::string(path), std::string(name));
					}
					
					ImGui::EndMenu();
				}
				ImGui::End();
				
				//ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
				//ImGui::Checkbox("Demo Window", &test);      // Edit bools storing our window open/close state
				//ImGui::Checkbox("Another Window", &test);

				//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
				//ImGui::ColorEdit3("clear color", (float*)&test2); // Edit 3 floats representing a color

				//if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				//	counter++;
				//ImGui::SameLine();
				//ImGui::Text("counter = %d", counter);

				//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			// -------------------------------------------------------------------------------
			glfwSwapBuffers(m_window);

			// input
			// -----
			if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(m_window, true);
		}

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(m_window);
		glfwTerminate();
	}
}