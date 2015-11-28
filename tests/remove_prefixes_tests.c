#ifdef __linux
  #define _GNU_SOURCE 
#endif
#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libsastrawi.h"
#include "dbg.h"


char *test_remove_plain_prefix_returns_0_if_word_notin_dictionary() 
{
  char *stemmed_word = NULL; 
  char *removed_part = NULL;

  int rc = remove_plain_prefix("dipertikai", &stemmed_word, &removed_part);

  mu_assert(rc == 0, "successfully stems but not in dictionary");
  mu_assert(strcmp("pertikai", stemmed_word) == 0, "we expect 'pertikai' as the stemmed word");
  mu_assert(strcmp("di", removed_part) == 0, "we expect 'di' as the removed part");

  return NULL;
}

char *test_remove_plain_prefix_di() 
{
  char *stemmed_word = NULL; 
  char *removed_part = NULL;

  int rc = remove_plain_prefix("dicinta", &stemmed_word, &removed_part);

  mu_assert(rc == 1, "successfully stems");
  mu_assert(strcmp("cinta", stemmed_word) == 0, "we expect 'sana' as the stemmed word");
  mu_assert(strcmp("di", removed_part) == 0, "we expect 'di' as the removed part");

  return NULL;
}

char *test_remove_plain_prefix_ke() 
{
  char *stemmed_word = NULL; 
  char *removed_part = NULL;

  int rc = remove_plain_prefix("kesana", &stemmed_word, &removed_part);

  mu_assert(rc == 1, "successfully stems");
  mu_assert(strcmp("sana", stemmed_word) == 0, "we expect 'sana' as the stemmed word");
  mu_assert(strcmp("ke", removed_part) == 0, "we expect 'ke' as the removed part");

  return NULL;
}

char *test_remove_plain_prefix_se() 
{
  char *stemmed_word = NULL; 
  char *removed_part = NULL;

  int rc = remove_plain_prefix("sejenis", &stemmed_word, &removed_part);

  mu_assert(rc == 1, "successfully stems");
  mu_assert(strcmp("jenis", stemmed_word) == 0, "we expect 'jenis' as the stemmed word");
  mu_assert(strcmp("se", removed_part) == 0, "we expect 'se' as the removed part");

  return NULL;
}



char *test_remove_complex_prefix_rule1_a() 
{
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = remove_complex_prefix_rule1("beria", &stemmed_word, &removed_part);
  debug("stem word: beria, expected: ia, actual: %s", stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("ia", stemmed_word) == 0, "it stems to ia");
  mu_assert(strcmp("ber", removed_part) == 0, "remove part should be ber");
  free(stemmed_word);
  free(removed_part);

  return NULL;
}

char *test_remove_complex_prefix_rule1_b() 
{
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = remove_complex_prefix_rule1("berakit", &stemmed_word, &removed_part);
  debug("stem word: berakit, expected: rakit, actual: %s", stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("rakit", stemmed_word) == 0, "it stems to rakit");
  mu_assert(strcmp("be", removed_part) == 0, "remove part should be be");
  free(stemmed_word);
  free(removed_part);

  return NULL;
}

char *test_remove_complex_prefix_rule2() 
{
  char *word = "berkop";
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = remove_complex_prefix_rule2(word, &stemmed_word, &removed_part);
  debug("stem word: %s, expected: kop, actual: %s", word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("kop", stemmed_word) == 0, "it stems to kop");
  mu_assert(strcmp("ber", removed_part) == 0, "remove part should be ber");
  free(stemmed_word);
  free(removed_part);

  return NULL;
}

char *test_remove_complex_prefix_rule2_excludes_er() 
{
  char *word = "berdaerah";
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = remove_complex_prefix_rule2(word, &stemmed_word, &removed_part);
  debug("stem word: %s, expected: berdaerah, actual: %s", word, stemmed_word);
  mu_assert(rc == 0, "does not stem");
  mu_assert(strcmp("berdaerah", stemmed_word) == 0, "it does not stem it");
  free(stemmed_word);
  free(removed_part);

  return NULL;
}

char *test_remove_complex_prefix_rule3_only_includes_er() 
{
  char *stemable_word = "berdaerah";
  char *nonstemable_word = "bertabur";
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = remove_complex_prefix_rule3(stemable_word, &stemmed_word, &removed_part);
  debug("stem word: %s, expected: daerah, actual: %s", stemable_word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("daerah", stemmed_word) == 0, "it stems to daerah");
  mu_assert(strcmp("ber", removed_part) == 0, "remove part should be ber");
  free(stemmed_word);
  free(removed_part);
 
  rc = remove_complex_prefix_rule3(nonstemable_word, &stemmed_word, &removed_part);
  mu_assert(rc == 0, "cannot stem");
  free(stemmed_word);
  free(removed_part);

  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  dictionary_load(dictionary_fullpath("data/kata-dasar.txt"));

  mu_run_test(test_remove_plain_prefix_returns_0_if_word_notin_dictionary)
  mu_run_test(test_remove_plain_prefix_di);
  mu_run_test(test_remove_plain_prefix_ke);
  mu_run_test(test_remove_plain_prefix_se);
  mu_run_test(test_remove_complex_prefix_rule1_a);
  mu_run_test(test_remove_complex_prefix_rule1_b);
  mu_run_test(test_remove_complex_prefix_rule2);
  mu_run_test(test_remove_complex_prefix_rule2_excludes_er);
  mu_run_test(test_remove_complex_prefix_rule3_only_includes_er);

  return NULL;
}

RUN_TESTS(all_tests);
