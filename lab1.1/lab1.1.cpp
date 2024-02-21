#include <cmath>

#include "../lab1/lab1.cpp"

// Вариант 4. [0, π]. f(x) = 2x*cos(x/2)

#define PI 3.1415
#define N 32

double f(double x) {
    return 2 * x * std::cos(x / 2);
}

auto main() -> int {
    double a = 0, b = PI;
    double h = (b - a) / N;

    Matrix<double, N + 1, 2> table{};
    for (std::size_t i = 0; i != N + 1; ++i) {
        table.at(i, 0) = a + h * i;
        table.at(i, 1) = f(table.at(i, 0));
    }

    std::cout << "x\t|\ty\n------------------\n" << table << '\n';

    ThreeDiagonalMatrix<double, N - 1> SLAE{};
    Vector<double, N - 1> Y{};
    for (std::size_t i = 0; i != N - 1; ++i) {
        if (i != 0) {
            SLAE.at(i, i - 1) = 1;
        }
        SLAE.at(i, i) = 4;
        if (i != N - 2) {
            SLAE.at(i, i + 1) = 1;
        }
        Y.at(i) = 3 - (table.at(i, 1) - 2 * table.at(i + 1, 1) + table.at(i + 2, 1));
    }

    auto solve = findSolve(SLAE, Y);  // c | i е [1, N - 1]

    Vector<double, N + 2> A, B, C, D;

    // c | i e [1, N + 1]
    for (std::size_t i = 0; i != N - 1; ++i) {
        C.at(i + 1) = solve.at(i);
    }
    C.at(0) = 0;
    C.at(N) = 0;
    C.at(N + 1) = 0;

    // d | i e [1, N]
    for (std::size_t i = 1; i != N + 1; ++i) {
        D.at(i) = (C.at(i + 1) + C.at(i)) / (3 * h);
    }

    // a | i e [1, N]
    for (std::size_t i = 1; i != N + 1; ++i) {
        A.at(i) = table.at(i - 1, 1);
    }

    B.at(0) = 0;
    for (std::size_t i = 1; i != N + 1; ++i) {
        B.at(i) = B.at(i - 1) + h * (C.at(i) + C.at(i - 1));
    }

    std::cout << "\n\nA\tB\tC\tD\n";
    for (std::size_t i = 1; i != N; ++i) {
        std::cout << A.at(i) << '\t' << B.at(i) << '\t' << C.at(i) << '\t' << D.at(i) << '\n';
    }
}