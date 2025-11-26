/*
 *                                              /$$$$$$
 *                                             /$$__  $$
 *     /$$$$$$$  /$$    /$$ /$$$$$$   /$$$$$$$|__/  \ $$
 *    | $$__  $$|  $$  /$$//$$__  $$ /$$_____/   /$$$$$/
 *    | $$  \ $$ \  $$/$$/| $$$$$$$$| $$        |___  $$
 *    | $$  | $$  \  $$$/ | $$_____/| $$       /$$  \ $$
 *    | $$  | $$   \  $/  |  $$$$$$$|  $$$$$$$|  $$$$$$/
 *    |__/  |__/    \_/    \_______/ \_______/ \______/

nvec3: a simple vec3 single header lib in C++
   https://github.com/nxck2005/nvec3

MIT License

Copyright (c) 2025 Nxck

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
#pragma once

#include <cmath>
#include <format>
#include <string>
namespace nvec3 {

    inline constexpr float EPS = 1e-6f;
    inline constexpr float EPSSQ = 1e-12f;

    struct Vec3 {
        float x;
        float y;
        float z;
        constexpr Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
        constexpr Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

        // ADD, ADD and concat
        constexpr Vec3& operator += (const Vec3& other) {
            this->x += other.x;
            this->y += other.y;
            this->z += other.z;
            return *this;
        }

        constexpr Vec3 operator + (const Vec3& other) const {
            return Vec3(this->x + other.x, this->y + other.y, this->z + other.z);
        }

        // SUB, SUB and concat
        constexpr Vec3& operator -= (const Vec3& other) {
            this->x -= other.x;
            this->y -= other.y;
            this->z -= other.z;
            return *this;
        }

        constexpr Vec3 operator - (const Vec3& other) const {
            return Vec3(this->x - other.x, this->y - other.y, this->z - other.z);
        }

        // Scalar div and mult
        constexpr Vec3& operator /= (const float scalar) {
            // todo; add an assert for 0?
            this->x /= scalar;
            this->y /= scalar;
            this->z /= scalar;
            return *this;
        }

        constexpr Vec3 operator / (const float scalar) const {
            return Vec3(this->x / scalar, this->y / scalar, this->z / scalar);
        }

        constexpr Vec3& operator *= (const float scalar) {
            this->x *= scalar;
            this->y *= scalar;
            this->z *= scalar;
            return *this;
        }

        constexpr Vec3 operator * (const float scalar) const {
            return Vec3(this->x * scalar, this->y * scalar, this->z * scalar);
        }

        // utility functions (ideas from game engines)
        [[nodiscard]] constexpr static Vec3 zero() noexcept {
            return Vec3(0.0f, 0.0f, 0.0f);
        }
        [[nodiscard]] constexpr static Vec3 one() noexcept {
            return Vec3(1.0f, 1.0f, 1.0f);
        }
        [[nodiscard]] constexpr static Vec3 up() noexcept {
            return Vec3(0.0f, 1.0f, 0.0f);
        }

        // length func
        [[nodiscard]] float length() const noexcept {
            return std::sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
        }
        // length^2 func
        [[nodiscard]] constexpr float length2() const noexcept {
            return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
        }

        // normalization functions

        // return a new, normalized version of the vector
        [[nodiscard]] Vec3 normalized() const noexcept {
            float lenSq = this->length2();
            if (lenSq < EPSSQ) return Vec3::zero();
            float invLen = 1.0f / std::sqrt(lenSq);
            return Vec3(this->x * invLen, this->y * invLen, this->z * invLen);
        }

        // normalize the instance it was called by
        Vec3& normalize() noexcept {
            float lensq = this->length2();
            if (lensq < EPSSQ) {
                this->x = this->y = this->z = 0.0f;
                return *this;
            }
            float invlen = 1.0f / std::sqrt(lensq);
            this->x *= invlen;
            this->y *= invlen;
            this->z *= invlen;
            return *this;
        }
    };
    // anything that treats both vecs equally are going to be implemented as free functions.
    // Vector and Dot product
    [[nodiscard]] constexpr float dot(const Vec3& first, const Vec3& second) noexcept {
        return (first.x * second.x) + (first.y * second.y) + (first.z * second.z);
    }
    [[nodiscard]] constexpr Vec3 cross(const Vec3& first, const Vec3& second) noexcept {
        return Vec3(
            (first.y * second.z) - (first.z * second.y),  // x component
            (first.z * second.x) - (first.x * second.z),  // y component
            (first.x * second.y) - (first.y * second.x)   // z component
        );
    }
    // refection logic (bouncing off a surface)
    // incident is the incoming ray, normal is the surface direction
    // normal ray must be normalized
    [[nodiscard]] constexpr Vec3 reflect(const Vec3& incident, const Vec3& normal) noexcept {
        return incident - normal * (2.0f * dot(incident, normal));
    }

    // distance between two vectors
    [[nodiscard]] inline float distance(const Vec3& a, const Vec3& b) noexcept {
        return (a - b).length();
    }
    // faster ver for simpler checks. doesn't do sqrt
    // try as (if distsq < range * range)..
    [[nodiscard]] constexpr inline float distanceSquared(const Vec3& a, const Vec3& b) noexcept {
        return (a - b).length2();
    }
    // linear interpolation
    // t = 0.0 returns start
    // t = 1.0 returns end
    // t = 0.5 returns exactly halfway
    [[nodiscard]] constexpr Vec3 lerp(const Vec3& start, const Vec3& end, float t) noexcept {
        return Vec3(
            std::lerp(start.x, end.x, t),
            std::lerp(start.y, end.y, t),
            std::lerp(start.z, end.z, t)
        );
    }
    // handles "2.0 * vec"
    [[nodiscard]] constexpr inline Vec3 operator * (float scalar, const Vec3& v) noexcept {
        return v * scalar; // calls the main overload
    }
}
template <>
struct std::formatter<nvec3::Vec3> : std::formatter<std::string> {
    auto format(const nvec3::Vec3& v, format_context& ctx) const {
        return format_to(ctx.out(), "({:.2f}, {:.2f}, {:.2f})", v.x, v.y, v.z);
    }
};
