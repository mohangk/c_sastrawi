#include "features.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
#include "sastrawi_internal.h"
#include "text_util.h"
#include "prefix_removers.h"
#include "remove_prefixes.h"
#include "../dbg.h"


int remove_plain_prefix(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc =  prefix_split_word(stemmer, "^(di|ke|se)(\\w+)$", word, removed_part, stemmed_word);

  if(split_rc == 1) {
      rc = PARTIALLY_STEMMED;

      if(dictionary_contains(*stemmed_word)) {
        rc = FULLY_STEMMED;
      }
  }

  return rc;
}

int remove_complex_prefix_rule1(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = prefix_split_word(stemmer, "(^ber)([aiueo].*)$", word, removed_part, stemmed_word);

  //1a
  if(split_rc == 1) {
    rc = PARTIALLY_STEMMED;
    if(dictionary_contains(*stemmed_word)) {
      rc = FULLY_STEMMED;
    } else {
      //1b
      char *alternative_stemmed_word;
      asprintf(&alternative_stemmed_word, "r%s", *stemmed_word);
      int alt_rc = assign_if_root_word(stemmed_word, alternative_stemmed_word, removed_part, "be");
      if(alt_rc == FULLY_STEMMED) {
        rc = FULLY_STEMMED;
      }
      free(alternative_stemmed_word);
    }
  }
  return rc;
}

int remove_complex_prefix_rule2(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = split_word3(stemmer, "(^ber)([^aeiou][a-z](\\w*))", word, removed_part, stemmed_word, "er");

  if(split_rc == 1) {
      rc = PARTIALLY_STEMMED;

      if(dictionary_contains(*stemmed_word)) {
        rc = FULLY_STEMMED;
      }
  }

  return rc;
}

int remove_complex_prefix_rule3(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = prefix_split_word(stemmer, "(^ber)([^aeiour][a-z]er[aeiou]\\w*)", word, removed_part, stemmed_word);


  if(split_rc == 1) {
      rc = PARTIALLY_STEMMED;

      if(dictionary_contains(*stemmed_word)) {
        rc = FULLY_STEMMED;
      }
  }

  return rc;
}

int remove_complex_prefix_rule4(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = prefix_split_word(stemmer, "(^bel)(ajar\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1) {
      rc = PARTIALLY_STEMMED;

      if(dictionary_contains(*stemmed_word)) {
        rc = FULLY_STEMMED;
      }
  }

  return rc;
}

int remove_complex_prefix_rule5(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = prefix_split_word(stemmer, "(^be)([^aeiour]er[^aeiou]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1) {
      rc = PARTIALLY_STEMMED;

      if(dictionary_contains(*stemmed_word)) {
        rc = FULLY_STEMMED;
      }
  }
  return rc;
}

int remove_complex_prefix_rule6(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = prefix_split_word(stemmer, "(^ter)([aiueo].*)$", word, removed_part, stemmed_word);

  //6a
  if(split_rc == 1) {
    rc = PARTIALLY_STEMMED;
    if(dictionary_contains(*stemmed_word)) {
      rc = FULLY_STEMMED;
    } else {
  //6b
      char *alternative_stemmed_word;
      asprintf(&alternative_stemmed_word, "r%s", *stemmed_word);
      int alt_rc = assign_if_root_word(stemmed_word, alternative_stemmed_word, removed_part, "te");
      if(alt_rc == FULLY_STEMMED) {
        rc = alt_rc;
      }
      free(alternative_stemmed_word);
    }

  }
  return rc;
}

int remove_complex_prefix_rule7(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = prefix_split_word(stemmer, "(^ter)([^aeiour]er[aeiou]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1) {
    rc = PARTIALLY_STEMMED;
      if(dictionary_contains(*stemmed_word)) {
        rc = FULLY_STEMMED;
      }
  }

  return rc;
}

