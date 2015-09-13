#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "sastrawi.h"
#include "regex/preg.h"


int is_plural(char *word)
{
  char **matches;

  int count = preg_match("^(.*)-(ku|mu|nya)$", word, &matches);

  if(count > 0) {
    return strchr(matches[1], '-') != NULL;
  }

  return strchr(word, '-') != NULL;
}
