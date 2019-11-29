#include "Engine/Manager/RessourceManager.hpp"



void Core::RessourceManager::CheckRequestQueue()
{
	while (!m_requestQueueEmpty.load())
	{
		{
			std::unique_lock<std::mutex> lock(m_mutex);

			while (!m_requestQueue.empty() && m_requestQueue.front()._Is_ready())
			{
				m_loadeds.emplace_back(std::move(m_requestQueue.front().get()));
				m_requestQueue.pop();
			}
		}
			if (m_requestQueue.empty())
				m_requestQueueEmpty.store(true);
	}
}
