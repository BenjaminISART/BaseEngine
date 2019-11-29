#ifndef __ENGINE__
#define __ENGINE__

#include "Engine/Manager/SceneLoader.hpp"
#include "Engine/Manager/RessourceManager.hpp"

namespace Core
{
	class Engine
	{
	private:

#pragma region private attributes
		RessourceManager m_rm;
#pragma endregion

#pragma region private methods
#pragma endregion

	public:

		Engine(); // CTOR
		// Engine(Engine const& c); // CPY CTOR
		// Engine(Engine const && c); // MV CTOR
		~Engine(); // DTOR

#pragma region public attributes
#pragma endregion

#pragma region public methods
#pragma endregion

	};
}

#endif // __ENGINE__