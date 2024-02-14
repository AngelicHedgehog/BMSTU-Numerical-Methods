#pragma once

#include <vector>
#include <random>
#include <cassert>
#include <iostream>

template< typename T, int HEIGHT, int WIDTH >
requires (
    std::is_floating_point_v<T> &&
    HEIGHT > 0 &&
    WIDTH > 0
)
class Matrix {
public:
    Matrix() : m_matrix(HEIGHT, std::vector<T>(WIDTH)) {}

    virtual ~Matrix() {};

    auto fillRandomValues(const T& minValue, const T& maxValue, const T& stepValue) -> void {
        std::size_t countValues = (maxValue - minValue) / stepValue;
        #define getRandValue() {(rand() % static_cast<int>(countValues)) * stepValue + minValue};

        for (auto& row : m_matrix) {
            for (auto& element : row) {
                element = getRandValue();
            }
        }
    }

    virtual auto at(int i, int j) -> T& {
        assert(0 <= i && i < HEIGHT);
        assert(0 <= j && j < WIDTH);

        return m_matrix[i][j];
    }

    virtual auto at(int i, int j) const -> const T& {
        assert(0 <= i && i < HEIGHT);
        assert(0 <= j && j < WIDTH);

        return m_matrix[i][j];
    }

    template< int WIDTH_OTHER >
    auto dot(const Matrix<T, WIDTH, WIDTH_OTHER>& other) const -> Matrix<T, HEIGHT, WIDTH_OTHER> {
        Matrix<T, HEIGHT, WIDTH_OTHER> matrixProduct{};

        for (int i = 0; i != HEIGHT; ++i) {
            for (int j = 0; j != WIDTH; ++j) {
                for (int k = 0; k != WIDTH_OTHER; ++k) {
                    matrixProduct.at(i, k) += at(i, j) * other.at(j, k);
                }
            }
        }

        return matrixProduct;
    }
    
protected:
    std::vector<std::vector<T>> m_matrix;
};

template< typename T, int HEIGHT, int WIDTH >
std::ostream& operator<<(std::ostream& os, const Matrix<T, HEIGHT, WIDTH>& matrix) {
    for (int i = 0; i != HEIGHT; ++i) {
        for (int j = 0; j != WIDTH; ++j) {
            os << matrix.at(i, j);
            if (j + 1 != WIDTH) {
                os << '\t';
            }
        }
        if (i + 1 != HEIGHT) {
            os << '\n';
        }
    }
    return os;
}
