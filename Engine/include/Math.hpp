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
}

#endif