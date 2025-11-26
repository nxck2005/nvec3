#include "../src/vec3.hpp"
#include <iostream>
#include <cassert>
#include <cmath> // For std::fabs

using namespace nvec3;

// A simple macro for testing equality of floats with a tolerance
#define ASSERT_FLOAT_EQ(a, b, epsilon) \
    assert(std::fabs((a) - (b)) < (epsilon) && "Float values are not equal enough!")

void test_constructors() {
    std::cout << "Running test_constructors..." << std::endl;
    nvec3::Vec3 v1;
    assert(v1.x == 0.0f && v1.y == 0.0f && v1.z == 0.0f && "Default constructor failed");

    nvec3::Vec3 v2(1.0f, 2.0f, 3.0f);
    assert(v2.x == 1.0f && v2.y == 2.0f && v2.z == 3.0f && "Parameterized constructor failed");
    std::cout << "test_constructors passed." << std::endl;
}

void test_addition() {
    std::cout << "Running test_addition..." << std::endl;
    nvec3::Vec3 v1(1.0f, 2.0f, 3.0f);
    nvec3::Vec3 v2(4.0f, 5.0f, 6.0f);
    nvec3::Vec3 v3 = v1 + v2;
    assert(v3.x == 5.0f && v3.y == 7.0f && v3.z == 9.0f && "operator+ failed");

    v1 += v2;
    assert(v1.x == 5.0f && v1.y == 7.0f && v1.z == 9.0f && "operator+= failed");
    std::cout << "test_addition passed." << std::endl;
}

void test_subtraction() {
    std::cout << "Running test_subtraction..." << std::endl;
    nvec3::Vec3 v1(5.0f, 7.0f, 9.0f);
    nvec3::Vec3 v2(4.0f, 5.0f, 6.0f);
    nvec3::Vec3 v3 = v1 - v2;
    assert(v3.x == 1.0f && v3.y == 2.0f && v3.z == 3.0f && "operator- failed");

    v1 -= v2;
    assert(v1.x == 1.0f && v1.y == 2.0f && v1.z == 3.0f && "operator-= failed");
    std::cout << "test_subtraction passed." << std::endl;
}

void test_scalar_multiplication() {
    std::cout << "Running test_scalar_multiplication..." << std::endl;
    nvec3::Vec3 v(1.0f, 2.0f, 3.0f);
    float scalar = 2.0f;
    nvec3::Vec3 v_mult = v * scalar;
    assert(v_mult.x == 2.0f && v_mult.y == 4.0f && v_mult.z == 6.0f && "operator* (Vec3 * scalar) failed");

    v *= scalar;
    assert(v.x == 2.0f && v.y == 4.0f && v.z == 6.0f && "operator*= failed");

    nvec3::Vec3 v_mult_prefix = scalar * nvec3::Vec3(1.0f, 2.0f, 3.0f);
    assert(v_mult_prefix.x == 2.0f && v_mult_prefix.y == 4.0f && v_mult_prefix.z == 6.0f && "operator* (scalar * Vec3) failed");
    std::cout << "test_scalar_multiplication passed." << std::endl;
}

void test_scalar_division() {
    std::cout << "Running test_scalar_division..." << std::endl;
    nvec3::Vec3 v(2.0f, 4.0f, 6.0f);
    float scalar = 2.0f;
    nvec3::Vec3 v_div = v / scalar;
    assert(v_div.x == 1.0f && v_div.y == 2.0f && v_div.z == 3.0f && "operator/ failed");

    v /= scalar;
    assert(v.x == 1.0f && v.y == 2.0f && v.z == 3.0f && "operator/= failed");
    std::cout << "test_scalar_division passed." << std::endl;
}

