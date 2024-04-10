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

// δφₖ(t)/δt
double fi_k_t_zero(CoordX x_k) {
    return -std::pow(f_x1(x_k), 2) -std::pow(f_x1(x_k), 2);
}


// δ²φₖ(t)/δt²
double fi_k_t_t_zero(CoordX x_k) {
    return -f_x1(x_k) * (
                -f_x1_x1(x_k) * f_x1_x1(x_k - gradient_f(x_k) * t) +
                -f_x1_x2(x_k) * f_x1_x2(x_k - gradient_f(x_k) * t)
            ) +
           -f_x2(x_k) * (
                -f_x1_x2(x_k) * f_x1_x2(x_k - gradient_f(x_k) * t) +
                -f_x2_x2(x_k) * f_x2_x2(x_k - gradient_f(x_k) * t)
            );
}

// t : φₖ(t) = min(φₖ)
double min_fi_k(CoordX x_k) {
    double t_k = 0;
    double t_k_last;

    do {
        t_k_last = t_k;
        t_k = t_k_last - fi_k_t(x_k, t_k_last) / fi_k_t_t(x_k, t_k_last);
    } while (std::abs(t_k - t_k_last) <= EPSILON);

    return t_k;
}

int main() {
    CoordX x_k{1, 1};
    CoordX gradient = gradient_f(x_k);

    while (std::max(gradient.x1, gradient.x2) >= EPSILON) {
        double t_star = min_fi_k(x_k);
        x_k = x_k - gradient * t_star;
        

        std::cout << "x1 = " << x_k.x1 << "\nx2 = " << x_k.x2 << "\n\n";
    }
}