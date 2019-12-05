#include "Engine/Object/Object.hpp"
#include "Engine/Engine.hpp"

#include <sstream>

void Object::Draw(unsigned int s)
{
	if (!m_modelReady)
	{
		m_model = Core::Engine::GetEngine()->GetRessourceManager()->FindModel(m_modelName);

		if (m_model)
		{
			m_modelReady = true;
			std::ostringstream buf;
			buf << "Model Setted : " << m_modelName << std::endl;
			std::cout << buf.str();
			return;
		}
	}

	else
		m_model->Draw(s);
}
