#pragma once

#include "Matrix.cpp"

template<std::size_t SIZE>
concept IsSizeOne = (SIZE == 1);

template< typename T, std::size_t SIZE >
requires std::is_floating_point_v<T>
class SquareMatrix : public Matrix<T, SIZE, SIZE> {
public:
    constexpr SquareMatrix() {}

    constexpr SquareMatrix(const Matrix<T, SIZE, SIZE>& matrix)
    : Matrix<T, SIZE, SIZE>(matrix) {}

    constexpr SquareMatrix(const std::array<std::array<T, SIZE>, SIZE>& arrays) {
        this->m_matrix = arrays;
    }

    constexpr auto getTransposed() const -> SquareMatrix<T, SIZE> {
        SquareMatrix<T, SIZE> transposed{};

        for (std::size_t row = 0; row != SIZE; ++row) {
            for (std::size_t col = 0; col != SIZE; ++col) {
                transposed.at(row, col) = this->at(col, row);
            }
        }

        return transposed;
    }

    constexpr auto getMinor(std::size_t minorRow, std::size_t minorCol) const
    -> SquareMatrix<T, SIZE - 1> {
        assert(minorRow < SIZE && minorCol < SIZE);

        SquareMatrix<T, SIZE - 1> minor{};

        for (std::size_t row = 0; row != SIZE - 1; ++row) {
            for (std::size_t col = 0; col != SIZE - 1; ++col) {
                minor.at(row, col) = this->at(row + (row >= minorRow), col + (col >= minorCol));
            }
        }
        
        return minor;
    }

    template<std::size_t S = SIZE>
    requires IsSizeOne<S>
    constexpr auto getDeterminant() const -> T {
        return this->at(0, 0);
    }

    template<std::size_t S = SIZE>
    requires (!IsSizeOne<S>)
    constexpr auto getDeterminant() const -> T {
        T determinant{};

        for (std::size_t col = 0; col != SIZE; ++col) {
            determinant +=
                (col % 2 == 0 ? 1 : -1)
                * this->at(0, col)
                * this->getMinor(0, col).getDeterminant();
        }

        return determinant;
    }

    constexpr auto getInverse() const -> SquareMatrix<T, SIZE> {
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
