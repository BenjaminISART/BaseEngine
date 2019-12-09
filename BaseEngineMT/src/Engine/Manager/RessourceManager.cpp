#include "Engine/Manager/RessourceManager.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <sstream>

void Core::RessourceManager::CheckRequestQueue()
{
	while (!m_requestQueueEmpty.load() && !m_programEnded.load())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

		{
			std::unique_lock<std::mutex> lock(m_mutex);

			while (!m_requestQueue.empty() && m_requestQueue.front().first._Is_ready())
			{
				std::ostringstream buf;
				buf << "Model Loaded -> " << m_requestQueue.front().second << std::endl;
				std::cout << buf.str();
				m_loadeds.insert({ std::move(m_requestQueue.front().second), std::move(m_requestQueue.front().first.get()) });
				m_requestQueue.pop();
				std::cout << "end\n";
			}
		}

		if (m_requestQueue.empty())
			m_requestQueueEmpty.store(true);
	}
}



Core::Model* Core::RessourceManager::FindModel(std::string name)
{
	if (m_loadeds.find(name) != m_loadeds.end())
		return &m_loadeds.find(name)->second;

	else
		return nullptr;
}