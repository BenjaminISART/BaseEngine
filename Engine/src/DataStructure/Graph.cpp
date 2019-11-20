#include <utility>
#include "DataStructure/Graph.hpp"

namespace DataStructure
{
	std::unique_ptr<Graph> Graph::m_instance = nullptr;

	Graph::Graph() :
		m_head{nullptr}
	{
		m_head = std::make_shared<Node>("World");
		m_head->data = std::make_shared<Objects::GameObject>();
		m_head->parent = nullptr;
	}

	Graph::~Graph()
		= default;

	Node::Node(std::string _name) : 
		name{std::move(_name)}
	{
		data = std::make_shared<Objects::GameObject>();
	}


	Graph* Graph::Instance()
	{
		if (m_instance == nullptr)
			m_instance = std::make_unique<Graph>();

		return m_instance.get();
	}

	void Graph::AddElement(const std::string& name, const std::string& parent)
	{
		if (parent == "noParent")
		{
			m_head->childrens.push_back(std::make_shared<Node>(name));
		}
	}

	Objects::GameObject* Graph::FindGameObject(std::string const& name)
	{
		return SearchRecursive(m_head.get(), name);;
	}


	Objects::GameObject* Graph::SearchRecursive(Node* n, std::string const& _name, Objects::GameObject* go)
	{
		if (n == nullptr) return nullptr;

		static Objects::GameObject* ret = nullptr;

		if (_name == n->name)
			ret = go = n->data.get();

		if (go == nullptr)
			for (auto& children : n->childrens)
				SearchRecursive(children.get(), _name);

		return ret;
	}

	void Graph::DebugGraph(Node* n, int i)
	{
		for (int y = 0; y < i; y++)
			std::cout << " ";

		std::cout << n->name << std::endl;

		for (auto& children : n->childrens)
		{
			DebugGraph(children.get(), i + 1);
		}
	}
}
