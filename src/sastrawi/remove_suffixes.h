#ifndef SASTRAWI_REMOVE_SUFFIXES_H_INCLUDED
#define SASTRAWI_REMOVE_SUFFIXES_H_INCLUDED
int remove_suffixes(char *word, char **stemmed_word);
int remove_inflectional_particle(char *word, char **stemmed_word, char **removed_part);
int remove_possessive_pronoun(char *word, char **stemmed_word, char **removed_part);
int remove_derivational_suffix(char *word, char **stemmed_word, char **removed_part);
int remove_suffix(char *suffixes, char *word, char **stemmed_word, char **removed_part);
#endif
