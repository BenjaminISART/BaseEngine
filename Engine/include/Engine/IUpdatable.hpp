#ifndef __IUpdatable__
#define __IUpdatable__

namespace Core
{
	class IUpdatable
	{
	private:
		bool m_hasToUpdate;
		bool m_enabled;

		friend class UpdateHandler;

	public:
		IUpdatable();
		~IUpdatable() = default;

		virtual void Update() {};
	};
}

#endif