int remove_complex_prefix_rule8(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = split_word3(stemmer, "(^ter)([^aeiour](\\w*))", word, removed_part, stemmed_word, "er");

  if(split_rc == 1) {
      rc = PARTIALLY_STEMMED;

      if(dictionary_contains(*stemmed_word)) {
        rc = FULLY_STEMMED;
      }
  }


  return rc;
}

int remove_complex_prefix_rule9(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = prefix_split_word(stemmer, "(^te)([^aeiour]er[^aeiou]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1) {
    rc = PARTIALLY_STEMMED;
    if(dictionary_contains(*stemmed_word)) {
      rc = FULLY_STEMMED;
    }
  }
  return rc;
}

int remove_complex_prefix_rule10(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = prefix_split_word(stemmer, "(^me)([lrwy][aeiou]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1) { 
    rc = PARTIALLY_STEMMED;
    if(dictionary_contains(*stemmed_word)) {
      rc = FULLY_STEMMED;
    }
  }
  return rc;
}

int remove_complex_prefix_rule11(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = prefix_split_word(stemmer, "(^mem)([fbv]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1) { 
    rc = PARTIALLY_STEMMED;
    if(dictionary_contains(*stemmed_word)) {
      rc = FULLY_STEMMED;
    }
  }

  return rc;
}

int remove_complex_prefix_rule12(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = prefix_split_word(stemmer, "(^mem)(pe\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1) { 
    rc = PARTIALLY_STEMMED;
    if(dictionary_contains(*stemmed_word)) {
      rc = FULLY_STEMMED;
    }
  }

  return rc;
}

int remove_complex_prefix_rule13(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = prefix_split_word(stemmer, "(^me)(m[aeiou]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1 ) {
    rc = PARTIALLY_STEMMED;
    if(dictionary_contains(*stemmed_word)) {
      rc = FULLY_STEMMED;
    } else {
      char *alternative_stemmed_word;
      asprintf(&alternative_stemmed_word, "p%s", *stemmed_word+1);
      int alt_rc = assign_if_root_word(stemmed_word, alternative_stemmed_word, removed_part, "me");
      if(alt_rc == FULLY_STEMMED) {
        rc = FULLY_STEMMED;
      }
      free(alternative_stemmed_word);
    }
  }
  return rc;
}

int remove_complex_prefix_rule14(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = prefix_split_word(stemmer, "(^men)([cdjstz]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1) {
    rc = PARTIALLY_STEMMED;
    if(dictionary_contains(*stemmed_word)) {
      rc = FULLY_STEMMED;
    }
  }
  return rc;
}

int remove_complex_prefix_rule15(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = prefix_split_word(stemmer, "(^me)(n[aeiou]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1 ) {
    rc = PARTIALLY_STEMMED;
    if(dictionary_contains(*stemmed_word)) {
      rc = FULLY_STEMMED;
    } else {
      char *alternative_stemmed_word;
      asprintf(&alternative_stemmed_word, "t%s", *stemmed_word+1);
      int alt_rc = assign_if_root_word(stemmed_word, alternative_stemmed_word, removed_part, "me");
      if(alt_rc == FULLY_STEMMED) {
        rc = FULLY_STEMMED;
      }
      free(alternative_stemmed_word);
    }
  }
  return rc;
}

int remove_complex_prefix_rule16(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = prefix_split_word(stemmer, "(^meng)([ghqk]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1) {
    rc = PARTIALLY_STEMMED;
    if(dictionary_contains(*stemmed_word)) {
      rc = FULLY_STEMMED;
    }
  }
  return rc;
}

