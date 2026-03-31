# Tomás Achával Berzero, Parcial 1 MyS 2025, FaMAF.
from numpy.random import uniform
from math import sqrt

# Ejercicio 1
def monte_carlo(N):

    f = lambda x : sqrt(x + sqrt(x))
    h = lambda y : 6 * f(1 + 6 * y)

    val = 0
    for _ in range(N):
        U = uniform()
        val += h(U)
    
    return val/N

print("\n***** Ejercicio 1b *****")
for n in [1000, 10000, 100000]:
    print(f"N° de sim = {n}, Integral ~ {monte_carlo(n)}")

# Ejercicio 2
def juego():
    N, sum = 0, 0

    # suma acumulada de realizaciones de v.a.i. uniformes en (0,1)
    # hasta que el valor total supere 1 (acierto)
    while sum < 1:
        sum += uniform()
        N += 1
    
    return N

def pares(N):
    impares = 0

    # simulación de jugar N veces, contando la cantidad de veces
    # en las que el resultado es impar
    for _ in range(N):
        impares += (juego() % 2) # = 1 si juego() es impar, = 0 c.c.

    return impares/N

print("\n***** Ejercicio 2b *****")
for n in [100, 1000, 10000]:
    print(f"N° de sim = {n}, p ~ {pares(n)}")
