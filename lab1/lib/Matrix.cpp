#pragma once

#include <array>
#include <random>
#include <cassert>
#include <iostream>

template< typename T, std::size_t HEIGHT, std::size_t WIDTH >
requires (
    std::is_arithmetic_v<T> &&
    HEIGHT != 0 &&
    WIDTH != 0
)
class Matrix {
public:
    constexpr Matrix() {}

    constexpr Matrix(const std::array<std::array<T, WIDTH>, HEIGHT>& arrays)
    : m_matrix(arrays) {}

    virtual constexpr ~Matrix() {};

    virtual constexpr auto at(std::size_t i, std::size_t j) -> T& {
        assert(i < HEIGHT && j < WIDTH);
        return m_matrix[i][j];
    }

    virtual constexpr auto at(std::size_t i, std::size_t j) const -> const T& {
        assert(i < HEIGHT && j < WIDTH);
        return m_matrix[i][j];
    }

    constexpr auto fillRandomValues(
        const T& minValue,
        const T& maxValue,
        const T& stepValue)
    -> void {
        std::size_t countValues = (maxValue - minValue) / stepValue + 1;
        #define getRandValue() static_cast<T>((rand() % countValues) * stepValue + minValue);

        for (auto& row : m_matrix) {
            for (auto& element : row) {
                element = getRandValue();
            }
        }
    }

    constexpr auto operator*(T coef) const -> Matrix<T, HEIGHT, WIDTH> {
        Matrix<T, HEIGHT, WIDTH> resMatrix{};
        for (std::size_t row = 0; row != HEIGHT; ++row) {
            for (std::size_t col = 0; col != WIDTH; ++col) {
                resMatrix.at(row, col) = this->at(row, col) * coef;
            }
        }
        return resMatrix;
    }

    constexpr auto operator+(const Matrix<T, HEIGHT, WIDTH>& rightMatrix) const
    -> Matrix<T, HEIGHT, WIDTH> {
        Matrix<T, HEIGHT, WIDTH> resMatrix{};
        for (std::size_t row = 0; row != HEIGHT; ++row) {
            for (std::size_t col = 0; col != WIDTH; ++col) {
                resMatrix.at(row, col) = this->at(row, col) + rightMatrix.at(row, col);
            }
        }
        return resMatrix;
    }

    constexpr auto operator-(const Matrix<T, HEIGHT, WIDTH>& rightMatrix) const
    -> Matrix<T, HEIGHT, WIDTH> {
        Matrix<T, HEIGHT, WIDTH> resMatrix{};
        for (std::size_t row = 0; row != HEIGHT; ++row) {
            for (std::size_t col = 0; col != WIDTH; ++col) {
                resMatrix.at(row, col) = this->at(row, col) - rightMatrix.at(row, col);
            }
        }
        return resMatrix;
    }

    template< std::size_t WIDTH_OTHER >
    constexpr auto operator*(const Matrix<T, WIDTH, WIDTH_OTHER>& rightMatrix) const 
    -> Matrix<T, HEIGHT, WIDTH_OTHER> {
        Matrix<T, HEIGHT, WIDTH_OTHER> matrixProduct{};
        for (std::size_t i = 0; i != HEIGHT; ++i) {
            for (std::size_t j = 0; j != WIDTH; ++j) {
                for (std::size_t k = 0; k != WIDTH_OTHER; ++k) {
                    matrixProduct.at(i, k) += this->at(i, j) * rightMatrix.at(j, k);
                }
            }
        }
        return matrixProduct;
    }

    constexpr auto averageValue() const -> T {
        T sum{};
        for (std::size_t row = 0; row != HEIGHT; ++row) {
            for (std::size_t col = 0; col != WIDTH; ++col) {
                sum += this->at(row, col);
            }
        }
        return sum / (HEIGHT * WIDTH);
    }

    constexpr auto absoluteSum() const -> T {
        T absSum{};
        for (std::size_t row = 0; row != HEIGHT; ++row) {
            for (std::size_t col = 0; col != WIDTH; ++col) {
                absSum += std::abs(this->at(row, col));
            }
        }
        return absSum;
    }
    
protected:
    std::array<std::array<T, WIDTH>, HEIGHT> m_matrix;
};

template< typename T, std::size_t HEIGHT, std::size_t WIDTH >
constexpr std::ostream& operator<<(std::ostream& os, const Matrix<T, HEIGHT, WIDTH>& matrix) {
    for (std::size_t row = 0; row != HEIGHT; ++row) {
        for (std::size_t col = 0; col != WIDTH; ++col) {
            os << matrix.at(row, col);
            if (col + 1 != WIDTH) {
                os << '\t';
            }
        }
        if (row + 1 != HEIGHT) {
            os << '\n';
        }
    }
    return os;
}
