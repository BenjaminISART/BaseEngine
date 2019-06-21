#ifndef __IUpdatable__
#define __IUpdatable__

namespace Core
{
	class IUpdatable
	{
	private:
		bool m_hasToUpdate;
		bool m_enabled;
		int m_ID;

		friend class UpdateHandler;

	public:
		IUpdatable();
		virtual ~IUpdatable();

		virtual void Update() = 0;
	};
}

#endif
