#ifndef __GRAPH__
#define __GRAPH__

#include <vector>
#include <string>
#include <memory>
#include "Objects/GameObject.hpp"
#include "Objects/Components/Camera.hpp"

namespace DataStructure
{
	struct Node
	{
	private:
		std::shared_ptr<Node> parent;
		std::vector<std::shared_ptr<Node>> childrens;

		const std::string name;

		friend class Graph;

	public:
		std::shared_ptr<Objects::GameObject> data;

		[[nodiscard]] std::vector<std::shared_ptr<Node>> Childrens() const { return childrens; }

		Node(std::string name);
	};

	class Graph
	{
	private:
		std::shared_ptr<Node> m_head;


		static std::unique_ptr<Graph> m_instance;

		Graph();
		friend std::unique_ptr<Graph> std::make_unique<Graph>();

		Objects::GameObject* SearchRecursive(Node* n, std::string const& _name, Objects::GameObject* go = nullptr);
		template<class T>
		Objects::GameObject* SearchRecursiveWithScript(Node* n);

		void DebugGraph(Node* n, int = 0);


	public:
		~Graph();

		Objects::Components::Camera* m_mainCamera = nullptr;

		static Graph* Instance();

		void AddElement(const std::string& name, const std::string& parent = "noParent");

		Objects::GameObject* FindGameObject(std::string const& name);

		template<class T>
		Objects::GameObject* FindGameObjectWithScript();

		[[nodiscard]] Node* Head() const { return m_head.get(); }

		void Debug() { DebugGraph(m_head.get()); }
		
	};
}

#define SGraph DataStructure::Graph::Instance()
#include "Graph.inl"

#endif