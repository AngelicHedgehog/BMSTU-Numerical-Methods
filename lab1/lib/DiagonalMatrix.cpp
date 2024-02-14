#pragma once

#include <vector>
#include <cassert>

#include "SquareMatrix.cpp"

template< typename T, std::size_t SIZE, std::size_t DIAGS >
requires (
    (DIAGS & 1) == 1 &&
    SIZE > (DIAGS >> 1)
)
class DiagonalMatrix : public SquareMatrix<T, SIZE> {
public:
    DiagonalMatrix() {
        this->m_matrix = std::vector<std::vector<T>>(SIZE, std::vector<T>(DIAGS));
    }

    auto at(std::size_t i, std::size_t j) -> T& override {
        assert(i < SIZE && j < SIZE);

        if (std::max(i, j) - std::min(i, j) > (DIAGS >> 1)) {
            return m_zeroValue;
        }

        return this->m_matrix[std::min(i, j)][j - i + (DIAGS >> 1)];
    }

    auto at(std::size_t i, std::size_t j) const -> const T& override {
        assert(i < SIZE && j < SIZE);

        if (std::max(i, j) - std::min(i, j) > (DIAGS >> 1)) {
            return m_zeroValue;
        }

        return this->m_matrix[std::min(i, j)][j - i + (DIAGS >> 1)];
    }
    
    template< std::size_t WIDTH_OTHER >
    auto operator*(const Matrix<T, SIZE, WIDTH_OTHER>& other) const -> Matrix<T, SIZE, WIDTH_OTHER> {
        Matrix<T, SIZE, WIDTH_OTHER> matrixProduct{};
        for (std::size_t i = 0; i != SIZE; ++i) {
            for (std::size_t j = 0; j != SIZE; ++j) {
                for (std::size_t k = 0; k != WIDTH_OTHER; ++k) {
                    matrixProduct.at(i, k) += this->at(i, j) * other.at(j, k);
                }
            }
        }
        return matrixProduct;
    }

private:
    T m_zeroValue{};
};

template< typename T, std::size_t SIZE >
using ThreeDiagonalMatrix = DiagonalMatrix<T, SIZE, 3>;
