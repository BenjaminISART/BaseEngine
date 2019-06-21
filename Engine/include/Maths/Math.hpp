#ifndef __PTM_MATH__
#define __PTM_MATH__

namespace ptm
{
	#pragma region SQRT

		double constexpr sqrtNewtonRaphson(const double x, const double curr, const double prev)
		{
			return curr == prev
				? curr
				: sqrtNewtonRaphson(x, 0.5 * (curr + x / curr), curr);
		}

		double constexpr sqrt(const double x)
		{
			return x >= 0 && x < std::numeric_limits<double>::infinity()
				? sqrtNewtonRaphson(x, x, 0)
				: std::numeric_limits<double>::quiet_NaN();
		}

	#pragma endregion personnal sqrt func


	#define PI 3.141592f

	constexpr float RAD(float const& x) { return x * PI / 180.0f; }
	constexpr float DEG(float const& x) { return x * 180.0f / PI; }

}

#endif