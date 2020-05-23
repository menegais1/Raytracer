//
// Created by menegais1 on 26/04/2020.
//

#ifndef TINYRENDERER_VECTOR4_H
#define TINYRENDERER_VECTOR4_H

#include <cmath>
#include <stdexcept>
#include <iostream>
#include "Matrix.h"

template<class t>
struct Vector4 {
public:
    t x, y, z, w;

    Vector4(t x, t y, t z, t w);

    Vector4();

    Vector4<t> operator+(Vector4<t> v2) const;

    Vector4<t> operator-(const Vector4<t> v2) const;

    Vector4<t> operator-() const;

    Vector4<t> operator*(t v) const;

    Vector4<t> operator/(t v) const;

    Vector4<t> operator+=(const Vector4<t> v1);

    Vector4<t> operator-=(const Vector4<t> v1);

    Vector4<t> operator/=(const t v);

    Vector4<t> operator*=(const t v);

    t &operator[](int idx);

    bool operator==(const Vector4 &rhs) const;

    bool operator!=(const Vector4 &rhs) const;

    void print();

    t length();

    Vector4<t> unit();

    Matrix<t> toMatrix() const;

};

template<class t>
Vector4<t>::Vector4(t x, t y, t z, t w) : x(x), y(y), z(z), w(w) {

}

template<class t>
Vector4<t>::Vector4() : x(0), y(0), z(0), w(0) {

}

template<class t>
Vector4<t> Vector4<t>::operator+(const Vector4<t> v2) const {
    return Vector4<t>(x + v2.x, y + v2.y, z + v2.z, w + v2.w);
}

template<class t>
Vector4<t> Vector4<t>::operator-(const Vector4<t> v2) const {
    return Vector4<t>(x - v2.x, y - v2.y, z - v2.z, w - v2.w);
}

template<class t>
Vector4<t> Vector4<t>::operator*(const t v) const {
    return Vector4<t>(x * v, y * v, z * v, w * v);
}

template<class t>
Vector4<t> Vector4<t>::operator/(const t v) const {
    return Vector4<t>(x / v, y / v, z / v, w / v);
}

template<class t>
Vector4<t> Vector4<t>::operator+=(Vector4<t> v1) {
    x += v1.x;
    y += v1.y;
    z += v1.z;
    w += v1.w;
}

template<class t>
Vector4<t> Vector4<t>::operator-=(Vector4<t> v1) {
    x -= v1.x;
    y -= v1.y;
    z -= v1.z;
    w -= v1.w;
}

template<class t>
Vector4<t> Vector4<t>::operator/=(t v) {
    x /= v;
    y /= v;
    z /= v;
    w /= v;
}

template<class t>
Vector4<t> Vector4<t>::operator*=(t v) {
    x *= v;
    y *= v;
    z *= v;
    w *= v;
}


template<class t>
t Vector4<t>::length() {
    return std::sqrt(x * x + y * y + z * z + w * w);
}

template<class t>
Vector4<t> Vector4<t>::unit() {
    t l = length();
    return Vector4<t>(x / l, y / l, z / l, w / l);
}

template<class t>
t &Vector4<t>::operator[](int idx) {
    if (idx == 0) return x;
    if (idx == 1) return y;
    if (idx == 2) return z;
    if (idx == 3) return w;
    else
        throw std::out_of_range("Index out of bounds");
}

template<class t>
Vector4<t> Vector4<t>::operator-() const {
    return Vector4<t>(-x, -y, -z, -w);
}

template<class t>
void Vector4<t>::print() {
    std::cout << "x: " << x << " y: " << y << " z: " << z << " w: " << w << std::endl;
}

template<class t>
bool Vector4<t>::operator==(const Vector4 &rhs) const {
    return x == rhs.x &&
           y == rhs.y &&
           z == rhs.z &&
           w == rhs.w;
}

template<class t>
bool Vector4<t>::operator!=(const Vector4 &rhs) const {
    return !(rhs == *this);
}

template<class t>
Matrix<t> Vector4<t>::toMatrix() const {
    Matrix<t> M(4, 1);
    M.setCol(*this, 0);
    return M;
}


typedef Vector4<int> ivec4;
typedef Vector4<double> dvec4;
typedef Vector4<float> fvec4;

#endif //TINYRENDERER_VECTOR4_H
