-- Ejercicio 1)
-- a)
type Titulo = String
type Artista = String
type Duracion = Int

data Genero = Rock | Blues | Pop | Jazz
data Cancion = Tema Titulo Artista Genero Duracion | Publicidad Duracion

-- b) 
mismo_genero :: Genero -> Genero -> Bool
mismo_genero Rock Rock = True
mismo_genero Blues Blues = True
mismo_genero Pop Pop = True
mismo_genero Jazz Jazz = True
mismo_genero a b = False

-- c)
duracion_de :: Cancion -> Duracion
duracion_de (Publicidad c) = c
duracion_de (Tema a b c d) = d

-- d)
-- Necesito instanciar Eq para poder hacer comparacion utilizando el operador "<=".
instance Eq Cancion where
    c1 == c2 = duracion_de c1 == duracion_de c2
instance Ord Cancion where
    c1 <= c2 = duracion_de c1 <= duracion_de c2

-- Ejercicio 2)
solo_genero :: [Cancion] -> Genero -> [Titulo]
solo_genero [] gi = []
solo_genero ((Publicidad c):cs) gi = solo_genero cs gi
solo_genero ((Tema a b c d):cs) gi | mismo_genero gi c = a:(solo_genero cs gi) 
                                   | otherwise = solo_genero cs gi

-- Ejercicio 3)
data ListaAsoc a b = Vacia | Nodo a b (ListaAsoc a b)

-- b debe ser de tipo Num y Ord para poder utilizar los operadores "+" y ">".
la_suma_mayores :: (Num b, Ord b) => ListaAsoc a b -> b -> b
la_suma_mayores Vacia x = 0
la_suma_mayores (Nodo a b c) x | b > x = b + la_suma_mayores c x
                               | otherwise = la_suma_mayores c x

-- Ejercicio 4)
data Arbol a = Hoja | Rama (Arbol a) a (Arbol a)

a_listar :: Arbol a -> [a]
a_listar Hoja = []
a_listar (Rama a b c) = b:(a_listar a ++ a_listar c)

-- b) a_listar (Rama (Rama Hoja 5 Hoja) 8 (Rama Hoja 7 (Rama Hoja 9 Hoja)))
-- c) [8,5,7,9]