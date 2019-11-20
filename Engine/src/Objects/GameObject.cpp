#include "Objects/GameObject.hpp"
#include "Objects/Components/Component.hpp"
#include <iostream>

namespace Objects
{
	GameObject::GameObject()
	{
	}

	GameObject::GameObject(const GameObject& g)
	{
	}

	GameObject::~GameObject()
	{
	}

	GameObject& GameObject::operator=(GameObject const& g)
	{
		return *this;
	}

	void GameObject::AddComponent(std::shared_ptr<Component> c)
	{
		m_componentList.push_back(c);
	}

	void GameObject::AddComponent(Components::Component* c)
	{
		m_componentList.push_back(std::shared_ptr<Components::Component>(c));
		c->m_gameObject = this;
	}

	void GameObject::Update()
	{
		for (auto& i : m_componentList)
			if (i->m_firstFrame)
			{
				i->Start();
				i->m_firstFrame = false;
			}

		//std::cout << "update gameObject" << std::endl;
	}
}
