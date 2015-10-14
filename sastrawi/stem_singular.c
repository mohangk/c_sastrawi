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
  (*stemmed_word) = strndup(word, strlen(word));

  if(dictionary_contains(word)) {
    return 1;
  } else {
    return 0;
  }
}

int remove_inflectional_particle(char *word, char **stemmed_word, char **removed_part)
{
  return remove_suffix("lah|kah|tah|pun", word, stemmed_word, removed_part);
}

int remove_possessive_pronoun(char *word, char **stemmed_word, char **removed_part)
{
  return remove_suffix("ku|mu|nya", word, stemmed_word, removed_part);
}

int remove_suffix(char *suffixes, char *word, char **stemmed_word, char **removed_part)
{
  char **matches = NULL;
  int rc;
  char *pattern = NULL;

  int pattern_rc = asprintf(&pattern, "(\\w+)-*(%s)$", suffixes);

  int match_count = preg_match(pattern, word, &matches);

  if(match_count == 3) {

    //debug("word: %s, matches: %d, matches: 0, %s, 1, %s, 2, %s", word, match_count, matches[0], matches[1], matches[2]);
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
