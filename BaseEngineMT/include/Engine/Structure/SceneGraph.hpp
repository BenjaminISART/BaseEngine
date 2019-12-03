#ifndef __SCENE_GRAPH__
#define __SCENE_GRAPH__

#include "Engine/Object/Object.hpp"
#include "Engine/Maths/Vec3.hpp"
#include <unordered_map>
#include <string>

using namespace ptm;

class SceneGraph
{
public:

#pragma region private attributes
	std::unordered_map<std::string, Object> m_objects;
#pragma endregion

#pragma region private methods
#pragma endregion

public:

	SceneGraph() = default; // CTOR
	// SceneGraph(SceneGraph const& c); // CPY CTOR
	// SceneGraph(SceneGraph const && c); // MV CTOR
	~SceneGraph() = default; // DTOR

	friend class Engine;
	friend class Renderer;

#pragma region public attributes
#pragma endregion

#pragma region public methods
	void AddObject(std::string name, Vec3 p = Vec3::zero, Vec3 r = Vec3::zero, Vec3 s = 1_Vec3)
	{
		m_objects.insert({ name, Object(p, r, s) });
	}

	void AddObject(std::string name, Object& o)
	{
		m_objects.insert({ name, std::move(o) });
	}
#pragma endregion
};

#endif // __SCENE_GRAPH__