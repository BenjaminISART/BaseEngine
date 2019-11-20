#ifndef __GRAPHINL__
#define __GRAPHINL__

#include <type_traits>

namespace DataStructure
{
	template <class T>
	Objects::GameObject* Graph::FindGameObjectWithScript()
	{
		return SearchRecursiveWithScript<T>(m_head.get());
	}

	template<class T>
	Objects::GameObject* Graph::SearchRecursiveWithScript(Node* n)
	{
		if (n == nullptr) return nullptr;

		static Objects::GameObject* ret;

		for (auto i = 0; i < n->data->Components().size(); i++)
			if (typeid(T) == typeid(*n->data->Components()[i]))
				ret = n->data.get();

		if (ret == nullptr)
			for (auto& children : n->childrens)
				SearchRecursiveWithScript<T>(children.get());

		return ret;
	}
}

#endif