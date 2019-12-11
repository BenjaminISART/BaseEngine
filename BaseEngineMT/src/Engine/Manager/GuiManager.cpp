#include "Engine/Manager/GuiManager.hpp"
#include "Engine/Engine.hpp"

#include "Engine/Manager/LogManager.hpp"

#include "ExtraLibs/imgui/imgui.h"
#include "ExtraLibs/imgui/imgui_impl_glfw.h"
#include "ExtraLibs/imgui/imgui_impl_opengl3.h"

void GuiManager::Init(GLFWwindow* w)
{
	m_window = w;
	
	ImGui::CreateContext();
	ImGui_ImplOpenGL3_Init("#version 130");
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui::StyleColorsDark();
}



void GuiManager::NewFrame() const
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}



void GuiManager::SetViewPort()
{
	lw.Draw("Log");

	//************************************* Scene's Objects

	//ImGui::Begin("Scene");

	//ImGui::SetWindowPos({ 0,0 });
	//ImGui::SetWindowSize({ 400, 200 });

	Core::Engine* eng = Core::Engine::GetEngine();
	auto sg = eng->GetRenderer()->GetActualScene()->GetSGraph().GetObjects();

	std::vector<std::string> toDelete;

	//ImGui::Separator();

	/* Objects */
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("MyScene"))
		{
			for (auto it = sg->begin(); it != sg->end(); it++)
			{
				if (ImGui::BeginMenu(std::string(it->first + " :").c_str()))
				{
					if (ImGui::BeginMenu("Position"))
					{
						ImGui::InputFloat(std::string("x##" + it->first + "pos").c_str(), &it->second.transform.position.x); ImGui::SameLine();
						ImGui::InputFloat(std::string("y##" + it->first + "pos").c_str(), &it->second.transform.position.y); ImGui::SameLine();
						ImGui::InputFloat(std::string("z##" + it->first + "pos").c_str(), &it->second.transform.position.z);
						ImGui::SliderFloat(std::string("x##" + it->first + "poss").c_str(), &it->second.transform.position.x, -100.0f, 100.0f); ImGui::SameLine();
						ImGui::SliderFloat(std::string("y##" + it->first + "poss").c_str(), &it->second.transform.position.y, -100.0f, 100.0f); ImGui::SameLine();
						ImGui::SliderFloat(std::string("z##" + it->first + "poss").c_str(), &it->second.transform.position.z, -100.0f, 100.0f);

						ImGui::EndMenu();
					}

					if (ImGui::BeginMenu("Rotation"))
					{
						ImGui::Text("Rotation");
						ImGui::InputFloat(std::string("x##" + it->first + "rot").c_str(), &it->second.transform.rotation.x); ImGui::SameLine();
						ImGui::InputFloat(std::string("y##" + it->first + "rot").c_str(), &it->second.transform.rotation.y); ImGui::SameLine();
						ImGui::InputFloat(std::string("z##" + it->first + "rot").c_str(), &it->second.transform.rotation.z);
						ImGui::SliderFloat(std::string("x##" + it->first + "rott").c_str(), &it->second.transform.rotation.x, -3.14f, 3.14f); ImGui::SameLine();
						ImGui::SliderFloat(std::string("y##" + it->first + "rott").c_str(), &it->second.transform.rotation.y, -3.14f, 3.14f); ImGui::SameLine();
						ImGui::SliderFloat(std::string("z##" + it->first + "rott").c_str(), &it->second.transform.rotation.z, -3.14f, 3.14f);

						ImGui::EndMenu();
					}

					if (ImGui::BeginMenu("Scale"))
					{
						ImGui::InputFloat(std::string("x##" + it->first + "scl").c_str(), &it->second.transform.scale.x); ImGui::SameLine();
						ImGui::InputFloat(std::string("y##" + it->first + "scl").c_str(), &it->second.transform.scale.y); ImGui::SameLine();
						ImGui::InputFloat(std::string("z##" + it->first + "scl").c_str(), &it->second.transform.scale.z);
						ImGui::SliderFloat(std::string("x##" + it->first + "scll").c_str(), &it->second.transform.scale.x, 0.0f, 10.0f); ImGui::SameLine();
						ImGui::SliderFloat(std::string("y##" + it->first + "scll").c_str(), &it->second.transform.scale.y, 0.0f, 10.0f); ImGui::SameLine();
						ImGui::SliderFloat(std::string("z##" + it->first + "scll").c_str(), &it->second.transform.scale.z, 0.0f, 10.0f);

						ImGui::EndMenu();
					}

					ImGui::Separator();

					// set new model
					static char name[80] = {};
					ImGui::InputText("name", name, 80);
					if (ImGui::Button("Set model"))
						it->second.SetNewModel(name);

					ImGui::Separator();

					// Set new texture
					static char namet[80] = {};
					ImGui::InputText("name##t", namet, 80);
					if (ImGui::Button("Set texture"))
						it->second.SetModelTexture(namet);

					ImGui::Separator();

					if (ImGui::Button("Remove"))
					{
						toDelete.push_back(it->first);
						EngineLog("Object " + it->first + " removed");
					}
					else
						it->second.transform.UpdateMatrix();

					ImGui::EndMenu();
				}
			}

			ImGui::Separator();

			/* Add Object */
			{
				if (ImGui::BeginMenu("Add Object"))
				{
					static char nam[80] = {};
					static char mod[80] = {};

					ImGui::InputText("name", nam, 80);
					ImGui::InputText("model", mod, 80);

					if (ImGui::Button("Confirm", { 100, 20 }))
					{
						EngineLog("new Object : " + std::string(nam));
						Object toAdd;
						toAdd.SetModelName(std::string(mod));
						eng->GetRenderer()->GetActualScene()->GetSGraph().AddObject(std::string(nam), toAdd);
					}

					ImGui::EndMenu();
				}
			}

			/* Remove Object with name */
			{
				if (ImGui::BeginMenu("Remove Object"))
				{
					static char nameToDelete[80] = {};

					ImGui::InputText("name", nameToDelete, 80);

					if (ImGui::Button("Confirm", { 100, 20 }))
					{
						EngineLog("Deleted Object : " + std::string(nameToDelete));
						eng->GetRenderer()->GetActualScene()->GetSGraph().RemoveObject(std::string(nameToDelete));
					}

					ImGui::EndMenu();
				}
			}

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	for (auto td : toDelete)
	{
		eng->GetRenderer()->GetActualScene()->GetSGraph().RemoveObject(td);
	}
	toDelete.clear();

	//ImGui::Separator();

	//ImVec2 size = ImGui::GetWindowSize();

	

	//ImGui::End();

	//************************************ Ressource Manager gui

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("RessourceManager"))
		{
			/* Models */
			{
				for (auto& model : *eng->GetRessourceManager()->GetLoadedsModel())
				{
					if (ImGui::BeginMenu(std::string(model.first + " :").c_str()))
					{
						ImGui::Text("path : "); ImGui::SameLine();
						ImGui::Text(model.second.GetPath());
						ImGui::Text("NumVertex : "); ImGui::SameLine();
						ImGui::Text(std::to_string(model.second.numVertex).c_str());
						ImGui::Text("NumFaces : "); ImGui::SameLine();
						ImGui::Text(std::to_string(model.second.numFace).c_str());
						ImGui::Spacing();
						if (ImGui::Button("Remove"))
							toDelete.push_back(model.first);

						ImGui::EndMenu();
					}
				}

				for (auto td : toDelete)
				{
					if (eng->GetRessourceManager()->FindModel(td))
					{
						EngineLog("Model " + td + " removed");
						eng->GetRessourceManager()->GetLoadedsModel()->erase(td);
					}
				}
				toDelete.clear();
			}

			ImGui::Separator();

			/* Texture */
			{
				for (auto& texture : *eng->GetRessourceManager()->GetLoadedsTexture())
				{
					if (ImGui::BeginMenu(std::string(texture.first + " :").c_str()))
					{
						ImGui::Text("path : "); ImGui::SameLine();
						ImGui::Text(texture.second.path.c_str());
						ImGui::Spacing();
						if (ImGui::Button("Remove"))
							toDelete.push_back(texture.first);

						ImGui::EndMenu();
					}
				}

				for (auto td : toDelete)
				{
					if (eng->GetRessourceManager()->FindTexture(td))
					{
						EngineLog("Texture " + td + " removed");
						eng->GetRessourceManager()->GetLoadedsTexture()->erase(td);
					}
				}
				toDelete.clear();
			}

			ImGui::Separator();

			/* Add / Remove model */
			{
				if (ImGui::BeginMenu("Load Model"))
				{
					static char path[80] = {};
					static char name[80] = {};

					ImGui::InputText("name", name, 80);
					ImGui::InputText("path", path, 80);

					if (ImGui::Button("Confirm", { 100, 20 }))
					{
						EngineLog("Loading " + std::string(path));
						eng->GetRessourceManager()->RequestModelLoad(std::string(path), std::string(name));
					}

					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Remove Model"))
				{
					static char nameToDelete[80] = {};

					ImGui::InputText("name", nameToDelete, 80);

					if (ImGui::Button("Confirm", { 100, 20 }))
					{
						if (eng->GetRessourceManager()->FindModel(nameToDelete))
						{
							EngineLog(std::string(nameToDelete) + " deleted");
							eng->GetRessourceManager()->GetLoadedsModel()->erase(nameToDelete);
						}
					}

					ImGui::EndMenu();
				}

				ImGui::Separator();

				if (ImGui::Button("Exemple Load"))
					eng->GetRessourceManager()->RequestModelLoad("Resources/Model/Skull/Gufram_Jolly_Roger_mat(1).obj", "test");
			}

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	static bool showPerf;
	static bool posReset;
	ImVec2 reset(10, 10);

	/* Window */
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Window"))
		{
			if (ImGui::Checkbox("Show Perf Window", &showPerf))
				posReset = true;

			if (ImGui::Checkbox("Show Log Window", &lw.draw))
				lw.reseted = false;

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	/* Perf */
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Perf"))
		{
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	static float newSpeed = 1.0f;
	static float newSensi = 1.0f;
	static bool	 tLoad = true;

	/* Option */
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Options"))
		{

			ImGui::SliderFloat("Camera Speed : ", &newSpeed, 0.0f, 10.0f, "%.1f");
			eng->SetOverviewCameraSpeed(newSpeed);
			ImGui::SliderFloat("Camera Sensi : ", &newSensi, 0.0f, 10.0f, "%.1f");
			eng->SetOverviewCameraSensibility(newSensi);

			if (ImGui::Checkbox("Threaded Ressource Load", &tLoad))
			{
				eng->GetRessourceManager()->threadedLoad.store(tLoad);
			}

			if (ImGui::Button("Exit"))
			{
				glfwSetWindowShouldClose(m_window, true);
			}

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	/* Perf Window */
	if (showPerf)
	{
		ImGui::Begin("Perf");

		if (posReset)
		{
			posReset = false;
			ImGui::SetWindowPos(reset);
		}

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::End();
	}

	
}



void GuiManager::Rend()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}



void GuiManager::Terminate()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
