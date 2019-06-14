#ifndef __Vec3INL__
#define __Vec3INL__

#include <cmath>
#include "Math.hpp"

namespace ptm
{
	#pragma region Operators

		#pragma region Out

            constexpr Vec3 operator ""_Vec3x(long double x)
            {
                return Vec3((float)x, 0.0f, 0.0f);
            }

            constexpr Vec3 operator ""_Vec3y(long double y)
            {
                return Vec3(0.0f, (float)y, 0.0f);
            }

            constexpr Vec3 operator ""_Vec3z(long double z)
            {
                return Vec3(0.0f, 0.0f, (float)z);
            }

            constexpr Vec3 operator ""_Vec3(long double a)
            {
                return Vec3((float)a, (float)a, (float)a);
            }

            constexpr Vec3 operator ""_Vec3x(unsigned long long x)
            {
                return Vec3((float)x, 0.0f, 0.0f);
            }

            constexpr Vec3 operator ""_Vec3y(unsigned long long y)
            {
                return Vec3(0.0f, (float)y, 0.0f);
            }

            constexpr Vec3 operator ""_Vec3z(unsigned long long z)
            {
                return Vec3(0.0f, 0.0f, (float)z);
            }

            constexpr Vec3 operator ""_Vec3(unsigned long long a)
            {
                return Vec3((float)a, (float)a, (float)a);
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

            constexpr void Vec3::operator=(Vec3 const& v) noexcept
            {
                x = v.x ; y = v.y ; z = v.z ; w = v.w ;
            }

            constexpr Vec3 Vec3::operator-() noexcept
            {
                return Vec3(-x,-y,-z);
            }

		#pragma endregion
        
	#pragma endregion

	#pragma region CTOR / DTOR

        constexpr Vec3::Vec3 () noexcept :
            Vec3{0.0f,0.0f,0.0f,0.0f}
        {}

        constexpr Vec3::Vec3 (float x, float y, float z, float w) noexcept :
            x{x}, y{y}, z{z}, w{w}
        {}

        constexpr Vec3::Vec3 (Vec3 const& v) noexcept :
            x{v.x}, y{v.y}, z{v.z}, w{v.w}
        {}

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
            float a = v1.y * v2.z - v1.z * v2.y ;
            float b = v1.z * v2.x - v1.x * v2.z ;
            float c = v1.x * v2.y - v1.y * v2.x ;
            return Vec3(a, b, c);
        }

        constexpr float Vec3::Dot(Vec3 const& v) noexcept
        {
            return x * v.x + y * v.y + z * v.z;
        }

        constexpr Vec3 Vec3::Cross(Vec3 const& v) noexcept
        {
            float a = y * v.z - z * v.y ;
            float b = z * v.x - x * v.z ;
            float c = x * v.y - y * v.x ;
            return Vec3(a, b, c);
        }

        constexpr float Vec3::Magnitude(Vec3 const& v) noexcept
        {
            return ptm::sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
        }

        constexpr float Vec3::Magnitude() const noexcept
        {
			float _x = x * x;
			float _y = y * y;
			float _z = z * z;
			float t = _x + _y + _z;
            return ptm::sqrt(t);
        }

        constexpr float Vec3::Distance(Vec3 const& v) noexcept
        {
            return Vec3(*this, v).Magnitude();
        }

        constexpr float Vec3::Distance(Vec3 const& v1, Vec3 const& v2) noexcept
        {
            return Vec3(v1, v2).Magnitude();
        }

		constexpr Vec3 Vec3::Normal(Vec3 const& v) noexcept
		{
			float m{ v.Magnitude() };
			return Vec3(v.x / m, v.y / m, v.z / m);
		}

		constexpr Vec3 Vec3::Normal() const noexcept
		{
			float m{ Magnitude() };
			return Vec3(x / m, y / m, z / m);
		}

	#pragma endregion
}

#endif