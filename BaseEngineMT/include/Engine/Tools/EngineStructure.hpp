#ifndef __ENGINESTRUCTURE__
#define __ENGINESTRUCTURE__

namespace Core
{
	class EngineStructure abstract
	{
	private:

#pragma region private attributes
		static void* m_ressourceManager;
		static void* m_engine;
		static void* m_renderer;

		friend class Engine;
#pragma endregion

#pragma region private methods
#pragma endregion

	public:

		EngineStructure() {}; // CTOR
		EngineStructure(EngineStructure const& c) = delete; // CPY CTOR
		EngineStructure(EngineStructure&& c) = delete; // MV CTOR
		virtual ~EngineStructure() {}; // DTOR

#pragma region public attributes
#pragma endregion

#pragma region public methods
#pragma endregion
	};
}

#endif // __ENGINESTRUCTURE__