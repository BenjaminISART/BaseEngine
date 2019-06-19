#include "Engine/UpdateHandler.hpp"

namespace Core
{
	std::unique_ptr<UpdateHandler> UpdateHandler::m_instance = nullptr;

	UpdateHandler::UpdateHandler() = default;

	//TODO vider le vector a la destruction
	UpdateHandler::~UpdateHandler() = default;

	UpdateHandler* UpdateHandler::Instance()
	{
		if (m_instance == nullptr)
			m_instance = std::make_unique<UpdateHandler>();

		return m_instance.get();
	}

	void UpdateHandler::UpdateAll()
	{
		for (const auto& i : m_updateList)
		{
			if (i->m_hasToUpdate)
				i->Update();
		}
	}
}
