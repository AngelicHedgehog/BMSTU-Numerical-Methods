#include <iostream>

#include "lib/DiagonalMatrix.cpp"
#include "lib/Vector.cpp"

template< int SIZE >
auto isSolveExists(
    const std::vector<double>& a,
    const std::vector<double>& b,
    const std::vector<double>& c
) -> bool{
    if (
        abs(b[0]) < abs(c[0]) ||
        abs(b[SIZE - 1]) < abs(a[SIZE - 2])
    ) {
        return false;
    }
    for (std::size_t i = 1; i != SIZE - 1; ++i) {
        if (abs(b[i]) < abs(a[i - 1]) + abs(c[i])) {
            return false;
        }
    }
    return true;
}

template< int SIZE >
auto findSolve(
    const std::vector<double>& a,
    const std::vector<double>& b,
    const std::vector<double>& c,
    const Vector<double, SIZE>& d
) -> Vector<double, SIZE>{
    std::vector<double> alpha(SIZE);
    std::vector<double> beta(SIZE);
    alpha[0] = - c[0] / b[0];
    beta[0] = d.at(0) / b[0];
    for (std::size_t i = 1; i != SIZE; ++i) {
        alpha[i] = c[i]
                 / (alpha[i - 1] * a[i - 1] + b[i]);
        beta[i] = (d.at(i) - a[i - 1] * beta[i - 1])
                / (alpha[i - 1] * a[i - 1] + b[i]);
    }

    Vector<double, SIZE> x{};
    x.at(SIZE - 1) = (alpha[SIZE - 1] - a[SIZE - 2] * beta[SIZE - 2])
                   / (alpha[SIZE - 2] * a[SIZE - 2] + b[SIZE - 1]);
    for (std::size_t i = SIZE - 2; i != -1; --i) {
        x.at(i) = alpha[i] * x.at(i + 1) + beta[i];
    }

    return x;
}

template< std::size_t SIZE >
auto checkSolve(
    const ThreeDiagonalMatrix<double, SIZE>& A,
    const Vector<double, SIZE>& xStar,
    const Vector<double, SIZE>& d
) -> Vector<double, SIZE> {
    Vector<double, SIZE> dStar = A * xStar;
    Vector<double, SIZE> r = d - dStar;
    Vector<double, SIZE> e = A.getInverse() * r;

    return e;
}

template< std::size_t SIZE >
auto test_alghorithm() -> void {
    ThreeDiagonalMatrix<double, SIZE> A{};
    A.fillRandomValues(-10, 10, .1);

    std::vector<double> a(SIZE - 1);
    std::vector<double> b(SIZE);
    std::vector<double> c(SIZE - 1);
    for (std::size_t i = 0; i != SIZE - 1; ++i) {
        a[i] = A.at(i + 1, i);
        b[i] = A.at(i, i);
        c[i] = A.at(i, i + 1);
    }
    // if (!isSolveExists<SIZE>(a, b, c)) {
    //     test_alghorithm<SIZE>();
    //     return;
    // }

    Vector<double, SIZE> d{};
    d.fillRandomValues(-10, 10, .1);

    Vector<double, SIZE> x = findSolve<SIZE>(a, b, c, d);
    Vector<double, SIZE> error = checkSolve(A, x, d);
    std::cout << "Error for this test = " << error.averageValue() << '\n';
}

auto main() -> int {
    for (std::size_t i = 0; i != 10; ++i) {
        test_alghorithm<6>();
    }

    return 0;
}
