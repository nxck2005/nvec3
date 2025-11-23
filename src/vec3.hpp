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
        return std::sqrt((this->x * this->x) + (this->y * this->y) + (this->z + this->z));
    }
    // length^2 func
    float length2() const {
        return (this->x * this->x) + (this->y * this->y) + (this->z + this->z);
    }
    // add linear interp later

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
};
