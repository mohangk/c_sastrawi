#include "../libsastrawi.h"

#ifndef SASTRAWI_REMOVE_PREFIXES_H_INCLUDED
#define SASTRAWI_REMOVE_PREFIXES_H_INCLUDED
#define NOT_STEMMED 0
#define PARTIALLY_STEMMED 1
#define FULLY_STEMMED 2

int remove_prefixes(sastrawi_stemmer *, char *word, char **stemmed_word, int *removal_count, AFFIX_REMOVAL **removals);
#endif
