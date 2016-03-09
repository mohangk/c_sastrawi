#include "features.h"
#include <string.h>
#include "sastrawi_internal.h"
#include "../regex/preg.h"
#include "text_util.h"
#include "dbg.h"
int prefix_split_word(sastrawi_stemmer *stemmer, char *pattern, char *word, char **first_part, char **second_part)
{
  char **matches = NULL;
  int rc = 0;

  int match_count = preg_match(&stemmer->regex_cache, pattern, word, &matches);

  if(match_count == 3) {
    (*first_part) = strdup(matches[1]);
    (*second_part) = strdup(matches[2]);
    rc = 1;
    free_matches(match_count, &matches);
  } else {
    (*first_part) = strdup("");
    (*second_part) = strdup(word);
  }

  return rc;
}

int suffix_split_word(sastrawi_stemmer *stemmer, char *pattern, char *word, char **first_part, char **second_part)
{
  char **matches = NULL;
  int rc = 0;

  int match_count = preg_match(&stemmer->regex_cache, pattern, word, &matches);

  if(match_count == 3) {
    (*first_part) = strdup(matches[1]);
    (*second_part) = strdup(matches[2]);
    rc = 1;
    free_matches(match_count, &matches);
  } else {
    (*first_part) = strdup(word);
    (*second_part) = strdup("");
  }

  return rc;
}


//the third_path_match is a sad excuse for not being able to write a better regex - need to figure out a better way
int split_word3(sastrawi_stemmer *stemmer, char *pattern, char *word, char **first_part, char **second_part, char *third_part_match)
{
  char **matches = NULL;
  int rc = 0;

  int match_count = preg_match(&stemmer->regex_cache, pattern, word, &matches);

  if(match_count == 4 && (strstr(matches[3], third_part_match) == NULL)) {
    (*first_part) = strdup(matches[1]);
    (*second_part) = strdup(matches[2]);
    rc = 1;
  } else {
    (*first_part) = strdup("");
    (*second_part) = strdup(word);
  }


  //cleanup
  if(match_count == 4) {
    free_matches(match_count, &matches);
  }

  return rc;
}
