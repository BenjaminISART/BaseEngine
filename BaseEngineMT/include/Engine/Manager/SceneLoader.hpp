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
		static void SetGameObject(Scene* s, xml_node<>*, const std::string& parentName = "noparent");
		static void LoadResources(Scene* s, xml_node<>*);
		static void LoadGameObjects(Scene* s, xml_node<>*);/*
		static void LoadShader(xml_node<>*);
		static void LoadTexture(xml_node<>*);
		static void LoadModel(xml_node<>*);*/

	public:
		SceneLoader() = delete;
		SceneLoader(SceneLoader const& s) = delete;
		~SceneLoader() = default;

		static Scene LoadScene(const std::string& s);
	};
}

#endif
