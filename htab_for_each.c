/**
 * @file    htab.c
 * @brief   Řešení IJC-DU2, příklad 2)
 *          Implementace konstruktoru tabulky
 * @author  Ondřej Hruboš (xhrubo01), FIT
 * @date    14.04.2023
 */

#include "htab.h"
#include "htab_struct.h"

/**
 * @brief for_each: projde všechny záznamy a zavolá na ně funkci f
 * @note Pozor : f nesmí měnit klíč.key ani přidávat / rušit položky
 */
void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data)) {
    for (size_t i = 0; i < t->buckets_count; i++) {
        htab_item_t *tmp = t->buckets[i];
        while (tmp) {
            f(&(tmp->data));
            tmp = tmp->next;
        }
    }
}