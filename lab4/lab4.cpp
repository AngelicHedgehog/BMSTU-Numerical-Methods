#include <cmath>
#include <numbers>
#include <iostream>
#include <iomanip>

#include "../lab1/lab1.cpp"

// lab 14

// test:
// y = eˣ, x ∈ [0, 1], y(0)=e⁰=1, y(1)=e
// y"(x) + 5y'(x) - 4y(x) = 2eˣ

#define N 10

auto main() -> int {
    auto y = [](double x){return std::pow(std::numbers::e, x);};

    double a = y(0);
    double b = y(1);

    // y"(x) + p(x)*y'(x) + q(x)*y(x) = f(x)
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
    SLAEright.at(0) -= a * (1 - h / 2 * p_i(1));
    SLAEright.at(N - 2) -= b * (1 + h / 2 * p_i(N - 1));
    Vector<double, N - 1> SLAEsolve = findSolve(SLAE, SLAEright);

    Vector<double, N + 1> y_i{};
    y_i.at(0) = a;
    y_i.at(N) = b;
    for (std::size_t i = 1; i != N; ++i) {
        y_i.at(i) = SLAEsolve.at(i - 1);
    }

    // ||y - y˜|| = max|y(xᵢ) - yᵢ|
    // double solve_error = 0;
    std::cout
        << std::setw(4) << " i"
        << std::setw(12) << " y(x_i)"
        << std::setw(12) << " y_i"
        << std::setw(16) << " |y(x_i) - y_i|" << '\n';
    std::cout << std::setw(45) << std::setfill('-') << '\n';
    std::cout << std::setfill(' ');
    for (std::size_t i = 0; i != N + 1; ++i) {
        double error_i = std::abs(y(x_i(i)) - y_i.at(i));
        // solve_error = std::max(solve_error, error_i);
        std::cout
            << std::setw(4) << i
            << std::setw(12) << y(x_i(i))
            << std::setw(12) << y_i.at(i)
            << std::setw(16) << error_i << '\n';
    }

    return 0;
}
