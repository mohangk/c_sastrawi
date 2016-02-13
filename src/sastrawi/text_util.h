#ifndef SASTRAWI_TEXT_UTIL_H_INCLUDED
#define SASTRAWI_TEXT_UTIL_H_INCLUDED
int split_word(char *pattern, char *word, char **first_part, char **second_part);
int split_word3(char *pattern, char *word, char **first_part, char **second_part, char *third_part_match);
int prefix_split_word(char *pattern, char *word, char **first_part, char **second_part);
#endif
