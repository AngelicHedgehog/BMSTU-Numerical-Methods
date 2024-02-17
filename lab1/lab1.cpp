#include <iostream>

#include "lib/DiagonalMatrix.cpp"
#include "lib/Vector.cpp"

const double EPSILON = .001;

// source of algo: https://dzen.ru/a/YDWWQaMy3XNzjwmJ

template< typename T, std::size_t SIZE >
constexpr auto isSolveExists(
    const ThreeDiagonalMatrix<T, SIZE>& A
) -> bool {

    bool wasStrict = false;

    if (
        abs(A.at(0, 0)) < EPSILON ||
        abs(A.at(SIZE - 1, SIZE - 1)) < EPSILON
    ) {
        return false;
    }

    for (std::size_t i = 1; i != SIZE - 1; ++i) {
        T rightPart = abs(A.at(i, i - 1)) + abs(A.at(i, i + 1));
        if (
            abs(A.at(i, i)) < EPSILON ||
            A.at(i, i) < rightPart
        ) {
            return false;
        }
        if (A.at(i, i) > rightPart) {
            wasStrict = true;
        }
    }

    return wasStrict;
}

template< typename T, std::size_t SIZE >
constexpr auto findSolve(
    const ThreeDiagonalMatrix<T, SIZE>& A,
    const Vector<T, SIZE>& d
) -> Vector<T, SIZE> {

    std::array<T, SIZE> alpha{};
    std::array<T, SIZE> beta{};
    alpha[0] = - A.at(0, 1) / A.at(0, 0);
    beta[0] = d.at(0) / A.at(0, 0);
    for (std::size_t i = 1; i != SIZE - 1; ++i) {
        alpha[i] = - A.at(i, i + 1)
                 / (A.at(i, i) + A.at(i, i - 1) * alpha[i - 1]);
        beta[i] = (d.at(i) - A.at(i, i - 1) * beta[i - 1])
                / (A.at(i, i) + A.at(i, i - 1) * alpha[i - 1]);
    }
    alpha[SIZE - 1] = 0;
    beta[SIZE - 1] = (d.at(SIZE - 1) - A.at(SIZE - 1, SIZE - 2) * beta[SIZE - 2])
                   / (A.at(SIZE - 1, SIZE - 1) + A.at(SIZE - 1, SIZE - 2) * alpha[SIZE - 2]);

    Vector<T, SIZE> x{};
    x.at(SIZE - 1) = beta[SIZE - 1];
    for (std::size_t i = SIZE - 2; i != -1; --i) {
        x.at(i) = alpha[i] * x.at(i + 1) + beta[i];
    }

    return x;
}

template< typename T, std::size_t SIZE >
constexpr auto checkSolve(
    const ThreeDiagonalMatrix<T, SIZE>& A,
    const Vector<T, SIZE>& xStar,
    const Vector<T, SIZE>& d
) -> Vector<T, SIZE> {

    auto dStar = A * xStar;
    auto range = d - dStar;
    auto error = A.getInverse() * range;

    return error;
}

template< typename T, std::size_t SIZE >
constexpr auto test_alghorithm() -> void {
    ThreeDiagonalMatrix<T, SIZE> A{};
    A.fillRandomValues(-10, 10, .1);

    if (!isSolveExists(A)) {
        test_alghorithm<T, SIZE>();
        return;
    }

    Vector<T, SIZE> d{};
    d.fillRandomValues(-10, 10, .1);

    auto x = findSolve(A, d);
    auto error = checkSolve(A, x, d);
    std::cout << "Error for this test = " << error.absoluteSum() << '\n';
}

template< typename T, std::size_t SIZE >
constexpr auto test_check(
    const ThreeDiagonalMatrix<T, SIZE>& A,
    const Vector<T, SIZE>& x
) -> void {

    if (!isSolveExists(A)) {
        std::cout << "Solve unexists\n\n";
        return;
    }

    auto xStar = findSolve<T, SIZE>(A, A * x);
    std::cout << xStar << "\n\n";
}

auto main() -> int {
    for (std::size_t i = 0; i != 5; ++i) {
        test_alghorithm<double, 4>();
    }
    test_check(
        ThreeDiagonalMatrix<float, 4>({{
            {4, 1, 0, 0},
            {1, 4, 1, 0},
            {0, 1, 4, 1},
            {0, 0, 1, 4}
        }}),
        {{1, 1, 1, 1}}
    );

    test_check(
        ThreeDiagonalMatrix<float, 4>({{
            {4, 1, 0, 0},
            {1, 4, 1, 0},
            {0, 1, 4, 1},
            {0, 0, 1, 4}
        }}) * (1./3),
        {{1./3, 1./3, 1, 2}}
    );

    return 0;
}
