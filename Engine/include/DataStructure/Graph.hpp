#ifndef __GRAPH__
#define __GRAPH__

#include <vector>
#include <memory>
#include "Objects/GameObject.hpp"

namespace DataStructure
{
	struct Node
	{
	private:
		std::shared_ptr<Objects::GameObject> data;
		std::shared_ptr<Node> parent;
		std::vector<std::shared_ptr<Node>> childrens;

		friend class Graph;
	};

	class Graph
	{
	private:
		Node* m_head;

	public:
		Graph();
		~Graph();
	};
}

#endif