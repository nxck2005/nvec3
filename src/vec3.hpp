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
        constexpr static Vec3 zero() {
            return Vec3(0.0f, 0.0f, 0.0f);
        }
        constexpr static Vec3 one() {
            return Vec3(1.0f, 1.0f, 1.0f);
        }
        constexpr static Vec3 up() {
            return Vec3(0.0f, 1.0f, 0.0f);
        }

        // length func
        float length() const {
            return std::sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
        }
        // length^2 func
        constexpr float length2() const {
            return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
        }

        Vec3 normalized() const {
            float len = this->length();
            // TODO : add epsilon check later
            if (len < 1e-6f) return Vec3::zero();
            return Vec3(this->x / len, this->y / len, this->z / len);
        }

        // static funcs
        // anything that treats both vecs equally are going to be implemented as static.
        // Vector and Dot product
        constexpr static float dot(const Vec3& first, const Vec3& second) {
            return (first.x * second.x) + (first.y * second.y) + (first.z * second.z);
        }

        constexpr static Vec3 cross(const Vec3& first, const Vec3& second) {
            return Vec3(
                (first.y * second.z) - (first.z * second.y),  // x component
                (first.z * second.x) - (first.x * second.z),  // y component
                (first.x * second.y) - (first.y * second.x)   // z component
            );
        }

        static Vec3 normalize(const Vec3& vec) {
            return vec.normalized();
        }

        // linear interpolation
        // t = 0.0 returns start
        // t = 1.0 returns end
        // t = 0.5 returns exactly halfway
        constexpr static Vec3 lerp(const Vec3& start, const Vec3& end, float t) {
            return Vec3(
                std::lerp(start.x, end.x, t),
                std::lerp(start.y, end.y, t),
                std::lerp(start.z, end.z, t)
            );
        }
        // refection logic (bouncing off a surface)
        // incident is the incoming ray, normal is the surface direction
        // normal ray must be normalized
        constexpr static Vec3 reflect(const Vec3& incident, const Vec3& normal) {
            return incident - normal * (2.0f * dot(incident, normal));
        }

        // distance between two vectors
        static float distance(const Vec3& a, const Vec3& b) {
            return (a - b).length();
        }
        // faster ver for simpler checks. doesn't do sqrt
        // try as (if distsq < range * range)..
        constexpr static float distanceSquared(const Vec3& a, const Vec3& b) {
            return (a - b).length2();
        }
    };
    // handles "2.0 * vec"
    constexpr inline Vec3 operator * (float scalar, const Vec3& v) {
        return v * scalar; // calls the main overload
    }
}
template <>
struct std::formatter<nvec3::Vec3> : std::formatter<std::string> {
    auto format(const nvec3::Vec3& v, format_context& ctx) const {
        return format_to(ctx.out(), "({:.2f}, {:.2f}, {:.2f})", v.x, v.y, v.z);
    }
};
