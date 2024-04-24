from linear_solve import *
from math import sin, cos

det_2 = lambda A: A[0][0] * A[1][1] - A[1][0] * A[0][1]

f1 = lambda x, y: cos(x) + y - 1.5
f1_x = lambda x, y: -sin(x)
f1_y = lambda x, y: 1

f2 = lambda x, y: 2 * x - sin(y - .5) - 1
f2_x = lambda x, y: 2
f2_y = lambda x, y: -cos(y - .5)

f = lambda x, y: (f1(x, y), f2(x, y))
f_ = lambda x, y: (
    (f1_x(x, y), f1_y(x, y)),
    (f2_x(x, y), f2_y(x, y)))
# def f_inv(x, y):
#     ((a, b), (c, d)) = f_(x, y)
#     D = det_2((a, b), (c, d)))
#     return (
#         (d / D, -b / D),
#         (-c / D, a / D))

def find_step(x, y):
    A = f_(x, y)
    f1_v, f2_v = f(x, y)
    b = (-f1_v, -f2_v)
    det_v = det_2(A)
    det_1_v = det_2((
        (b[0], A[0][1]),
        (b[1], A[1][1])))
    det_2_v = det_2((
        (A[0][0], b[0]),
        (A[1][0], b[1])))
    return (det_1_v / det_v, det_2_v / det_v)

x_k, y_k = 0, 0
x_k_, y_k_ = x_k + 1, y_k + 1
iter_count = 0
while( max(abs(x_k - x_k_), abs(y_k - y_k_)) > .01 ):
    iter_count += 1
    x_k_, y_k_ = x_k, y_k
    x_step, y_step = find_step(x_k, y_k)
    x_k += x_step
    y_k += y_step

print(f"x_{iter_count} = {x_k}")
print(f"y_{iter_count} = {y_k}")
