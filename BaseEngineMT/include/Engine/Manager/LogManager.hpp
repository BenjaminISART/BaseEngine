#ifndef __LOGMANAGER__
#define __LOGMANAGER__

#include "Engine/Engine.hpp"
#include <functional>
#include <memory>

#define EngineLog Core::LogManager::GetLogManager()->Log

namespace Core
{
	class LogManager
	{
	private:

#pragma region private attributes
		static std::unique_ptr<LogManager> m_instance;
#pragma endregion

#pragma region private methods
		LogManager() = default; // CTOR

		friend std::unique_ptr<LogManager> std::make_unique<LogManager>();
#pragma endregion

	public:

		// LogManager(LogManager const& c); // CPY CTOR
		// LogManager(LogManager const && c); // MV CTOR
		~LogManager() = default; // DTOR

#pragma region public attributes

		template<class ... Args>
		void Log(const std::string& log, Args&& ... args)
		{
			std::string returnAdded = "> " + log + "\n";
			Core::Engine::GetEngine()->GetGuiManager()->lw.AddLog(returnAdded.c_str());
		}

		static LogManager* GetLogManager();
#pragma endregion

#pragma region public methods
#pragma endregion
	};

}

#endif // __LOGMANAGER__