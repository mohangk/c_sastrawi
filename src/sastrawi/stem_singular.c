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
#include "../dbg.h"

int stem_singular_word(char *word, char **stemmed_word)
{

  //step 1: word already in dictionary
  if(dictionary_contains(word)) {
    (*stemmed_word) = strndup(word, strlen(word));
    return 1;
  }

  if(is_precedence_adjustment_satisfied(word)) {

    int rc = remove_prefixes(word, stemmed_word);

    //in dict and done - return
    if(rc) {
      return 1;
    }

    char *post_remove = strndup(*stemmed_word, strlen(*stemmed_word));
    free(*stemmed_word);
    *stemmed_word = NULL;

    remove_suffixes(post_remove, stemmed_word);
    if(dictionary_contains(*stemmed_word)) {
      return 1;
    } else {
      free(*stemmed_word);
      *stemmed_word = NULL;
    }
  }


  //step 2 & 3: remove suffixes
  remove_suffixes(word, stemmed_word);
  if(dictionary_contains(*stemmed_word)) {
    return 1;
  }

  char *post_suffix_removal_word = strndup(*stemmed_word, strlen(*stemmed_word));
  free(*stemmed_word);
  *stemmed_word = NULL;

  return remove_prefixes(post_suffix_removal_word, stemmed_word);
}
