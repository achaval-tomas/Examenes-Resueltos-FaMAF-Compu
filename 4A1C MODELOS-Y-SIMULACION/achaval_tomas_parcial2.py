from numpy.random import uniform


print("---------- Ejercicio 1 ----------")
def ejercicio1():
    while True:
        Y = uniform()
        if uniform() < 16*(Y**2 - 2*Y**3 + Y**4):
            return Y
        
N = 10000
print(f"E(X) ~ {sum(ejercicio1() for _ in range(N))/N}")

print("---------- Ejercicio 2 ----------")

def codigoX(p):
    X = 10
    prob = p
    F = prob
    U = uniform()
    while U >= F:
        prob = (1-p)*prob
        F += prob
        X += 1
    return X

N = 10000
print(f"E(X) ~ {sum(codigoX(0.5) for _ in range(N))/N}")