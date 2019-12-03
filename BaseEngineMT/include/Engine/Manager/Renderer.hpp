#ifndef __RENDERER__
#define __RENDERER__

#include "Engine/Structure/Scene.hpp"
#include "Engine/Object/Camera.hpp"
#include <vector>

class Renderer
{
public:

#pragma region private attributes
	std::vector<Scene> m_scene;
	int m_actualScene;
#pragma endregion

#pragma region private methods
#pragma endregion

public:

	Renderer() : m_actualScene{ 0 } {} // CTOR
	// Renderer(Renderer const& c); // CPY CTOR
	// Renderer(Renderer const && c); // MV CTOR
	~Renderer() = default; // DTOR

#pragma region public attributes
#pragma endregion

#pragma region public methods
	void SetActualScene(int i) { m_actualScene = i; }

	Scene* GetActualScene() { return &m_scene[m_actualScene]; }

	void RendActualScene(unsigned int shaderid);
#pragma endregion
};

#endif // __RENDERER__