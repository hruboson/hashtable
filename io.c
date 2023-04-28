/**
 * @file    io.c
 * @brief   Řešení IJC-DU2, příklad 2)
 *          Implementace chybového výstupu
 * @author  Ondřej Hruboš (xhrubo01), FIT
 * @date    14.04.2023
 */

#include "io.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief čte jedno slovo ze souboru f do zadaného pole znaků a vrátí délku slova
 * @details Funkce vrací EOF, pokud je konec souboru.
 * @note Slovo je souvislá posloupnost znaků oddělená isspace znaky.
 * @return délka načteného slova
 */
int read_word(char *s, int max, FILE *f) {
    int len = 0;
    int max_len = max - 1;
    char c;

    while ((c = getc(f)) != EOF) {
        if (isspace(c)) {
            break;
        }
        if (len >= max_len) {
            fprintf(stderr, "Error: Word too long.\n");
            return len;
        }

        s[len++] = c;
    }
    s[len] = '\0';

    return (feof(f)) ? EOF : len;
}