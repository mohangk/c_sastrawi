#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "sastrawi.h"
#include "regex/preg.h"
#include "dbg.h"


int is_plural(char *word)
{
  char **matches;

  int count = preg_match("^(.*)-(ku|mu|nya)$", word, &matches);

  if(count > 0) {
    return strchr(matches[1], '-') != NULL;
  }

  return strchr(word, '-') != NULL;
}

int plural_parts(char *word, char **parts[])
{
  char **matches;

  int count = preg_match("^(.*)-(.*)-(ku|mu|nya)$", word, &matches);

  if(count < 0) {
    count = preg_match("^(.*)-(.*)$", word, &matches);
  }

  if(count>0) {

    char *second_part;

    if(count == 4) {
      asprintf(&second_part, "%s-%s",matches[2], matches[3]);
    } else {
      second_part = strndup(matches[2], strlen(matches[2]));
    }

    *parts = malloc(2 * sizeof(char*));
    (*parts)[0] = strndup(matches[1], strlen(matches[1]));
    (*parts)[1] = second_part;

    return 2;

  } else {
    //Allocate the parts array with the original string
    *parts = malloc(1 * sizeof(char*));
    (*parts)[0] = strndup(word, strlen(word));
    return 1;
  }

  //must free matches
}


//Add function to clear a preg_match set


