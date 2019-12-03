#ifndef __MATRIX__
#define __MATRIX__

#include <array>
#include <iostream>

namespace ptm
{
	struct Mat4
	{
			float m_array[16]{};

			constexpr Mat4 () noexcept;
			constexpr Mat4 (Mat4 const&) noexcept;
			constexpr Mat4 (Mat4&&) noexcept;
			explicit constexpr Mat4(float const v);
			~Mat4() noexcept = default;

			[[nodiscard]]
			constexpr float& get(unsigned int, unsigned int) noexcept;
			[[nodiscard]]
			constexpr const float& get(unsigned int, unsigned int) const noexcept;

			static const Mat4&& identity;
			static const Mat4&& zero;

			inline void Transpose() noexcept;
			[[nodiscard]]
			inline Mat4 Transposed() const noexcept;

			inline void Print() noexcept;

			friend inline std::ostream& operator<<(std::ostream& os, const Mat4& dt);

			[[nodiscard]]
			float& operator()(unsigned int r, unsigned int c) noexcept;
			[[nodiscard]]
			Mat4 operator*(Mat4 const& m) const noexcept;
			constexpr Mat4& operator=(Mat4 const& m) noexcept;
	};

	inline std::ostream& operator<<(std::ostream& os, Mat4& dt);

}

#include "Mat4.inl"
#include "Mat4_utils.hpp"

#endif