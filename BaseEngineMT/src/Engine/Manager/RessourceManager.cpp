#include "Engine/Manager/RessourceManager.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>



void Core::RessourceManager::CheckRequestQueue()
{
	while (!m_requestQueueEmpty.load() && !m_programEnded.load())
	{
		{
			std::unique_lock<std::mutex> lock(m_mutex);

			while (!m_requestQueue.empty() && m_requestQueue.front()._Is_ready())
			{
				m_loadeds.emplace_back(std::move(m_requestQueue.front().get()));
				m_requestQueue.pop();
				//std::cout << "on a trouve" << std::endl;
			}
		}

		if (m_requestQueue.empty())
			m_requestQueueEmpty.store(true);
	}
}
