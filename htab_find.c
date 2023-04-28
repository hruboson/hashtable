/**
 * @file    htab_find.c
 * @brief   Řešení IJC-DU2, příklad 2)
 *          Implementace htab_find
 * @author  Ondřej Hruboš (xhrubo01), FIT
 * @date    14.04.2023
 */

#include <stdio.h>

#include "htab.h"
#include "htab_struct.h"
#include "string.h"

/**
 * @brief nalezne záznam s odpovídajícím klíčem
 * @return nalezenou dvojici
 */
htab_pair_t *htab_find(const htab_t *t, htab_key_t key) {
    size_t hash = htab_hash_function(key);

#ifdef HASH_MULTIP
    size_t index = hash_multip(hash);
#else
    size_t index = (hash % t->buckets_count);
#endif

    htab_item_t *tmp = t->buckets[index];
    if (tmp) {
        if (strcmp(tmp->data.key, key) == 0) {
            return &(tmp->data);
        }

        while (tmp->next) {
            tmp = tmp->next;
            if (strcmp(tmp->data.key, key) == 0) {
                return &(tmp->data);
            }
        }
    }

    return NULL;
}