int remove_complex_prefix_rule17(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;
  int alt_rc = NOT_STEMMED;
  char *alternative_stemmed_word;

  int split_rc = prefix_split_word(stemmer, "(^meng)([aeiou]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1) {

    rc = PARTIALLY_STEMMED;
    if(dictionary_contains(*stemmed_word)) {
      rc = FULLY_STEMMED;
    } 

    if(rc != FULLY_STEMMED) {
      asprintf(&alternative_stemmed_word, "k%s", *stemmed_word);
      alt_rc = assign_if_root_word(stemmed_word, alternative_stemmed_word, removed_part, "meng");

      if(alt_rc == FULLY_STEMMED) {
        rc = FULLY_STEMMED;
      }
      free(alternative_stemmed_word);
    }

    if(rc != FULLY_STEMMED) {
      asprintf(&alternative_stemmed_word, "%s", *stemmed_word+1);
      alt_rc = assign_if_root_word(stemmed_word, alternative_stemmed_word, removed_part, "menge");
      if(alt_rc == FULLY_STEMMED) {
        rc = FULLY_STEMMED;
      }
      free(alternative_stemmed_word);
    }

    if(rc != FULLY_STEMMED) {
      asprintf(&alternative_stemmed_word, "ng%s", *stemmed_word);
      alt_rc = assign_if_root_word(stemmed_word, alternative_stemmed_word, removed_part, "me");
      if(alt_rc == FULLY_STEMMED) {
        rc = FULLY_STEMMED;
      }
      free(alternative_stemmed_word);
    }
  }
  return rc;
}

int remove_complex_prefix_rule18(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = prefix_split_word(stemmer, "(^me)(ny\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1 ) {
    rc = PARTIALLY_STEMMED;
    if(dictionary_contains(*stemmed_word)) {
      rc = FULLY_STEMMED;
    } else {
      char *alternative_stemmed_word;
      asprintf(&alternative_stemmed_word, "s%s", *stemmed_word+2);
      int alt_rc = assign_if_root_word(stemmed_word, alternative_stemmed_word, removed_part, "meny");
      if(alt_rc == FULLY_STEMMED) {
        rc = FULLY_STEMMED;
      }
      free(alternative_stemmed_word);
    }
  }
  return rc;
}

int remove_complex_prefix_rule19(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = prefix_split_word(stemmer, "(^mem)(p[^e]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1) {
    rc = PARTIALLY_STEMMED;
    if(dictionary_contains(*stemmed_word)) {
      rc = FULLY_STEMMED;
    }
  }
  return rc;
}

int remove_complex_prefix_rule20(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = prefix_split_word(stemmer, "(^pe)([wy][aeiou]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1) {
    rc = PARTIALLY_STEMMED;
    if(dictionary_contains(*stemmed_word)) {
      rc = FULLY_STEMMED;
    }
  }
  return rc;
}

int remove_complex_prefix_rule21(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = prefix_split_word(stemmer, "(^per)([aiueo].*)$", word, removed_part, stemmed_word);

  //21a
  if(split_rc == 1) {
    rc = PARTIALLY_STEMMED;
    if(dictionary_contains(*stemmed_word)) {
      rc = FULLY_STEMMED;
    } else {
      //1b
      char *alternative_stemmed_word;
      asprintf(&alternative_stemmed_word, "r%s", *stemmed_word);
      int alt_rc = assign_if_root_word(stemmed_word, alternative_stemmed_word, removed_part, "pe");
      if(alt_rc == FULLY_STEMMED) {
        rc = FULLY_STEMMED;
      }
      free(alternative_stemmed_word);
    }
  }
  return rc;
}

int remove_complex_prefix_rule23(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = split_word3(stemmer, "(^per)([^aeiou][a-z](\\w*))", word, removed_part, stemmed_word, "er");

  if(split_rc == 1) {
      rc = PARTIALLY_STEMMED;

      if(dictionary_contains(*stemmed_word)) {
        rc = FULLY_STEMMED;
      }
  }

  return rc;
}

int remove_complex_prefix_rule24(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = prefix_split_word(stemmer, "(^per)([^aeiour][a-z]er[aeiou]\\w*)", word, removed_part, stemmed_word);


  if(split_rc == 1) {
      rc = PARTIALLY_STEMMED;

      if(dictionary_contains(*stemmed_word)) {
        rc = FULLY_STEMMED;
      }
  }

  return rc;
}

int remove_complex_prefix_rule25(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = prefix_split_word(stemmer, "(^pem)([fbv]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1) { 
    rc = PARTIALLY_STEMMED;
    if(dictionary_contains(*stemmed_word)) {
      rc = FULLY_STEMMED;
    }
  }

  return rc;
}

