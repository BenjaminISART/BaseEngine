#include "Objects/Components/Transform.hpp"

namespace Objects::Components
{
	Transform::Transform() :
		translation(Vec3::zero),
		rotation(Vec3::zero),
		scale(1_Vec3),
		TRS(Mat4(0.0f))
	{
	}

	Transform::Transform(Transform const& t) :
		translation(t.translation),
		rotation(t.rotation),
		scale(t.scale),
		TRS(t.TRS)
	{
	}

	Transform::Transform(Vec3 const& t, Vec3 const& r, Vec3 const& s) :
		translation(t),
		rotation(r),
		scale(s)
	{
		TRS = Mat4_utils::CreateTRS(t, r, s);
	}

	Transform::~Transform()
		= default;

	void Transform::Update()
	{
		TRS = Mat4_utils::CreateTRS(translation, rotation, scale);
	}

	Transform& Transform::operator=(Transform const& t)
	{
		translation = t.translation;
		rotation = t.rotation;
		scale = t.scale;
		TRS = t.TRS;

		return *this;
	}
}
