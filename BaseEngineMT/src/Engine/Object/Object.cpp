#include "Engine/Object/Object.hpp"
#include "Engine/Engine.hpp"

#include <sstream>



Object::Object(Vec3 p, Vec3 r, Vec3 s) :
	model{ nullptr },
	m_modelReady{ false }
{
	SetTransform(p, r, s);
}



void Object::Draw(unsigned int s)
{
	if (!m_modelReady)
	{
		model = Core::Engine::GetEngine()->GetRessourceManager()->FindModel(m_modelName);

		if (model)
		{
			m_modelReady = true;
			std::ostringstream buf;
			buf << "Model Setted : " << m_modelName << std::endl;
			std::cout << buf.str();
			return;
		}
	}

	else if (model)
		model->Draw(s);

	if (!Core::Engine::GetEngine()->GetRessourceManager()->FindModel(m_modelName))
		m_modelReady = false;
}



void Object::SetTransform(Vec3 p, Vec3 r, Vec3 s)
{
	transform.position = p;
	transform.rotation = r;
	transform.scale = s;
	transform.UpdateMatrix();
}