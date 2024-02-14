#pragma once

#include "Matrix.cpp"

template< typename T, std::size_t SIZE >
requires std::is_floating_point_v<T>
class SquareMatrix : public Matrix<T, SIZE, SIZE> {
public:
    SquareMatrix() {}

    SquareMatrix(const Matrix<T, SIZE, SIZE>& other) {
        for (std::size_t row = 0; row != SIZE; ++row) {
            for (std::size_t col = 0; col != SIZE; ++col) {
                this->at(row, col) = other.at(row, col);
            }
        }
    }

    SquareMatrix(const std::vector<std::vector<T>>& matrix)
    : Matrix<T, SIZE, SIZE>::m_matrix(matrix) {
        assert(matrix.size() == SIZE);
        for (const auto& row : matrix) {
            assert(row.size() == SIZE);
        }
    }

    auto operator*(const Matrix<T, SIZE, SIZE>& other) const -> SquareMatrix<T, SIZE> {
        SquareMatrix<T, SIZE> matrixProduct{};
        for (std::size_t i = 0; i != SIZE; ++i) {
            for (std::size_t j = 0; j != SIZE; ++j) {
                for (std::size_t k = 0; k != SIZE; ++k) {
                    matrixProduct.at(i, k) += this->at(i, j) * other.at(j, k);
                }
            }
        }
        return matrixProduct;
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

    auto getTransposed() const -> SquareMatrix<T, SIZE> {
        SquareMatrix<T, SIZE> transposed{};

        for (std::size_t row = 0; row != SIZE; ++row) {
            for (std::size_t col = 0; col != SIZE; ++col) {
                transposed.at(row, col) = this->at(col, row);
            }
        }

        return transposed;
    }

    auto getMinor(std::size_t minorRow, std::size_t minorCol) const -> SquareMatrix<T, SIZE - 1> {
        assert(minorRow < SIZE && minorCol < SIZE);

        SquareMatrix<T, SIZE - 1> minor{};

        for (std::size_t row = 0; row != SIZE - 1; ++row) {
            for (std::size_t col = 0; col != SIZE - 1; ++col) {
                minor.at(row, col) = this->at(row + (row >= minorRow), col + (col >= minorCol));
            }
        }
        
        return minor;
    }

    template<
        std::size_t S = SIZE,
        class = typename std::enable_if<S == 1>::type
    >
    auto getDeterminant() const -> T {
        return this->at(0, 0);
    }

    template<
        int S = SIZE,
        class = typename std::enable_if<S != 1>::type
    >
    auto getDeterminant() const -> T {
        T determinant{};

        for (std::size_t col = 0; col != SIZE; ++col) {
            determinant +=
                (col % 2 == 0 ? 1 : -1)
                * this->at(0, col)
                * this->getMinor(0, col).getDeterminant();
        }

        return determinant;
    }

    auto getInverse() const -> SquareMatrix<T, SIZE> {
        T determinant{this->getDeterminant()};
        assert(determinant != 0);

        SquareMatrix<T, SIZE> inverseMatrix{};

        for (std::size_t row = 0; row != SIZE; ++row) {
            for (std::size_t col = 0; col != SIZE; ++col) {
                inverseMatrix.at(row, col) =
                    ((row + col) % 2 == 0 ? 1 : -1)
                    * this->getMinor(col, row).getDeterminant()
                    / determinant;
            }
        }

        return inverseMatrix;
    }
};
