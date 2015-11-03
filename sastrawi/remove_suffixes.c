#ifdef __linux
  #define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include "text_util.h"
#include "remove_suffixes.h"
#include "../dbg.h"

void remove_suffixes(char *word, char **stemmed_word)
{

  char *removed_parts = NULL;
  char *suffix_remove1 = NULL;
  char *suffix_remove2 = NULL;

  //step 2a
  remove_inflectional_particle(word, &suffix_remove1, &removed_parts);
  free(removed_parts);

  //step 2b
  remove_possessive_pronoun(suffix_remove1, &suffix_remove2, &removed_parts);
  free(removed_parts);

  //step 3
  remove_derivational_suffix(suffix_remove2, stemmed_word, &removed_parts);
  free(removed_parts);
  free(suffix_remove1);
  free(suffix_remove2);
}


int remove_inflectional_particle(char *word, char **stemmed_word, char **removed_part)
{
  return remove_suffix("lah|kah|tah|pun", word, stemmed_word, removed_part);
}

int remove_possessive_pronoun(char *word, char **stemmed_word, char **removed_part)
{
  return remove_suffix("ku|mu|nya", word, stemmed_word, removed_part);
}

int remove_derivational_suffix(char *word, char **stemmed_word, char **removed_part)
{
  return remove_suffix("is|isme|isasi|i|kan|an", word, stemmed_word, removed_part);
}

int remove_suffix(char *suffixes, char *word, char **stemmed_word, char **removed_part)
{
  char **matches = NULL;
  int rc;
  char *pattern = NULL;

  int pattern_rc = asprintf(&pattern, "(\\w+?)-?(%s)$", suffixes);

  rc = split_word(pattern, word, stemmed_word, removed_part);

  if(rc != 1) {
    (*stemmed_word) = strndup(word, strlen(word));
    (*removed_part) = strndup("", 0);
  }

  free(pattern);
  return rc;
}
