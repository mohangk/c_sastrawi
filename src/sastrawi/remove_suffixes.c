#include "features.h"
#include <stdio.h>
#include <stdlib.h>
#include "sastrawi_internal.h"
#include "text_util.h"
#include "suffix_removers.h"
#include "remove_suffixes.h"
#include "remove_prefixes.h"
#include "dictionary.h"
#include "../dbg.h"

int remove_suffixes(sastrawi_stemmer *stemmer, char *word, char **stemmed_word)
{
  int rc = 0;

  char *removed_parts = NULL;
  char *suffix_remove1 = NULL;
  char *suffix_remove2 = NULL;

  //step 2a
  remove_inflectional_particle(stemmer, word, &suffix_remove1, &removed_parts);
  free(removed_parts);

  //step 2b
  remove_possessive_pronoun(stemmer, suffix_remove1, &suffix_remove2, &removed_parts);
  free(removed_parts);

  //step 3
  remove_derivational_suffix(stemmer, suffix_remove2, stemmed_word, &removed_parts);
  free(removed_parts);
  free(suffix_remove1);
  free(suffix_remove2);

  if(dictionary_contains(*stemmed_word)) {
    rc = FULLY_STEMMED;
  }

  return rc;
}
