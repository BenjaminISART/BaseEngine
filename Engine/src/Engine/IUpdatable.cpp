#include "Engine/IUpdatable.hpp"
#include "Engine/UpdateHandler.hpp"
#include <iostream>

namespace  Core
{
	IUpdatable::IUpdatable() :
		m_hasToUpdate { true },
		m_enabled { true },
		m_ID { 0 }
	{
		Core::UpdateHandler::Instance()->AddElement(this);
	}

	IUpdatable::~IUpdatable()
	{
		Core::UpdateHandler::Instance()->DisableElement(m_ID);
		std::cout << "disqbling " << m_ID << std::endl;
	}
}
