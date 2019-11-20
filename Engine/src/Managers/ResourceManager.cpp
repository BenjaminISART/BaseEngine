#include "Managers/ResourceManager.hpp"

namespace Managers
{
	std::unique_ptr<ResourceManager> ResourceManager::m_instance = nullptr;

	ResourceManager* ResourceManager::Instance()
	{
		if (m_instance == nullptr)
			m_instance = std::make_unique<ResourceManager>();

		return m_instance.get();
	}

	void ResourceManager::AddShader(const std::string& name, const std::string& vs, const std::string& fs)
	{
		m_mapShader.emplace(name, std::make_shared<Objects::Components::Shader>(vs, fs));
	}

	void ResourceManager::AddTexture(const std::string& name, const std::string& path)
	{
		m_mapTexture.emplace(name, std::make_shared<Objects::Resources::Texture>(path));
	}

	void ResourceManager::AddModel(const std::string& name, const std::string& path)
	{
		m_mapModel.emplace(name, std::make_shared<Objects::Components::Model>(path));
	}
}
