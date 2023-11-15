#pragma once

#include <cmath>
#include <ostream>
#include <istream>
#include <stdexcept>

// Forward declaration for Vector2 <-> Vector3 <-> Vector4 implicit conversion
template <typename T>
class Vector2;

template <typename T>
class Vector3;

template <typename T>
class Vector4;

// A 2-dimensional vector.
template <typename T>
class Vector2 {
public:
    T x, y;

    // Constructors
    explicit Vector2(T x = T(), T y = T()) : x(x), y(y) {}
    Vector2(const Vector2<T>& other) : x(other.x), y(other.y) {}
    template <typename U>
    Vector2(const Vector2<U>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}
    Vector2(const Vector3<T>& other) : x(other.x), y(other.y) {}
    template <typename U>
    Vector2(const Vector3<U>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}
    Vector2(const Vector4<T>& other) : x(other.x), y(other.y) {}
    template <typename U>
    Vector2(const Vector4<U>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}

    // Vector addition and assignment
    Vector2& operator+=(const Vector2& other) const {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    // Vector addition
    Vector2 operator+(const Vector2& other) const {
        return Vector2(*this) += other;
    }

    // Scalar addition and assignment
    template <typename U>
    Vector2& operator+=(const U& scalar) const {
        this->x = scalar;
        this->y = scalar;
        return *this;
    }

    // Scalar addition
    template <typename U>
    Vector2 operator+(const U& scalar) const {
        return Vector2(*this) += scalar;
    }

    // Vector subtraction and assignment
    Vector2& operator-=(const Vector2& other) {
        this->x -= other.x;
        this->y -= other.y;
        return *this;
    }

    // Vector subtraction
    Vector2 operator-(const Vector2& other) const {
        return Vector2(*this) -= other;
    }

    // Scalar subtraction and assignment
    template <typename U>
    Vector2& operator-=(const U& scalar) {
        this->x -= scalar;
        this->y -= scalar;
        return *this;
    }

    // Scalar subtraction
    template <typename U>
    Vector2 operator-(const U& scalar) const {
        return Vector2(*this) -= scalar;
    }

    // Scalar multiplication and assignment
    template <typename U>
    Vector2& operator*=(const U& scalar) {
        this->x *= scalar;
        this->y *= scalar;
        return *this;
    }

    // Scalar multiplication
    template <typename U>
    Vector2 operator*(const U& scalar) const {
        return Vector2(*this) *= scalar;
    }

    // Scalar division and assignment
    template <typename U>
    Vector2& operator/=(const U& scalar) {
        if (scalar == 0) throw std::runtime_error("Division by zero.");
        this->x /= scalar;
        this->y /= scalar;
        return *this;
    }

    // Scalar division
    template <typename U>
    Vector2 operator/(const U& scalar) const {
        return Vector2(*this) /= scalar;
    }

    // Dot product
    T dot(const Vector2& other) const {
        return x * other.x + y * other.y;
    }

    // STRING //

    friend std::ostream& operator<<(std::ostream& os, const Vector2& obj) {
        os << "Vector2(" << obj.x << ", " << obj.y << ")";
        return os;
    }
};

// An 3-dimensional vector.
template <typename T>
class Vector3 {
public:
    T x, y, z;

