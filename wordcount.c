/**
 * @file    wordcount.c
 * @brief   Řešení IJC-DU2, příklad 2)
 *          Implementace programu wordcount (C)
 *          Program počítá četnost slov ve vstupním textu, slovo je cokoli oddělené "bílým znakem"
 * @author  Ondřej Hruboš (xhrubo01), FIT
 * @date    14.04.2023
 */

#include <stdio.h>

#include "htab.h"
#include "htab_struct.h"
#include "io.h"

/**
 *  @brief zvolil jsem mocninu dvou pro snadné rozšiřování tabulky, a zároveň opdovídá Heapsovu zákonu pro dokument s ~750 000 slovy (K = 44, b = 0.49 - https://nlp.stanford.edu/IR-book/html/htmledition/heaps-law-estimating-the-number-of-terms-1.html)
 *  @note pokud bychom vypočítali celkový počet slov dokumentu předem, mohli bychom makrem vypočítat velikost tabulky Heapsovým zákonem, což by značně redukovalo potřebu měnit velikost tabulky (a kolizí) a zároveň nealokovalo příliš mnoho místa pro tabulku (pro běžné dokumenty)
 *      V(n) = K*(n^b)
 *      n - celkový počet slov v textu
 *      K - volitelný parametr (pro anglický text typicky v rozsahu <10;100>)
 *      b - volitelný parametr (typicky v rozsahu <0.4;0.6>)
 */
#define HTAB_SIZE 128
#define MAX_WORD_LEN 184  // 3. nejdelší anglické slovo je 183 znaků dlouhé (2. 1909, 1. 189819)

void print_pair(htab_pair_t *data) {
    printf("%s\t%u\n", data->key, data->value);
}

int main() {
    htab_t *t = htab_init(HTAB_SIZE);
    if (!t) {
        return 1;
    }

    char word[MAX_WORD_LEN] = {0};
    int word_len = 0;
    while ((word_len = read_word(word, MAX_WORD_LEN, stdin)) != EOF) {
        if (word[0] != '\0') {
            htab_pair_t *item = htab_lookup_add(t, word);
            if (!item) {
                return 1;
            } else {
                item->value++;
            }
        }
    }

    htab_for_each(t, print_pair);
    htab_free(t);

    return 0;
}
