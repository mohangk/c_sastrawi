#ifndef SASTRAWI_SUFFIX_REMOVERS_H_INCLUDED
#define SASTRAWI_SUFFIX_REMOVERS_H_INCLUDED
int remove_inflectional_particle(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part);
int remove_possessive_pronoun(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part);
int remove_derivational_suffix(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part);
int remove_suffix(sastrawi_stemmer *stemmer, char *suffixes, char *word, char **stemmed_word, char **removed_part);
#endif
