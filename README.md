# nvec3

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
![Language](https://img.shields.io/badge/language-C%2B%2B20-blue.svg)

A simple, header-only C++20 library for 3D vector mathematics.

## Features

- Intuitive vector arithmetic (`+`, `-`, `*`, `/`).
- Functions for dot product, cross product, magnitude, and normalization.
- Includes other useful vector functions like `lerp`, `reflect`, and `distance`.

## Usage

To use `nvec3` in your project, simply include the `src/vec3.hpp` header file.

```cpp
#include <iostream>
#include "vec3.hpp"

int main() {
    Vec3 v1(1.0f, 2.0f, 3.0f);
    Vec3 v2(4.0f, 5.0f, 6.0f);

    // Add two vectors
    Vec3 sum = v1 + v2;
    std::cout << "Sum: (" << sum.x << ", " << sum.y << ", " << sum.z << ")" << std::endl;

    // Calculate dot product
    float dot_product = Vec3::dot(v1, v2);
    std::cout << "Dot Product: " << dot_product << std::endl;

    // Calculate magnitude
    std::cout << "Magnitude of v1: " << v1.length() << std::endl;

    return 0;
}
```

## Build

To build the demo programs located in the `demo/` directory.

1.  **Build the sphere demo:**
    ```sh
    mkdir build
    make sphere
    ```
    The executable will be placed in the `build/` directory.

2.  **Clean the build directory:**
    ```sh
    make clean
    ```


https://github.com/user-attachments/assets/b7fc8333-d947-48fb-8745-2374c08810cf


## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
