/**
 * @file    htab_lookup_add.c
 * @brief   Řešení IJC-DU2, příklad 2)
 *          Implementace htab_lookup_add
 * @author  Ondřej Hruboš (xhrubo01), FIT
 * @date    14.04.2023
 */

#include <stdio.h>
#include <stdlib.h>

#include "htab.h"
#include "htab_struct.h"

#ifdef HASH_MULTIP

#define hash_a (size_t)2654435769
#define hash_w sizeof(long)  // long je typicky velikosti word (zdroj: Linux Kernel Development Second Edition, ISBN: 0-672-32720-1)
#define hash_m 3

/**
 * @brief multiplicative hashing
 * @param   x zahashovaný string
 *          m velikost tabulky

 * lze použít místo modulo hashování
*/
size_t hash_multip(size_t x, size_t m) {
    return (x * hash_a) >> (hash_w - m);
}

#endif

// todo resize
/**
 * tabulka bude fungovat bez problému i bez zvětšování, jen se může stát, že bude přístup trvat příliš dlouho kvůli kolizím
 */
#if 0
htab_t* htab_resize(htab_t *t) {
    if (t->size >= (t->buckets_count / 3)) {
        htab_t *new_table = htab_init(t->size * 2);
        for(size_t i = 0; i < t->size; i++){
            
        }
    }
}
#endif

/**
 * @brief   V tabulce t vyhledá záznam odpovídající řetězci key a
            pokud jej nalezne, vrátí ukazatel na záznam
            pokud nenalezne, automaticky přidá záznam a vrátí ukazatel
*/
htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) {
    if (!t) return NULL;
    size_t index;
#ifndef HASH_MULTIP
    index = (htab_hash_function(key) % t->buckets_count);
#else
    index = hash_multip(htab_hash_function(key), t->buckets_count);
#endif

    htab_pair_t *data = htab_find(t, key);
    if (data) {
        return data;
    }

    htab_item_t *item_ptr = t->buckets[index];

    if (!item_ptr) {
        // first item
        t->buckets[index] = malloc(sizeof(htab_item_t));

        if (!t->buckets[index]) {
            fprintf(stderr, "Error: allocating bucket at index %lu", index);
            return NULL;
        }

        t->buckets[index]->data.key = malloc((strlen(key) + 1) * sizeof(char));
        if (!t->buckets[index]->data.key) {
            free(t->buckets[index]);
            fprintf(stderr, "Error: allocating string at index %lu", index);
            return NULL;
        }
        strcpy((char *)t->buckets[index]->data.key, key);
        t->buckets[index]->data.value = 0;
        t->buckets[index]->next = NULL;
        t->size += 1;
        if (t->size >= (t->buckets_count / 3)) {
            // todo resize
        }

        return &(t->buckets[index]->data);
    } else if (item_ptr) {
        // append item to already existing item
        while (item_ptr->next) {
            item_ptr = item_ptr->next;
        }
        htab_item_t *alloc_item = malloc(sizeof(htab_item_t));  //  + (sizeof(htab_key_t) * sizeof(char) + 1)
        if (alloc_item == NULL) {
            fprintf(stderr, "Error: allocating item");
            return NULL;
        }
        item_ptr->next = alloc_item;
        alloc_item->data.key = malloc((strlen(key) + 1) * sizeof(char));
        if (!alloc_item->data.key) {
            free(alloc_item);
            fprintf(stderr, "Error: allocating item key");
            return NULL;
        }

        strcpy((char *)alloc_item->data.key, key);
        alloc_item->data.value = 0;
        alloc_item->next = NULL;
        t->size += 1;
        if (t->size >= (t->buckets_count / 3)) {
            // todo resize
        }
        return &(alloc_item->data);
    }
    return NULL;
}