#ifndef __UPDATEHANDLER__
#define __UPDATEHANDLER__

#include "IUpdatable.hpp"
#include <vector>
#include <memory>

namespace  Core
{
	class UpdateHandler
	{
	private:
		static std::unique_ptr<UpdateHandler> m_instance;

		std::vector<std::shared_ptr<IUpdatable>> m_updateList;

		UpdateHandler();

	public:

		~UpdateHandler();

		static UpdateHandler* Instance();

		void UpdateAll();

	};
}

#endif
