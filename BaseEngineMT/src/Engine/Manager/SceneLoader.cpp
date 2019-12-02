#include "Engine/Manager/SceneLoader.hpp"
#include "Engine/Engine.hpp"
#include "Engine/Property/Model.hpp"
#include <vector>
#include <fstream>


using namespace rapidxml;

namespace Core
{
	int SceneLoader::LoadScene(const std::string& s)
	{
		xml_document<> doc;

		std::ifstream file(s);
		std::vector<char> buffer((std::istreambuf_iterator<char>(file)),
								 std::istreambuf_iterator<char>());
		buffer.push_back('\0');

		doc.parse<0>(&buffer[0]);

		xml_node<>* root_node = doc.first_node("Scene");

		LoadResources(root_node);
		LoadGameObjects(root_node);

		return 1;
	}

	void SceneLoader::LoadGameObjects(xml_node<>* root_node)
	{
		/*for (xml_node<>* gO = root_node->first_node("GameObject"); gO; gO = gO->next_sibling())
		{
			if (strcmp(gO->name(), "GameObject") == 0)
				SetGameObject(gO);
		}*/
	}

	void SceneLoader::LoadResources(xml_node<>* root_node)
	{
		xml_node<>* gO = root_node->first_node("Resource");

		for (xml_node<>* resource = gO->first_node(); resource; resource = resource->next_sibling())
		{
			if (strcmp(resource->name(), "Model") == 0)
				Core::Engine::GetEngine()->GetRessourceManager()->RequestLoad(resource->value());
		}
	}

	void SceneLoader::SetGameObject(xml_node<>* gO, const std::string& parentName)
	{
		/*SGraph->AddElement( gO->first_attribute("name")->value() );
		std::cout << "new game objet : " << gO->first_attribute("name")->value() << std::endl;

		Objects::GameObject* fgO = SGraph->FindGameObject(
			gO->first_attribute("name")->value() );

		for (xml_node<>* script = gO->first_node(); script; script = script->next_sibling())
		{
			std::cout << script->name() << std::endl;

			std::shared_ptr<Component> c = Managers::ComponentFactory::CreateComponentWithName(script->name(), 
																		 script->value());
			if (c != nullptr)
			{
				std::cout << "lol" << std::endl;
				fgO->AddComponent(c);
			}
		}*/
	}

	/*void SceneLoader::LoadShader(xml_node<>* shader)
	{
		const std::string vs = shader->first_node("vertex")->value();
		const std::string fs = shader->first_node("fragment")->value();

		RManager->AddShader(shader->first_attribute("name")->value(), vs, fs);
		std::cout << "added shader " << shader->first_attribute("name")->value() << std::endl;
	}

	void SceneLoader::LoadTexture(xml_node<>* texture)
	{
		const std::string path = texture->value();

		RManager->AddTexture(texture->first_attribute("name")->value(), path);
		std::cout << "added texture " << texture->first_attribute("name")->value() << std::endl;
	}

	void SceneLoader::LoadModel(xml_node<>* model)
	{
		const std::string path = model->value();

		RManager->AddModel(model->first_attribute("name")->value(), path);
		std::cout << "added model " << model->first_attribute("name")->value() << std::endl;
	}*/
}

