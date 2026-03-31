# Tomás Achával Berzero, Parcial 3 MyS 2025, FaMAF
from math import exp, log
from numpy.random import uniform

datos = [15.22860536, 40.60145536, 33.67482894, 44.03841737, 15.69560109, 16.2321714, 25.02174735, 30.34655637, 3.3181228, 5.69447539, 10.1119561, 49.10266584, 3.6536329, 35.82047148, 3.37816632, 36.72299321, 50.67085322, 3.25476304, 20.12426236, 20.2668814, 17.49593589, 2.70768636, 14.77332745, 1.72267967, 23.34685662, 8.46376635, 9.18330789, 9.97428217, 2.33951729, 137.51657441, 9.79485269, 10.40308179, 1.57849658, 6.26959703, 4.74251574, 1.53479053, 34.74136011, 27.47600572, 9.1075566, 1.88056595, 27.59551348, 6.82283137, 12.45162807, 28.01983651, 0.36890593, 7.82520791, 3.17626161, 46.91791271, 38.08371186, 41.10961135]
datos.sort()

n = len(datos)

def estadistico(muestra, F=lambda x:x):
    return max(
        max(j/n - F(muestra[j-1]), F(muestra[j-1]) - (j-1)/n)
        for j in range(1,n+1)
    )

lambda_expon = 0.05
FDA_expon = lambda x : 1 - exp(-lambda_expon*x)
d_KS = estadistico(datos, FDA_expon)

def simUniformes(Niter):
    pvalor = 0

    for _ in range(Niter):
        uniformes = uniform(size=n)
        uniformes.sort()

        if estadistico(uniformes) > d_KS:
            pvalor += 1

    return pvalor/Niter

def generate_sample(n):
    return [-log(1 - uniform()) / lambda_expon for _ in range(n)]

def simExponenciales(Niter):
    pvalor = 0

    for _ in range(Niter):
        expons = generate_sample(n)
        expons.sort()

        if estadistico(expons, FDA_expon) > d_KS:
            pvalor += 1

    return pvalor/Niter

Nsim = 10000
print("***** Ejercicio 2 *****")
print(f"Estadístico: {d_KS}")
print(f"p-valor con uniformes ~ {simUniformes(Nsim)}")
print(f"p-valor con exponenciales ~ {simExponenciales(Nsim)}")



from scipy.stats import binom

datos = [38, 144, 342, 287, 164, 25]
n = sum(datos) # numero total de observaciones
k = 6 # valores posibles de la variable
n_binom = 5

# estimación inicial del parámetro p
p_estim = sum(i*datos[i] for i in range(len(datos)))/(n_binom*n)

# probabilidades teóricas de cada valor de Bin(5, p_estim)
probs = [binom.pmf(i, n_binom, p_estim) for i in range(k)]

# valores posibles de la variable
VAR_RANGE = range(k)

# estimador del parámetro p
def get_param(muestra):
    return sum(muestra)/(n_binom*n)

# frecuencias observadas en una muestra
def get_freqs(sample):
    return [sample.count(v) for v in VAR_RANGE]

# probabilidades de cada valor para Bin(5, p)
def get_probs(p):
    return [binom.pmf(v, n_binom, p) for v in VAR_RANGE]

# genera una muestra de n variables Bin(5, p_estim)
def get_sample():
    return list(binom.rvs(n_binom, p_estim, size=n))

# estadístico del test
def estadistico(N, p):
    return sum(
        (obs - n*esp)**2/(n*esp)
        for obs, esp in zip(N, p)
    )

freqs = datos # los datos son las frecuencias observadas
probs = get_probs(p_estim)

# valor del estadístico en los datos observados
t = estadistico(freqs, probs)

def sim(Nsim):
    p_valor = 0
    for _ in range(Nsim):
        muestra = get_sample()
        p_sim = get_param(muestra)
        
        freq_sim = get_freqs(muestra)
        probs_sim = get_probs(p_sim)

        if estadistico(freq_sim, probs_sim) >= t:
            p_valor += 1
    
    return p_valor/Nsim

N = 1000
print("\n***** Ejercicio 3 *****")
print(f"Estadístico: {t}")
print(f"p-valor por simulación ~ {sim(N)}")



from numpy.random import uniform
from math import sqrt
from scipy.stats import norm


z = norm.ppf(1 - 0.025)
# Niter=0 indica que se debe frenar cuando el semi-ancho del IC(95%) es menor a 0.001
# si Niter != 0, se realizan Niter iteraciones.
def montecarlo(f, Niter=0):
    media = f(2 + uniform()) # evalúo la funcion en puntos uniformemente distribuidos en (2, 3)
    SS, n = 0, 1

    while (n < 100 or z * sqrt(SS/n) >= 0.001)*(not Niter) or (n < Niter):
        n += 1
        media_ant = media
        media = media_ant + (f(2 + uniform()) - media_ant) / n
        SS = SS * (1 - 1 /(n-1)) + n*(media - media_ant)**2
    
    return n, media, sqrt(SS), z * sqrt(SS/n)

def printInfo(n, media, S, L):
    print()
    print("-"*30)
    print(f"Datos generados : {n}"
        f"\nIntegral i): {media}"
        f"\nS = {S}"
        f"\nIC 95% = [{media - L}, {media + L}]"
    )
    print("-"*30)


f = lambda x : exp(-x) * (1 - x**4)

print("\n***** Ej 4 *****")
for N in [1000, 5000, 7000, 0]:
    n, I, S, semiancho_IC = montecarlo(f, N)

    printInfo(n, I, S, semiancho_IC)