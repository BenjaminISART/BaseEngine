#ifndef __OBJECT__
#define __OBJECT__

#include "Engine/Property/Model.hpp"
#include "Engine/Property/Transform.hpp"
#include "Engine/Maths/Vec3.hpp"

using namespace ptm;

class Object
{
public:

#pragma region private attributes
	Core::Model*	m_model;
	std::string		m_modelName;
	bool			m_modelReady;

	Transform m_transform;
#pragma endregion

#pragma region private methods
#pragma endregion

public:

	Object() = default; // CTOR
	Object(Vec3 p, Vec3 r = Vec3::zero, Vec3 s = 1_Vec3) :
		m_model{nullptr},
		m_modelReady{false}
	{
		m_transform.position = p;
		m_transform.rotation = r;
		m_transform.scale = s;
		m_transform.UpdateMatrix();
	}
	// Object(Object const& c); // CPY CTOR
	// Object(Object const && c); // MV CTOR
	~Object() = default; // DTOR

#pragma region public attributes
#pragma endregion

#pragma region public methods
	void SetTransform(Vec3 p, Vec3 r, Vec3 s)
	{
		m_transform.position = p;
		m_transform.rotation = r;
		m_transform.scale = s;
		m_transform.UpdateMatrix();
	}

	void Draw();
#pragma endregion
};

#endif // __OBJECT__