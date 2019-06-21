#ifndef __UPDATEHANDLER__
#define __UPDATEHANDLER__

#include "IUpdatable.hpp"
#include <vector>
#include <memory>
#include <iostream>

namespace  Core
{
	class UpdateHandler
	{
	private:
		static std::unique_ptr<UpdateHandler> m_instance;

		std::vector<IUpdatable*> m_updateList;

		UpdateHandler();
		friend std::unique_ptr<UpdateHandler> std::make_unique<UpdateHandler>();

	public:

		~UpdateHandler();

		[[ nodiscard ]]
		static UpdateHandler* Instance();

		void UpdateAll();
		void AddElement(IUpdatable* u);
		void RemoveElement(int);
		void DisableElement(int);

	};
}

#endif
