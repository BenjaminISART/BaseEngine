#ifndef __MATRIX__
#define __MATRIX__

#include <array>
#include <iostream>

namespace ptm
{
	class Mat4
	{
		private:
			float m_array[16]{};


		public:

			constexpr Mat4 () noexcept;
			constexpr Mat4 (Mat4 const&) noexcept;
			constexpr Mat4 (Mat4&&) noexcept;
			constexpr Mat4(float const v);
			~Mat4() noexcept = default;

			constexpr float& get(unsigned int, unsigned int) noexcept;
			static const Mat4 identity;
			inline void print();

			friend inline std::ostream& operator<<(std::ostream& os, const Mat4& dt);

			float& operator()(unsigned int r, unsigned int c);
			Mat4& operator=(Mat4 const& m);
	};

	inline std::ostream& operator<<(std::ostream& os, const Mat4& dt);

}

#include "Mat4.inl"

#endif