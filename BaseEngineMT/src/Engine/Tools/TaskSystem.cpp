#include "Engine/Tools/TaskSystem.hpp"

namespace TaskExecution
{
	// CTOR
	TaskSystem::TaskSystem(size_t nbWorkers) :
		m_stop{ false }
	{
		for (size_t i = 0; i < nbWorkers; ++i)
		{
			m_workers.emplace_back(

				[this]
				{
					for (;;)
					{
						std::function<void()> task;

						{
							std::unique_lock<std::mutex> lock(this->m_mutex);

							this->m_condition.wait(lock,
								[this] { return this->m_stop || !this->m_tasks.empty(); }
							);

							if (this->m_stop && this->m_tasks.empty())
								return;

							task = std::move(this->m_tasks.front());
							this->m_tasks.pop();
						}

						task();
					}
				}
				);
		}
	}



	// DTOR
	TaskSystem::~TaskSystem()
	{
		Wait();
	}



	void TaskSystem::Wait()
	{
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_stop = true;
		}

		m_condition.notify_all();

		for (std::thread& worker : m_workers)
			if (worker.joinable())
				worker.join();
	}
}