#include "Engine/Manager/LogManager.hpp"



namespace Core
{
	std::unique_ptr<LogManager> LogManager::m_instance = nullptr;

	LogManager* LogManager::GetLogManager()
	{
		return nullptr;
	}
}
