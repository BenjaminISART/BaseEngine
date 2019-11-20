#ifndef __RESOURCE_MANAGER__
#define __RESOURCE_MANAGER__

#include "Objects/Components/Model.hpp"
#include "Objects/Components/Shader.hpp"
#include "Objects/Resources/Texture.hpp"
#include <memory>
#include <unordered_map>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Managers
{
	class ResourceManager
	{
	private:

		std::unordered_map<std::string, std::shared_ptr<Objects::Components::Shader>> m_mapShader;
		std::unordered_map<std::string, std::shared_ptr<Objects::Components::Model>> m_mapModel;
		std::unordered_map<std::string, std::shared_ptr<Objects::Resources::Texture>> m_mapTexture;

		static std::unique_ptr<ResourceManager> m_instance;

		friend std::unique_ptr<ResourceManager> std::make_unique<ResourceManager>();
		ResourceManager() = default;

	public:
		ResourceManager(const ResourceManager& r) = delete;
		~ResourceManager() = default;

		[[nodiscard]]
		static ResourceManager* Instance();

		void AddShader(const std::string& name, const std::string& vs, const std::string& fs);
		void AddTexture(const std::string& name, const std::string& path);
		void AddModel(const std::string& name, const std::string& path);

		std::shared_ptr<Objects::Components::Shader> GetShader(const std::string& name) { return m_mapShader[name]; }
		std::shared_ptr<Objects::Components::Model> GetModel(const std::string& name) { return m_mapModel[name]; }
		std::shared_ptr<Objects::Resources::Texture> GetTexture(const std::string& name) { return m_mapTexture[name]; }

		ResourceManager& operator=(ResourceManager const& r) = delete;
	};
}

#define RManager Managers::ResourceManager::Instance()

#endif