void test_utility_functions() {
    std::cout << "Running test_utility_functions..." << std::endl;
    nvec3::Vec3 v1 = nvec3::Vec3::zero();
    assert(v1.x == 0.0f && v1.y == 0.0f && v1.z == 0.0f && "Vec3::zero() failed");

    nvec3::Vec3 v2 = nvec3::Vec3::one();
    assert(v2.x == 1.0f && v2.y == 1.0f && v2.z == 1.0f && "Vec3::one() failed");

    nvec3::Vec3 v3 = nvec3::Vec3::up();
    assert(v3.x == 0.0f && v3.y == 1.0f && v3.z == 0.0f && "Vec3::up() failed");
    std::cout << "test_utility_functions passed." << std::endl;
}

void test_length_and_normalize() {
    std::cout << "Running test_length_and_normalize..." << std::endl;
    nvec3::Vec3 v(3.0f, 4.0f, 0.0f); // length should be 5
    ASSERT_FLOAT_EQ(v.length(), 5.0f, 0.0001f);
    ASSERT_FLOAT_EQ(v.length2(), 25.0f, 0.0001f);

    nvec3::Vec3 normalized_v = v.normalized();
    ASSERT_FLOAT_EQ(normalized_v.x, 0.6f, 0.0001f);
    ASSERT_FLOAT_EQ(normalized_v.y, 0.8f, 0.0001f);
    ASSERT_FLOAT_EQ(normalized_v.z, 0.0f, 0.0001f);
    ASSERT_FLOAT_EQ(normalized_v.length(), 1.0f, 0.0001f);

    nvec3::Vec3 zero_vec = nvec3::Vec3::zero();
    nvec3::Vec3 normalized_zero = zero_vec.normalized();
    assert(normalized_zero.x == 0.0f && normalized_zero.y == 0.0f && normalized_zero.z == 0.0f && "Normalized zero vector failed");

    nvec3::Vec3 normalized_static = v.normalize();
    ASSERT_FLOAT_EQ(normalized_static.x, 0.6f, 0.0001f);
    ASSERT_FLOAT_EQ(normalized_static.y, 0.8f, 0.0001f);
    ASSERT_FLOAT_EQ(normalized_static.z, 0.0f, 0.0001f);
    std::cout << "test_length_and_normalize passed." << std::endl;
}

void test_dot_cross() {
    std::cout << "Running test_dot_cross..." << std::endl;
    nvec3::Vec3 v1(1.0f, 0.0f, 0.0f); // x-axis
    nvec3::Vec3 v2(0.0f, 1.0f, 0.0f); // y-axis

    // Dot product
    ASSERT_FLOAT_EQ(nvec3::dot(v1, v2), 0.0f, 0.0001f);
    nvec3::Vec3 v3(2.0f, 3.0f, 4.0f);
    nvec3::Vec3 v4(5.0f, 6.0f, 7.0f);
    ASSERT_FLOAT_EQ(nvec3::dot(v3, v4), (2.0f * 5.0f + 3.0f * 6.0f + 4.0f * 7.0f), 0.0001f); // 10 + 18 + 28 = 56

    // Cross product
    nvec3::Vec3 cross_prod = nvec3::cross(v1, v2); // should be (0,0,1) for x cross y
    ASSERT_FLOAT_EQ(cross_prod.x, 0.0f, 0.0001f);
    ASSERT_FLOAT_EQ(cross_prod.y, 0.0f, 0.0001f);
    ASSERT_FLOAT_EQ(cross_prod.z, 1.0f, 0.0001f);

    cross_prod = nvec3::cross(v2, v1); // should be (0,0,-1) for y cross x
    ASSERT_FLOAT_EQ(cross_prod.x, 0.0f, 0.0001f);
    ASSERT_FLOAT_EQ(cross_prod.y, 0.0f, 0.0001f);
    ASSERT_FLOAT_EQ(cross_prod.z, -1.0f, 0.0001f);
    std::cout << "test_dot_cross passed." << std::endl;
}

