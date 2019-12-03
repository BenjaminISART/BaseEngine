#ifndef __INPUTMANAGER__
#define __INPUTMANAGER__

#include <memory>
#include <unordered_map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Managers
{
	class InputManager
	{
	private:
		static std::unique_ptr<InputManager> m_instance;

		std::unordered_map<int, std::pair<bool, bool>> m_keys;

		static inline bool m_firstframemouse = true;
		static inline float m_lastX = 800;
		static inline float m_lastY = 450;

		InputManager();
		friend std::unique_ptr<InputManager> std::make_unique<InputManager>();

	public:

		~InputManager();

		[[nodiscard]]
		bool IsPressingKey(const int& key) const;
		[[nodiscard]]
		bool IsKeyDown(const int& key);
		[[nodiscard]]
		bool IsKeyUp(const int& key);

		static void MouseCallback(GLFWwindow* window, double xpos, double ypos);

		[[nodiscard]]
		static InputManager* Instance();
	};
}

#define Input Managers::InputManager::Instance()

#endif