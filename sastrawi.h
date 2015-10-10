#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "regex/preg.h"
#include "sastrawi/dictionary.h"

//Sastrawi\Stemmer::isPlural
int is_plural(char *word);

int plural_parts(char *word, char **parts[]);

//Sastrawi\Stemmer::stemPluralWord
int stem_plural_word(char *word, char **stemmed_word);

