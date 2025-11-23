#pragma once

#include <cmath>
struct Vec3 {
    float x;
    float y;
    float z;
    Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    // ADD, ADD and concat
    Vec3& operator += (const Vec3& other) {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
    }

    Vec3 operator + (const Vec3& other) const {
        return Vec3(this->x + other.x, this->y + other.y, this->z + other.z);
    }

    // SUB, SUB and concat
    Vec3& operator -= (const Vec3& other) {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        return *this;
    }

    Vec3 operator - (const Vec3& other) const {
        return Vec3(this->x - other.x, this->y - other.y, this->z - other.z);
    }

    // Scalar div and mult
    Vec3& operator /= (const float scalar) {
        // todo; add an assert for 0?
        this->x /= scalar;
        this->y /= scalar;
        this->z /= scalar;
        return *this;
    }

    Vec3 operator / (const float scalar) const {
        return Vec3(this->x / scalar, this->y / scalar, this->z / scalar);
    }

    Vec3& operator *= (const float scalar) {
        this->x *= scalar;
        this->y *= scalar;
        this->z *= scalar;
        return *this;
    }

    Vec3 operator * (const float scalar) const {
        return Vec3(this->x * scalar, this->y * scalar, this->z * scalar);
    }

    // utility functions (ideas from game engines)
    static Vec3 zero() {
        return Vec3(0.0f, 0.0f, 0.0f);
    }
    static Vec3 one() {
        return Vec3(1.0f, 1.0f, 1.0f);
    }
    static Vec3 up() {
        return Vec3(0.0f, 1.0f, 0.0f);
    }

    // length func
    float length() const {
        return std::sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
    }
    // length^2 func
    float length2() const {
        return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
    }

    Vec3 normalized() const {
        float len = this->length();
        // TODO : add epsilon check later
        if (len == 0.0f) return *this;
        return Vec3(this->x / len, this->y / len, this->z / len);
    }

    // static funcs
    // anything that treats both vecs equally are going to be implemented as static.
    // Vector and Dot product
    static float dot(const Vec3& first, const Vec3& second) {
        return (first.x * second.x) + (first.y * second.y) + (first.z * second.z);
    }

    static Vec3 cross(const Vec3& first, const Vec3& second) {
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
    static Vec3 lerp(const Vec3& start, const Vec3& end, float t) {
        return Vec3(
            std::lerp(start.x, end.x, t),
            std::lerp(start.y, end.y, t),
            std::lerp(start.z, end.z, t)
        );
    }
    // refection logic (bouncing off a surface)
    // incident is the incoming ray, normal is the surface direction
    // normal ray must be normalized
    static Vec3 reflect(const Vec3& incident, const Vec3& normal) {
        return incident - normal * (2.0f * dot(incident, normal));
    }

    // distance between two vectors
    static float distance(const Vec3& a, const Vec3& b) {
        return (a - b).length();
    }
    // faster ver for simpler checks. doesn't do sqrt
    // try as (if distsq < range * range)..
    static float distanceSquared(const Vec3& a, const Vec3& b) {
        return (a - b).length2();
    }
};

// handles "2.0 * vec"
inline Vec3 operator * (float scalar, const Vec3& v) {
    return v * scalar; // calls the main overload
}
