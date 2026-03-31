/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"

static const int EXPECTED_DIM_VALUE = 2;

static const char* CITY_NAMES[CITIES] = {
    "Cordoba", "Rosario", "Posadas", "Tilcara", "Bariloche"};
static const char* SEASON_NAMES[SEASONS] = {"low", "high"};

void array_dump(BakeryProductTable a)
{
    for (unsigned int city = 0u; city < CITIES; ++city)
    {
        for (unsigned int season = 0u; season < SEASONS; ++season)
        {
            fprintf(stdout, "%s in %s season: flour (%u,%u) Yeast (%u,%u) Butter (%u,%u) Sales value %u",
                    CITY_NAMES[city], SEASON_NAMES[season], a[city][season].flour_cant,
                    a[city][season].flour_price, a[city][season].yeast_cant,
                    a[city][season].yeast_price, a[city][season].butter_cant,
                    a[city][season].butter_price, a[city][season].sale_value);
            fprintf(stdout, "\n");
        }
    }
}

unsigned int best_profit(BakeryProductTable a)
{
    unsigned int max_profit = 0u;
    unsigned int totalprofit = 0u;
    
        for(unsigned int city = 0u; city<CITIES; city++){
            for(season_t season = 0u; season<SEASONS; season++){
            
            /* Calculo la ganancia de cada ciudad y temporada en la variable totalprofit. */
               totalprofit = (a[city][season].sale_value) - (
                             (a[city][season].flour_cant)*(a[city][season].flour_price) +
                             (a[city][season].yeast_cant)*(a[city][season].yeast_price) +
                             (a[city][season].butter_cant)*(a[city][season].butter_price));
            
            /* Si la ganancia de la ciudad y temporada actual superan la anterior
            maxima ganancia registrada, entonces la maxima ganancia es actualizada. */
               if (totalprofit > max_profit){max_profit = totalprofit;}
            }

        }
    return max_profit;
}

void array_from_file(BakeryProductTable array, const char* filepath)
{
    FILE* file = NULL;

    file = fopen(filepath, "r");
    if (file == NULL)
    {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    /* Mientras no termine la lectura del archivo, continua el ciclo. */
    while (!feof(file))
    {
        season_t season;
        unsigned int city;
        int res = fscanf(file, "##%u??%u ", &city, &season);
        if (res != EXPECTED_DIM_VALUE)
        {
            fprintf(stderr, "Invalid file.\n");
            exit(EXIT_FAILURE);
        }
        
        /* La variable info almacena todos los datos para cada ciudad y temporada
        y luego es cargada al array multidimensional en la posicion correspondiente. */
        BakeryProduct info = bakery_product_from_file(file);
        array[city][season] = info;
            
        ++i;
    }
    
   /* Aseguro antes de finalizar la funcion que la cantidad de lineas leidas del archivo sea 
   exactamente igual a la cantidad total de ciudades, cada una con sus temporadas. */
    if (i!=CITIES*SEASONS){
       fprintf(stderr, "File is incomplete or overloaded.\n");
       exit(EXIT_FAILURE);
    }
        
    fclose(file);
}
