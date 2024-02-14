#pragma once

#include "Matrix.cpp"

template< typename T, std::size_t SIZE >
class Vector : public Matrix<T, SIZE, 1> {
public:
    auto at(std::size_t i) -> T& {
        assert(i < SIZE);
        return Matrix<T, SIZE, 1>::at(i, 0);
    }

    auto at(std::size_t i) const -> const T& {
        assert(i < SIZE);
        return Matrix<T, SIZE, 1>::at(i, 0);
    }

    template< std::size_t WIDTH_OTHER >
    auto operator*(const Matrix<T, 1, WIDTH_OTHER>& other) const -> Matrix<T, SIZE, WIDTH_OTHER> {
        Matrix<T, SIZE, WIDTH_OTHER> matrixProduct{};
        for (std::size_t i = 0; i != SIZE; ++i) {
            for (std::size_t j = 0; j != WIDTH_OTHER; ++j) {
                matrixProduct.at(i, j) = this->at(i) * other.at(1, j);
            }
        }
        return matrixProduct;
    }
};
