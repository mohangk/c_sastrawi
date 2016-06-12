#ifndef SASTRAWI_PREFIX_REMOVERS_H_INCLUDED
#define SASTRAWI_PREFIX_REMOVERS_H_INCLUDED

typedef int (*PREFIX_REMOVER)(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part);

int assign_if_root_word(char **, char *, char **, char *);
int remove_plain_prefix(sastrawi_stemmer *, char *, char **, char**);
int remove_complex_prefix_rule1(sastrawi_stemmer *, char *, char **, char**);
int remove_complex_prefix_rule2(sastrawi_stemmer *, char *, char **, char**);
int remove_complex_prefix_rule3(sastrawi_stemmer *, char *, char **, char**);
int remove_complex_prefix_rule4(sastrawi_stemmer *, char *, char **, char**);
int remove_complex_prefix_rule5(sastrawi_stemmer *, char *, char **, char**);
int remove_complex_prefix_rule6(sastrawi_stemmer *, char *, char **, char**);
int remove_complex_prefix_rule7(sastrawi_stemmer *, char *, char **, char**);
int remove_complex_prefix_rule8(sastrawi_stemmer *, char *, char **, char**);
int remove_complex_prefix_rule9(sastrawi_stemmer *, char *, char **, char**);
int remove_complex_prefix_rule10(sastrawi_stemmer *, char *, char **, char**);
int remove_complex_prefix_rule11(sastrawi_stemmer *, char *, char **, char**);
int remove_complex_prefix_rule12(sastrawi_stemmer *, char *, char **, char**);
int remove_complex_prefix_rule13(sastrawi_stemmer *, char *, char **, char**);
int remove_complex_prefix_rule14(sastrawi_stemmer *, char *, char **, char**);
int remove_complex_prefix_rule15(sastrawi_stemmer *, char *, char **, char**);
int remove_complex_prefix_rule16(sastrawi_stemmer *, char *, char **, char**);
int remove_complex_prefix_rule17(sastrawi_stemmer *, char *, char **, char**);
int remove_complex_prefix_rule18(sastrawi_stemmer *, char *, char **, char**);
int remove_complex_prefix_rule19(sastrawi_stemmer *, char *, char **, char**);
int remove_complex_prefix_rule20(sastrawi_stemmer *, char *, char **, char**);
int remove_complex_prefix_rule21(sastrawi_stemmer *, char *, char **, char**);
int remove_complex_prefix_rule23(sastrawi_stemmer *, char *, char **, char**);
int remove_complex_prefix_rule24(sastrawi_stemmer *, char *, char **, char**);



#endif
