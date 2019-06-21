#ifndef __MAT4INL__
#define __MAT4INL__

namespace ptm
{
	#pragma region CTOR / DTOR

		constexpr Mat4::Mat4() noexcept
		{
			for (auto& i : m_array)
				i = 0;
		}

		constexpr Mat4::Mat4(Mat4 const& m) noexcept
		{
			for (auto i = 0; i < 16; i++)
				m_array[i] = m.m_array[i];
		}

		constexpr Mat4::Mat4(Mat4&& m) noexcept
		{
			for (auto i = 0; i < 16; i++)
				m_array[i] = std::move(m.m_array[i]);
		}

		constexpr Mat4::Mat4(float const v) : Mat4()
		{
			get(1, 1) = v;
			get(2, 2) = v;
			get(3, 3) = v;
			get(4, 4) = v;
		}

	#pragma endregion

	#pragma region Funcs

		constexpr float& Mat4::get(unsigned int r, unsigned int c) noexcept
		{
			return m_array[((r - 1) * 4 + c) - 1];
		}

		constexpr const float& Mat4::get(unsigned int r, unsigned int c) const noexcept
		{
			return m_array[((r - 1) * 4 + c) - 1];
		}

		inline void Mat4::Transpose() noexcept
		{
			*this = Transposed();
		}

		inline Mat4 Mat4::Transposed() const noexcept
		{
			Mat4 ret = *this;

			ret(1, 2) = get(2, 1);
			ret(1, 3) = get(3, 1);
			ret(1, 4) = get(4, 1);
			ret(2, 1) = get(1, 2);
			ret(2, 3) = get(3, 2);
			ret(2, 4) = get(4, 2);
			ret(3, 1) = get(1, 3);
			ret(3, 2) = get(2, 3);
			ret(3, 4) = get(4, 3);
			ret(4, 1) = get(1, 4);
			ret(4, 2) = get(2, 4);
			ret(4, 3) = get(3, 4);

			return ret;
		}


		inline void Mat4::Print() noexcept
		{
			std::cout << "Mat4(\n\t" << get(1, 1) << " " <<
				get(1, 2) << " " <<
				get(1, 3) << " " <<
				get(1, 4) << "\n\t" <<
				get(2, 1) << " " <<
				get(2, 2) << " " <<
				get(2, 3) << " " <<
				get(2, 4) << "\n\t" <<
				get(3, 1) << " " <<
				get(3, 2) << " " <<
				get(3, 3) << " " <<
				get(3, 4) << "\n\t" <<
				get(4, 1) << " " <<
				get(4, 2) << " " <<
				get(4, 3) << " " <<
				get(4, 4) << "\n);" << std::endl;
		}

	#pragma endregion 

	#pragma region operators

		inline std::ostream& operator<<(std::ostream& os, Mat4& dt)
		{
			os << "Mat4(\n\t" << dt.get(1,1) << " " <<
				dt.get(1, 2) << " " <<
				dt.get(1, 3) << " " <<
				dt.get(1, 4) << "\n\t" <<
				dt.get(2, 1) << " " << 
				dt.get(2, 2) << " " << 
				dt.get(2, 3) << " " << 
				dt.get(2, 4) << "\n\t" << 
				dt.get(3, 1) << " " << 
				dt.get(3, 2) << " " << 
				dt.get(3, 3) << " " << 
				dt.get(3, 4) << "\n\t" << 
				dt.get(4, 1) << " " << 
				dt.get(4, 2) << " " << 
				dt.get(4, 3) << " " << 
				dt.get(4, 4) << "\n);";

			return os;
		}

		inline float& Mat4::operator()(unsigned int r, unsigned int c) noexcept
		{
			return m_array[((r - 1) * 4 + c) - 1];
		}

		inline Mat4 Mat4::operator*(Mat4 const& m) const noexcept
		{
			auto ret = Mat4::zero;

			for (unsigned int i = 1; i <= 4; i++)
				for (unsigned int y = 1; y <= 4; y++)
				{
					ret.get(i, y) = 0.0f;
					for (unsigned int z = 1; z <= 4; z++)
						ret(i, y) += get(i, z) * m.get(z, y);
				}

			return ret;
		}
		
		constexpr Mat4& Mat4::operator=(Mat4 const& m) noexcept
		{
			for (int i = 0; i < 16; i++)
				m_array[i] = m.m_array[i];

			return *this;
		}

	#pragma endregion 

		
}

#endif