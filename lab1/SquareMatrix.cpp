#pragma once

#include "Matrix.cpp"

template< typename T, int SIZE >
class SquareMatrix : public Matrix<T, SIZE, SIZE> {
public:
    SquareMatrix() {}

    SquareMatrix(const Matrix<T, SIZE, SIZE>& matrix) {
        for (int i = 0; i != SIZE; ++i) {
            for (int j = 0; j != SIZE; ++j) {
                this->at(i, j) = matrix.at(i, j);
            }
        }
    }

    auto getTransposed() const -> SquareMatrix<T, SIZE> {
        SquareMatrix<T, SIZE> transposed{};

        for (int i = 0; i != SIZE; ++i) {
            for (int j = 0; j != SIZE; ++j) {
                transposed.at(i, j) = this->at(j, i);
            }
        }

        return transposed;
    }

    auto getMinor(int minorRow, int minorCol) const -> SquareMatrix<T, SIZE - 1> {
        assert(minorRow < SIZE && minorCol < SIZE);

        SquareMatrix<T, SIZE - 1> minor{};

        for (int row = 0; row != SIZE - 1; ++row) {
            for (int col = 0; col != SIZE - 1; ++col) {
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

        for (int col = 0; col != SIZE; ++col) {
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

        for (int i = 0; i != SIZE; ++i) {
            for (int j = 0; j != SIZE; ++j) {
                inverseMatrix.at(i, j) =
                    ((i + j) % 2 == 0 ? 1 : -1)
                    * this->getMinor(j, i).getDeterminant()
                    / determinant;
            }
        }

        return inverseMatrix;
    }
};
