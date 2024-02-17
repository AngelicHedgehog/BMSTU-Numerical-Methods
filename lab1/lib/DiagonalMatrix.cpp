#pragma once

#include "SquareMatrix.cpp"

template< typename T, std::size_t SIZE, std::size_t DIAGS >
requires (
    (DIAGS & 1) == 1 &&
    SIZE > (DIAGS >> 1)
)
class DiagonalMatrix : public SquareMatrix<T, SIZE> {
public:
    constexpr DiagonalMatrix() {}

    constexpr DiagonalMatrix(const Matrix<T, SIZE, SIZE>& matrix)
    : DiagonalMatrix<T, SIZE, DIAGS>(matrix.m_matrix) {}

    constexpr DiagonalMatrix(const std::array<std::array<T, SIZE>, SIZE>& arrays) {
        for (std::size_t row = 0; row != SIZE; ++row) {
            for (std::size_t col = 0; col != SIZE; ++col) {
                T& valueCell = this->at(row, col);
                if (&valueCell == &m_zeroValue) {
                    assert(arrays[row][col] == m_zeroValue);
                    continue;
                }
                valueCell = arrays[row][col];
            }
        }
    }

    constexpr auto at(std::size_t i, std::size_t j) -> T& override {
        assert(i < SIZE && j < SIZE);
        if (std::max(i, j) - std::min(i, j) > (DIAGS >> 1)) {
            return m_zeroValue;
        }
        return this->m_matrix[std::min(i, j)][j - i + (DIAGS >> 1)];
    }

    constexpr auto at(std::size_t i, std::size_t j) const -> const T& override {
        assert(i < SIZE && j < SIZE);
        if (std::max(i, j) - std::min(i, j) > (DIAGS >> 1)) {
            return m_zeroValue;
        }
        return this->m_matrix[std::min(i, j)][j - i + (DIAGS >> 1)];
    }

    constexpr auto operator*(T coef) const -> DiagonalMatrix<T, SIZE, DIAGS> {
        DiagonalMatrix<T, SIZE, DIAGS> resMatrix{};
        for (std::size_t row = 0; row != SIZE; ++row) {
            for (std::size_t col = 0; col != SIZE; ++col) {
                T& valueCell = resMatrix.at(row, col);
                if (&valueCell != &m_zeroValue) {
                    valueCell = this->at(row, col) * coef;
                }
            }
        }
        return resMatrix;
    }

    template< std::size_t WIDTH_OTHER >
    constexpr auto operator*(const Matrix<T, SIZE, WIDTH_OTHER>& rightMatrix) const
    -> Matrix<T, SIZE, WIDTH_OTHER> {
        Matrix<T, SIZE, WIDTH_OTHER> matrixProduct{};
        for (std::size_t i = 0; i != SIZE; ++i) {
            for (std::size_t j = 0; j != SIZE; ++j) {
                for (std::size_t k = 0; k != WIDTH_OTHER; ++k) {
                    matrixProduct.at(i, k) += this->at(i, j) * rightMatrix.at(j, k);
                }
            }
        }
        return matrixProduct;
    }

private:
    std::array<std::array<T, DIAGS>, SIZE> m_diags;
    T m_zeroValue{};
};

template< typename T, std::size_t SIZE >
using ThreeDiagonalMatrix = DiagonalMatrix<T, SIZE, 3>;
