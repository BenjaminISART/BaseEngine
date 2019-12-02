#ifndef __RENDERER__
#define __RENDERER__

#include <vector>

class Renderer
{
private:

#pragma region private attributes
	std::vector<int> m_scene;
	int m_actualScene;
#pragma endregion

#pragma region private methods
#pragma endregion

public:

	Renderer() : m_actualScene{0} {} // CTOR
	// Renderer(Renderer const& c); // CPY CTOR
	// Renderer(Renderer const && c); // MV CTOR
	~Renderer(); // DTOR

#pragma region public attributes
#pragma endregion

#pragma region public methods
#pragma endregion
};

#endif // __RENDERER__