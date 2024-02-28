#include <cmath>
#include <numbers>
#include <iostream>

#include "../lab1/lib/Matrix.cpp"

// Вариант 4. [0, π]. f(x) = 2x*cos(x/2)

#define EPSILON .001

auto f(double x) -> double {
    return 2 * x * std::cos(x / 2);
}

auto f_antiderivative(double x) -> double {
    return 4 * x * std::sin(x / 2) + 8 * std::cos(x / 2);
}

auto main() -> int {
    double a = 0, b = std::numbers::pi;
    double I = f_antiderivative(b) - f_antiderivative(a);
    
    Matrix<double, 4, 3> dataTable{};

    // метод средних прямоугольников
    dataTable.at(0, 0) = 1;                         // n
    dataTable.at(1, 0) = f((a + b) / 2) * (b - a);  // I_last
    do {
        double n = dataTable.at(0, 0) + 1;
        double h = (b - a) / n;

        double I = 0;
        for (std::size_t i = 1; i != n + 1; ++i) {
            I += f(a + h * (i - .5));
        }
        I *= h;

        dataTable.at(0, 0) = n;
        dataTable.at(2, 0) = (I - dataTable.at(1, 0)) / (std::pow(2, n) - 1);
        dataTable.at(1, 0) = I;
    } while (abs(dataTable.at(2, 0)) > EPSILON);
    dataTable.at(3, 0) = dataTable.at(1, 0) + dataTable.at(2, 0);
    
    // метод трапеций
    dataTable.at(0, 1) = 1;                             // n
    dataTable.at(1, 1) = ((f(a) + f(b)) / 2) * (b - a); // I_last
    do {
        double n = dataTable.at(0, 1) + 1;
        double h = (b - a) / n;

        double I = (f(a) + f(b)) / 2;
        for (std::size_t i = 1; i != n; ++i) {
            I += f(a + h * i);
        }
        I *= h;

        dataTable.at(0, 1) = n;
        dataTable.at(2, 1) = (I - dataTable.at(1, 1)) / (std::pow(2, n) - 1);
        dataTable.at(1, 1) = I;
    } while (abs(dataTable.at(2, 1)) > EPSILON);
    dataTable.at(3, 1) = dataTable.at(1, 1) + dataTable.at(2, 1);
    
    // метод Симпсона
    dataTable.at(0, 2) = 1;                     // n
    dataTable.at(1, 2) = (f(a) + 4 * f((a + b) / 2) + f(b))
                       * (b - a) / 6;           // I_last
    do {
        double n = dataTable.at(0, 2) + 1;
        double h = (b - a) / (2 * n);

        double I = f(a) - f(b);
        for (std::size_t i = 1; i != n + 1; ++i) {
            I += 4 * f(a + h * (2 * i - 1));
            I += 2 * f(a + h * 2 * i);
        }
        I = I * h / 3;

        dataTable.at(0, 2) = n;
        dataTable.at(2, 2) = (I - dataTable.at(1, 2)) / (std::pow(2, n) - 1);
        dataTable.at(1, 2) = I;
    } while (abs(dataTable.at(2, 2)) > EPSILON);
    dataTable.at(3, 2) = dataTable.at(1, 2) + dataTable.at(2, 2);

    std::cout << "I = " << I << '\n';
    std::cout << "\t\taverage\t\ttrapez\t\tSimpson\n";
    std::cout << "n\t\t"
              << dataTable.at(0, 0) << "\t\t"
              << dataTable.at(0, 1) << "\t\t"
              << dataTable.at(0, 2) << '\n'
              << "I*_(h/2)\t"
              << dataTable.at(1, 0) << "\t\t"
              << dataTable.at(1, 1) << "\t\t"
              << dataTable.at(1, 2) << '\n'
              << "R\t\t"
              << dataTable.at(2, 0) << "\t"
              << dataTable.at(2, 1) << "\t"
              << dataTable.at(2, 2) << '\n'
              << "I*_(h/2)+R\t"
              << dataTable.at(3, 0) << "\t\t"
              << dataTable.at(3, 1) << "\t\t"
              << dataTable.at(3, 2) << '\n';
}
