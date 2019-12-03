#include "Engine/Manager/RessourceManager.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>



void Core::RessourceManager::CheckRequestQueue()
{
	while (!m_requestQueueEmpty.load() && !m_programEnded.load())
	{
		{
			std::unique_lock<std::mutex> lock(m_mutex);

			while (!m_requestQueue.empty() && m_requestQueue.front().first._Is_ready())
			{
				m_loadeds.insert({ m_requestQueue.front().second, std::move(m_requestQueue.front().first.get()) });
				m_requestQueue.pop();
				std::cout << "Model Loaded" << std::endl;
			}
		}

		if (m_requestQueue.empty())
			m_requestQueueEmpty.store(true);
	}
}
