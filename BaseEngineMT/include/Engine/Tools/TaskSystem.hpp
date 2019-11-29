#ifndef __TASKSYSTEM__
#define __TASKSYSTEM__

#include <condition_variable>
#include <functional>
#include <thread>
#include <future>
#include <mutex>

#include <memory>
#include <vector>
#include <queue>

namespace TaskExecution
{
	class TaskSystem final
	{
	private:

		std::vector< std::thread > m_workers;
		std::queue< std::function<void()> > m_tasks;

		std::mutex m_mutex;
		std::condition_variable m_condition;
		bool m_stop;


	public:

		TaskSystem() = delete;
		explicit TaskSystem(size_t nbWorkers);
		~TaskSystem();

		template<class Function, class ...Args>
		auto AddTask(Function&& func, Args&& ... args)
			-> std::future<typename std::result_of<Function(Args...)>::type>;

		void Wait();
	};

	
	#include "TaskSystem.inl"
	
	

}

#endif // __TASKSYSTEM__

