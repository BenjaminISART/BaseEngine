#include "Maths/Mat4_utils.hpp"
#include "Maths/Mat4.hpp"
#include "Maths/Math.hpp"
#include "Maths/Vec3.hpp"


namespace ptm::Mat4_utils
{
	#pragma region Transform

		[[nodiscard]]
		Mat4 CreateRotationMatrix(Vec3 const& v, float angle)
		{
			Mat4 ret {Mat4::identity};
			const float c = cos(angle);
			const float s = sin(angle);
			const float t = 1 - c;
			ret.get(1, 1) = t * pow(v.x, 2) + c;
			ret.get(2, 1) = t * v.x * v.y - s * v.z;
			ret.get(3, 1) = t * v.x * v.z + s * v.y;
			ret.get(1, 2) = t * v.x * v.y + s * v.z;
			ret.get(2, 2) = t * pow(v.y, 2) + c;
			ret.get(3, 2) = t * v.z * v.y - s * v.x;
			ret.get(1, 3) = t * v.x * v.z - s * v.y;
			ret.get(2, 3) = t * v.z * v.y + s * v.x;
			ret.get(3, 3) = t * pow(v.z, 2) + c;
			ret.get(4, 4) = 1;
			return ret;
		}

		[[nodiscard]]
		Mat4 CreateRotationMatrixX(float const& angleX)
		{
			Mat4 ret;
			ret.get(1, 1) = 1;
			ret.get(2, 2) = cos(angleX);
			ret.get(3, 2) = -sin(angleX);
			ret.get(2, 3) = sin(angleX);
			ret.get(3, 3) = cos(angleX);
			ret.get(4, 4) = 1;
			return ret;
		}

		[[nodiscard]]
		Mat4 CreateRotationMatrixY(float const& angleY)
		{
			Mat4 ret = Mat4::identity;
			ret.get(1, 1) = cos(angleY);
			ret.get(1, 3) = -sin(angleY);
			ret.get(3, 1) = sin(angleY);
			ret.get(3, 3) = cos(angleY);
			ret.get(2, 2) = 1;
			ret.get(4, 4) = 1;
			return ret;
		}

		[[nodiscard]]
		Mat4 CreateRotationMatrixZ(float const& angleZ)
		{
			Mat4 ret = Mat4::identity;
			ret.get(1, 1) = cos(angleZ);
			ret.get(2, 1) = -sin(angleZ);
			ret.get(1, 2) = sin(angleZ);
			ret.get(2, 2) = cos(angleZ);
			return ret;
		}

		[[nodiscard]]
		Mat4 CreateEulerRotationMatrix(Vec3 const& v)
		{
			const Mat4 X = CreateRotationMatrixX(v.x);
			const Mat4 Y = CreateRotationMatrixY(v.y);
			const Mat4 Z = CreateRotationMatrixZ(v.z);
			return Z * X * Y;
		}

		[[nodiscard]]
		Mat4 CreateTranslationMatrix(Vec3 const& v)
		{
			Mat4 ret{ Mat4::identity };
			ret(4, 1) = v.x;
			ret(4, 2) = v.y;
			ret(4, 3) = v.z;
			return ret;
		}

		[[nodiscard]]
		Mat4 CreateScaleMatrix(Vec3 const& v)
		{
			Mat4 ret = Mat4::identity;
			ret(1, 1) = v.x;
			ret(2, 2) = v.y;
			ret(3, 3) = v.z;
			ret(4, 4) = 1.0f;
			return ret;
		}

		[[nodiscard]]
		Mat4 CreateTRS(Vec3 const& vT, Vec3 const& vR, Vec3 const& vS)
		{
			Mat4 TRS = CreateScaleMatrix(vS)
				* CreateEulerRotationMatrix(vR)
				* CreateTranslationMatrix(vT);

			return TRS;
		}

	#pragma endregion


	#pragma region Camera

		Mat4 InfinitePerspectiveProjection(float const& fov, float const& aspect, float const & zNear)
		{
			const float epsilon = 2.4e-7f;

			Mat4 ret = Mat4::zero;

			const float f = 1.0f / tan(RAD(fov) * 0.5f);

			ret(1, 1) = f / aspect;
			ret(2, 2) = f;
			ret(3, 3) = epsilon - 1.0f;
			ret(3, 4) = -1.0f;
			ret(4, 3) = (epsilon - 2.0f) * zNear;

			return ret;
		}

		Mat4 LookAt(const Vec3& eye, const Vec3& dir, const Vec3& up)
		{
			const Vec3 zaxis = (eye - dir).Normal();
			const Vec3 xaxis = (Vec3::Cross(up.Normal(), zaxis)).Normal();
			const Vec3 yaxis = Vec3::Cross(zaxis, xaxis);

			Mat4 translation = Mat4::identity;
			translation(4, 1) = -eye.x;
			translation(4, 2) = -eye.y;
			translation(4, 3) = -eye.z;
			Mat4 rotation = Mat4::identity;
			rotation(1, 1) = xaxis.x;
			rotation(2, 1) = xaxis.y;
			rotation(3, 1) = xaxis.z;
			rotation(1, 2) = yaxis.x;
			rotation(2, 2) = yaxis.y;
			rotation(3, 2) = yaxis.z;
			rotation(1, 3) = zaxis.x;
			rotation(2, 3) = zaxis.y;
			rotation(3, 3) = zaxis.z;

			return (translation * rotation);
		}

	#pragma endregion

}
