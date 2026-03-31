import math
from time import time

# Parte 1: Generadores de numeros aleatorios adaptados a punto flotante en (0, 1)

def LCG(seed):
    """
    Generador congruencial lineal
    """
    value = seed
    a = 16807
    m = 2**31 - 1

    while True:
        value = (a * value) % m
        yield value / m


def XORShift_int(seed):
    """
    Generador XORShift de 32 bits
    """
    value = seed
    mask_32b = 0xFFFFFFFF

    while True:
        value = (value ^ (value << 13)) & mask_32b
        value = (value ^ (value >> 17)) & mask_32b
        value = (value ^ (value << 5)) & mask_32b
        yield value


def XORShift(seed):
    gen = XORShift_int(seed)
    while True:
        yield next(gen) / (2**32)


def Xoshiro(seed):
    """
    Generador xoshiro128**
    Basado en: https://xoshiro.di.unimi.it/xoshiro128starstar.c
    """
    mask_32b = 0xFFFFFFFF

    # Generar los 4 estados a partir de la seed, utilizando XORShift.
    s_gen = XORShift_int(seed)
    s = [next(s_gen) for _ in range(4)]

    def rotl(x, k):
        """Rotación a izquierda de 32 bits"""
        return ((x << k) & mask_32b) | (x >> (32 - k))

    while True:
        result = (rotl(s[1] * 5, 7) * 9) & mask_32b

        t = (s[1] << 9) & mask_32b

        s[2] ^= s[0]
        s[3] ^= s[1]
        s[1] ^= s[2]
        s[0] ^= s[3]

        s[2] ^= t
        s[3] = rotl(s[3], 11)

        yield result / 2**32


# Parte 2: Simulación y Análisis

def integral_monte_carlo(gen, d, nsim):
    def f(xs):
        return math.prod(math.exp(-(x**2)) for x in xs)

    sum = 0
    for _ in range(nsim):
        xs = [next(gen) for _ in range(d)]
        sum += f(xs)

    integral = sum / nsim
    return integral


def integral_exacta(d):
    return (0.5 * math.sqrt(math.pi) * math.erf(1)) ** d


def calcular_ecm(x0, xs):
    return sum((x0 - x) ** 2 for x in xs) / len(xs)


def calcular_varianza_muestral(xs):
    m = sum(xs) / len(xs)
    return sum((x - m) ** 2 for x in xs) / (len(xs) - 1)


def test_generadores(seed, M=100):
    generators = [
        ("LCG", LCG(seed)),
        ("XORShift", XORShift(seed)),
        ("Xoshiro", Xoshiro(seed)),
    ]

    print("Generador, d, N, ECM, Var, Tiempo")
    for name, gen in generators:
        for d in [2, 5, 10]:
            for N in [10**4, 10**5, 10**6]:
                start = time()
                data = [integral_monte_carlo(gen, d, N) for _ in range(M)]
                elapsed = time() - start

                exacto = integral_exacta(d)
                ecm = calcular_ecm(exacto, data)
                var = calcular_varianza_muestral(data)

                print(name, d, N, ecm, var, elapsed, sep=", ")


"""
    Para obtener los resultados de un test, se debe seleccionar
    una semilla s_0 para los generadores, un tamaño de muestra
    M para las estimaciones de ECM y Var del estimador
    y luego correr

    test_generadores(s_0, M)

    que mostrará en consola los resultados obtenidos.

    El informe del trabajo fue realizado con s_0 = 1239 y M = 100.
"""
test_generadores(1239, 100)