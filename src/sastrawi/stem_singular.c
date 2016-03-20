#include "features.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sastrawi_internal.h"
#include "dictionary.h"
#include "remove_suffixes.h"
#include "remove_prefixes.h"
#include "stem_singular.h"
#include "precedence_adjustment.h"
#include "../dbg.h"


const AFFIX_REMOVER prefix_suffix_removers[2] = {remove_prefixes, remove_suffixes};
const AFFIX_REMOVER suffix_prefix_removers[2] = {remove_suffixes, remove_prefixes};
int apply_affix_removers(sastrawi_stemmer *, char *, char **, const AFFIX_REMOVER[]);
void free_affix_removals(int, AFFIX_REMOVAL *);

int stem_singular_word(sastrawi_stemmer *stemmer, char *original_word, char **stemmed_word)
{

  //step 1: word already in dictionary
  if(dictionary_contains(original_word)) {
    (*stemmed_word) = strdup(original_word);
    return FULLY_STEMMED;
  }

  char *post_remove = NULL;
  int remover_rc = NOT_STEMMED;

  if(is_precedence_adjustment_satisfied(original_word)) {
    remover_rc = apply_affix_removers(stemmer, original_word, &post_remove, prefix_suffix_removers);
  }   
  
  if(remover_rc == NOT_STEMMED) {
    remover_rc = apply_affix_removers(stemmer, original_word, &post_remove, suffix_prefix_removers);
  }

  if(remover_rc != FULLY_STEMMED) {
    //don't we need to clean up post_remove before using it here ?
    remover_rc = suffix_returning_loop(stemmer, original_word, &post_remove);
  }

  if(remover_rc == FULLY_STEMMED) {
    *stemmed_word = strdup(post_remove);
    free(post_remove);
  } else {
    *stemmed_word = strdup(original_word);
  }

  return remover_rc;
}


int suffix_returning_loop(sastrawi_stemmer *stemmer, char *original_word, char **stemmed_word)
{
  int rc = NOT_STEMMED;

  AFFIX_REMOVAL *removals;
  int removal_count;
  char *suffix_removed_word;

  remove_suffixes(stemmer, original_word, &suffix_removed_word, &removal_count, &removals);
  free(suffix_removed_word);

  if(removal_count == 0) {
    return rc;
  }

  for(int i = removal_count - 1; i >= 0; i--) {

    char *post_removed;
    AFFIX_REMOVAL *tmp_removals;
    int tmp_removal_count = 0;

    if(strcmp(removals[i].removed_part,"kan") == 0) {
      char *tmp;
      asprintf(&tmp, "%sk", removals[i].result);

      int rc_remove_prefixes = remove_prefixes(stemmer, tmp, &post_removed, &tmp_removal_count, &tmp_removals);
      free(tmp);
      free_affix_removals(tmp_removal_count, tmp_removals);

      if(rc_remove_prefixes == FULLY_STEMMED) {
        rc = FULLY_STEMMED;
        *stemmed_word = post_removed;
        break;
      } else {
        free(post_removed);
      }
    }

    int rc_remove_prefixes = remove_prefixes(stemmer, removals[i].original_word, &post_removed, &tmp_removal_count, &tmp_removals);
    free_affix_removals(tmp_removal_count, tmp_removals);

    if(rc_remove_prefixes == FULLY_STEMMED) {
      rc = FULLY_STEMMED;
      *stemmed_word = post_removed;
      break;
    } else {
      free(post_removed);
    }

    free_affix_removals(removal_count, removals);
  }

  return rc;
}


int apply_affix_removers(sastrawi_stemmer *stemmer, char *original_word, char **stemmed_word, const AFFIX_REMOVER affix_removers[]) 
{
  char *word = strdup(original_word);
  int remover_rc = NOT_STEMMED;

  AFFIX_REMOVAL *removals;
  int removal_count = 0;

  for(int i = 0; i<2; i++) {
    remover_rc = affix_removers[i](stemmer, word, stemmed_word, &removal_count, &removals);
    if(remover_rc == FULLY_STEMMED) {
      break;
    } else {
      free(word);
      word = strdup(*stemmed_word);
      free(*stemmed_word);
      if(removal_count > 0) {
        free_affix_removals(removal_count, removals);
      }
    }
  }

  free(word);

  return remover_rc;
}


void free_affix_removals(int removal_count, AFFIX_REMOVAL *removals) {

  for(int i = 0; i < removal_count; i++) {
    free(removals[i].original_word);
    free(removals[i].removed_part);
    free(removals[i].result);
  }
  free(removals);

}
