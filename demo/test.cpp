#include <print>
#include "../src/vec3.hpp"
using namespace std;

int main(void) {
    Vec3 v1(0.1, 0.2, 0.3);
    Vec3 v2(1, 2, 3);
    Vec3 v3 = v1 + v2;
    v1 += v3 -= v2;
    v1 = Vec3::cross(v2, v3);
    std::println("V1: {}", v1);
    return 0;
}
