#include <cmath>

#include "../lab1/lab1.cpp"

// Вариант 4. [0, π]. f(x) = 2x*cos(x/2)

#define PI 3.1415
#define N 32

auto f(double x) -> double {
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

    for (std::size_t i = 0; i != N + 1; ++i) {
        std::cout << "(x" << i << ", y" << i << ")\t= ("
                  << table.at(i, 0) << ",\t" << table.at(i, 1) << ")\n";
    }
    std::cout << '\n';

    ThreeDiagonalMatrix<double, N - 1> SLAE{};
    Vector<double, N - 1> SLAEright{};
    for (std::size_t i = 0; i != N - 1; ++i) {
        if (i != N - 2) {
            SLAE.at(i + 1, i) = SLAE.at(i, i + 1) = 1;
        }
        SLAE.at(i, i) = 4;

        SLAEright.at(i) =
                (table.at(i + 2, 1) - 2 * table.at(i + 1, 1) + table.at(i, 1))
                / (h * h);
    }
    Vector<double, N - 1> SLAEsolve = findSolve(SLAE, SLAEright);

    Vector<double, N + 1> A, B, C, D{};

    for (std::size_t i = 0; i != N - 1; ++i) {
        C.at(i + 1) = SLAEsolve.at(i);
    }
    C.at(0) = C.at(N) = 0;

    for (std::size_t i = 0; i != N - 1; ++i) {
        A.at(i) = table.at(i, 1);
        B.at(i) = (table.at(i + 1, 1) - table.at(i, 1)) *
                  (C.at(i + 1) + 2 * C.at(i)) / 3;
        D.at(i) = (C.at(i + 1) - C.at(i)) / (3 * h);
    }
    A.at(N - 1) = table.at(N - 1, 1);
    B.at(N - 1) = (table.at(N, 1) - table.at(N - 1, 1)) * C.at(N - 1) * 2 / 3;
    D.at(N - 1) = - C.at(N) / (3 * h);

    for (std::size_t i = 0; i != N; ++i) {
        std::cout << "(a" << i <<
                    ", b" << i <<
                    ", c" << i <<
                    ", d" << i << ")\t= (" <<
                    A.at(i) << ",\t" <<
                    B.at(i) << ",\t" <<
                    C.at(i) << ",\t" <<
                    D.at(i) << ")\n";
    }
    std::cout << '\n';

    auto spline = [&](double x) {
        int i = (x - a) * N / (b - a);
        double delta_x = x - table.at(i, 0);
        double res = D.at(i);
        res = res * delta_x + C.at(i);
        res = res * delta_x + B.at(i);
        res = A.at(i);
        return res;
    };

    double splineError = 0;
    for (std::size_t i = 0; i != N; ++i) {
        double x = a + (i + .5) * h;
        double y = f(x);
        double y_star = spline(x);
        splineError += abs(y_star - y);
    }

    std::cout << "Error of spline in centers = " << splineError << "\n\n";

    double x;
    std::cout << "Enter x from interval [" << a << ", " << b << "]: ";
    std::cin >> x;
    assert(a <= x && x <= b);
    std::cout << "Original f(" << x << ") = " << f(x) << '\n';
    std::cout << "Spline   f(" << x << ") = " << spline(x) << "\n\n";
}