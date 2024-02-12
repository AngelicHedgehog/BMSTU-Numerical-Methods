#include <iostream>

#include "DiagonalMatrix.cpp"
#include "Vector.cpp"

template <typename T, int SIZE>
using ThreeDiagonalMatrix = DiagonalMatrix<T, SIZE, 3>;

int main() {
    ThreeDiagonalMatrix<int, 5> matrix{10, 100};
    std::cout << matrix << '\n' << '\n';
    Vector<int, 5> vector{10, 100};
    std::cout << vector << '\n';

    return 0;
}
