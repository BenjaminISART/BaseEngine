#include "Engine/Object/Object.hpp"
#include "Engine/Engine.hpp"
#include "Engine/Manager/LogManager.hpp"

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
			EngineLog("Model setted : " + m_modelName);
			return;
		}
	}

	else if (model)
		model->Draw(s);

	if (!Core::Engine::GetEngine()->GetRessourceManager()->FindModel(m_modelName))
		m_modelReady = false;
}



void Object::SetNewModel(const std::string& newName)
{
	if (Core::Engine::GetEngine()->GetRessourceManager()->FindModel(newName) != nullptr)
	{
		SetModelName(newName);
		m_modelReady = false;
		model = nullptr;
	}
}



void Object::SetTransform(Vec3 p, Vec3 r, Vec3 s)
{
	transform.position = p;
	transform.rotation = r;
	transform.scale = s;
	transform.UpdateMatrix();
}