#include <string.h>
#include "../regex/preg.h"
int prefix_split_word(char *pattern, char *word, char **first_part, char **second_part)
{
  char **matches = NULL;
  int rc = 0;

  int match_count = preg_match(pattern, word, &matches);

  if(match_count == 3) {
    (*first_part) = strndup(matches[1], strlen(matches[1]));
    (*second_part) = strndup(matches[2], strlen(matches[2]));
    rc = 1;
    free_matches(match_count, &matches);
  } else {
    (*first_part) = strndup("", 0);
    (*second_part) = strndup(word, strlen(word));
  }

  return rc;
}

int suffix_split_word(char *pattern, char *word, char **first_part, char **second_part)
{
  char **matches = NULL;
  int rc = 0;

  int match_count = preg_match(pattern, word, &matches);

  if(match_count == 3) {
    (*first_part) = strndup(matches[1], strlen(matches[1]));
    (*second_part) = strndup(matches[2], strlen(matches[2]));
    rc = 1;
    free_matches(match_count, &matches);
  } else {
    (*first_part) = strndup(word, strlen(word));
    (*second_part) = strndup("", 0);
  }

  return rc;
}


//the third_path_match is a sad excuse for not being able to write a better regex - need to figure out a better way
int split_word3(char *pattern, char *word, char **first_part, char **second_part, char **third_part, char *third_part_match)
{
  char **matches = NULL;
  int rc = 0;

  int match_count = preg_match(pattern, word, &matches);

  if(match_count == 4 && (strstr(matches[3], third_part_match) == NULL)) {
    (*first_part) = strndup(matches[1], strlen(matches[1]));
    (*second_part) = strndup(matches[2], strlen(matches[2]));
    (*third_part) = strndup(matches[3], strlen(matches[3]));

    rc = 1;
  } 

  //cleanup
  if(match_count == 4) {
    free_matches(match_count, &matches);
  }

  return rc;
}
