#include "Managers/InputManager.hpp"
#include "Engine/Engine.hpp"

namespace Managers
{
	std::unique_ptr<InputManager> InputManager::m_instance = nullptr;

	InputManager::InputManager()
		= default;

	InputManager::~InputManager()
		= default;

	InputManager* InputManager::Instance()
	{
		if (m_instance == nullptr)
			m_instance = std::make_unique<InputManager>();

		return m_instance.get();
	}

	bool InputManager::IsKeyDown(const int& key) const
	{
		GLFWwindow* window = Core::Engine::Instance()->GetWindow();

		if (window == nullptr)
			return false;

		return glfwGetKey(window, key) == GLFW_PRESS;
	}



}