#ifndef __COMPONENT__
#define __COMPONENT__

#include "Engine/IUpdatable.hpp"

namespace Objects
{
	class GameObject;
}

namespace Objects::Components
{
	class Component : public Core::IUpdatable
	{
	protected:
		bool m_firstFrame;

		virtual void Start() = 0;
		virtual void Update() override = 0;

		friend class Objects::GameObject;

	public:
		Component();
		Component(Component const& c) = default;
		virtual ~Component() = default;

		template<class T>
		[[nodiscard]]
		T* GetComponent();

		GameObject* m_gameObject;
	};
}

#include "Component.inl"

#endif
