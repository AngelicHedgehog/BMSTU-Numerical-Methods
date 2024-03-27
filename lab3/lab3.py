import matplotlib.pyplot as plt 
import numpy as np
import math

zₓ = {
    1   : 0.16,
    1.5 : 0.68,
    2   : 1.96,
    2.5 : 2.79,
    3   : 3.80,
    3.5 : 6.81,
    4   : 9.50,
    4.5 : 15.60,
    5   : 24.86, 
}
n = len(zₓ) - 1
xₒ = min(zₓ)
xₙ = max(zₓ)
yₒ = zₓ[xₒ]
yₙ = zₓ[xₙ]

def z_table(x: float) -> float:
    if x in zₓ:
        return zₓ[x]
    if x <= xₒ:
        return yₒ
    if x >= xₙ:
        return yₙ
    last_x = int(x * 2) / 2
    return (zₓ[last_x] + zₓ[last_x + .5]) / 2

### 1
x = np.arange(xₒ, xₙ, 0.01)
# plt.plot(x, list(map(z_table, x)))
plt.plot(*zip(*zₓ.items()))


### 2
xₐ = (xₒ + xₙ) / 2
xⱼ = (xₒ * xₙ) ** .5
xₕ = 2 / (1 / xₒ + 1 / xₙ)
print(f"{xₐ=}\n{xⱼ=}\n{xₕ=}\n")

yₐ = (yₒ + yₙ) / 2
yⱼ = (yₒ * yₙ) ** .5
yₕ = 2 / (1 / yₒ + 1 / yₙ)
print(f"{yₐ=}\n{yⱼ=}\n{yₕ=}\n")

z_xₐ = z_table(xₐ)
z_xⱼ = z_table(xⱼ)
z_xₕ = z_table(xₕ)
print(f"{z_xₐ=}\n{z_xⱼ=}\n{z_xₕ=}\n")

δ1 = abs(z_xₐ - yₐ)
δ2 = abs(z_xⱼ - yⱼ)
δ3 = abs(z_xₐ - yⱼ)
δ4 = abs(z_xⱼ - yₐ)
δ5 = abs(z_xₕ - yₐ)
δ6 = abs(z_xₐ - yₕ)
δ7 = abs(z_xₕ - yₕ)
δ8 = abs(z_xₕ - yⱼ)
δ9 = abs(z_xⱼ - yₕ)
δk = min(δ1, δ2, δ3, δ4, δ5, δ6, δ7, δ8, δ9)
print(f"{δ1=}\n{δ2=}\n{δ3=}\n{δ4=}\n{δ5=}\n{δ6=}\n{δ7=}\n{δ8=}\n{δ9=}\n")
print(f"{δk=}\n")

### 3
# k = 2 =>
#   z(x) = z₂(x) = axᵇ
#   ln(z(x)) = ln(a) + b*ln(x)
#   min -> sum((ln(a) + b*ln(xᵢ) - ln(yᵢ))²)

A = sum(math.log(xᵢ) ** 2 for xᵢ in zₓ.keys())
B = sum(math.log(xᵢ) for xᵢ in zₓ.keys())
D1 = sum(math.log(yᵢ) * math.log(xᵢ) for xᵢ, yᵢ in zₓ.items())
D2 = sum(math.log(yᵢ) for yᵢ in zₓ.values())

a = math.e ** (
    (
        D2 -
        (D1 * (n + 1) - D2 * B) * B /
        (A * (n + 1) - B ** 2)
    ) / (n + 1)
)
b = (
    (D1 * (n + 1) - D2 * B) /
    (A * (n + 1) - B ** 2)
)

SKU = math.sqrt(sum(
    (math.log(a) + b * math.log(xᵢ) - math.log(yᵢ)) ** 2
    for xᵢ, yᵢ in zₓ.items()
))

SKO = SKU / math.sqrt(n)
print(f"{SKO=}")

def z_new(x: float) -> float:
    return a * x ** b
plt.plot(x, list(map(z_new, x)))

plt.show()