    // Constructors
    explicit Vector3(T x = T(), T y = T(), T z = T()) : x(x), y(y), z(z) {}
    Vector3(const Vector3<T>& other) : x(other.x), y(other.y), z(other.z) {}
    template <typename U>
    Vector3(const Vector3<U>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(static_cast<T>(other.z)) {}
    Vector3(const Vector2<T>& other, T z = T()) : x(other.x), y(other.y), z(z) {}
    template <typename U>
    Vector3(const Vector2<U>& other, T z = T()) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(z) {}
    Vector3(const Vector4<T>& other) : x(other.x), y(other.y), z(other.z) {}
    template <typename U>
    Vector3(const Vector4<U>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(static_cast<T>(other.z)) {}

    // Vector addition and assignment
    Vector3& operator+=(const Vector3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    // Vector addition
    Vector3 operator+(const Vector3& other) const {
        return Vector3(*this) += other;
    }

    // Scalar addition and assignment
    template <typename U>
    Vector3& operator+=(const U& scalar) {
        x += scalar;
        y += scalar;
        z += scalar;
        return *this;
    }

    // Scalar addition
    template <typename U>
    Vector3 operator+(const U& scalar) const {
        return Vector3(*this) += scalar;
    }

    // Vector subtraction and assignment
    Vector3& operator-=(const Vector3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    // Vector subtraction
    Vector3 operator-(const Vector3& other) const {
        return Vector3(*this) -= other;
    }

    // Scalar subtraction and assignment
    template <typename U>
    Vector3& operator-=(const U& scalar) {
        x -= scalar;
        y -= scalar;
        z -= scalar;
        return *this;
    }

    // Scalar subtraction
    template <typename U>
    Vector3 operator-(const U& scalar) const {
        return Vector3(*this) -= scalar;
    }

    // Scalar multiplication and assignment
    template <typename U>
    Vector3& operator*=(const U& scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    // Scalar multiplication
    template <typename U>
    Vector3 operator*(const U& scalar) const {
        return Vector3(*this) *= scalar;
    }

    // Scalar division and assignment
    template <typename U>
    Vector3& operator/=(const U& scalar) {
        if (scalar == 0) throw std::runtime_error("Division by zero.");
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    // Scalar division
    template <typename U>
    Vector3 operator/(const U& scalar) const {
        return Vector3(*this) /= scalar;
    }

    // Dot product
    float dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Cross product
    Vector3 cross(const Vector3& other) const {
        return Vector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    // STRING //
    friend std::ostream& operator<<(std::ostream& os, const Vector3& obj) {
        os << "Vector3(" << obj.x << ", " << obj.y << ", " << obj.z << ")";
        return os;
    }
};

// An 4-dimensional vector.
template <typename T>
class Vector4 {
public:
    T x, y, z, w;

    // Constructors
    explicit Vector4(T x = T(), T y = T(), T z = T(), T w = T()) : x(x), y(y), z(z), w(w) {}
    Vector4(const Vector4<T>& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}
    template <typename U>
    Vector4(const Vector4<U>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(static_cast<T>(other.z)), w(static_cast<T>(other.w)) {}
    Vector4(const Vector3<T>& other, T w = T()) : x(other.x), y(other.y), z(other.z), w(w) {}
    template <typename U>
    Vector4(const Vector3<U>& other, T w = T()) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(static_cast<T>(other.z)), w(w) {}
    Vector4(const Vector2<T>& other, T z = T(), T w = T()) : x(other.x), y(other.y), z(z), w(w) {}
    template <typename U>
    Vector4(const Vector2<U>& other, T z = T(), T w = T()) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(z), w(w) {}

    // Vector addition and assignment
    Vector4& operator+=(const Vector4& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    // Vector addition
    Vector4 operator+(const Vector4& other) const {
        return Vector4(*this) += other;
    }

    // Scalar addition and assignment
    template <typename U>
    Vector4& operator+=(const U& scalar) {
        x += scalar;
        y += scalar;
        z += scalar;
        w += scalar;
        return *this;
    }

    // Scalar addition
    template <typename U>
    Vector4 operator+(const U& scalar) const {
        return Vector4(*this) += scalar;
    }

    // Vector subtraction and assignment
    Vector4& operator-=(const Vector4& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

    // Vector subtraction
    Vector4 operator-(const Vector4& other) const {
        return Vector4(*this) -= other;
    }

    // Scalar subtraction and assignment
    template <typename U>
    Vector4& operator-=(const U& scalar) {
        x -= scalar;
        y -= scalar;
        z -= scalar;
        w -= scalar;
        return *this;
    }

    // Scalar subtraction
    template <typename U>
    Vector4 operator-(const U& scalar) const {
        return Vector4(*this) -= scalar;
    }

    // Scalar multiplication and assignment
    template <typename U>
    Vector4& operator*=(const U& scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;
    }

    // Scalar multiplication
    template <typename U>
    Vector4 operator*(const U& scalar) const {
        return Vector4(*this) *= scalar;
    }

    // Scalar division and assignment
    template <typename U>
    Vector4& operator/=(const U& scalar) {
        if (scalar == 0) throw std::runtime_error("Division by zero.");
        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;
        return *this;
    }

    // Scalar division
    template <typename U>
    Vector4 operator/(const U& scalar) const {
        return Vector4(*this) /= scalar;
    }

    // Dot product
    float dot(const Vector4& other) const {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    // STRING //
    friend std::ostream& operator<<(std::ostream& os, const Vector4& obj) {
        os << "Vector4(" << obj.x << ", " << obj.y << ", " << obj.z << ", " << obj.w << ")";
        return os;
    }
};

// scalar @ vec operations

template <typename T, typename U>
Vector2<T> operator*(const U& scalar, const Vector2<T>& vec) {
    return Vector2<T>(scalar * vec.x, scalar * vec.y);
}

template <typename T, typename U>
Vector3<T> operator*(const U& scalar, const Vector3<T>& vec) {
    return Vector3<T>(scalar * vec.x, scalar * vec.y, scalar * vec.z);
}

template <typename T, typename U>
Vector4<T> operator*(const U& scalar, const Vector4<T>& vec) {
    return Vector4<T>(scalar * vec.x, scalar * vec.y, scalar * vec.z, scalar * vec.w);
}

template <typename T, typename U>
Vector2<T> operator/(const U& scalar, const Vector2<T>& vec) {
    if (vec.x == 0 || vec.y == 0) {
        throw std::runtime_error("Division by zero component in vector.");
    }
    return Vector2<T>(scalar / vec.x, scalar / vec.y);
}

template <typename T, typename U>
Vector3<T> operator/(const U& scalar, const Vector3<T>& vec) {
    if (vec.x == 0 || vec.y == 0 || vec.z == 0) {
        throw std::runtime_error("Division by zero component in vector.");
    }
    return Vector3<T>(scalar / vec.x, scalar / vec.y, scalar / vec.z);
}

template <typename T, typename U>
Vector4<T> operator/(const U& scalar, const Vector4<T>& vec) {
    if (vec.x == 0 || vec.y == 0 || vec.z == 0 || vec.w == 0) {
        throw std::runtime_error("Division by zero component in vector.");
    }
    return Vector4<T>(scalar / vec.x, scalar / vec.y, scalar / vec.z, scalar / vec.w);
}
