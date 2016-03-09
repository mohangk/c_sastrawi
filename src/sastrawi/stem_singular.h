#ifndef SASTRAWI_STEM_SINGULAR_H_INCLUDED
#define SASTRAWI_STEM_SINGULAR_H_INCLUDED
#include "../libsastrawi.h"
int stem_singular_word(sastrawi_stemmer *stemmer, char *word, char **stemmed_word);
typedef int (*AFFIX_REMOVER)(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, int *removal_count, AFFIX_REMOVAL **removals);
#endif
