#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int stem_singular_word(char *word, char **stemmed_word);
typedef int (*AFFIX_REMOVER)(char *word, char **stemmed_word);
