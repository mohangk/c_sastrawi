#include "features.h"
#include <stdio.h>
#include <stdlib.h>
#include "text_util.h"
#include "remove_suffixes.h"
#include "remove_prefixes.h"
#include "dictionary.h"
#include "../dbg.h"

int remove_suffixes(char *word, char **stemmed_word)
{
  int rc = 0;

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

  if(dictionary_contains(*stemmed_word)) {
    rc = FULLY_STEMMED;
  }

  return rc;
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
  int rc;
  char *pattern = NULL;

  asprintf(&pattern, "(\\w+?)-?(%s)$", suffixes);

  rc = suffix_split_word(pattern, word, stemmed_word, removed_part);

  free(pattern);
  return rc;
}
