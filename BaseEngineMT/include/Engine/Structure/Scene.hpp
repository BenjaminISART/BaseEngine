#ifndef __SCENE__
#define __SCENE__

#include "Engine/Structure/SceneGraph.hpp"

class Scene
{
	friend class Engine;
	friend class Renderer;
	friend class SceneLoader;

private:

#pragma region private attributes
	SceneGraph m_sceneGraph;
#pragma endregion

#pragma region private methods
#pragma endregion

public:

	Scene() = default; // CTOR
	// Scene(Scene const& c); // CPY CTOR
	// Scene(Scene const && c); // MV CTOR
	~Scene() = default; // DTOR

#pragma region public attributes
#pragma endregion

#pragma region public methods
	SceneGraph& GetSGraph() { return m_sceneGraph; };
#pragma endregion
};

#endif // __SCENE__