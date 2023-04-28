/**
 * @file    htab_clear.c
 * @brief   Řešení IJC-DU2, příklad 2)
 *          Implementace htab_clear
 * @author  Ondřej Hruboš (xhrubo01), FIT
 * @date    14.04.2023
 */

#include <stdlib.h>

#include "htab.h"
#include "htab_struct.h"

/**
 * @brief ruší všechny záznamy
 */
void htab_clear(htab_t *t) {
    for (size_t i = 0; i < t->buckets_count; i++) {
        if (t->buckets[i]) {
            htab_item_t *tmp = t->buckets[i];
            while (tmp) {
                htab_item_t *next = tmp->next; 
                free((char *)tmp->data.key);
                free(tmp);
                tmp = next;
            }
            tmp = NULL;
        }
    }
}