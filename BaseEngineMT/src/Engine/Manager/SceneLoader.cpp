#include "Engine/Manager/SceneLoader.hpp"
#include "Engine/Engine.hpp"
#include "Engine/Property/Model.hpp"
#include "Engine/Engine.hpp"
#include "Engine/Maths/Vec3.hpp"
#include <vector>
#include <sstream>
#include <fstream>


using namespace rapidxml;

namespace Core
{
	Scene SceneLoader::LoadScene(const std::string& s)
	{
		Scene ret;

		xml_document<> doc;

		std::ifstream file(s);
		std::vector<char> buffer((std::istreambuf_iterator<char>(file)),
								 std::istreambuf_iterator<char>());
		buffer.push_back('\0');

		doc.parse<0>(&buffer[0]);

		xml_node<>* root_node = doc.first_node("Scene");

		LoadResources(&ret, root_node);
		LoadGameObjects(&ret, root_node);

		return ret;
	}

	void SceneLoader::LoadGameObjects(Scene* s, xml_node<>* root_node)
	{
		for (xml_node<>* gO = root_node->first_node("GameObject"); gO; gO = gO->next_sibling())
		{
			if (strcmp(gO->name(), "GameObject") == 0)
				SetGameObject(s, gO);
		}
	}

	void SceneLoader::LoadResources(Scene* s, xml_node<>* root_node)
	{
		xml_node<>* gO = root_node->first_node("Resource");

		for (xml_node<>* resource = gO->first_node(); resource; resource = resource->next_sibling())  
		{
			if (strcmp(resource->name(), "Model") == 0)
				Core::Engine::GetEngine()->GetRessourceManager()->RequestLoad(resource->value(), 
																			  resource->first_attribute("name")->value());
		}
	}

	void SceneLoader::SetGameObject(Scene* s, xml_node<>* gO, const std::string& parentName)
	{
		Object toAdd;

		std::cout << "new game objet : " << gO->first_attribute("name")->value() << std::endl;

		for (xml_node<>* script = gO->first_node(); script; script = script->next_sibling())
		{
			if (strcmp(std::string(script->name()).c_str(), "Model") == 0)
			{
				toAdd.SetModelName(script->value());
			}

			if (strcmp(script->name(), "Transform") == 0)
			{
				ptm::Vec3 t, r, s;

				std::stringstream sstr(script->value());

				sstr >> t.x;
				sstr >> t.y;
				sstr >> t.z;
				sstr >> r.x;
				sstr >> r.y;
				sstr >> r.z;
				sstr >> s.x;
				sstr >> s.y;
				sstr >> s.z;

				toAdd.SetTransform({ t.x, t.y, t.z }, { r.x, r.y, r.z }, { s.x, s.y, s.z });
			}
		}

		s->GetSGraph().AddObject(gO->first_attribute("name")->value(), toAdd);
	}
}

