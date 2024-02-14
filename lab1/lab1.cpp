#include <iostream>

#include "DiagonalMatrix.cpp"

int main() {
    ThreeDiagonalMatrix<float, 5> matrix{};
    matrix.fillRandomValues(-1, 1, .01);
    std::cout << matrix << "\n\n";
    auto inv = matrix.getInverse();
    std::cout << inv << "\n\n";
    std::cout << matrix.dot(inv) << '\n';

    return 0;
}
