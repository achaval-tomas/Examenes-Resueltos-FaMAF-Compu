/*
  @file array_helpers.h
  @brief defines array helpers methods. These methods operates over multidimensional array of prices
*/
#ifndef _ARRAY_HELPERS_H
#define _ARRAY_HELPERS_H
#include <stdbool.h>
#include "bakery_product.h"

#define CITIES 5
#define SEASONS 2

typedef BakeryProduct BakeryProductTable[CITIES][SEASONS];

/**
 * @brief Write the content of the array 'a' into stdout.
 * @param[in] a array to dump in stdout
 */
void array_dump(BakeryProductTable a);

/**
 * @brief calculates best bakery/season profit
 * @param[in] a array with data
 */
unsigned int best_profit(BakeryProductTable a);

/**
 * @brief reads an array of prices information from file
 * @details
 *
 *  Each element is read from the file located at 'filepath'.
 *  The file must exist in disk and must have its contents in a sequence of
 *  lines, each with the following format:
 *
 *   ##<city_number>??<season_number> (<f_c>,<f_p>) (<y_c>,<y_p>) (<b_c>,<b_p>) <s_v>
 *
 *   Those elements are copied into the multidimensional array 'a'.
 *   The dimensions of the array are given by the macros noted above.
 *
 * @param a array which will contain read file
 * @param filepath file with prices data
 */

void array_from_file(BakeryProductTable a, const char *filepath);

#endif
