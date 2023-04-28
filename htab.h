/**
 * @file    htab.h
 * @brief   Řešení IJC-DU2, příklad 2)
 *          Rozhraní knihovny htab
 * @author  Dr. Ing. Petr Peringer
 * @copyright Public domain
 */

// následující řádky zabrání násobnému vložení:
#ifndef HTAB_H__
#define HTAB_H__

#include <stdbool.h>  // bool
#include <string.h>   // size_t

// Tabulka:
struct htab;                 // neúplná deklarace struktury - uživatel nevidí obsah
typedef struct htab htab_t;  // typedef podle zadání

struct htab_item;
typedef struct htab_item htab_item_t;

// Typy:
typedef const char *htab_key_t;  // typ klíče
typedef int htab_value_t;        // typ hodnoty

// Dvojice dat v tabulce:
typedef struct htab_pair {
    htab_key_t key;      // klíč
    htab_value_t value;  // asociovaná hodnota
} htab_pair_t;           // typedef podle zadání

// Rozptylovací (hash) funkce (stejná pro všechny tabulky v programu)
// Pokud si v programu definujete stejnou funkci, použije se ta vaše.
size_t htab_hash_function(htab_key_t str);

// Funkce pro práci s tabulkou:
htab_t *htab_init(const size_t n);          // konstruktor tabulky
size_t htab_size(const htab_t *t);          // počet záznamů v tabulce
size_t htab_bucket_count(const htab_t *t);  // velikost pole

htab_pair_t *htab_find(const htab_t *t, htab_key_t key);  // hledání
htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key);

bool htab_erase(htab_t *t, htab_key_t key);  // ruší zadaný záznam

// for_each: projde všechny záznamy a zavolá na ně funkci f
// Pozor: f nesmí měnit klíč .key ani přidávat/rušit položky
void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data));

void htab_clear(htab_t *t);  // ruší všechny záznamy
void htab_free(htab_t *t);   // destruktor tabulky

// výpočet a tisk statistik délky seznamů (min,max,avg) do stderr:
void htab_statistics(const htab_t *t);

#endif  // HTAB_H__