int remove_complex_prefix_rule26(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = prefix_split_word(stemmer, "(^pe)(m[aeiou]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1 ) {
    rc = PARTIALLY_STEMMED;
    if(dictionary_contains(*stemmed_word)) {
      rc = FULLY_STEMMED;
    } else {
      char *alternative_stemmed_word;
      asprintf(&alternative_stemmed_word, "p%s", *stemmed_word+1);
      int alt_rc = assign_if_root_word(stemmed_word, alternative_stemmed_word, removed_part, "pe");
      if(alt_rc == FULLY_STEMMED) {
        rc = FULLY_STEMMED;
      }
      free(alternative_stemmed_word);
    }
  }
  return rc;
}

int remove_complex_prefix_rule27(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = prefix_split_word(stemmer, "(^pen)([cdjz]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1) {
    rc = PARTIALLY_STEMMED;
    if(dictionary_contains(*stemmed_word)) {
      rc = FULLY_STEMMED;
    }
  }
  return rc;
}


int remove_complex_prefix_rule28(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = prefix_split_word(stemmer, "(^pe)(n[aeiou]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1 ) {
    rc = PARTIALLY_STEMMED;
    if(dictionary_contains(*stemmed_word)) {
      rc = FULLY_STEMMED;
    } else {
      char *alternative_stemmed_word;
      asprintf(&alternative_stemmed_word, "t%s", *stemmed_word+1);
      int alt_rc = assign_if_root_word(stemmed_word, alternative_stemmed_word, removed_part, "pe");
      if(alt_rc == FULLY_STEMMED) {
        rc = FULLY_STEMMED;
      }
      free(alternative_stemmed_word);
    }
  }
  return rc;
}

int remove_complex_prefix_rule29(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;

  int split_rc = prefix_split_word(stemmer, "(^peng)([ghqk]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1) {
    rc = PARTIALLY_STEMMED;
    if(dictionary_contains(*stemmed_word)) {
      rc = FULLY_STEMMED;
    }
  }
  return rc;
}

int remove_complex_prefix_rule30(sastrawi_stemmer *stemmer, char *word, char **stemmed_word, char **removed_part)
{
  int rc = NOT_STEMMED;
  int alt_rc = NOT_STEMMED;
  char *alternative_stemmed_word;

  int split_rc = prefix_split_word(stemmer, "(^peng)([aeiou]\\w*)", word, removed_part, stemmed_word);

  if(split_rc == 1 ) {
    rc = PARTIALLY_STEMMED;
    if(dictionary_contains(*stemmed_word)) {
      rc = FULLY_STEMMED;
    } 

    if(rc != FULLY_STEMMED) {
      asprintf(&alternative_stemmed_word, "k%s", *stemmed_word);
      alt_rc = assign_if_root_word(stemmed_word, alternative_stemmed_word, removed_part, "peng");
      if(alt_rc == FULLY_STEMMED) {
        rc = FULLY_STEMMED;
      }
      free(alternative_stemmed_word);
    }

    if(rc != FULLY_STEMMED) {
      asprintf(&alternative_stemmed_word, "%s", *stemmed_word+1);
      alt_rc = assign_if_root_word(stemmed_word, alternative_stemmed_word, removed_part, "penge");
      if(alt_rc == FULLY_STEMMED) {
        rc = FULLY_STEMMED;
      }
      free(alternative_stemmed_word);
    }
  }
  return rc;
}

int assign_if_root_word(char **stemmed_word, char *alternative_stemmed_word, char **removed_part, char *alternative_removed_part) {
  int rc = NOT_STEMMED;

  if(dictionary_contains(alternative_stemmed_word)) {
    free(*removed_part);
    *removed_part = strdup(alternative_removed_part);

    free(*stemmed_word);
    *stemmed_word = strdup(alternative_stemmed_word);
    rc = FULLY_STEMMED;
  }

  return rc;
}
