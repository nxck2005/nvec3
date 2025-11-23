#include <print>
#include "../src/vec3.hpp"
using namespace std;

int main(void) {
    Vec3 v1(0.1, 0.2, 0.3);
    Vec3 v2(1, 2, 3);
    Vec3 v3 = v1 + v2;
    v1 += v3 -= v2;
    v1 = Vec3::zero();
    std::println("V1: {} {} {}", v1.x, v1.y, v1.z);
    return 0;
}
