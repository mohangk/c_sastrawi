#ifdef __linux
  #define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include "sastrawi_internal.h"
#include "text_util.h"
#include "suffix_removers.h"
#include "dictionary.h"
#include "../dbg.h"


int remove_inflectional_particle(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  return remove_suffix(stemmer, "lah|kah|tah|pun", word, stemmed_word, removed_part);
}

int remove_possessive_pronoun(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  return remove_suffix(stemmer, "ku|mu|nya", word, stemmed_word, removed_part);
}

int remove_derivational_suffix(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  return remove_suffix(stemmer, "is|isme|isasi|i|kan|an", word, stemmed_word, removed_part);
}

int remove_suffix(sastrawi_stemmer *stemmer, char *suffixes, char *word, char **stemmed_word, char **removed_part)
{
  int rc;
  char *pattern = NULL;

  asprintf(&pattern, "(\\w+?)-?(%s)$", suffixes);

  rc = suffix_split_word(stemmer, pattern, word, stemmed_word, removed_part);

  free(pattern);
  return rc;
}
