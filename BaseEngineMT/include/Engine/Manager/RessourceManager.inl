#include "RessourceManager.hpp"

inline void Core::RessourceManager::RequestLoad(std::string path, std::string name)
{
#ifdef MTLOAD

	std::pair<std::future<Model>, std::string>		p{ m_threadPool.AddTask([=] { return Model(path); }), std::move(name) };

	m_requestQueue.emplace(std::move(p));

	if (m_requestQueueEmpty.load())
	{
		std::cout << "Launch Check thread" << std::endl;
		m_requestQueueEmpty.store(false);
		m_threadPool.AddTask([this] { this->CheckRequestQueue(); });
	}

#else

	m_loadeds.insert({ name, Model(path) });
	std::cout << "Non MT Loaded Ressource : " << name << std::endl;

#endif
}