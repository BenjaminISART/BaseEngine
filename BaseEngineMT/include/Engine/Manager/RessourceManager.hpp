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
#include "Engine/Property/Property.hpp"
#include "Engine/Property/Model.hpp"
#include "Engine/Tools/EngineStructure.hpp"
#include "Engine/Tools/TaskSystem.hpp"

namespace Core
{
	class RessourceManager
	{
	private:

#pragma region private attributes

		std::queue<std::future<Model>> m_requestQueue;
		std::atomic<bool> m_requestQueueEmpty;
		std::atomic<bool> m_programEnded;
		std::mutex m_mutex;

		std::vector<Model> m_loadeds;

		TaskExecution::TaskSystem m_threadPool;

#pragma endregion

		//-----------------------------------

#pragma region private methods
	public:

		void CheckRequestQueue();

#pragma endregion

	public:

		RessourceManager() : m_requestQueueEmpty{ true }, m_programEnded{false}, m_threadPool{ 20 } {}; // CTOR
		explicit RessourceManager(size_t nbThread) : m_requestQueueEmpty{ true }, m_programEnded{ false }, m_threadPool{nbThread} {}; // CTOR
		// RessourceManager(RessourceManager const& c); // CPY CTOR
		// RessourceManager(RessourceManager const && c); // MV CTOR
		~RessourceManager() {}; // DTOR

#pragma region public attributes
#pragma endregion

		//-----------------------------------

#pragma region public methods

		void RequestLoad(std::string path);

#pragma endregion
	}; // RessourceManager end



	inline void RessourceManager::RequestLoad(std::string path)
	{
		//std::cout << "Request : " << path << std::endl;
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_requestQueue.emplace(m_threadPool.AddTask([=] { return Model(path); }));
		}

		/*if (m_requestQueueEmpty.load())
		{
			std::cout << "Launch Check thread" << std::endl;
			m_requestQueueEmpty.store(false);
			m_threadPool.AddTask([this] { this->CheckRequestQueue(); });
		}*/
	}

}
#endif // __RESOURCE_MANAGER__