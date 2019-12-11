#include "Engine/Manager/RessourceManager.hpp"

#include "Engine/Manager/LogManager.hpp"

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
				EngineLog("Model Loaded -> " + m_requestQueue.front().second);
				m_loadedModel.insert({ std::move(m_requestQueue.front().second), std::move(m_requestQueue.front().first.get()) });
				m_requestQueue.pop();
			}
		}

		if (m_requestQueue.empty())
			m_requestQueueEmpty.store(true);
	}
}



void Core::RessourceManager::CheckTextureRequestQueue()
{
	while (!m_textureRequestQueueEmpty.load() && !m_programEnded.load())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

		{
			std::unique_lock<std::mutex> lock(m_mutex);

			while (!m_textureRequestQueue.empty() && m_textureRequestQueue.front().first._Is_ready())
			{
				EngineLog("Texture Loaded -> " + m_textureRequestQueue.front().second);
				m_loadedTexture.insert({ std::move(m_textureRequestQueue.front().second), std::move(m_textureRequestQueue.front().first.get()) });
				m_textureRequestQueue.pop();
			}
		}

		if (m_textureRequestQueue.empty())
			m_textureRequestQueueEmpty.store(true);
	}
}



void Core::RessourceManager::NonThreadedLoadModel(std::string path, std::string name)
{
	m_loadedModel.insert({ name, Model(path) });
	EngineLog("Non MT Loaded Ressource (Model) : " + name);
}



void Core::RessourceManager::NonThreadedLoadTexture(std::string path, std::string name)
{
	m_loadedTexture.insert({ name, Texture(path) });
	EngineLog("Non MT Loaded Ressource (Texture) : " + name);
}



Core::Model* Core::RessourceManager::FindModel(std::string name)
{
	if (m_loadedModel.find(name) != m_loadedModel.end())
		return &m_loadedModel.find(name)->second;

	else
		return nullptr;
}



Texture* Core::RessourceManager::FindTexture(std::string name)
{
	if (m_loadedTexture.find(name) != m_loadedTexture.end())
		return &m_loadedTexture.find(name)->second;

	else
		return nullptr;
}
