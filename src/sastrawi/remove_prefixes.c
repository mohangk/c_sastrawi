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

#define prefix_remover_count 21

const PREFIX_REMOVER prefix_removers[prefix_remover_count] = {
  remove_plain_prefix,
  remove_complex_prefix_rule1,
  remove_complex_prefix_rule2,
  remove_complex_prefix_rule3,
  remove_complex_prefix_rule4,
  remove_complex_prefix_rule5,
  remove_complex_prefix_rule6,
  remove_complex_prefix_rule7,
  remove_complex_prefix_rule8,
  remove_complex_prefix_rule9,
  remove_complex_prefix_rule10,
  remove_complex_prefix_rule11,
  remove_complex_prefix_rule12,
  remove_complex_prefix_rule13,
  remove_complex_prefix_rule14,
  remove_complex_prefix_rule15,
  remove_complex_prefix_rule16,
  remove_complex_prefix_rule17,
  remove_complex_prefix_rule18,
  remove_complex_prefix_rule19,
  remove_complex_prefix_rule20
};

int assign_if_root_word(char **, char *, char **, char *);

int remove_prefixes(char *original_word, char **stemmed_word)
{
  int rc = 0;
  char *removed_part = NULL;

  char *word = strndup(original_word, strlen(original_word));
  char *post_remove = NULL;

  for(int attempts = 0; attempts < 3; attempts++) {
    for(int i =0; i < prefix_remover_count; i++) {

      free(post_remove);
      free(removed_part);
      rc = (*prefix_removers[i])(word, &post_remove, &removed_part);

      if(rc == FULLY_STEMMED) {
        break;
      } else {
        free(word);
        word = strndup(post_remove, strlen(post_remove));
      }
    }

    if(rc == FULLY_STEMMED) {
      break;
    }
  }

  *stemmed_word = strndup(post_remove, strlen(post_remove));

  //cleanup
  free(post_remove);
  free(removed_part);
  free(word);

  return rc;
}

int remove_plain_prefix(char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc =  prefix_split_word("^(di|ke|se)(\\w+)$", word, removed_part, stemmed_word);

  if(split_rc == 1) {
      rc = PARTIALLY_STEMMED;

      if(dictionary_contains(*stemmed_word)) {
        rc = FULLY_STEMMED;
      }
  }

  return rc;
}

int remove_complex_prefix_rule1(char *word, char **stemmed_word, char **removed_part)
{
  int rc = 0;

  int split_rc = prefix_split_word("(^ber)([aiueo].*)$", word, removed_part, stemmed_word);

  //1a
  if(split_rc == 1) {
    if(dictionary_contains(*stemmed_word)) {
      rc = 1;
    } else {
      //1b
      char *alternative_stemmed_word;
      asprintf(&alternative_stemmed_word, "r%s", *stemmed_word);
      rc = assign_if_root_word(stemmed_word, alternative_stemmed_word, removed_part, "be");
      free(alternative_stemmed_word);
    }
  }
  return rc;
}

int remove_complex_prefix_rule2(char *word, char **stemmed_word, char **removed_part)
{
  int rc = 0;

  int split_rc = split_word3("(^ber)([^aeiou][a-z](\\w*))", word, removed_part, stemmed_word, "er");

  if(split_rc == 1) {
      rc = PARTIALLY_STEMMED;

      if(dictionary_contains(*stemmed_word)) {
        rc = FULLY_STEMMED;
      }
  }

  return rc;
}

int remove_complex_prefix_rule3(char *word, char **stemmed_word, char **removed_part)
{
  int rc = 0;

  int split_rc = prefix_split_word("(^ber)([^aeiou][a-z]er\\w*)", word, removed_part, stemmed_word);


  if(split_rc == 1) {
      rc = PARTIALLY_STEMMED;

      if(dictionary_contains(*stemmed_word)) {
        rc = FULLY_STEMMED;
      }
  }

  return rc;
}

