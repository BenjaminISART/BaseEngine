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

		std::queue<std::pair<std::future<Model>, std::string>> m_requestQueue;
		std::atomic<bool> m_requestQueueEmpty;
		std::atomic<bool> m_programEnded;
		std::mutex m_mutex;

		std::unordered_map<std::string, Model> m_loadeds;

		TaskExecution::TaskSystem m_threadPool;

#pragma endregion

		//-----------------------------------

#pragma region private methods
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

		void RequestLoad(std::string path, std::string name);


		Model* FindModel(std::string name);

#pragma endregion
	};

	#include "RessourceManager.inl"
}
#endif // __RESOURCE_MANAGER__