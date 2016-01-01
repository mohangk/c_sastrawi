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

const int prefix_remover_count = 17;

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
  remove_complex_prefix_rule16
};


int remove_prefixes(char *original_word, char **stemmed_word)
{
  int rc = 0;
  char *removed_parts = NULL;

  char *word = strndup(original_word, strlen(original_word));

  for(int i =0; i < prefix_remover_count; i++) {

    char *post_remove = NULL;
    rc = (*prefix_removers[i])(word, &post_remove, &removed_parts);

    if(rc) {
      *stemmed_word = strndup(post_remove, strlen(post_remove));
      break;
    } else {
      free(word);
      word = strndup(post_remove, strlen(post_remove));
    }
    //cleanup
    free(post_remove);
    free(removed_parts);

  }

  return rc;
}

int remove_plain_prefix(char *word, char **stemmed_word, char **removed_part)
{
  int rc = 0;

  int split_rc =  prefix_split_word("^(di|ke|se)(\\w+)$", word, removed_part, stemmed_word);

  if(split_rc == 1 && dictionary_contains(*stemmed_word)) {
      rc = 1;
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
      char *rule_b_word;
      asprintf(&rule_b_word, "r%s", *stemmed_word);

      if(dictionary_contains(rule_b_word)) {
        free(*removed_part);
        *removed_part = strndup("be",2);

        free(*stemmed_word);
        *stemmed_word = strndup(rule_b_word, strlen(rule_b_word));
        rc = 1;
      }
    }
  }
  return rc;
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

  int split_rc = prefix_split_word("(^ber)([^aeiou][a-z]er\\w*)", word, removed_part, stemmed_word);


  if(split_rc == 1 && dictionary_contains(*stemmed_word)) {
      rc = 1;
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
      char *rule_b_word;
      asprintf(&rule_b_word, "r%s", *stemmed_word);

      if(dictionary_contains(rule_b_word)) {
        free(*removed_part);
        *removed_part = strndup("te",2);

        free(*stemmed_word);
        *stemmed_word = strndup(rule_b_word, strlen(rule_b_word));
        rc = 1;
      } 
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
  int rc = 0;
  char *partial_stemmed_word;

  int split_rc = split_word3("(^ter)([^aeiour](\\w*))", word, removed_part, stemmed_word, &partial_stemmed_word);

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

int remove_complex_prefix_rule9(char *word, char **stemmed_word, char **removed_part)
{
  int rc = 0;
  char *partial_stemmed_word;

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

      char *rule_b_word;

      asprintf(&rule_b_word, "p%s", *stemmed_word+1);

      if(dictionary_contains(rule_b_word)) {
        free(*removed_part);
        *removed_part = strndup("me",2);

        free(*stemmed_word);
        *stemmed_word = strndup(rule_b_word, strlen(rule_b_word));
        rc = 1;
      } 
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

      char *rule_b_word;
      asprintf(&rule_b_word, "t%s", *stemmed_word+1);

      if(dictionary_contains(rule_b_word)) {
        free(*removed_part);
        *removed_part = strndup("me",2);

        free(*stemmed_word);
        *stemmed_word = strndup(rule_b_word, strlen(rule_b_word));
        rc = 1;
      } 
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