int remove_complex_prefix_rule4(char *word, char **stemmed_word, char **removed_part)
{
  int rc = 0;

  int split_rc = prefix_split_word("(^bel)(ajar)", word, removed_part, stemmed_word);

  if(split_rc == 1 && dictionary_contains(*stemmed_word)) {
      rc = 1;
  }

  return rc;
}

int remove_complex_prefix_rule5(char *word, char **stemmed_word, char **removed_part)
{
  int rc = 0;

  int split_rc = prefix_split_word("(^be)([^aeiour]er[^aeiou]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1 && dictionary_contains(*stemmed_word)) {
      rc = 1;
  }
  return rc;
}

int remove_complex_prefix_rule6(char *word, char **stemmed_word, char **removed_part)
{
  int rc = 0;

  int split_rc = prefix_split_word("(^ter)([aiueo].*)$", word, removed_part, stemmed_word);

  //6a
  if(split_rc == 1) {
    if(dictionary_contains(*stemmed_word)) {
      rc = 1;
    } else {
  //6b
      char *alternative_stemmed_word;
      asprintf(&alternative_stemmed_word, "r%s", *stemmed_word);
      rc = assign_if_root_word(stemmed_word, alternative_stemmed_word, removed_part, "te");
      free(alternative_stemmed_word);
    }
  }
  return rc;
}

int remove_complex_prefix_rule7(char *word, char **stemmed_word, char **removed_part)
{
  int rc = 0;

  int split_rc = prefix_split_word("(^ter)([^aeiour]er[aeiou]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1 && dictionary_contains(*stemmed_word)) {
      rc = 1;
  }

  return rc;
}

int remove_complex_prefix_rule8(char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = split_word3("(^ter)([^aeiour](\\w*))", word, removed_part, stemmed_word, "er");

  if(split_rc == 1) {
      rc = PARTIALLY_STEMMED;

      if(dictionary_contains(*stemmed_word)) {
        rc = FULLY_STEMMED;
      }
  }


  return rc;
}

int remove_complex_prefix_rule9(char *word, char **stemmed_word, char **removed_part)
{
  int rc = 0;

  int split_rc = prefix_split_word("(^te)([^aeiour]er[^aeiou]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1 && dictionary_contains(*stemmed_word)) {
      rc = 1;
  }
  return rc;
}

int remove_complex_prefix_rule10(char *word, char **stemmed_word, char **removed_part)
{
  int rc = 0;

  int split_rc = prefix_split_word("(^me)([lrwy][aeiou]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1 && dictionary_contains(*stemmed_word)) {
      rc = 1;
  }
  return rc;
}

int remove_complex_prefix_rule11(char *word, char **stemmed_word, char **removed_part)
{
  int rc = 0;

  int split_rc = prefix_split_word("(^mem)([fbv]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1 && dictionary_contains(*stemmed_word)) {
      rc = 1;
  }

  return rc;
}

int remove_complex_prefix_rule12(char *word, char **stemmed_word, char **removed_part)
{
  int rc = 0;

  int split_rc = prefix_split_word("(^mem)(pe\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1 && dictionary_contains(*stemmed_word)) {
      rc = 1;
  }

  return rc;
}

int remove_complex_prefix_rule13(char *word, char **stemmed_word, char **removed_part)
{
  int rc = 0;

  int split_rc = prefix_split_word("(^me)(m[aeiou]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1 ) {
    if(dictionary_contains(*stemmed_word)) {
      rc = 1;
    } else {
      char *alternative_stemmed_word;
      asprintf(&alternative_stemmed_word, "p%s", *stemmed_word+1);
      rc = assign_if_root_word(stemmed_word, alternative_stemmed_word, removed_part, "me");
      free(alternative_stemmed_word);
    }
  }
  return rc;
}

