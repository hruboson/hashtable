/**
 * @file    htab_bucket_count.c
 * @brief   Řešení IJC-DU2, příklad 2)
 *          Implementace htab_bucket_count
 * @author  Ondřej Hruboš (xhrubo01), FIT
 * @date    14.04.2023
 */

#include "htab.h"
#include "htab_struct.h"

size_t htab_bucket_count(const htab_t *t){
    return t->buckets_count;
}