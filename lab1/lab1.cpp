#include <iostream>

#include "DiagonalMatrix.cpp"
#include "Vector.cpp"

int main() {
    Vector<int, 10> matrix{};
    matrix.fillRandomValues(10, 100);
    std::cout << matrix;
    // ThreeDiagonalMatrix<int, 5> matrix{};
    // matrix.fillRandomValues(10, 100);
    // std::cout << matrix << '\n' << '\n';
    // Vector<int, 5> vector{10, 100};
    // std::cout << vector << '\n';

    return 0;
}
