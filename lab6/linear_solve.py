import matplotlib.pyplot as plt 
import numpy as np
import math
from typing import Callable

def find_solve_splitting(
    f: Callable[[float], float],
    a: float,
    b: float,
    eps: float,
) -> (float, int):
    if( not(a <= b and f(a) * f(b) < 0) ):
        return None

    x = (a + b) / 2

    iter_count = 0
    while( b - a > 2 * eps ):
        iter_count += 1
        if( f(a) * f(x) < 0 ):
            b = x
        else:
            a = x
        x = (a + b) / 2

    return (x, iter_count)

def find_solve_newton(
    f: Callable[[float], float],
    f_: Callable[[float], float],
    f__: Callable[[float], float],
    a: float,
    b: float,
    eps: float,
) -> (float, int):
    if( not(a <= b and f(a) * f(b) < 0) ):
        return None

    sgn = lambda x: x and 1 if( x > 0 ) else -1

    x_k = a if( f(a) * f__(a) > 0 ) else b
    x_k_ = x_k

    iter_count = 0
    while( f(x_k) * f(x_k + sgn(x_k - x_k_) * eps) >= 0 ):
        iter_count += 1
        x_k_ = x_k
        if( f_(x_k) == 0 ):
            return None
        x_k = x_k - f(x_k) / f_(x_k)

    return (x_k, iter_count)


def main():
    eps = .001
    A, B, C, D = 2, 9, 0, -21
    f = lambda x: A * x ** 3 + B * x ** 2 + C * x + D
    f_ = lambda x: 3 * A * x ** 2 + 2 * B * x + C
    f__ = lambda x: 6 * A * x + 2 * B

    derive_zeros = []
    if( B ** 2 - 3 * A * C >= 0 ):
        derive_zeros += [
            (-B - (B ** 2 - 3 * A * C) ** .5)
                / (3 * A),
            (-B + (B ** 2 - 3 * A * C) ** .5)
                / (3 * A),
        ]
    if( A != 0 ):
        derive_zeros.append(-B / (3 * A))
    der_min = min(derive_zeros)
    der_max = max(derive_zeros)
    derive_zeros += [
        der_min - (der_max - der_min),
        der_max + (der_max - der_min),
    ]
    derive_zeros.sort()

    x = np.arange(derive_zeros[0], derive_zeros[-1], 0.01)
    plt.plot(x, list(map(f, x)))

    for a, b in zip(derive_zeros[:-1], derive_zeros[1:]):
        print(f'[{a}, {b}] -> [')
        splitting = find_solve_splitting(
            f, a, b, eps
        )
        if( splitting ):
            print('\tsplitting: (x={:06f}, iter={:03d}) '.format(*splitting))
        newton = find_solve_newton(
            f, f_, f__, a, b, eps
        )
        if( newton ):
            print('\tnewton:    (x={:06f}, iter={:03d})'.format(*newton))
        print(']')

    plt.show()

if __name__ == '__main__':
    main()
