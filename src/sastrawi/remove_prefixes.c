#include "features.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
#include "sastrawi_internal.h"
#include "text_util.h"
#include "../libsastrawi.h"
#include "prefix_removers.h"
#include "remove_prefixes.h"

#include "../dbg.h"

//Why can't the following be moved to prefix_removers.h ?
#define prefix_remover_count 22
const PREFIX_REMOVER prefix_removers[prefix_remover_count] = {
  remove_plain_prefix,
  remove_complex_prefix_rule1,
  remove_complex_prefix_rule2,
  remove_complex_prefix_rule3,
  remove_complex_prefix_rule4,
  remove_complex_prefix_rule5,
  remove_complex_prefix_rule6,
  remove_complex_prefix_rule7,
  remove_complex_prefix_rule8,
  remove_complex_prefix_rule9,
  remove_complex_prefix_rule10,
  remove_complex_prefix_rule11,
  remove_complex_prefix_rule12,
  remove_complex_prefix_rule13,
  remove_complex_prefix_rule14,
  remove_complex_prefix_rule15,
  remove_complex_prefix_rule16,
  remove_complex_prefix_rule17,
  remove_complex_prefix_rule18,
  remove_complex_prefix_rule19,
  remove_complex_prefix_rule20,
  remove_complex_prefix_rule21
};


int remove_prefixes(sastrawi_stemmer *stemmer, char *original_word, char **stemmed_word, int *removal_count, AFFIX_REMOVAL **removals)
{
  char *removed_part = NULL;
  char *word = strdup(original_word);
  char *post_remove = NULL;


  int overall_rc = NOT_STEMMED;

  *removal_count = 0;
  *removals = malloc(sizeof(AFFIX_REMOVAL) * 3);

  for(int attempts = 0; attempts < 3; attempts++) {

    int iteration_rc = NOT_STEMMED;
    for(int i =0; i < prefix_remover_count; i++) {

      free(post_remove);
      free(removed_part);

      int rc = (*prefix_removers[i])(stemmer, word, &post_remove, &removed_part);
      //log_err(">> in pref remover: %d, rc: %d", i, rc);

      // if it was either partially_stemmed or fully stemmed, increas the removal count
      if(rc >= PARTIALLY_STEMMED) {
        (*removals)[*removal_count].original_word = strdup(word);
        (*removals)[*removal_count].removed_part = strdup(removed_part);
        (*removals)[*removal_count].result = strdup(post_remove);
        (*removal_count)++;
      }

      if(iteration_rc < rc) {
        iteration_rc = rc;
      }

      if(rc == FULLY_STEMMED) {
        break;
      } else {
        free(word);
        word = strdup(post_remove);
      }
    }

    //log_err("> out pref remover: %d, iteration_rc: %d - word: %s", attempts, iteration_rc, word);

    if(overall_rc < iteration_rc) {
      overall_rc = iteration_rc;
    }

    if(iteration_rc == FULLY_STEMMED || iteration_rc == NOT_STEMMED) {
      //log_err("BREAK ON %d",iteration_rc);
      break;
    }
  }

  *stemmed_word = strdup(post_remove);

  //cleanup
  free(post_remove);
  free(removed_part);
  free(word);

  return overall_rc;
}
