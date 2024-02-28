#include <cmath>
#include <numbers>

#include "../lab1/lab1.cpp"

// Вариант 4. [0, π]. f(x) = 2x*cos(x/2)

#define LOOKAHEAD 1
#define N (10 + LOOKAHEAD)

auto f(double x) -> double {
    return 2 * x * std::cos(x / 2);
}

auto main() -> int {
    double a = 0, b = std::numbers::pi;
    double h = (b - a) / (N - LOOKAHEAD);

    b += h * LOOKAHEAD;

    Matrix<double, N + 1, 2> table{};
    for (std::size_t i = 0; i != N + 1; ++i) {
        table.at(i, 0) = a + h * i;
        table.at(i, 1) = f(table.at(i, 0));
    }

    ThreeDiagonalMatrix<double, N - 1> SLAE{};
    Vector<double, N - 1> SLAEright{};
    for (std::size_t i = 1; i != N; ++i) {
        if (i != N - 1) {
            SLAE.at(i, i - 1) = SLAE.at(i - 1, i) = 1;
        }
        SLAE.at(i - 1, i - 1) = 4;

        SLAEright.at(i - 1) =
                (table.at(i + 1, 1) - 2 * table.at(i, 1) + table.at(i - 1, 1))
                / (h * h);
    }
    Vector<double, N - 1> SLAEsolve = findSolve(SLAE, SLAEright);

    Vector<double, N + 1> A, B, C, D{};

    for (std::size_t i = 1; i != N; ++i) {
        C.at(i) = SLAEsolve.at(i - 1);
    }
    C.at(0) = C.at(N) = 0;

    for (std::size_t i = 0; i != N - 1; ++i) {
        A.at(i) = table.at(i, 1);
        B.at(i) = (table.at(i + 1, 1) - table.at(i, 1)) / h -
                  (h / 3) * (C.at(i + 1) + 2 * C.at(i));
        D.at(i) = (C.at(i + 1) - C.at(i)) / (3 * h);
    }
    A.at(N - 1) = table.at(N - 1, 1);
    B.at(N - 1) = (table.at(N, 1) - table.at(N - 1, 1)) * C.at(N - 1) * 2 / 3;
    D.at(N - 1) = - C.at(N) / (3 * h);

    auto spline = [&](double x) {
        int i = (x - a) * N / (b - a);
        double delta_x = x - table.at(i, 0);
        double res = D.at(i);
        res = res * delta_x + C.at(i);
        res = res * delta_x + B.at(i);
        res = res * delta_x + A.at(i);
        return res;
    };

    std::cout << "x\t\tS(x)\t\ty(x)\t\t|S(x)-y(x)|\n";
    for (std::size_t i = 0; i != 2 * (N - LOOKAHEAD) + 1; ++i) {
        double x = a + h * i / 2 + .0001;
        double s = spline(x);
        double y = f(x);
        std::cout << x << "  \t";
        std::cout << s << "  \t";
        std::cout << y << "    \t";
        std::cout << abs(s - y) << '\n';
    }
}
