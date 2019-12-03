#include "Engine/Object/Object.hpp"
#include "Engine/Engine.hpp"

void Object::Draw()
{
	std::cout << "Object Draw" << std::endl	;
	if (!m_modelReady)
	{
		m_model = Core::Engine::GetEngine()->GetRessourceManager()->FindModel(m_modelName);

		if (m_model)
		{
			m_modelReady = true;
			std::cout << "Model Setted" << std::endl;
			return;
		}
	}

	else
		m_model->Draw();
}
