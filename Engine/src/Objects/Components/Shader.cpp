#include "Objects/Components/Shader.hpp"

namespace Objects::Components
{
	Shader::Shader() :
		m_ID(0)
	{
		
	}

	Shader::Shader(Shader const& s) :
		m_ID(s.m_ID)
	{

	}

	Shader::~Shader()
	{

	}

	Shader& Shader::operator=(Shader const& s)
	{
		m_ID = s.m_ID;
		return *this;
	}

	void Shader::Update()
	{
		std::cout << "update shader\n";
	}
}
