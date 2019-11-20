#ifndef __TRANSFORM__
#define __TRANSFORM__

#include <iostream>
#include "Maths/Mat4.hpp"
#include "Maths/Vec3.hpp"
#include "Objects/Components/Component.hpp"

using namespace ptm;

namespace Objects::Components
{
	class Transform : public Component
	{
	public:
		Transform();
		Transform(Transform const& t);
		Transform(Vec3 const& t, Vec3 const& r, Vec3 const& s);
		~Transform();

		Vec3 translation;
		Vec3 rotation;
		Vec3 scale;

		Mat4 TRS;

		void Start() override {};
		void Update() override;

		Transform& operator=(Transform const& t);
	};
}

#endif