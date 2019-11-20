#ifndef __GOINL__
#define __GOINL__

namespace Objects
{
	template <class T>
	T* GameObject::GetComponent()
	{
		for (size_t i = 0; i < m_componentList.size(); i++)
		{
			if (typeid(T) == typeid(*m_componentList[i]))
				return static_cast<T*>(m_componentList[i].get());
		}

		return nullptr;
	}
}

#endif