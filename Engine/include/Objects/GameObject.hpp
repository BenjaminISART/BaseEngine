#ifndef __GAMEOBJECT__
#define __GAMEOBJECT__

#include "Engine/IUpdatable.hpp"
//#include "Objects/Components/Component.hpp"
#include <vector>
#include <memory>
#include <type_traits>


namespace Objects
{
	namespace Components
	{
		class Component;
	}

	using namespace Components;

	class GameObject final : public Core::IUpdatable
	{
	private:
		std::vector<std::shared_ptr<Component>> m_componentList;

	public:
		GameObject();
		GameObject(const GameObject& g);
		~GameObject();

		GameObject& operator=(GameObject const& g);

		void AddComponent(std::shared_ptr<Component> c);
		void AddComponent(Component* c);

		template<class T>
		[[nodiscard]]
		T* GetComponent();

		[[nodiscard]] std::vector<std::shared_ptr<Component>> Components() const { return m_componentList; }

		void Update() override;
	};

	
}

#include "GameObject.inl"

#endif