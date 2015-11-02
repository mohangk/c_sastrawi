#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int stem_singular_word(char *word, char **stemmed_word);
int remove_prefixes(char *word, char **stemmed_word);
int remove_plain_prefix(char *word, char **stemmed_word, char **removed_part);
int remove_prefix(char *prefixes, char *word, char **stemmed_word, char **removed_part);
int remove_inflectional_particle(char *word, char **stemmed_word, char **removed_part);
int remove_possessive_pronoun(char *word, char **stemmed_word, char **removed_part);
int remove_derivational_suffix(char *word, char **stemmed_word, char **removed_part);
void remove_suffixes(char *word, char **stemmed_word);
int remove_suffix(char *suffixes, char *word, char **stemmed_word, char **removed_part);
int split_word(char *pattern, char *word, char **first_part, char **second_part);
int split_word3(char *pattern, char *word, char **first_part, char **second_part, char **third_part);
int remove_complex_prefix_rule1(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule2(char *word, char **stemmed_word, char **removed_part);
