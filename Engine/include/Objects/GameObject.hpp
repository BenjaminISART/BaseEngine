#ifndef __GAMEOBJECT__
#define __GAMEOBJECT__

#include "Engine/IUpdatable.hpp"
#include "Objects/Components/Component.hpp"
#include <vector>
#include <memory>
#include <type_traits>

using namespace Objects::Components;

namespace Objects
{

	class GameObject final : public Core::IUpdatable
	{
	private:
		std::vector<std::shared_ptr<Component>> m_componentList;

	public:
		GameObject();
		GameObject(const GameObject& g);
		~GameObject();

		GameObject& operator=(GameObject const& g);

		void AddComponent(Component* c);
		template<class T>
		[[nodiscard]]
		Component* GetComponent();


		void Update() override;
	};

	// TODO faire un inl
	template <class T>
	Component* GameObject::GetComponent()
	{
		for (const std::shared_ptr<Component> c : m_componentList)
		{
			if (typeid(T) == typeid(*c))
				return c.get();
		}

		return nullptr;
	}
}

#endif