#ifndef __Vec3INL__
#define __Vec3INL__

#include "Math.hpp"

namespace ptm
{
	#pragma region Operators

		#pragma region Out

            constexpr Vec3 operator ""_Vec3x(const long double x)
            {
                return Vec3(float(x), 0.0f, 0.0f);
            }

            constexpr Vec3 operator ""_Vec3y(const long double y)
            {
                return Vec3(0.0f, float(y), 0.0f);
            }

            constexpr Vec3 operator ""_Vec3z(const long double z)
            {
                return Vec3(0.0f, 0.0f, float(z));
            }

            constexpr Vec3 operator ""_Vec3(const long double a)
            {
                return Vec3(float(a), float(a), float(a));
            }

            constexpr Vec3 operator ""_Vec3x(const unsigned long long x)
            {
                return Vec3(float(x), 0.0f, 0.0f);
            }

            constexpr Vec3 operator ""_Vec3y(const unsigned long long y)
            {
                return Vec3(0.0f, float(y), 0.0f);
            }

            constexpr Vec3 operator ""_Vec3z(const unsigned long long z)
            {
                return Vec3(0.0f, 0.0f, float(z));
            }

            constexpr Vec3 operator ""_Vec3(const unsigned long long a)
            {
                return Vec3(float(a), float(a), float(a));
            }

            inline std::ostream& operator<<(std::ostream& os, const Vec3& dt)
            {
                os << "Vec3(" << dt.x << ", " << dt.y << ", " << dt.z << ")";
                return os;
            }

		#pragma endregion

		#pragma region In
            
            constexpr Vec3& Vec3::operator+(Vec3 const& v) noexcept
            {
                x += v.x ; y += v.y ; z += v.z ; w += v.w ;
                return *this;
            }

            constexpr void Vec3::operator+=(Vec3 const& v) noexcept
            {
                x += v.x ; y += v.y ; z += v.z ; w += v.w ;
            }

            constexpr Vec3& Vec3::operator+(Vec3&& v) noexcept
            {
                x += v.x ; y += v.y ; z += v.z ; w += v.w ;
                return *this;
            }

            constexpr void Vec3::operator+=(Vec3&& v) noexcept
            {
                x += v.x ; y += v.y ; z += v.z ; w += v.w ;
            }

            constexpr Vec3& Vec3::operator=(Vec3 const& v) noexcept
            = default;

            constexpr Vec3 Vec3::operator-() const noexcept
            {
                return Vec3(-x,-y,-z);
            }

		#pragma endregion
        
	#pragma endregion

	#pragma region CTOR / DTOR

        constexpr Vec3::Vec3 () noexcept :
            Vec3{0.0f,0.0f,0.0f,0.0f}
        {}

        constexpr Vec3::Vec3 (const float x, const float y, const float z, const float w) noexcept :
            x{x}, y{y}, z{z}, w{w}
        {}

        constexpr Vec3::Vec3 (Vec3 const& v) noexcept 
        = default;

		constexpr Vec3::Vec3 (Vec3&& v) noexcept :
        x{std::move(v.x)}, y{std::move(v.y)}, z{std::move(v.z)}, w{std::move(v.w)}
        {}

        constexpr Vec3::Vec3 (Vec3 const& v1, Vec3 const& v2) noexcept :
            Vec3{v2.x - v1.x , v2.y - v1.y , v2.z - v1.z}
        {}


	#pragma endregion

	#pragma region Maths Funcs

        constexpr float Vec3::Dot(Vec3 const& v1, Vec3 const& v2) noexcept
        {
            return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
        }

        constexpr Vec3 Vec3::Cross(Vec3 const& v1, Vec3 const& v2) noexcept
        {
	        const auto a = v1.y * v2.z - v1.z * v2.y ;
            const auto b = v1.z * v2.x - v1.x * v2.z ;
            const auto c = v1.x * v2.y - v1.y * v2.x ;
            return Vec3(a, b, c);
        }

        constexpr float Vec3::Dot(Vec3 const& v) const noexcept
        {
            return x * v.x + y * v.y + z * v.z;
        }

        constexpr Vec3 Vec3::Cross(Vec3 const& v) const noexcept
        {
            const auto a = y * v.z - z * v.y ;
            const auto b = z * v.x - x * v.z ;
            const auto c = x * v.y - y * v.x ;
            return Vec3(a, b, c);
        }

        constexpr float Vec3::Magnitude(Vec3 const& v) noexcept
        {
			const auto a = v.x * v.x;
			const auto b = v.y * v.y;
			const auto c = v.z * v.z;
	        const auto t = a + b + c;
            return float(ptm::sqrt(t));
        }

        constexpr float Vec3::Magnitude() const noexcept
        {
			const auto _x = x * x;
			const auto _y = y * y;
			const auto _z = z * z;
			const auto t = _x + _y + _z;
            return float(ptm::sqrt(t));
        }

        constexpr float Vec3::Distance(Vec3 const& v) const noexcept
        {
            return Vec3(*this, v).Magnitude();
        }

        constexpr float Vec3::Distance(Vec3 const& v1, Vec3 const& v2) noexcept
        {
            return Vec3(v1, v2).Magnitude();
        }

		constexpr Vec3 Vec3::Normal(Vec3 const& v) noexcept
		{
			const auto m{ v.Magnitude() };
			return Vec3(v.x / m, v.y / m, v.z / m);
		}

		constexpr Vec3 Vec3::Normal() const noexcept
		{
			const auto m{ Magnitude() };
			return Vec3(x / m, y / m, z / m);
		}

	#pragma endregion
}

#endif