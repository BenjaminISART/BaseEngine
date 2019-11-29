#ifndef __TASKSYSTEMINL__
#define __TASKSYSTEMINL__

#include "TaskSystem.hpp"

template<class Function, class ...Args>
inline auto TaskExecution::TaskSystem::AddTask(Function&& func, Args&& ...args)
	-> std::future<typename std::result_of<Function(Args ...)>::type>
{
	using return_type = typename std::result_of<Function(Args...)>::type;

	auto task = std::make_shared< std::packaged_task<return_type()> >(
		std::bind(std::forward<Function>(func), std::forward<Args>(args)...)
		);

	std::future<return_type> res = task->get_future();

	{
		std::unique_lock<std::mutex> lock(m_mutex);

		if (m_stop)
			throw std::runtime_error("You can't enqueue after stop TaskSystem");

		m_tasks.emplace([task]() {(*task)(); });
	}

	m_condition.notify_one();
	return res;
}


#endif // __TASKSYSTEMINL__
