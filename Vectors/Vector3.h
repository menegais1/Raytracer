//
// Created by menegais1 on 26/04/2020.
//

#ifndef TINYRENDERER_VECTOR3_H
#define TINYRENDERER_VECTOR3_H

#include "Vector4.h"
#include "Matrix.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

template<class t>
class Matrix;

template<class t>
struct Vector3 {
public:
    t x, y, z;

    Vector3(t x, t y, t z);

    Vector3();

    Vector3<t> operator+(Vector3<t> v2) const;

    Vector3<t> operator-(const Vector3<t> v2) const;

    Vector3<t> operator-() const;

    Vector3<t> operator*(t v) const;

    Vector3<t> operator/(t v) const;

    Vector3<t> operator+=(const Vector3<t> v1);

    Vector3<t> operator-=(const Vector3<t> v1);

    Vector3<t> operator/=(const t v);

    Vector3<t> operator*=(const t v);

    t &operator[](int idx);

    bool operator==(const Vector3 &rhs) const;

    bool operator!=(const Vector3 &rhs) const;

    Vector4<t> toVector4(t w) const;

    Matrix<t> toMatrix() const;

    void print();

    t length();

    Vector3<t> unit();

    t dot(Vector3<t> v2);

    t angle(Vector3<t> v2);

    Vector3<t> cross(const Vector3<t> v2) const;

};

template<class t>
Vector3<t>::Vector3(t x, t y, t z) : x(x), y(y), z(z) {

}

template<class t>
Vector3<t>::Vector3() : x(0), y(0), z(0) {

}

template<class t>
Vector3<t> Vector3<t>::operator+(const Vector3<t> v2) const {
    return Vector3<t>(x + v2.x, y + v2.y, z + v2.z);
}

template<class t>
Vector3<t> Vector3<t>::operator-(const Vector3<t> v2) const {
    return Vector3<t>(x - v2.x, y - v2.y, z - v2.z);
}

template<class t>
Vector3<t> Vector3<t>::operator*(const t v) const {
    return Vector3<t>(x * v, y * v, z * v);
}

template<class t>
Vector3<t> Vector3<t>::operator/(const t v) const {
    return Vector3<t>(x / v, y / v, z / v);
}

template<class t>
Vector3<t> Vector3<t>::operator+=(Vector3<t> v1) {
    x += v1.x;
    y += v1.y;
    z += v1.z;
}

template<class t>
Vector3<t> Vector3<t>::operator-=(Vector3<t> v1) {
    x -= v1.x;
    y -= v1.y;
    z -= v1.z;
}

template<class t>
Vector3<t> Vector3<t>::operator/=(t v) {
    x /= v;
    y /= v;
    z /= v;
}

template<class t>
Vector3<t> Vector3<t>::operator*=(t v) {
    x *= v;
    y *= v;
    z *= v;
}


template<class t>
t Vector3<t>::length() {
    return std::sqrt(x * x + y * y + z * z);
}

template<class t>
Vector3<t> Vector3<t>::unit() {
    t l = length();
    return Vector3<t>(x / l, y / l, z / l);
}

template<class t>
t Vector3<t>::dot(Vector3<t> v2) {
    return x * v2.x + y * v2.y + z * v2.z;
}

template<class t>
Vector3<t> Vector3<t>::cross(const Vector3<t> v2) const {
    return Vector3<t>(y * v2.z - z * v2.y, z * v2.x - x * v2.z, x * v2.y - y * v2.x);
}

template<class t>
t Vector3<t>::angle(Vector3<t> v2) {
    float cosA = dot(v2) / (length() * v2.length());
    if (cosA > 1 || cosA < -1) cosA = (int) cosA;
    return acos(cosA);
}

template<class t>
t &Vector3<t>::operator[](int idx) {
    if (idx == 0) return x;
    if (idx == 1) return y;
    if (idx == 2) return z;
    else
        throw std::out_of_range("Index out of bounds");
}

template<class t>
Vector3<t> Vector3<t>::operator-() const {
    return Vector3<t>(-x, -y, -z);
}

template<class t>
void Vector3<t>::print() {
    std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;
}

template<class t>
bool Vector3<t>::operator==(const Vector3 &rhs) const {
    return x == rhs.x &&
           y == rhs.y &&
           z == rhs.z;
}

template<class t>
bool Vector3<t>::operator!=(const Vector3 &rhs) const {
    return !(rhs == *this);
}

template<class t>
Vector4<t> Vector3<t>::toVector4(t w) const {
    return Vector4<t>(x, y, z, w);
}

template<class t>
Matrix<t> Vector3<t>::toMatrix() const {
    Matrix<t> M(3, 1);
    M.setCol(*this, 0);
    return M;
}

typedef Vector3<int> ivec3;
typedef Vector3<double> dvec3;
typedef Vector3<float> fvec3;

#endif //TINYRENDERER_VECTOR3_H
