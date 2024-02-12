#include <vector>
#include <random>
#include <cassert>
#include <iostream>

template <typename T, int SIZE, int DIAGS>
requires (
    std::is_integral_v<T> &&
    (DIAGS & 1) == 1 &&
    SIZE > (DIAGS >> 1)
)
class DiagonalMatrix {
public:
    DiagonalMatrix(const T& minValue, const T& maxValue)
    : m_matrix(SIZE, std::vector<T>(DIAGS)) {

        #define getRandValue() {rand() % (maxValue - minValue) + minValue};

        for (auto& diagsSlice : m_matrix) {
            for (auto& element : diagsSlice) {
                element = getRandValue();
            }
        }
    }

    T& at(int i, int j) {
        assert(0 <= i && i < SIZE);
        assert(0 <= j && j < SIZE);

        if (abs(i - j) > (DIAGS >> 1)) {
            return m_zeroValue;
        }

        return m_matrix[std::min(i, j)][j - i + (DIAGS >> 1)];
    }

    const T& at(int i, int j) const {
        assert(0 <= i && i < SIZE);
        assert(0 <= j && j < SIZE);

        if (abs(i - j) > (DIAGS >> 1)) {
            return m_zeroValue;
        }

        return m_matrix[std::min(i, j)][j - i + (DIAGS >> 1)];
    }
    
private:
    std::vector<std::vector<T>> m_matrix;
    const T m_zeroValue{};
};

template <typename T, int SIZE, int DIAGS>
std::ostream& operator<<(std::ostream& os, const DiagonalMatrix<T, SIZE, DIAGS>& matrix) {
    for (int i = 0; i != SIZE; ++i) {
        for (int j = 0; j != SIZE; ++j) {
            os << matrix.at(i, j);
            if (j + 1 != SIZE) {
                os << '\t';
            }
        }
        if (i + 1 != SIZE) {
            os << '\n';
        }
    }
    return os;
}
