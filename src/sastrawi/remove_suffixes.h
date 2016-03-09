#include "../libsastrawi.h"

#ifndef SASTRAWI_REMOVE_SUFFIXES_H_INCLUDED
#define SASTRAWI_REMOVE_SUFFIXES_H_INCLUDED
int remove_suffixes(sastrawi_stemmer *stemmer, char *word, char **stemmed_word,  int *removal_count, AFFIX_REMOVAL **removals);
#endif
