#include "Objects/GameObject.hpp"
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

	void GameObject::AddComponent(Components::Component* c)
	{
		m_componentList.push_back(std::shared_ptr<Components::Component>(c));
	}

	void GameObject::Update()
	{
		for (auto& i : m_componentList)
			if (i->m_firstFrame)
			{
				i->Start();
				i->m_firstFrame = false;
			}

		std::cout << "update gameObject" << std::endl;
	}
}
