#pragma once

#include <vector>
#include <cassert>

#include "SquareMatrix.cpp"

template <typename T, int SIZE, int DIAGS>
requires (
    (DIAGS & 1) == 1 &&
    SIZE > (DIAGS >> 1)
)
class DiagonalMatrix final : public SquareMatrix<T, SIZE> {
public:
    DiagonalMatrix() {
        SquareMatrix<T, SIZE>::m_matrix = std::vector<std::vector<T>>(SIZE, std::vector<T>(DIAGS));
    }

    auto at(int i, int j) -> T& override final {
        assert(0 <= i && i < SIZE);
        assert(0 <= j && j < SIZE);

        if (abs(i - j) > (DIAGS >> 1)) {
            return m_zeroValue;
        }

        return SquareMatrix<T, SIZE>::m_matrix[std::min(i, j)][j - i + (DIAGS >> 1)];
    }

    auto at(int i, int j) const -> const T& override final {
        assert(0 <= i && i < SIZE);
        assert(0 <= j && j < SIZE);

        if (abs(i - j) > (DIAGS >> 1)) {
            return m_zeroValue;
        }

        return SquareMatrix<T, SIZE>::m_matrix[std::min(i, j)][j - i + (DIAGS >> 1)];
    }
    
private:
    T m_zeroValue{};
};

template <typename T, int SIZE>
using ThreeDiagonalMatrix = DiagonalMatrix<T, SIZE, 3>;
