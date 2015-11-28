#include <string.h>
#include "../regex/preg.h"

int split_word(char *pattern, char *word, char **first_part, char **second_part)
{
  char **matches = NULL;
  int rc = 0;

  int match_count = preg_match(pattern, word, &matches);

  if(match_count == 3) {
    (*first_part) = strndup(matches[1], strlen(matches[1]));
    (*second_part) = strndup(matches[2], strlen(matches[2]));
    rc = 1;
    free_matches(match_count, &matches);
  } 

  return rc;
}

int split_word3(char *pattern, char *word, char **first_part, char **second_part, char **third_part)
{
  char **matches = NULL;
  int rc = 0;

  int match_count = preg_match(pattern, word, &matches);

  if(match_count == 4) {
    (*first_part) = strndup(matches[1], strlen(matches[1]));
    (*second_part) = strndup(matches[2], strlen(matches[2]));
    (*third_part) = strndup(matches[3], strlen(matches[3]));

    rc = 1;
    free_matches(match_count, &matches);
  } 

  return rc;
}
