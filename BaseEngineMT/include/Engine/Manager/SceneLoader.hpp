#ifndef __SCENE_LOADER__
#define __SCENE_LOADER__

#include "Engine/Structure/Scene.hpp"
#include "ExtraLibs/XML/rapidxml.hpp"
#include <string>
#include <iostream>

using namespace rapidxml;

namespace Core
{
	class SceneLoader
	{
	private:
		static void CreateObject(Scene* s, xml_node<>*, const std::string& parentName = "noparent");
		static void LoadResources(Scene* s, xml_node<>*);
		static void LoadGameObjects(Scene* s, xml_node<>*);

	public:
		SceneLoader() = delete; // CTOR
		SceneLoader(SceneLoader const& s) = delete; // CPY CTOR
		SceneLoader(SceneLoader&& s) = delete; // MV CTOR
		~SceneLoader() = default; // DTOR

		static Scene LoadScene(const std::string& s);
	};
}

#endif
