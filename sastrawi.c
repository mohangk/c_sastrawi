#ifdef __linux
  #define _GNU_SOURCE 
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sastrawi.h"
#include "sastrawi/dictionary.h"
#include "dbg.h"


int is_plural(char *word)
{
  char **matches;

  int matches_count, dash_count;
    
  matches_count = preg_match("^(.*)-(ku|mu|nya)$", word, &matches);

  if(matches_count > 0) {
    dash_count = strchr(matches[1], '-') != NULL;
    free_matches(matches_count, &matches);
  } else {
    dash_count = strchr(word, '-') != NULL;
  }

  return dash_count;

}

int plural_parts(char *word, char **parts[])
{
  char **matches;
  int matches_count, parts_count, rc;

  matches_count = preg_match("^(.*)-(.*)-(ku|mu|nya)$", word, &matches);

  if(matches_count < 0) {
    matches_count = preg_match("^(.*)-(.*)$", word, &matches);
  }

  if(matches_count>0) {

    char *second_part;

    if(matches_count == 4) {
      rc = asprintf(&second_part, "%s-%s",matches[2], matches[3]);
      check_debug(rc != -1, "Cannot allocate memory");
    } else {
      second_part = strndup(matches[2], strlen(matches[2]));
    }

    *parts = malloc(2 * sizeof(char*));
    (*parts)[0] = strndup(matches[1], strlen(matches[1]));
    (*parts)[1] = second_part;

    parts_count = 2;

    free_matches(matches_count, &matches);
  } else {
    *parts = malloc(1 * sizeof(char*));
    (*parts)[0] = strndup(word, strlen(word));
    parts_count = 1;
  }


  return parts_count;
error:
  exit(1);
}


int stem_plural_word(char *word, char **stemmed_word)
{
  dictionary_load(dictionary_fullpath("data/kata-dasar.txt"));

  char **word_parts = NULL;
  int rc = plural_parts(word, &word_parts);

  debug("word parts %s, %s", word_parts[0], word_parts[1]);
  if(dictionary_contains(word_parts[0])) {
    (*stemmed_word) = strndup(word_parts[0], strlen(word_parts[0]));
  } else {
    (*stemmed_word) = strndup(word, strlen(word));
  }

  free_matches(rc, &word_parts);

  return 1;
}



