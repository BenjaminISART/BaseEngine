#ifndef __OBJECT__
#define __OBJECT__

#include "Engine/Property/Model.hpp"
#include "Engine/Property/Transform.hpp"
#include "Engine/Property/Shader.hpp"
#include "Engine/Maths/Vec3.hpp"

using namespace ptm;

class Object
{
private:

#pragma region private attributes
	std::string		m_modelName;
	bool			m_modelReady;
#pragma endregion

#pragma region private methods
#pragma endregion

public:

	Object() = default; // CTOR
	Object(Vec3 p, Vec3 r = Vec3::zero, Vec3 s = 1_Vec3);
	Object(Object const& c) = default; // CPY CTOR
	Object(Object&& c) = default; // MV CTOR
	~Object() = default; // DTOR

#pragma region public attributes
	Core::Model* model;

	Transform transform;
#pragma endregion

#pragma region public methods
	void SetTransform(Vec3 p, Vec3 r, Vec3 s);

	void SetModelName(const std::string& newName) { m_modelName = newName; }

	void Draw(unsigned int s);
#pragma endregion
};

#endif // __OBJECT__