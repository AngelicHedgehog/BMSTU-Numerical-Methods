#pragma once

#include <vector>
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
    Matrix() : m_matrix(HEIGHT, std::vector<T>(WIDTH)) {}

    Matrix(const std::vector<std::vector<T>>& matrix)
    : m_matrix(matrix) {
        assert(matrix.size() == HEIGHT);
        for (const auto& row : matrix) {
            assert(row.size() == WIDTH);
        }
    }

    virtual ~Matrix() {};

    auto fillRandomValues(const T& minValue, const T& maxValue, const T& stepValue) -> void {
        std::size_t countValues = (maxValue - minValue) / stepValue + 1;
        #define getRandValue() static_cast<T>((rand() % countValues) * stepValue + minValue);

        for (auto& row : m_matrix) {
            for (auto& element : row) {
                element = getRandValue();
            }
        }
    }

    virtual auto at(std::size_t i, std::size_t j) -> T& {
        assert(i < HEIGHT && j < WIDTH);
        return m_matrix[i][j];
    }

    virtual auto at(std::size_t i, std::size_t j) const -> const T& {
        assert(i < HEIGHT && j < WIDTH);
        return m_matrix[i][j];
    }

    auto operator*(const T& coef) const -> Matrix<T, HEIGHT, WIDTH> {
        Matrix<T, HEIGHT, WIDTH> resMatrix{};
        for (std::size_t row = 0; row != HEIGHT; ++row) {
            for (std::size_t col = 0; col != WIDTH; ++col) {
                resMatrix.at(row, col) = this->at(row, col) * coef;
            }
        }
        return resMatrix;
    }

    auto operator+(const Matrix<T, HEIGHT, WIDTH>& rightMatrix) const -> Matrix<T, HEIGHT, WIDTH> {
        Matrix<T, HEIGHT, WIDTH> resMatrix{};
        for (std::size_t row = 0; row != HEIGHT; ++row) {
            for (std::size_t col = 0; col != WIDTH; ++col) {
                resMatrix.at(row, col) = this->at(row, col) + rightMatrix.at(row, col);
            }
        }
        return resMatrix;
    }

    auto operator-(const Matrix<T, HEIGHT, WIDTH>& rightMatrix) const -> Matrix<T, HEIGHT, WIDTH> {
        Matrix<T, HEIGHT, WIDTH> resMatrix{};
        for (std::size_t row = 0; row != HEIGHT; ++row) {
            for (std::size_t col = 0; col != WIDTH; ++col) {
                resMatrix.at(row, col) = this->at(row, col) - rightMatrix.at(row, col);
            }
        }
        return resMatrix;
    }

    template< std::size_t WIDTH_OTHER >
    auto operator*(const Matrix<T, WIDTH, WIDTH_OTHER>& other) const -> Matrix<T, HEIGHT, WIDTH_OTHER> {
        Matrix<T, HEIGHT, WIDTH_OTHER> matrixProduct{};
        for (std::size_t i = 0; i != HEIGHT; ++i) {
            for (std::size_t j = 0; j != WIDTH; ++j) {
                for (std::size_t k = 0; k != WIDTH_OTHER; ++k) {
                    matrixProduct.at(i, k) += this->at(i, j) * other.at(j, k);
                }
            }
        }
        return matrixProduct;
    }

    auto averageValue() const -> T {
        T summ{};
        for (std::size_t row = 0; row != HEIGHT; ++row) {
            for (std::size_t col = 0; col != WIDTH; ++col) {
                summ += this->at(row, col);
            }
        }
        return summ / (HEIGHT * WIDTH);
    }
    
protected:
    std::vector<std::vector<T>> m_matrix;
};

template< typename T, std::size_t HEIGHT, std::size_t WIDTH >
std::ostream& operator<<(std::ostream& os, const Matrix<T, HEIGHT, WIDTH>& matrix) {
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
