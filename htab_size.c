/**
 * @file    htab_size.c
 * @brief   Řešení IJC-DU2, příklad 2)
 *          Implementace htab_size
 * @author  Ondřej Hruboš (xhrubo01), FIT
 * @date    14.04.2023
 */

#include "htab.h"
#include "htab_struct.h"

/**
 * @brief počet záznamů v tabulce
*/
size_t htab_size(const htab_t *t){
    return t->size;
}