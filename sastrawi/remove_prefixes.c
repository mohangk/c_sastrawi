#ifdef __linux
  #define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
#include "text_util.h"
#include "remove_prefixes.h"
#include "../dbg.h"

int remove_prefixes(char *word, char **stemmed_word)
{
  char *removed_parts = NULL;
  char *post_remove_plain = NULL;

  //step 4
  remove_plain_prefix(word, &post_remove_plain, &removed_parts);
  free(removed_parts);

  if(dictionary_contains(post_remove_plain)) {
    *stemmed_word = strndup(post_remove_plain, strlen(post_remove_plain));
    return 1;
  } 

  char *post_remove_rule1 = NULL;
  int rc_rule1 = remove_complex_prefix_rule1(post_remove_plain, &post_remove_rule1, &removed_parts);
  free(removed_parts);
  if(rc_rule1) {
    *stemmed_word = strndup(post_remove_rule1, strlen(post_remove_rule1));
    return 1;
  }

  char *post_remove_rule2 = NULL;
  int rc_rule2 = remove_complex_prefix_rule2(post_remove_rule1, &post_remove_rule2, &removed_parts);
  free(removed_parts);
  if(rc_rule2) {
    *stemmed_word = strndup(post_remove_rule2, strlen(post_remove_rule2));
    return 1;
  }

  char *post_remove_rule3 = NULL;
  int rc_rule3 = remove_complex_prefix_rule3(post_remove_rule2, &post_remove_rule3, &removed_parts);
  free(removed_parts);
  *stemmed_word = strndup(post_remove_rule3, strlen(post_remove_rule3));
  if(rc_rule3) {
    return 1;
  }

  return 0;
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

int remove_complex_prefix_rule2(char *word, char **stemmed_word, char **removed_part)
{
  int rc = 0;
  char *partial_stemmed_word;

  int split_rc = split_word3("(^ber)([^aeiou][a-z](\\w*))", word, removed_part, stemmed_word, &partial_stemmed_word);


  if(split_rc == 1 && (strstr(partial_stemmed_word, "er") == NULL)) {
    if(dictionary_contains(*stemmed_word)) {
      rc = 1;
    } 
  } else {

    (*stemmed_word) = strndup(word, strlen(word));
    (*removed_part) = strndup("", 0);

  }

  return rc;
}

int remove_complex_prefix_rule3(char *word, char **stemmed_word, char **removed_part)
{
  int rc = 0;
  char *partial_stemmed_word;

  int split_rc = split_word("(^ber)([^aeiou][a-z]er\\w*)", word, removed_part, stemmed_word);


  if(split_rc == 1) {
    if(dictionary_contains(*stemmed_word)) {
      rc = 1;
    }   
  } else {

    (*stemmed_word) = strndup(word, strlen(word));
    (*removed_part) = strndup("", 0);

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


