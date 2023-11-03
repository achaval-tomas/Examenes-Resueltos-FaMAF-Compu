/*
  @file bakery_product.h
  @brief Defines bakery products information
*/

#ifndef _BAKERY_PRODUCT_H
#define _BAKERY_PRODUCT_H
#define EXPECTED_PRODUCT_FILE_FORMAT "(%u,%u) (%u,%u) (%u,%u) %u "
typedef enum
{
    low,
    high
} season_t;

#include <stdio.h>

/** @brief Type used to represent bakery product data.*/
typedef struct _product
{
    unsigned int flour_cant;
    unsigned int flour_price;
    unsigned int yeast_cant;
    unsigned int yeast_price;
    unsigned int butter_cant;
    unsigned int butter_price;
    unsigned int sale_value;
} BakeryProduct;

/**
 * @brief reads bakery product data from file line
 * @details
 * Bakery product file line must contain:
 * (<unsigned int>,<unsigned int>) (<unsigned int>,<unsigned int>) (<unsigned int>,<unsigned int>) <unsigned int>
 *
 * @param[in] file Opened file stream
 * @return BakeryProduct structure which contains read information from file
 */
BakeryProduct bakery_product_from_file(FILE *file);

#endif  //_BAKERY_PRODUCT_H
