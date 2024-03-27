#include <cmath>
#include <numbers>
#include <iostream>

#include "../lab1/lab1.cpp"

// lab 14

// test:
// y = eˣ, x ∈ [0, 1], y(0)=e⁰=1, y(1)=e
// y"(x) + 5y'(x) - 4y(x) = 2eˣ

// в отчет вынести два столбика значений y(xᵢ) и yᵢ(x)

#define N 50

auto main() -> int {
    auto y = [](double x){return std::numbers::e;};

    double a = 1;
    double b = std::numbers::e;

    // y"(x) + p(x)*y'(x) - q(x)*y(x) = f(x)
    auto p_x = [](double x){return 5;};
    auto q_x = [](double x){return -4;};
    auto f_x = [](double x){return 2 * std::pow(std::numbers::e, x);};

    double h = 1. / N;

    auto x_i = [&](std::size_t i){return i * h;};
    auto p_i = [&](std::size_t i){return p_x(x_i(i));};
    auto q_i = [&](std::size_t i){return q_x(x_i(i));};
    auto f_i = [&](std::size_t i){return f_x(x_i(i));};

    ThreeDiagonalMatrix<double, N - 1> SLAE{};
    Vector<double, N - 1> SLAEright{};
    for (std::size_t i = 1; i != N; ++i) {
        if (i != 1) {
            SLAE.at(i - 1, i - 2) = 1 - h / 2 * p_i(i);
        }

        if (i != N - 1) {
            SLAE.at(i - 1, i) = 1 + h / 2 * p_i(i);
        }

        SLAE.at(i - 1, i - 1) = h * h * q_i(i) - 2;
        SLAEright.at(i - 1) = h * h * f_i(i);
    }
    Vector<double, N - 1> SLAEsolve = findSolve(SLAE, SLAEright);

    Vector<double, N + 1> y_i{};
    y_i.at(0) = a;
    y_i.at(N) = b;

    for (std::size_t i = 1; i != N; ++i) {
        y_i.at(i) = SLAEsolve.at(i - 1);
    }

    // ||y - y˜|| = max|y(xᵢ) - yᵢ|
    double solve_error = 0;
    for (std::size_t i = 0; i != N + 1; ++i) {
        solve_error = std::max(solve_error, std::abs(y(x_i(i)) - y_i.at(i)));
    }

    std::cout << "Numeral solve error = " << solve_error << '\n';

    return 0;
}
