#include <vector>
#include <random>
#include <cassert>
#include <iostream>

template <typename T, int SIZE>
class Vector {
public:
    Vector(const T& minValue, const T& maxValue) : m_vector(SIZE) {

        #define getRandValue() {rand() % (maxValue - minValue) + minValue};

        for (auto& element : m_vector) {
            element = getRandValue();
        }
    }

    T& at(int i) {
        assert(0 <= i && i < SIZE);
        return m_vector[i];
    }

    const T& at(int i) const {
        assert(0 <= i && i < SIZE);
        return m_vector[i];
    }

private:
    std::vector<T> m_vector;
};

template <typename T, int SIZE>
std::ostream& operator<<(std::ostream& os, const Vector<T, SIZE>& matrix) {
    for (int i = 0; i != SIZE; ++i) {
        os << matrix.at(i);
        if (i + 1 != SIZE) {
            os << '\t';
        }
    }
    return os;
}
