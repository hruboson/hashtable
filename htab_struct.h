/**
 * @file    htab_struct.h
 * @brief   Řešení IJC-DU2, příklad 2)
 *          Struktury pro htab
 * @author  Ondřej Hruboš (xhrubo01), FIT
 * @date    14.04.2023
 */

#ifndef HTAB_STRUCT_H__
#define HTAB_STRUCT_H__

#include "htab.h"

typedef struct htab_item {
    htab_item_t* next;
    htab_pair_t data;
} htab_item_t;

typedef struct htab {
    size_t size;
    size_t buckets_count;
    htab_item_t* buckets[];
} htab_t;

#endif