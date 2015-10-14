#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int stem_singular_word(char *word, char **stemmed_word);
int remove_inflectional_particle(char *word, char **stemmed_word, char **removed_part);
int remove_possessive_pronoun(char *word, char **stemmed_word, char **removed_part);
int remove_suffix(char *suffixes, char *word, char **stemmed_word, char **removed_part);
