#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int stem_singular_word(char *word, char **stemmed_word);
void remove_prefixes(char *word, char **stemmed_word);
int remove_plain_prefix(char *word, char **stemmed_word, char **removed_part);
int remove_prefix(char *prefixes, char *word, char **stemmed_word, char **removed_part);
int remove_inflectional_particle(char *word, char **stemmed_word, char **removed_part);
int remove_possessive_pronoun(char *word, char **stemmed_word, char **removed_part);
int remove_derivational_suffix(char *word, char **stemmed_word, char **removed_part);
void remove_suffixes(char *word, char **stemmed_word);
int remove_suffix(char *suffixes, char *word, char **stemmed_word, char **removed_part);
