/**
 * @file    htab_erase.c
 * @brief   Řešení IJC-DU2, příklad 2)
 *          Implementace htab_erase
 * @author  Ondřej Hruboš (xhrubo01), FIT
 * @date    14.04.2023
 */

#include <stdlib.h>
#include <string.h>

#include "htab.h"
#include "htab_struct.h"

/**
 * @brief ruší záznam s klíčem key
 * @return true při úspěchu, false při neúspěchu
 */
bool htab_erase(htab_t *t, htab_key_t key) {
    size_t hash = htab_hash_function(key);
#ifdef HASH_MULTIP
    size_t index = hash_multip(hash);
#else
    size_t index = hash % t->buckets_count;
#endif

    if (strcmp(t->buckets[index]->data.key, key) == 0) {
        if (!t->buckets[index]->next) {
            free((char *)t->buckets[index]->data.key);
            t->buckets[index]->data.key = NULL;
            free(t->buckets[index]);
            t->buckets[index] = NULL;
            return true;
        } else {
            htab_item_t *tmp = t->buckets[index];
            htab_item_t *next = t->buckets[index]->next;
            free((char *)tmp->data.key);
            free(tmp);
            tmp = next;
            next = NULL;
            return true;
        }
    } else {
        return false;
    }
    return false;
}