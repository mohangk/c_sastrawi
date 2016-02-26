#ifndef SASTRAWI_STEM_SINGULAR_H_INCLUDED
#define SASTRAWI_STEM_SINGULAR_H_INCLUDED
int stem_singular_word(char *word, char **stemmed_word);
typedef int (*AFFIX_REMOVER)(char *word, char **stemmed_word);
#endif
