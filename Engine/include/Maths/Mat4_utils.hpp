#ifndef __MAT4_UTILS__
#define __MAT4_UTILS__

#include "Maths/Mat4.hpp"
#include "Maths/Vec3.hpp"

namespace ptm::Mat4_utils
{
	#pragma region Transform

		[[nodiscard]]
		Mat4 CreateRotationMatrix(Vec3 const&, float);
		[[nodiscard]]
		Mat4 CreateRotationMatrixX(float const&);
		[[nodiscard]]
		Mat4 CreateRotationMatrixY(float const&);
		[[nodiscard]]
		Mat4 CreateRotationMatrixZ(float const&);
		[[nodiscard]]
		Mat4 CreateEulerRotationMatrix(Vec3 const&);
		[[nodiscard]]
		Mat4 CreateTranslationMatrix(Vec3 const&);
		[[nodiscard]]
		Mat4 CreateScaleMatrix(Vec3 const&);
		[[nodiscard]]
		Mat4 CreateTRS(Vec3 const&, Vec3 const&, Vec3 const&);

	#pragma endregion

	#pragma region Camera

		Mat4 InfinitePerspectiveProjection(float const& fov, float const& aspect, float const& zNear);
		Mat4 LookAt(const Vec3& eye, const Vec3& dir, const Vec3& up);

	#pragma endregion
}

#endif
