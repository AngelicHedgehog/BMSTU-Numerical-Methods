#include <iostream>
#include <numbers>
#include <cmath>

// Лаба 18
// Страница 49
// Вариант 4.1
// f(x) = exp(x₁+x₂²) + (x₁+x₂)²
// x₀(1,1)

#define EPSILON 0.001

struct CoordX {
    double x1;
    double x2;

    CoordX operator-(const CoordX& other) const {
        return {x1 - other.x1, x2 - other.x2};
    }

    CoordX operator*(double t) const {
        return {x1 * t, x2 * t};
    }

    CoordX operator-() const {
        return {-x1, -x2};
    }
};

// исходная фнукция
double f(const CoordX& x) {
    return
        std::pow(std::numbers::e, x.x1 + std::pow(x.x2, 2))
        + std::pow(x.x1 + x.x2, 2);
}

// δf/δx₁
double f_x1(const CoordX& x) {
    return
        std::pow(std::numbers::e, x.x1 + std::pow(x.x2, 2)) +
        2 * (x.x1 + x.x2);
}


// δf/δx₂
double f_x2(const CoordX& x) {
    return
        2 * x.x2 *
            std::pow(std::numbers::e, x.x1 + std::pow(x.x2, 2)) +
        2 * (x.x1 + x.x2);
}

// δ²f/δx₁²
double f_x1_x1(const CoordX& x) {
    return
        std::pow(std::numbers::e, x.x1 + std::pow(x.x2, 2)) +
        2;
}

// δ²f/δx₁δx₂
double f_x1_x2(const CoordX& x) {
    return
        2 * x.x2 *
            std::pow(std::numbers::e, x.x1 + std::pow(x.x2, 2)) +
        2;
}

// δ²f/δx₂²
double f_x2_x2(const CoordX& x) {
    return
        2 * std::pow(std::numbers::e, x.x1 + std::pow(x.x2, 2)) +
        4 * std::pow(x.x2, 2) *
            std::pow(std::numbers::e, x.x1 + std::pow(x.x2, 2)) +
        2;
}

// grad(f(xᵏ))
CoordX gradient_f(const CoordX& x) {
    return {f_x1(x), f_x2(x)};
}

// φₖ(t)
double fi_k(const CoordX& x_k, double t) {
    return f(x_k - gradient_f(x_k) * t);
}

// φₖ'(0)
double fi_k_t_zero(const CoordX& x_k) {
    return  -std::pow(f_x1(x_k), 2) +
            -std::pow(f_x2(x_k), 2);
}


// φₖ"(0)
double fi_k_t_t_zero(const CoordX& x_k) {
    return  f_x1_x1(x_k) * std::pow(f_x1(x_k), 2) +
        2 * f_x1_x2(x_k) * f_x1(x_k) * f_x2(x_k) +
            f_x2_x2(x_k) * std::pow(f_x2(x_k), 2);
}

int main() {
    CoordX x_k{1, 1};
    CoordX gradient = gradient_f(x_k);
    std::size_t iter_count = 0;

    while (std::max(std::abs(gradient.x1), std::abs(gradient.x2)) >= EPSILON) {
        double t_star = -fi_k_t_zero(x_k) / fi_k_t_t_zero(x_k);
        x_k = x_k - gradient * t_star;
        gradient = gradient_f(x_k);

        ++iter_count;
    }

    std::cout << "Iterations count: " << iter_count << '\n';
    std::cout   << "(x1, x2) = (" << x_k.x1 << ", " << x_k.x2 << ")\n"
                << "Analitic solve: (-0.791, .5).\n";

    return 0;
}
