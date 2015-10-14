#ifdef __linux
  #define _GNU_SOURCE 
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stem_singular_word(char *word, char **stemmed_word)
{
  (*stemmed_word) = strndup(word, strlen(word));
  return 1;
}
