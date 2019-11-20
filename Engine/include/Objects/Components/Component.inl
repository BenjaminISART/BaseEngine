#ifndef __COMPONENTINL__
#define __COMPONENTINL__

#include "Objects/GameObject.hpp"

namespace Objects::Components
{
	template <class T>
	T* Component::GetComponent()
	{
		return m_gameObject->GetComponent<T>();
	}
}

#endif