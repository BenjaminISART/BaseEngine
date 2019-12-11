#include "RessourceManager.hpp"

inline void Core::RessourceManager::RequestModelLoad(std::string path, std::string name)
{
	if (threadedLoad.load())
	{
		std::pair<std::future<Model>, std::string>		p{ m_threadPool.AddTask([=] { return Model(path); }), std::move(name) };

		m_requestQueue.emplace(std::move(p));

		if (m_requestQueueEmpty.load())
		{
			m_requestQueueEmpty.store(false);
			m_threadPool.AddTask([this] { this->CheckRequestQueue(); });
		}
	}

	else
		NonThreadedLoadModel(path, name);
}



inline void Core::RessourceManager::RequestTextureLoad(std::string path, std::string name)
{
	if (threadedLoad.load())
	{
		std::pair<std::future<Texture>, std::string> p{ m_threadPool.AddTask([=] { return Texture(path); }), std::move(name) };

		m_textureRequestQueue.emplace(std::move(p));

		if (m_textureRequestQueueEmpty.load())
		{
			m_textureRequestQueueEmpty.store(false);
			m_threadPool.AddTask([this] { this->CheckTextureRequestQueue(); });
		}
	}

	else
		NonThreadedLoadModel(path, name);
}
