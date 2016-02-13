#ifdef __linux
  #define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
#include "remove_suffixes.h"
#include "remove_prefixes.h"
#include "stem_singular.h"
#include "precedence_adjustment.h"
#include "../dbg.h"


const AFFIX_REMOVER prefix_suffix_removers[2] = {remove_prefixes, remove_suffixes};
const AFFIX_REMOVER suffix_prefix_removers[2] = {remove_suffixes, remove_prefixes};

int stem_singular_word(char *original_word, char **stemmed_word)
{

  //step 1: word already in dictionary
  if(dictionary_contains(original_word)) {
    (*stemmed_word) = strndup(original_word, strlen(original_word));
    return 1;
  }

  char *post_remove = NULL;
  int remover_rc = 0;

  if(is_precedence_adjustment_satisfied(original_word)) {
    remover_rc = apply_affix_removers(original_word, &post_remove, prefix_suffix_removers);
  }

  if(remover_rc == 0) {
    remover_rc = apply_affix_removers(original_word, &post_remove, suffix_prefix_removers);
  }

  if(remover_rc == 1) {
    *stemmed_word = strndup(post_remove, strlen(post_remove));
    free(post_remove);
  } else {
    *stemmed_word = strndup(original_word, strlen(original_word));
  }

  return remover_rc;
}


int apply_affix_removers(char *original_word, char **stemmed_word, AFFIX_REMOVER affix_removers[]) {

  char *word = strndup(original_word, strlen(original_word));
  int remover_rc = 0;

  for(int i = 0; i<2; i++) {
    if((remover_rc = affix_removers[i](word, stemmed_word))) {
      break;
    } else {
      free(word);
      word = strndup(*stemmed_word, strlen(*stemmed_word));
      free(*stemmed_word);
    }
  }

  free(word);

  return remover_rc;
}
