#ifndef __RENDER__
#define __RENDER__

#include <memory>
#include "DataStructure/Graph.hpp"

namespace Core::Renderer
{
	class Render final
	{
	private:

		static std::unique_ptr<Render> m_instance;

		friend std::unique_ptr<Render> std::make_unique<Render>();

		Render() = default;

		void RecursiveRend(DataStructure::Node* n);

	public:
		~Render() = default;

		static Render* Instance();

		void RendScene();

		Render& operator=(Render const& r) = delete;
	};
}

#endif