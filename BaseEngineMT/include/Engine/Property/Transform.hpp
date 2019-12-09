#ifndef __TRANSFORM
#define __TRANSFORM

#include "Engine/Maths/Vec3.hpp"
#include "Engine/Maths/Mat4.hpp"
#include "Engine/Maths/Mat4_utils.hpp"

using namespace ptm;

class Transform
{
private:

#pragma region private attributes
#pragma endregion

#pragma region private methods
#pragma endregion

public:

	Transform(); // CTOR
	Transform(Transform const& c) = default; // CPY CTOR
	Transform(Transform&& c) = default; // MV CTOR
	~Transform() = default; // DTOR

#pragma region public attributes
	ptm::Mat4 transformMatrix;

	ptm::Vec3 position;
	ptm::Vec3 rotation;
	ptm::Vec3 scale;
#pragma endregion

#pragma region public methods

	void UpdateMatrix();

#pragma endregion
};

#endif // __TRANSFORM