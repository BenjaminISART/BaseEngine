#ifndef __ENGINE__
#define __ENGINE__

#include "ExtraLibs/imgui/imgui.h"
#include "ExtraLibs/imgui/imgui_impl_glfw.h"
#include "ExtraLibs/imgui/imgui_impl_opengl3.h"

#include <mutex>
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Engine/Manager/SceneLoader.hpp"
#include "Engine/Manager/RessourceManager.hpp"
#include "Engine/Manager/Renderer.hpp"
#include "Engine/Manager/GuiManager.hpp"

namespace Core
{
	class Engine
	{
	private:

#pragma region private attributes
		std::mutex m_mutex;
		static std::unique_ptr<Engine> m_instance;

		RessourceManager	m_rm;
		Renderer			m_renderer;
		GuiManager			m_guiManager
;
		GLFWwindow* m_window;
#pragma endregion

#pragma region private methods
		Engine(); // CTOR
		friend std::unique_ptr<Engine> std::make_unique<Engine>();

		static void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
		{
			// make sure the viewport matches the new window dimensions; note that width and 
			// height will be significantly larger than specified on retina displays.
			glViewport(0, 0, width, height);
			GetEngine()->overviewCamera.UpdateProjectionMatrix(width, height);
		}
		
#pragma endregion

	public:
		static Engine* GetEngine();

		// Engine(Engine const& c); // CPY CTOR
		// Engine(Engine const && c); // MV CTOR
		~Engine() {}; // DTOR


#pragma region public attributes
		Camera overviewCamera;
#pragma endregion

#pragma region public methods 
		void Run();

		GLFWwindow*			GetWindow() { return m_window; }
		Renderer*			GetRenderer() { return &m_renderer; }
		RessourceManager*	GetRessourceManager() { return &m_rm; }
		GuiManager*			GetGuiManager() { return &m_guiManager; }

		void SetOverviewCameraSpeed(float _speed) { overviewCamera.speed = _speed; }
		void SetOverviewCameraSensibility(float _sensi) { overviewCamera.sensibility = _sensi; }
#pragma endregion

	};

}

#endif // __ENGINE__