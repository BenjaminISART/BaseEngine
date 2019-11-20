#include "Objects/Components/MeshRenderer.hpp"

namespace Objects::Components
{
	MeshRenderer::MeshRenderer()
	= default;

	MeshRenderer::MeshRenderer(MeshRenderer const& m) : Component(m), 
		m_IDs(m.m_IDs)
	{

	}

	MeshRenderer& MeshRenderer::operator=(MeshRenderer const& m)
	{
		m_IDs = m.m_IDs;

		return *this;
	}
}
