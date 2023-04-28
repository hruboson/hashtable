/**
 * @file    htab.c
 * @brief   Řešení IJC-DU2, příklad 2)
 *          Implementace htab_hash_function
 * @author  Ondřej Hruboš (xhrubo01), FIT
 * @date    14.04.2023
 */

#include <stdlib.h>
#include <stdint.h>
#include "htab.h"

// sdbm hash function
size_t htab_hash_function(htab_key_t str){
    uint32_t h = 0;  // musí mít 32 bitů
    const unsigned char *p;
    for (p = (const unsigned char *)str; *p != '\0'; p++)
        h = 65599 * h + *p;
    return h;
}