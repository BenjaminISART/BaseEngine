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

	bool InputManager::IsPressingKey(const int& key) const
	{
		GLFWwindow* window = EngineInst->GetWindow();

		if (window == nullptr)
			return false;

		return glfwGetKey(window, key) == GLFW_PRESS;
	}

	bool InputManager::IsKeyDown(const int& key)
	{
		const auto it = m_keys.find (key);
		const bool pressed = IsPressingKey(key);

		if (it == m_keys.end())
			m_keys.emplace(key, std::make_pair(false, false));

		if (pressed && !m_keys[key].first)
		{
			m_keys[key].first = true;
			return true;
		}

		if (!pressed)
			m_keys[key].first = false;

		return false;
	}

	bool InputManager::IsKeyUp(const int& key)
	{
		const auto it = m_keys.find(key);
		const bool pressed = IsPressingKey(key);

		if (it == m_keys.end())
			m_keys.emplace(key, std::make_pair(false, false));

		if (!pressed && m_keys[key].second)
		{
			m_keys[key].second = false;
			return true;
		}

		if (pressed)
			m_keys[key].second = true;

		return false;
	}
}
