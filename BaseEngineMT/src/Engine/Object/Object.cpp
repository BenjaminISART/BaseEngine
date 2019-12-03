#include "Engine/Object/Object.hpp"
#include "Engine/Engine.hpp"

void Object::Draw()
{
	if (!m_modelReady)
	{
		m_model = Core::Engine::GetEngine()->GetRessourceManager()->FindModel(m_modelName);
		m_modelReady = true;
		std::cout << "Model Setted" << std::endl;
		return;
	}

	//else
		//m_model->Draw();
}
