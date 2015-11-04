#ifdef __linux
  #define _GNU_SOURCE 
#endif
#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sastrawi.h"
#include "../dbg.h"

char *test_stem_singular_word() 
{
  char *word = "bola";
  char *stemmed_word = NULL;
  int rc = stem_singular_word(word, &stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("bola", stemmed_word) == 0, "if the word exists in the dictionary, just return it");
  free(stemmed_word);
  return NULL;
}

char *test_stem_singular_word_removes_plain_prefixes() 
{
  char *word = "kerajinannya";
  char *stemmed_word = NULL;
  int rc = stem_singular_word(word, &stemmed_word);
  debug("stem word: %s, expected: rajin, actual: %s", word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("rajin", stemmed_word) == 0, "it stems to rajin");
  free(stemmed_word);

  return NULL;
}

char *test_stem_singular_word_removes_suffixes() 
{
  char *word = "bajumukah";
  char *stemmed_word = NULL;
  int rc = stem_singular_word(word, &stemmed_word);
  debug("stem word: %s, expected: baju, actual: %s", word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("baju", stemmed_word) == 0, "it stems to baju");
  free(stemmed_word);

  return NULL;
}

char *test_stem_singular_word_removes_complex_prefixes_1() 
{
  char *word = "beria";
  char *stemmed_word = NULL;
  int rc = stem_singular_word(word, &stemmed_word);
  debug("stem word: %s, expected: ia, actual: %s", word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("ia", stemmed_word) == 0, "it stems to ia");
  free(stemmed_word);

  return NULL;
}


char *test_stem_singular_word_removes_complex_prefixes_2() 
{
  char *word = "bertabur";
  char *stemmed_word = NULL;
  int rc = stem_singular_word(word, &stemmed_word);
  debug("stem word: %s, expected: tabur, actual: %s", word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("tabur", stemmed_word) == 0, "it stems to tabur");
  free(stemmed_word);

  return NULL;
}

char *test_stem_singular_word_removes_complex_prefixes_3() 
{
  char *word = "berdaerah";
  char *stemmed_word = NULL;
  int rc = stem_singular_word(word, &stemmed_word);
  debug("stem word: %s, expected: daerah, actual: %s", word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("daerah", stemmed_word) == 0, "it stems to daerah");
  free(stemmed_word);

  return NULL;
}
