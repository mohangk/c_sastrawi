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

int remove_complex_prefix_rule1(char *word, char **stemmed_word, char **removed_part)
{
  int rc = 0;

  rc = split_word("(^ber)([aiueo].*)$", word, removed_part, stemmed_word);


  //1a
  if(rc == 1) {
    if(dictionary_contains(*stemmed_word)) {
      return 1;
    } else {
  //1b
      char *rule1b_word;
      asprintf(&rule1b_word, "r%s", *stemmed_word);

      if(dictionary_contains(rule1b_word)) {
        free(*removed_part);
        *removed_part = strndup("be",2);

        free(*stemmed_word);
        *stemmed_word = strndup(rule1b_word, strlen(rule1b_word));
        return 1;
      } 
    }
  } else {

    (*stemmed_word) = strndup(word, strlen(word));
    (*removed_part) = strndup("", 0);

  }

  return 0;
}


int split_word(char *pattern, char *word, char **first_part, char **second_part)
{
  char **matches = NULL;
  int rc = 0;

  int match_count = preg_match(pattern, word, &matches);

  if((*first_part) != NULL) {
    debug("freeing first_part");
    free((*first_part));
  }

  if(match_count == 3) {
    (*first_part) = strndup(matches[1], strlen(matches[1]));
    (*second_part) = strndup(matches[2], strlen(matches[2]));
    rc = 1;
    free_matches(match_count, &matches);
  } 

  return rc;
}

int remove_prefix(char *suffixes, char *word, char **stemmed_word, char **removed_part)
{
  char **matches = NULL;
  int rc;
  char *pattern = NULL;

  int pattern_rc = asprintf(&pattern, "^(%s)(\\w+)$", suffixes);

  rc = split_word(pattern, word, removed_part, stemmed_word);

  if(rc != 1) {
    (*stemmed_word) = strndup(word, strlen(word));
    (*removed_part) = strndup("", 0);
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

  rc = split_word(pattern, word, stemmed_word, removed_part);

  if(rc != 1) {
    (*stemmed_word) = strndup(word, strlen(word));
    (*removed_part) = strndup("", 0);
  }

  free(pattern);
  return rc;
}
