#include "Engine/UpdateHandler.hpp"
#include "Managers/InputManager.hpp"

namespace Core
{
	std::unique_ptr<UpdateHandler> UpdateHandler::m_instance = nullptr;

	UpdateHandler::UpdateHandler()
		= default;

	//TODO vider le vector a la destruction
	UpdateHandler::~UpdateHandler()
		= default;

	UpdateHandler* UpdateHandler::Instance()
	{
		if (m_instance == nullptr)
			m_instance = std::make_unique<UpdateHandler>();

		return m_instance.get();
	}

	void UpdateHandler::UpdateAll()
	{
		std::cout << "begin update of " << m_updateList.size() << " objects" << std::endl;
		for (size_t i = 0; i < m_updateList.size(); i++)
		{
			if (m_updateList[i] != nullptr)
			{
				if (m_updateList[i]->m_hasToUpdate && m_updateList[i]->m_enabled)
					m_updateList[i]->Update();
			}

			else
				RemoveElement(i);
		}
		std::cout << "end" << std::endl;
	}

	void UpdateHandler::AddElement(IUpdatable* u)
	{
		u->m_ID = m_updateList.size();
		m_updateList.push_back(u);
	}

	void UpdateHandler::RemoveElement(int i)
	{
		m_updateList.erase(m_updateList.begin() + i);

		for (unsigned int y = i; y < m_updateList.size(); ++y)
		{
			if (m_updateList[y] != nullptr)
			{
				m_updateList[y]->m_ID--;
			}
		}
	}

	void UpdateHandler::DisableElement(int id)
	{
		if (unsigned int(id) < m_updateList.size())
			m_updateList[id] = nullptr;
	}
}
