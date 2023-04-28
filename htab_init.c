/**
 * @file    htab_init.c
 * @brief   Řešení IJC-DU2, příklad 2)
 *          Implementace konstruktoru tabulky
 * @author  Ondřej Hruboš (xhrubo01), FIT
 * @date    14.04.2023
 */

#include "htab.h"
#include "htab_struct.h"

#include <stdlib.h>

htab_t *htab_init(const size_t n) {
    htab_t *table = malloc((sizeof(htab_t) + (sizeof(htab_item_t) * n)));

    if (!table) {
        return NULL;
    }

    table->size = 0;
    table->buckets_count = n;

    for (size_t i = 0; i < n; i++) {
        table->buckets[i] = NULL;
    }

    return table;
}