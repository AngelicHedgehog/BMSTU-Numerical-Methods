#include <iostream>

#include "lib/DiagonalMatrix.cpp"
#include "lib/Vector.cpp"

template< int SIZE >
auto isSolveExists(
    const ThreeDiagonalMatrix<float, SIZE>& A
) -> bool {

    bool wasNotStrict = false;

    if (
        abs(A.at(0, 0)) < .001 ||
        abs(A.at(SIZE - 1, SIZE - 1)) < .001
    ) {
        return false;
    }

    for (std::size_t i = 1; i != SIZE - 1; ++i) {
        float rightPart = abs(A.at(i, i - 1)) + abs(A.at(i, i + 1));
        if (
            abs(A.at(i, i)) < .001 ||
            A.at(i, i) < rightPart
        ) {
            return false;
        }
        if (abs(A.at(i, i) - rightPart) < .001) {
            wasNotStrict = true;
        }
    }

    return wasNotStrict;
}

template< int SIZE >
auto findSolve(
    const ThreeDiagonalMatrix<float, SIZE>& A,
    const Vector<float, SIZE>& d
) -> Vector<float, SIZE> {

    std::vector<float> alpha(SIZE);
    std::vector<float> beta(SIZE);
    alpha[0] = - A.at(0, 1) / A.at(0, 0);
    beta[0] = d.at(0) / A.at(0, 0);
    for (std::size_t i = 1; i != SIZE - 1; ++i) {
        alpha[i] = A.at(i, i + 1)
                 / (- A.at(i, i) - A.at(i, i - 1) * alpha[i - 1]);
        beta[i] = (A.at(i, i - 1) * beta[i - 1] - d.at(i))
                / (- A.at(i, i) - A.at(i, i - 1) * alpha[i - 1]);
    }
    alpha[SIZE - 1] = 0;
    beta[SIZE - 1] = (A.at(SIZE - 1, SIZE - 2) * beta[SIZE - 2] - d.at(SIZE - 1))
                   / (- A.at(SIZE - 1, SIZE - 1) - A.at(SIZE - 1, SIZE - 2) * alpha[SIZE - 2]);

    Vector<float, SIZE> x{};
    x.at(SIZE - 1) = beta[SIZE - 1];
    for (std::size_t i = SIZE - 2; i != -1; --i) {
        x.at(i) = alpha[i] * x.at(i + 1) + beta[i];
    }

    return x;
}

template< std::size_t SIZE >
auto checkSolve(
    const ThreeDiagonalMatrix<float, SIZE>& A,
    const Vector<float, SIZE>& xStar,
    const Vector<float, SIZE>& d
) -> Vector<float, SIZE> {

    Vector<float, SIZE> dStar = A * xStar;
    Vector<float, SIZE> r = d - dStar;
    Vector<float, SIZE> e = A.getInverse() * r;

    return e;
}

template< std::size_t SIZE >
auto test_alghorithm() -> void {
    ThreeDiagonalMatrix<float, SIZE> A{};
    A.fillRandomValues(-10, 10, .1);

    if (!isSolveExists<SIZE>(A)) {
        test_alghorithm<SIZE>();
        return;
    }

    Vector<float, SIZE> d{};
    d.fillRandomValues(-10, 10, .1);

    Vector<float, SIZE> x = findSolve<SIZE>(A, d);
    Vector<float, SIZE> error = checkSolve(A, x, d);
    std::cout << "Error for this test = " << error.averageValue() << '\n';
}

template< std::size_t SIZE >
auto test_check(
    const ThreeDiagonalMatrix<float, SIZE>& A,
    const Vector<float, SIZE>& x
) -> void {

    // if (!isSolveExists<SIZE>(A)) {
    //     std::cout << "Solve unexists\n\n";
    //     return;
    // }

    Vector<float, SIZE> xStar = findSolve<SIZE>(A, A * x);
    std::cout << xStar << "\n\n";
}

auto main() -> int {
    test_check<4>(
        std::vector<std::vector<float>>({
            {4, 1, 0, 0},
            {1, 4, 1, 0},
            {0, 1, 4, 1},
            {0, 0, 1, 4}
        }),
        std::vector<float>{1, 1, 1, 1}
    );

    test_check<4>(
        ThreeDiagonalMatrix<float, 4>({
            {4, 1, 0, 0},
            {1, 4, 1, 0},
            {0, 1, 4, 1},
            {0, 0, 1, 4}
        }) * (1. / 3),
        Vector<float, 4>(
            {1./3, 1./3, 1, 2}
        )
    );

    return 0;
}
