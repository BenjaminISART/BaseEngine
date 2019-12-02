#ifndef __SCENE_LOADER__
#define __SCENE_LOADER__

#include "ExtraLibs/XML/rapidxml.hpp"
#include <string>
#include <iostream>

using namespace rapidxml;

namespace Core
{
	class SceneLoader
	{
	private:
		static void SetGameObject(xml_node<>*, const std::string& parentName = "noparent");
		static void LoadResources(xml_node<>*);
		static void LoadGameObjects(xml_node<>*);/*
		static void LoadShader(xml_node<>*);
		static void LoadTexture(xml_node<>*);
		static void LoadModel(xml_node<>*);*/

	public:
		SceneLoader() = delete;
		SceneLoader(SceneLoader const& s) = delete;
		~SceneLoader() = default;

		static int LoadScene(const std::string& s);
	};
}

#endif
