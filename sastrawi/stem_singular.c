#ifdef __linux
  #define _GNU_SOURCE 
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
#include "stem_singular.h"
#include "../regex/preg.h"
#include "../dbg.h"

int stem_singular_word(char *word, char **stemmed_word)
{

  dictionary_load(dictionary_fullpath("data/kata-dasar.txt"));

  //step 1: word already in dictionary
  if(dictionary_contains(word)) {
    (*stemmed_word) = strndup(word, strlen(word));
    return 1;
  }

  //step 2 & 3: remove suffixes
  remove_suffixes(word, stemmed_word);
  if(dictionary_contains(*stemmed_word)) {
    return 1;
  }

  char *post_suffix_removal_word = strndup(*stemmed_word, strlen(*stemmed_word));
  free(*stemmed_word);
  *stemmed_word = NULL;

  remove_prefixes(post_suffix_removal_word, stemmed_word);
  if(dictionary_contains(*stemmed_word)) {
    return 1;
  }

  return 0;
}

void remove_prefixes(char *word, char **stemmed_word) 
{

  char *removed_parts = NULL;

  //step 4
  remove_plain_prefix(word, stemmed_word, &removed_parts);

  free(removed_parts);
}


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

int remove_plain_prefix(char *word, char **stemmed_word, char **removed_part)
{

  return remove_prefix("di|ke|se", word, stemmed_word, removed_part);
}

int remove_prefix(char *suffixes, char *word, char **stemmed_word, char **removed_part)
{
  char **matches = NULL;
  int rc;
  char *pattern = NULL;

  int pattern_rc = asprintf(&pattern, "^(%s)(\\w+)$", suffixes);

  int match_count = preg_match(pattern, word, &matches);

  if((*stemmed_word) != NULL) {
    debug("freeing stemmed_word");
    free((*stemmed_word));
  }

  if(match_count == 3) {
    (*removed_part) = strndup(matches[1], strlen(matches[1]));
    (*stemmed_word) = strndup(matches[2], strlen(matches[2]));
    rc = 1;
    free_matches(match_count, &matches);

  } else {

    (*stemmed_word) = strndup(word, strlen(word));
    (*removed_part) = strndup("", 0);
    rc = 0;

  }
  free(pattern);


  return rc;
}

int remove_suffix(char *suffixes, char *word, char **stemmed_word, char **removed_part)
{
  char **matches = NULL;
  int rc;
  char *pattern = NULL;

  int pattern_rc = asprintf(&pattern, "(\\w+?)-?(%s)$", suffixes);

  int match_count = preg_match(pattern, word, &matches);

  if((*stemmed_word) != NULL) {
    debug("freeing stemmed_word");
    free((*stemmed_word));
  }

  /* if((*removed_part) != NULL) { */
  /*   free((*removed_part)); */
  /* } */

  if(match_count == 3) {
    //debug("REMOVE_SUFFIX >> word: %s, matches: %d, matches: 0, %s, 1, %s, 2, %s", word, match_count, matches[0], matches[1], matches[2]);
    (*stemmed_word) = strndup(matches[1], strlen(matches[1]));
    (*removed_part) = strndup(matches[2], strlen(matches[2]));
    rc = 1;
    free_matches(match_count, &matches);

  } else {

    (*stemmed_word) = strndup(word, strlen(word));
    (*removed_part) = strndup("", 0);
    rc = 0;

  }
  free(pattern);


  return rc;
}
