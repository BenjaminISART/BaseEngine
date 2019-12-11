#include "RessourceManager.hpp"

inline void Core::RessourceManager::RequestModelLoad(std::string path, std::string name)
{
#ifdef MTLOAD

	std::pair<std::future<Model>, std::string>		p{ m_threadPool.AddTask([=] { return Model(path); }), std::move(name) };

	m_requestQueue.emplace(std::move(p));

	if (m_requestQueueEmpty.load())
	{
		std::cout << "Launch Check thread (Model)" << std::endl;
		m_requestQueueEmpty.store(false);
		m_threadPool.AddTask([this] { this->CheckRequestQueue(); });
	}

#else

	m_loadedModel.insert({ name, Model(path) });
	std::cout << "Non MT Loaded Ressource (Model) : " << name << std::endl;

#endif
}



inline void Core::RessourceManager::RequestTextureLoad(std::string path, std::string name)
{
#ifdef MTLOAD

	std::pair<std::future<Texture>, std::string> p{ m_threadPool.AddTask([=] { return Texture(path); }), std::move(name) };

	m_textureRequestQueue.emplace(std::move(p));

	if (m_textureRequestQueueEmpty.load())
	{
		std::cout << "Launch Check thread (Texture)" << std::endl;
		m_textureRequestQueueEmpty.store(false);
		m_threadPool.AddTask([this] { this->CheckTextureRequestQueue(); });
	}

#else

	m_loadedTexture.insert({ name, Texture(path) });
	std::cout << "Non MT Loaded Ressource (Texture) : " << name << std::endl;

#endif
}
