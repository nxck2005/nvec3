#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

#include "../src/vec3.hpp"

int main() {
    int width = 80;
    int height = 40;
    float aspect = (float)width / height * 0.5f;

    Vec3 spherePos(0.0f, 0.0f, 0.0f);
    float sphereRad = 1.0f;

    std::string gradient = " .'`,:;i><~+-?1/rxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
    int gradLen = gradient.length();

    float time = 0.0f;

    std::cout << "\x1b[?25l";

    while (true) {
        Vec3 lightDir = Vec3(std::sin(time), 1.0f, std::cos(time)).normalized();

        std::string buffer;
        buffer.reserve(width * height + height);

        std::cout << "\x1b[H";

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {

                float u = (float)x / width * 2.0f - 1.0f;
                float v = (float)y / height * 2.0f - 1.0f;

                Vec3 rayOrigin(0.0f, 0.0f, -2.0f);
                Vec3 rayDir = Vec3(u * aspect, v, 1.0f).normalized();

                Vec3 toSphere = spherePos - rayOrigin;
                float t = Vec3::dot(toSphere, rayDir);

                Vec3 closest = rayOrigin + (rayDir * t);
                float dist = (spherePos - closest).length();

                if (dist < sphereRad) {
                    float offset = std::sqrt(sphereRad * sphereRad - dist * dist);
                    Vec3 hitPoint = closest - (rayDir * offset);

                    Vec3 normal = (hitPoint - spherePos).normalized();

                    float intensity = Vec3::dot(normal, lightDir);
                    if (intensity < 0.0f) intensity = 0.0f;

                    int idx = (int)(intensity * (gradLen - 1));
                    buffer += gradient[idx];
                } else {
                    buffer += ' ';
                }
            }
            buffer += '\n';
        }

        std::cout << buffer;

        time += 0.01f;
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }

    return 0;
}
