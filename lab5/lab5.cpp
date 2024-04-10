#include <iostream>
#include <numbers>
#include <cmath>

// Лаба 18
// Страница 49
// Вариант 4
// f(x) = exp(x₁) + (x₁+x₂)²
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
double f(CoordX x) {
    return std::pow(std::numbers::e, x.x1) + std::pow(x.x1 + x.x2, 2);
}

// δf/δx₁
double f_x1(CoordX x) {
    return std::pow(std::numbers::e, x.x1) + 2 * (x.x1 + x.x2);
}


// δf/δx₂
double f_x2(CoordX x) {
    return 2 * (x.x1 + x.x2);
}

// δ²f/δx₁²
double f_x1_x1(CoordX x) {
    return std::pow(std::numbers::e, x.x1) + 2;
}

// δ²f/δx₁δx₂
double f_x1_x2(CoordX x) {
    return 2;
}

// δ²f/δx₂²
double f_x2_x2(CoordX x) {
    return 2;
}

// grad(f(xᵏ))
CoordX gradient_f(CoordX x) {
    return {f_x1(x), f_x2(x)};
}

// φₖ(t)
double fi_k(CoordX x_k, double t) {
    return f(x_k - gradient_f(x_k) * t);
}

// φₖ'(0)
double fi_k_t_zero(CoordX x_k) {
    return  -std::pow(f_x1(x_k), 2) +
            -std::pow(f_x2(x_k), 2);
}


// φₖ"(0)
double fi_k_t_t_zero(CoordX x_k) {
    return  f_x1_x1(x_k) * std::pow(f_x1(x_k), 2) +
        2 * f_x1_x2(x_k) * f_x1(x_k) * f_x2(x_k) +
            f_x2_x2(x_k) * std::pow(f_x2(x_k), 2);
}

int main() {
    CoordX x_k{1, 1};
    CoordX gradient = gradient_f(x_k);

    while (std::max(gradient.x1, gradient.x2) >= EPSILON) {
        double t_star = -fi_k_t_zero(x_k) / fi_k_t_t_zero(x_k);
        x_k = x_k - gradient * t_star;
        gradient = gradient_f(x_k);
    }

    std::cout   << "(x1, x2) = (" << x_k.x1 << ", " << x_k.x2 << ")\n"
                << "Analitic solve: (t, -t), where t tends to infinity\n";
}