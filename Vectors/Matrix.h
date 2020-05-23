//
// Created by menegais1 on 28/04/2020.
//

#ifndef TINYRENDERER_MATRIX_H
#define TINYRENDERER_MATRIX_H

#include <cstdlib>
#include <vector>
#include <iostream>
#include "Vector3.h"
#include "Vector4.h"

template<class t>
struct Vector3;

template<class t>
struct Vector4;

template<class T>
class Matrix {
public:
    std::vector<std::vector<T>> m;
    int rows, cols;

    Matrix<T>(int rows, int cols);

    Matrix<T>();

    std::vector<T> &operator[](int idx);

    Matrix<T> operator*(Matrix<T> Mat);

    Matrix<T> operator*(Vector3<T> v);

    Matrix<T> operator*(Vector4<T> v);

    void setCol(const Vector3<T> v, int col);

    void setCol(const Vector4<T> v, int col);

    void setRow(const Vector3<T> v, int row);

    void setRow(const Vector4<T> v, int row);

    static Matrix<T> identity(int size);

    void printMatrix();

    Matrix<T> invert();
};

template<class T>
Matrix<T>::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    m = std::vector<std::vector<T>>(rows);
    for (int i = 0; i < rows; ++i) {
        m[i] = std::vector<T>(cols);
    }
}

template<class T>
std::vector<T> &Matrix<T>::operator[](int idx) {
    if (idx >= 0 && idx < rows) return m[idx];
    return m[0];
}

template<class T>
Matrix<T> Matrix<T>::operator*(Matrix<T> Mat) {
    if (Mat.rows != this->cols) {
        std::cerr << "INVALID MATRIX MUL" << std::endl;
        return Mat;
    }
    Matrix<T> Result(rows, Mat.cols);

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < Mat.cols; ++x) {
            for (int i = 0; i < cols; ++i) {
                Result[y][x] += m[y][i] * Mat[i][x];
            }
        }
    }
    return Result;
}

template<class T>
void Matrix<T>::printMatrix() {
    std::cout << std::endl;
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            std::cout << " " << m[y][x];
        }
        std::cout << std::endl;
    }
}

template<class T>
Matrix<T>::Matrix() {
    Matrix<T>(4, 4);
}

template<class T>
Matrix<T> Matrix<T>::invert() {
    if (rows != cols) return Matrix<T>();
    // augmenting the square matrix with the identity matrix of the same dimensions a => [ai]
    Matrix result(rows, cols * 2);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result[i][j] = m[i][j];
    for (int i = 0; i < rows; i++)
        result[i][i + cols] = 1;

    for (int i = 0; i < rows; i++) {
        T pivo;
        for (int j = 0; j < cols * 2; ++j) {
            if (result[i][j] != 0) {
                pivo = result[i][j];
                break;
            }
        }

        for (int j = 0; j < cols * 2; ++j) {
            result[i][j] = result[i][j] / pivo;
        }

        for (int k = 0; k < rows; ++k) {
            T mult = result[k][i];
            if (k == i) continue;
            for (int j = 0; j < cols * 2; ++j) {
                result[k][j] = result[k][j] - result[i][j] * mult;
            }
        }
    }
    Matrix truncate(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            truncate[i][j] = result[i][j + cols];
        }
    }

    return truncate;
}

template<class T>
Matrix<T> Matrix<T>::operator*(Vector3<T> v) {
    Matrix<T> V = v.toMatrix();
    return *this * V;
}


template<class T>
Matrix<T> Matrix<T>::operator*(Vector4<T> v) {
    Matrix<T> V = v.toMatrix();
    return *this * V;
}


template<class T>
Matrix<T> Matrix<T>::identity(int size) {
    Matrix<T> M(size, size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            M.m[i][j] = 0;
            if (i == j)
                M.m[i][j] = 1;
        }
    }
    return M;
}

template<class T>
void Matrix<T>::setCol(const Vector3<T> v, int col) {
    if (rows != 3 || col >= this->cols || col < 0) {
        std::cerr << "INVALID MATRIX SET COL" << std::endl;
    }
    this->m[0][col] = v.x;
    this->m[1][col] = v.y;
    this->m[2][col] = v.z;
}

template<class T>
void Matrix<T>::setCol(const Vector4<T> v, int col) {
    if (rows != 4 || col >= this->cols || col < 0) {
        std::cerr << "INVALID MATRIX SET COL" << std::endl;
    }
    this->m[0][col] = v.x;
    this->m[1][col] = v.y;
    this->m[2][col] = v.z;
    this->m[3][col] = v.w;
}

template<class T>
void Matrix<T>::setRow(const Vector3<T> v, int row) {
    if (cols != 3 || row >= this->rows || row < 0) {
        std::cerr << "INVALID MATRIX SET ROW" << std::endl;
    }
    this->m[row] = {v.x, v.y, v.z};
}

template<class T>
void Matrix<T>::setRow(const Vector4<T> v, int row) {
    if (cols != 4 || row >= this->rows || row < 0) {
        std::cerr << "INVALID MATRIX SET ROW" << std::endl;
    }
    this->m[row] = {v.x, v.y, v.z, v.w};
}

#endif //TINYRENDERER_MATRIX_H
