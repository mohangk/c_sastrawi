#ifdef __linux
  #define _GNU_SOURCE 
#endif
#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libsastrawi.h"
#include "dbg.h"

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

char *test_stem_singular_word_removes_complex_prefixes_4() 
{
  char *word = "belajar";
  char *stemmed_word = NULL;
  int rc = stem_singular_word(word, &stemmed_word);
  debug("stem word: %s, expected: ajar, actual: %s", word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("ajar", stemmed_word) == 0, "it stems to ajar");
  free(stemmed_word);

  return NULL;
}

char *test_stem_singular_word_removes_complex_prefixes_5() 
{
  char *word = "bekerja";
  char *stemmed_word = NULL;
  int rc = stem_singular_word(word, &stemmed_word);
  debug("stem word: %s, expected: kerja, actual: %s", word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("kerja", stemmed_word) == 0, "it stems to kerja");
  free(stemmed_word);

  return NULL;
}

char *test_stem_singular_word_removes_complex_prefixes_6() 
{
  char *word = "teracun";
  char *stemmed_word = NULL;
  int rc = stem_singular_word(word, &stemmed_word);
  debug("stem word: %s, expected: racun, actual: %s", word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("racun", stemmed_word) == 0, "it stems to kerja");
  free(stemmed_word);

  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  dictionary_load(dictionary_fullpath("data/kata-dasar.txt"));

  mu_run_test(test_stem_singular_word);
  mu_run_test(test_stem_singular_word_removes_suffixes);

  mu_run_test(test_stem_singular_word_removes_plain_prefixes);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_1);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_2);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_3);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_4);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_5);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_6);

  return NULL;
}

RUN_TESTS(all_tests);
