#ifndef __GUIMANAGER__
#define __GUIMANAGER__

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class GuiManager
{
private:

#pragma region private attributes
	GLFWwindow* m_window;
#pragma endregion

#pragma region private methods
#pragma endregion

public:

	GuiManager() = default; // CTOR
	GuiManager(GuiManager const& c) = delete; // CPY CTOR
	GuiManager(GuiManager&& c) = delete; // MV CTOR
	~GuiManager() = default; // DTOR

#pragma region public attributes
#pragma endregion

#pragma region public methods
	void Init(GLFWwindow* w);
	void NewFrame() const;
	void SetViewPort();
	void Rend();
	void Terminate();
#pragma endregion
};

#endif // __GUIMANAGER__