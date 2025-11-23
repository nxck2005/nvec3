struct Vec3 {
    float x;
    float y;
    float z;
    Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vec3& operator += (const Vec3& other) {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
    }

    Vec3 operator + (const Vec3& other) const {
        return Vec3(this->x + other.x, this->y + other.y, this->z + other.z);
    }

    Vec3& operator -= (const Vec3& other) {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        return *this;
    }

    Vec3 operator - (const Vec3& other) const {
        return Vec3(this->x - other.x, this->y - other.y, this->z - other.z);
    }
};
