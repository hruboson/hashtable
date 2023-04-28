/**
 * @file    htab_free.c
 * @brief   Řešení IJC-DU2, příklad 2)
 *          Implementace destruktoru tabulky
 * @author  Ondřej Hruboš (xhrubo01), FIT
 * @date    14.04.2023
 */

#include "htab.h"
#include <stdlib.h>

/**
 * @brief destruktor tabulky, zruší všechny záznamy včetně tabulky samotné
 */
void htab_free(htab_t *t){
    htab_clear(t);
    free(t);
    t = NULL;
}