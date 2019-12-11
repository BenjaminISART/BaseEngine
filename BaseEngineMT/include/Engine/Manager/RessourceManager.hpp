#ifndef __RESOURCE_MANAGER__
#define __RESOURCE_MANAGER__

#include <iostream>
#include <future>
#include <mutex>
#include <atomic>
#include <unordered_map>
#include <queue>
#include <string>
#include <memory>
#include <utility>
#include "Engine/Property/Model.hpp"
#include "Engine/Property/Texture.hpp"
#include "Engine/Tools/TaskSystem.hpp"

namespace Core
{
	class RessourceManager
	{
	private:

#pragma region private attributes

		std::queue<std::pair<std::future<Model>, std::string>> m_requestQueue;
		std::queue<std::pair<std::future<Texture>, std::string>> m_textureRequestQueue;
		std::atomic<bool> m_requestQueueEmpty;
		std::atomic<bool> m_textureRequestQueueEmpty;
		std::atomic<bool> m_programEnded;
		std::mutex m_mutex;

		std::unordered_map<std::string, Model> m_loadedModel;
		std::unordered_map<std::string, Texture> m_loadedTexture;

		TaskExecution::TaskSystem m_threadPool;

#pragma endregion

		//-----------------------------------

#pragma region private methods
		void CheckRequestQueue();
		void CheckTextureRequestQueue();
#pragma endregion

	public:

		RessourceManager() : m_requestQueueEmpty{ true },
							 m_textureRequestQueueEmpty{ true },
							 m_programEnded{false},
							 m_threadPool{ 50 } {}; // CTOR
		explicit RessourceManager(size_t nbThread) : m_requestQueueEmpty{ true },
													 m_textureRequestQueueEmpty{ true },
													 m_programEnded{ false },
													 m_threadPool{nbThread} {}; // CTOR
		RessourceManager(RessourceManager const& c) = delete; // CPY CTOR
		RessourceManager(RessourceManager&& c) = delete; // MV CTOR
		~RessourceManager() {}; // DTOR

#pragma region public attributes
#pragma endregion

		//-----------------------------------

#pragma region public methods

		void RequestModelLoad(std::string path, std::string name);
		void RequestTextureLoad(std::string path, std::string name);

		Model* FindModel(std::string name);
		Texture* FindTexture(std::string name);

		std::unordered_map<std::string, Model>* GetLoadedsModel() { return &m_loadedModel; }
		std::unordered_map<std::string, Texture>* GetLoadedsTexture() { return &m_loadedTexture; }

#pragma endregion
	};

	#include "RessourceManager.inl"
}
#endif // __RESOURCE_MANAGER__