void test_lerp() {
    std::cout << "Running test_lerp..." << std::endl;
    nvec3::Vec3 start(0.0f, 0.0f, 0.0f);
    nvec3::Vec3 end(10.0f, 10.0f, 10.0f);

    nvec3::Vec3 result0 = nvec3::lerp(start, end, 0.0f);
    assert(result0.x == 0.0f && result0.y == 0.0f && result0.z == 0.0f && "lerp t=0 failed");

    nvec3::Vec3 result1 = nvec3::lerp(start, end, 1.0f);
    assert(result1.x == 10.0f && result1.y == 10.0f && result1.z == 10.0f && "lerp t=1 failed");

    nvec3::Vec3 result0_5 = nvec3::lerp(start, end, 0.5f);
    assert(result0_5.x == 5.0f && result0_5.y == 5.0f && result0_5.z == 5.0f && "lerp t=0.5 failed");

    nvec3::Vec3 result0_25 = nvec3::lerp(start, end, 0.25f);
    assert(result0_25.x == 2.5f && result0_25.y == 2.5f && result0_25.z == 2.5f && "lerp t=0.25 failed");
    std::cout << "test_lerp passed." << std::endl;
}

void test_reflect() {
    std::cout << "Running test_reflect..." << std::endl;
    // Incident vector
    nvec3::Vec3 incident(1.0f, -1.0f, 0.0f); // Incoming ray hitting a surface from top-right
    // Surface normal (normalized)
    nvec3::Vec3 normal(0.0f, 1.0f, 0.0f); // Surface normal pointing upwards

    nvec3::Vec3 reflected = nvec3::reflect(incident, normal);
    // Expected reflected vector: (1.0, 1.0, 0.0)
    ASSERT_FLOAT_EQ(reflected.x, 1.0f, 0.0001f);
    ASSERT_FLOAT_EQ(reflected.y, 1.0f, 0.0001f);
    ASSERT_FLOAT_EQ(reflected.z, 0.0f, 0.0001f);

    // Test with another incident angle
    incident = nvec3::Vec3(-1.0f, -1.0f, 0.0f);
    reflected = nvec3::reflect(incident, normal);
    // Expected: (-1.0, 1.0, 0.0)
    ASSERT_FLOAT_EQ(reflected.x, -1.0f, 0.0001f);
    ASSERT_FLOAT_EQ(reflected.y, 1.0f, 0.0001f);
    ASSERT_FLOAT_EQ(reflected.z, 0.0f, 0.0001f);

    // Incident straight into the normal
    incident = nvec3::Vec3(0.0f, -1.0f, 0.0f);
    reflected = nvec3::reflect(incident, normal);
    // Expected: (0.0, 1.0, 0.0)
    ASSERT_FLOAT_EQ(reflected.x, 0.0f, 0.0001f);
    ASSERT_FLOAT_EQ(reflected.y, 1.0f, 0.0001f);
    ASSERT_FLOAT_EQ(reflected.z, 0.0f, 0.0001f);

    std::cout << "test_reflect passed." << std::endl;
}

void test_distance() {
    std::cout << "Running test_distance..." << std::endl;
    nvec3::Vec3 v1(0.0f, 0.0f, 0.0f);
    nvec3::Vec3 v2(3.0f, 4.0f, 0.0f); // Distance should be 5

    ASSERT_FLOAT_EQ(nvec3::distance(v1, v2), 5.0f, 0.0001f);
    ASSERT_FLOAT_EQ(nvec3::distanceSquared(v1, v2), 25.0f, 0.0001f);

    nvec3::Vec3 v3(1.0f, 1.0f, 1.0f);
    nvec3::Vec3 v4(1.0f, 1.0f, 1.0f);
    ASSERT_FLOAT_EQ(nvec3::distance(v3, v4), 0.0f, 0.0001f);
    ASSERT_FLOAT_EQ(nvec3::distanceSquared(v3, v4), 0.0f, 0.0001f);
    std::cout << "test_distance passed." << std::endl;
}


int main() {
    std::cout << "Starting all Vec3 tests..." << std::endl;
    test_constructors();
    test_addition();
    test_subtraction();
    test_scalar_multiplication();
    test_scalar_division();
    test_utility_functions();
    test_length_and_normalize();
    test_dot_cross();
    test_lerp();
    test_reflect();
    test_distance();
    std::cout << "All Vec3 tests passed!" << std::endl;
    return 0;
}
