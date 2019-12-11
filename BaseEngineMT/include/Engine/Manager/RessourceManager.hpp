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

		// tmp containers to stock std::future values
		std::queue<std::pair<std::future<Model>, std::string>> m_requestQueue;
		std::queue<std::pair<std::future<Texture>, std::string>> m_textureRequestQueue;

		// value to thread check if containers of std::futures are empty to stop check thread
		std::atomic<bool> m_requestQueueEmpty;
		std::atomic<bool> m_textureRequestQueueEmpty;

		std::atomic<bool> m_programEnded;
		std::mutex m_mutex;

		// Definitives containers of Model / Texture
		std::unordered_map<std::string, Model> m_loadedModel;
		std::unordered_map<std::string, Texture> m_loadedTexture;

		// THE thread pool
		TaskExecution::TaskSystem m_threadPool;

#pragma endregion

		//-----------------------------------

#pragma region private methods

		// those funcs are launched in an other thread and automatically killed if the atomic bools are false
		void CheckRequestQueue();
		void CheckTextureRequestQueue();

		void NonThreadedLoadModel(std::string path, std::string name);
		void NonThreadedLoadTexture(std::string path, std::string name);

#pragma endregion

	public:

		RessourceManager() : m_requestQueueEmpty{ true },
							 m_textureRequestQueueEmpty{ true },
							 m_programEnded{false},
							 m_threadPool{ 50 },
							 threadedLoad{ true } {} // CTOR
		explicit RessourceManager(size_t nbThread) : m_requestQueueEmpty{ true },
													 m_textureRequestQueueEmpty{ true },
													 m_programEnded{ false },
													 m_threadPool{nbThread},
													 threadedLoad{ true } {} // CTOR
		RessourceManager(RessourceManager const& c) = delete; // CPY CTOR
		RessourceManager(RessourceManager&& c) = delete; // MV CTOR
		~RessourceManager() {}; // DTOR

#pragma region public attributes

		std::atomic<bool> threadedLoad;

#pragma endregion

		//-----------------------------------

#pragma region public methods

		// call those func to load Models / Textures
		void RequestModelLoad(std::string path, std::string name);
		void RequestTextureLoad(std::string path, std::string name);

		// Find requested value in the definitives maps
		Model* FindModel(std::string name);
		Texture* FindTexture(std::string name);

		// getters
		std::unordered_map<std::string, Model>* GetLoadedsModel() { return &m_loadedModel; }
		std::unordered_map<std::string, Texture>* GetLoadedsTexture() { return &m_loadedTexture; }

#pragma endregion
	};

	#include "RessourceManager.inl"
}
#endif // __RESOURCE_MANAGER__