#ifndef __VEC3__
#define __VEC3__

#include <iostream>
#include <type_traits>

namespace ptm
{
    struct Vec3
    {
        // <Values>

            float x;
            float y;
            float z;
            float w;

        // </Values>

        // <CTOR / DTOR>

            constexpr Vec3 () noexcept;
            constexpr Vec3 (float x, float y, float z, float w = 0.0f) noexcept;
            constexpr Vec3 (Vec3 const& v) noexcept;
            constexpr Vec3 (Vec3&& v) noexcept;
            constexpr Vec3 (Vec3 const& v1, Vec3 const& v2) noexcept;
			~Vec3() noexcept = default;

        // </CTOR / DTOR>

        // <Constants>

            // Vec3(0,0,1)
            static const Vec3 forward;
            // Vec3(0,1,0)
            static const Vec3 up;
            // Vec3(1,0,0)
            static const Vec3 right;
			// Vec3(1,0,0)
			static const Vec3 zero;

        // </Constants>

        // <Maths Funcs>

            /* return the dot product between v1 and v2 */
            [[ nodiscard ]]
            static constexpr float Dot(Vec3 const& v1, Vec3 const& v2) noexcept;

            /* return the Cross product between v1 and v2 */
            [[ nodiscard ]]
            static constexpr Vec3 Cross(Vec3 const& v1, Vec3 const& v2) noexcept;

            /* return the dot product between this Vec3 and v */
            [[ nodiscard ]]
            constexpr float Dot(Vec3 const& v) const noexcept;

            /* return the Cross product between this Vec3 and v */
            [[ nodiscard ]]
            constexpr Vec3 Cross(Vec3 const& v) const noexcept;

            /* return the magnitude of v */
            [[ nodiscard ]]
            static constexpr float Magnitude(Vec3 const& v) noexcept;

            /* return the Magnitude of this Vec3 */
            [[ nodiscard ]]
            constexpr float Magnitude() const noexcept;

            /* return the normal Vec3 of v */
            [[ nodiscard ]]
            static constexpr Vec3 Normal(Vec3 const& v) noexcept;

            /* return the normal Vec3 of this Vec3 */
            [[ nodiscard ]]
            constexpr Vec3 Normal() const noexcept;

            /* return the distance between this Vec3 and v */
            [[ nodiscard ]]
            constexpr float Distance(Vec3 const& v) const noexcept;

            /* return the distance between v1 and v2 */
            [[ nodiscard ]]
            static constexpr float Distance(Vec3 const& v1, Vec3 const& v2) noexcept;

        // </Math Funcs>

        // <Other>

            // print the vector3
			inline void Print() const;

        // </Other>

        // <Operators>

            // <In>

                constexpr Vec3 operator+(Vec3 const& v) const noexcept;
                constexpr Vec3 operator+(Vec3&& v) const noexcept;
                constexpr Vec3& operator+=(Vec3 const& v) noexcept;
                constexpr Vec3& operator+=(Vec3&& v) noexcept;
                constexpr Vec3& operator=(Vec3 const& v) noexcept;
				constexpr Vec3 operator-() const noexcept;
				constexpr Vec3 operator-(Vec3 const& v) const noexcept;
				constexpr Vec3& operator-=(Vec3 const& v) noexcept;
				constexpr Vec3 operator-(Vec3&& v) const noexcept;
				constexpr Vec3 operator*(const float& v) const noexcept;
				constexpr Vec3& operator*=(const float& v) noexcept;

            // </In>

            // <Out>

                friend inline std::ostream& operator<<(std::ostream& os, const Vec3& dt);

                friend constexpr Vec3 operator ""_Vec3x(unsigned long long x);
                friend constexpr Vec3 operator ""_Vec3y(unsigned long long y);
                friend constexpr Vec3 operator ""_Vec3z(unsigned long long z);
                friend constexpr Vec3 operator ""_Vec3(unsigned long long a);
				friend constexpr Vec3 operator ""_Vec3x(const long double x);
				friend constexpr Vec3 operator ""_Vec3y(const long double y);
				friend constexpr Vec3 operator ""_Vec3z(const long double z);
				friend constexpr Vec3 operator ""_Vec3(const long double a);

            // </Out>

        // </Operators>

    }; // /Vec3

    // <Vec3 outsided declarations of operators and literals>

        // return a literal type
        constexpr Vec3 operator ""_Vec3x(const long double x);
        // return a literal type
        constexpr Vec3 operator ""_Vec3y(const long double y);
        // return a literal type
        constexpr Vec3 operator ""_Vec3z(const long double z);
        // return a literal type
        constexpr Vec3 operator ""_Vec3(const long double a);
        // return a literal type
        constexpr Vec3 operator ""_Vec3x(const unsigned long long x);
        // return a literal type
        constexpr Vec3 operator ""_Vec3y(const unsigned long long y);
        // return a literal type
        constexpr Vec3 operator ""_Vec3z(const unsigned long long z);
        // return a literal type
        constexpr Vec3 operator ""_Vec3(const unsigned long long a);

        inline std::ostream& operator<<(std::ostream& os, const Vec3& dt);

    // </>
}

#include "Engine/Maths/Vec3.inl"

#endif // __FOO__