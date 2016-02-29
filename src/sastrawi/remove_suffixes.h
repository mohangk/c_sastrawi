#ifndef SASTRAWI_REMOVE_SUFFIXES_H_INCLUDED
#define SASTRAWI_REMOVE_SUFFIXES_H_INCLUDED
int remove_suffixes(sastrawi_stemmer *stemmer, char *word, char **stemmed_word);
int remove_inflectional_particle(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part);
int remove_possessive_pronoun(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part);
int remove_derivational_suffix(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part);
int remove_suffix(sastrawi_stemmer *stemmer, char *suffixes, char *word, char **stemmed_word, char **removed_part);
#endif