int remove_complex_prefix_rule14(char *word, char **stemmed_word, char **removed_part)
{
  int rc = 0;

  int split_rc = prefix_split_word("(^men)([cdjstz]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1 && dictionary_contains(*stemmed_word)) {
      rc = 1;
  }
  return rc;
}

int remove_complex_prefix_rule15(char *word, char **stemmed_word, char **removed_part)
{
  int rc = 0;

  int split_rc = prefix_split_word("(^me)(n[aeiou]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1 ) {
    if(dictionary_contains(*stemmed_word)) {
      rc = 1;
    } else {
      char *alternative_stemmed_word;
      asprintf(&alternative_stemmed_word, "t%s", *stemmed_word+1);
      rc = assign_if_root_word(stemmed_word, alternative_stemmed_word, removed_part, "me");
      free(alternative_stemmed_word);
    }
  }
  return rc;
}

int remove_complex_prefix_rule16(char *word, char **stemmed_word, char **removed_part)
{
  int rc = 0;

  int split_rc = prefix_split_word("(^meng)([ghqk]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1 && dictionary_contains(*stemmed_word)) {
      rc = 1;
  }
  return rc;
}

int remove_complex_prefix_rule17(char *word, char **stemmed_word, char **removed_part)
{
  int rc = 0;
  char *alternative_stemmed_word;

  int split_rc = prefix_split_word("(^meng)([aeiou]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1) {
    if(dictionary_contains(*stemmed_word)) {
      rc = 1;
    }

    if(rc == 0) {
      asprintf(&alternative_stemmed_word, "k%s", *stemmed_word);
      rc = assign_if_root_word(stemmed_word, alternative_stemmed_word, removed_part, "meng");
      free(alternative_stemmed_word);
    }

    if(rc == 0) {
      asprintf(&alternative_stemmed_word, "%s", *stemmed_word+1);
      rc = assign_if_root_word(stemmed_word, alternative_stemmed_word, removed_part, "menge");
      free(alternative_stemmed_word);
    }

    if(rc == 0) {
      asprintf(&alternative_stemmed_word, "ng%s", *stemmed_word);
      rc = assign_if_root_word(stemmed_word, alternative_stemmed_word, removed_part, "me");
      free(alternative_stemmed_word);
    }
  }
  return rc;
}

int remove_complex_prefix_rule18(char *word, char **stemmed_word, char **removed_part)
{
  int rc = 0;

  int split_rc = prefix_split_word("(^me)(ny\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1 ) {
    if(dictionary_contains(*stemmed_word)) {
      rc = 1;
    } else {
      char *alternative_stemmed_word;
      asprintf(&alternative_stemmed_word, "s%s", *stemmed_word+2);
      rc = assign_if_root_word(stemmed_word, alternative_stemmed_word, removed_part, "meny");
      free(alternative_stemmed_word);
    }
  }
  return rc;
}

int remove_complex_prefix_rule19(char *word, char **stemmed_word, char **removed_part)
{
  int rc = 0;

  int split_rc = prefix_split_word("(^mem)(p[^e]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1 && dictionary_contains(*stemmed_word)) {
      rc = 1;
  }
  return rc;
}

int remove_complex_prefix_rule20(char *word, char **stemmed_word, char **removed_part)
{
  int rc = 0;

  int split_rc = prefix_split_word("(^pe)([wy][aeiou]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1 && dictionary_contains(*stemmed_word)) {
      rc = 1;
  }
  return rc;
}

int assign_if_root_word(char **stemmed_word, char *alternative_stemmed_word, char **removed_part, char *alternative_removed_part) {
  int rc = 0;

  if(dictionary_contains(alternative_stemmed_word)) {
    free(*removed_part);
    *removed_part = strndup(alternative_removed_part, strlen(alternative_removed_part));

    free(*stemmed_word);
    *stemmed_word = strndup(alternative_stemmed_word, strlen(alternative_stemmed_word));
    rc = 1;
  }

  return rc;
}
