#ifdef __linux
  #define _GNU_SOURCE 
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sastrawi.h"
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



