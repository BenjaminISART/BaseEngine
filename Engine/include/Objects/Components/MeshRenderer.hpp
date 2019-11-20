#ifndef __MESHRENDERER__
#define __MESHRENDERER__

#include "Objects/Components/Component.hpp"
#include <vector>

namespace Objects::Components
{
	class MeshRenderer : public Component
	{
	private:
		std::vector<unsigned int> m_IDs;

	public:
		MeshRenderer();
		MeshRenderer(MeshRenderer const& m);
		~MeshRenderer() = default;

		MeshRenderer& operator=(MeshRenderer const& m);

		void Start() override {}
		void Update() override {}
	};
}

#endif
