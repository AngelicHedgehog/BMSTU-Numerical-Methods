#pragma once

#include "Matrix.cpp"

template< typename T, std::size_t SIZE >
class Vector : public Matrix<T, SIZE, 1> {
public:
    constexpr Vector() {}

    constexpr Vector(const Matrix<T, SIZE, 1>& matrix)
    : Matrix<T, SIZE, 1>(matrix) {}

    constexpr Vector(const std::array<T, SIZE>& array) {
        for (std::size_t i = 0; i != SIZE; ++i) {
            this->at(i) = array[i];
        }
    }

    constexpr auto at(std::size_t i) -> T& {
        assert(i < SIZE);
        return Matrix<T, SIZE, 1>::at(i, 0);
    }

    constexpr auto at(std::size_t i) const -> const T& {
        assert(i < SIZE);
        return Matrix<T, SIZE, 1>::at(i, 0);
    }

    constexpr auto operator*(T coef) const -> Vector<T, SIZE> {
        Vector<T, SIZE> resVector{};
        for (std::size_t row = 0; row != SIZE; ++row) {
            resVector.at(row) = this->at(row) * coef;
        }
        return resVector;
    }

    template< std::size_t WIDTH_OTHER >
    constexpr auto operator*(const Matrix<T, 1, WIDTH_OTHER>& rightMatrix) const
    -> Matrix<T, SIZE, WIDTH_OTHER> {
        Matrix<T, SIZE, WIDTH_OTHER> matrixProduct{};
        for (std::size_t i = 0; i != SIZE; ++i) {
            for (std::size_t j = 0; j != WIDTH_OTHER; ++j) {
                matrixProduct.at(i, j) = this->at(i) * rightMatrix.at(1, j);
            }
        }
        return matrixProduct;
    }
};
