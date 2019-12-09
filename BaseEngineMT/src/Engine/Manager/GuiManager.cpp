#include "Engine/Manager/GuiManager.hpp"
#include "Engine/Engine.hpp"

#include "ExtraLibs/imgui/imgui.h"
#include "ExtraLibs/imgui/imgui_impl_glfw.h"
#include "ExtraLibs/imgui/imgui_impl_opengl3.h"

void GuiManager::Init(GLFWwindow* w)
{
	m_window = w;
	
	ImGui::CreateContext();
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
	ImGui::Begin("Scene");

	ImGui::SetWindowPos({ 0,0 });
	ImGui::SetWindowSize({ 200, 200 });

	Core::Engine* eng = Core::Engine::GetEngine();

	for (auto& object : *eng->GetRenderer()->GetActualScene()->GetSGraph().GetObjects())
	{

		if (ImGui::BeginMenu(std::string(object.first + " :").c_str()))
		{
			ImGui::InputFloat(std::string(object.first + " pos x").c_str(), &object.second.transform.position.x); ImGui::SameLine();
			ImGui::InputFloat(std::string(object.first + " pos y").c_str(), &object.second.transform.position.y); ImGui::SameLine();
			ImGui::InputFloat(std::string(object.first + " pos z").c_str(), &object.second.transform.position.z);
			ImGui::SliderFloat(std::string(object.first + "  pos x").c_str(), &object.second.transform.position.x, -100.0f, 100.0f); ImGui::SameLine();
			ImGui::SliderFloat(std::string(object.first + "  pos y").c_str(), &object.second.transform.position.y, -100.0f, 100.0f); ImGui::SameLine();
			ImGui::SliderFloat(std::string(object.first + "  pos z").c_str(), &object.second.transform.position.z, -100.0f, 100.0f);
			ImGui::InputFloat(std::string(object.first + " rot x").c_str(), &object.second.transform.rotation.x); ImGui::SameLine();
			ImGui::InputFloat(std::string(object.first + " rot y").c_str(), &object.second.transform.rotation.y); ImGui::SameLine();
			ImGui::InputFloat(std::string(object.first + " rot z").c_str(), &object.second.transform.rotation.z);
			ImGui::SliderFloat(std::string(object.first + "  rot x").c_str(), &object.second.transform.rotation.x, -3.14f, 3.14f); ImGui::SameLine();
			ImGui::SliderFloat(std::string(object.first + "  rot y").c_str(), &object.second.transform.rotation.y, -3.14f, 3.14f); ImGui::SameLine();
			ImGui::SliderFloat(std::string(object.first + "  rot z").c_str(), &object.second.transform.rotation.z, -3.14f, 3.14f);
			ImGui::InputFloat(std::string(object.first + " scl x").c_str(), &object.second.transform.scale.x); ImGui::SameLine();
			ImGui::InputFloat(std::string(object.first + " scl y").c_str(), &object.second.transform.scale.y); ImGui::SameLine();
			ImGui::InputFloat(std::string(object.first + " scl z").c_str(), &object.second.transform.scale.z);
			ImGui::SliderFloat(std::string(object.first + "  scl x").c_str(), &object.second.transform.scale.x, 0.0f, 10.0f); ImGui::SameLine();
			ImGui::SliderFloat(std::string(object.first + "  scl y").c_str(), &object.second.transform.scale.y, 0.0f, 10.0f); ImGui::SameLine();
			ImGui::SliderFloat(std::string(object.first + "  scl z").c_str(), &object.second.transform.scale.z, 0.0f, 10.0f);
			ImGui::EndMenu();
		}

		object.second.transform.UpdateMatrix();
	}

	ImGui::Separator();

	if (ImGui::BeginMenu("Add Object"))
	{
		static char nam[80] = {};
		static char mod[80] = {};

		ImGui::InputText("name", nam, 80);
		ImGui::InputText("model", mod, 80);

		if (ImGui::Button("Confirm", { 100, 20 }))
		{
			std::cout << "new Object : " << nam << std::endl;
			Object toAdd;
			toAdd.SetModelName(std::string(mod));
			eng->GetRenderer()->GetActualScene()->GetSGraph().AddObject(std::string(nam), toAdd);
		}

		ImGui::EndMenu();
	}

	ImVec2 size = ImGui::GetWindowSize();

	ImGui::End();

	ImGui::Begin("Ressource Manager");

	ImGui::SetWindowPos({ size.x,0 });
	ImGui::SetWindowSize({ 200, 200 });

	for (auto& model : *eng->GetRessourceManager()->GetLoadedsModel())
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

		if (ImGui::Button("Confirm", { 100, 20 }))
		{
			std::cout << "run time load : " << path << std::endl;
			eng->GetRessourceManager()->RequestLoad(std::string(path), std::string(name));
		}

		ImGui::EndMenu();
	}

	ImGui::End();
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
