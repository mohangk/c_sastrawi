#ifndef SASTRAWI_TEXT_UTIL_H_INCLUDED
#define SASTRAWI_TEXT_UTIL_H_INCLUDED
int split_word(sastrawi_stemmer *stemmer, char *pattern, char *word, char **first_part, char **second_part);
int split_word3(sastrawi_stemmer *stemmer, char *pattern, char *word, char **first_part, char **second_part, char *third_part_match);
int prefix_split_word(sastrawi_stemmer *stemmer, char *pattern, char *word, char **first_part, char **second_part);
int suffix_split_word(sastrawi_stemmer *stemmer, char *pattern, char *word, char **first_part, char **second_part);
#endif
