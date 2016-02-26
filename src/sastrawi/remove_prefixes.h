#ifndef SASTRAWI_REMOVE_PREFIXES_H_INCLUDED
#define SASTRAWI_REMOVE_PREFIXES_H_INCLUDED
#define NOT_STEMMED 0
#define PARTIALLY_STEMMED 1
#define FULLY_STEMMED 2

typedef int (*PREFIX_REMOVER)(char *word, char **stemmed_word, char **removed_part);

int remove_prefixes(char *word, char **stemmed_word);
int remove_plain_prefix(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule1(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule2(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule3(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule4(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule5(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule6(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule7(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule8(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule9(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule10(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule11(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule12(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule13(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule14(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule15(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule16(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule17(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule18(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule19(char *word, char **stemmed_word, char **removed_part);
int remove_complex_prefix_rule20(char *word, char **stemmed_word, char **removed_part);
#endif
