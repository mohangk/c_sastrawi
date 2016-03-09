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

int remove_suffixes(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, int *removal_count, AFFIX_REMOVAL **removals)
{
  int rc = NOT_STEMMED;
  int suffix_remover_rc = 0;

  *removal_count = 0;
  *removals = malloc(sizeof(AFFIX_REMOVAL) * 3);

  char *removed_parts = NULL;
  char *suffix_remove1 = NULL;
  char *suffix_remove2 = NULL;

  //step 2a
  suffix_remover_rc = remove_inflectional_particle(stemmer, word, &suffix_remove1, &removed_parts);

  if(suffix_remover_rc == 1) {
    (*removals)[*removal_count].original_word = strdup(word);
    (*removals)[*removal_count].removed_part = strdup(removed_parts);
    (*removal_count)++;
  }
  free(removed_parts);

  //step 2b
  suffix_remover_rc = remove_possessive_pronoun(stemmer, suffix_remove1, &suffix_remove2, &removed_parts);
  if(suffix_remover_rc == 1) {
    (*removals)[*removal_count].original_word = strdup(suffix_remove1);
    (*removals)[*removal_count].removed_part = strdup(removed_parts);
    (*removal_count)++;
  }
  free(removed_parts);

  //step 3
  suffix_remover_rc = remove_derivational_suffix(stemmer, suffix_remove2, stemmed_word, &removed_parts);
  if(suffix_remover_rc == 1) {
    (*removals)[*removal_count].original_word = strdup(suffix_remove1);
    (*removals)[*removal_count].removed_part = strdup(removed_parts);
    (*removal_count)++;
  }
  free(removed_parts);

  free(suffix_remove1);
  free(suffix_remove2);

  if(dictionary_contains(*stemmed_word)) {
    rc = FULLY_STEMMED;
  }

  return rc;
}
