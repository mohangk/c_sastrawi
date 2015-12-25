#ifdef __linux
  #define _GNU_SOURCE 
#endif
#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libsastrawi.h"
#include "sastrawi/remove_prefixes.h"
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

char *test_remove_complex_prefix_rule4() 
{
  char *stemable_word = "belajar";
  char *nonstemable_word = "bertabur";
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = remove_complex_prefix_rule4(stemable_word, &stemmed_word, &removed_part);
  debug("stem word: %s, expected: ajar, actual: %s", stemable_word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("ajar", stemmed_word) == 0, "it stems to ajar");
  mu_assert(strcmp("bel", removed_part) == 0, "remove part should be bel");
  free(stemmed_word);
  free(removed_part);
 
  rc = remove_complex_prefix_rule4(nonstemable_word, &stemmed_word, &removed_part);
  mu_assert(rc == 0, "cannot stem");
  free(stemmed_word);
  free(removed_part);

  return NULL;
}

char *test_remove_complex_prefix_rule5() 
{
  char *stemable_word = "bekerja";
  char *nonstemable_word = "berlari";
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = remove_complex_prefix_rule5(stemable_word, &stemmed_word, &removed_part);
  debug("stem word: %s, expected: kerja, actual: %s", stemable_word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("kerja", stemmed_word) == 0, "it stems to kerja");
  mu_assert(strcmp("be", removed_part) == 0, "remove part should be be");
  free(stemmed_word);
  free(removed_part);
 
  rc = remove_complex_prefix_rule5(nonstemable_word, &stemmed_word, &removed_part);
  mu_assert(rc == 0, "cannot stem");
  free(stemmed_word);
  free(removed_part);

  return NULL;
}

char *test_remove_complex_prefix_rule6a() 
{
  char *stemable_word = "terancam";
  char *nonstemable_word = "terbalik";
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = remove_complex_prefix_rule6(stemable_word, &stemmed_word, &removed_part);
  debug("stem word: %s, expected: ancam, actual: %s", stemable_word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("ancam", stemmed_word) == 0, "it stems to ancam");
  mu_assert(strcmp("ter", removed_part) == 0, "remove part should be be");
  free(stemmed_word);
  free(removed_part);
 
  rc = remove_complex_prefix_rule6(nonstemable_word, &stemmed_word, &removed_part);
  mu_assert(rc == 0, "cannot stem");
  free(stemmed_word);
  free(removed_part);

  return NULL;
}

char *test_remove_complex_prefix_rule6b() 
{
  char *stemable_word = "teracun";
  char *nonstemable_word = "terbalik";
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = remove_complex_prefix_rule6(stemable_word, &stemmed_word, &removed_part);
  debug("stem word: %s, expected: racun, actual: %s", stemable_word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("racun", stemmed_word) == 0, "it stems to racun");
  mu_assert(strcmp("te", removed_part) == 0, "remove part should be te");
  free(stemmed_word);
  free(removed_part);
 
  rc = remove_complex_prefix_rule6(nonstemable_word, &stemmed_word, &removed_part);
  mu_assert(rc == 0, "cannot stem");
  free(stemmed_word);
  free(removed_part);

  return NULL;
}

char *test_remove_complex_prefix_rule7() 
{
  char *stemable_word = "terperuk";
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = remove_complex_prefix_rule7(stemable_word, &stemmed_word, &removed_part);
  debug("stem word: %s, expected: peruk, actual: %s", stemable_word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("peruk", stemmed_word) == 0, "it stems to peruk");
  mu_assert(strcmp("ter", removed_part) == 0, "remove part should be ter");
  free(stemmed_word);
  free(removed_part);
  return NULL;
}

char *test_remove_complex_prefix_rule8() 
{
  char *stemable_word = "tertangkap";
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = remove_complex_prefix_rule8(stemable_word, &stemmed_word, &removed_part);
  debug("stem word: %s, expected: tangkap, actual: %s", stemable_word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("tangkap", stemmed_word) == 0, "it stems to tangkap");
  mu_assert(strcmp("ter", removed_part) == 0, "remove part should be ter");
  free(stemmed_word);
  free(removed_part);
  return NULL;
}

char *test_remove_complex_prefix(char *stemable_word, char *expected_stemmed_word, char *expected_removed_part, PREFIX_REMOVER fn)
{  
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = fn(stemable_word, &stemmed_word, &removed_part);
  debug("word: %s, expected stemmed word: %s, actual stemmed word: %s, expected removed part: %s, actual removed part: %s", stemable_word, expected_stemmed_word, stemmed_word, expected_removed_part, removed_part);
  mu_assert(rc == 1, "failed to stem");
  mu_assert(strcmp(expected_stemmed_word, stemmed_word) == 0, "failed while asserting stemmed word");
  mu_assert(strcmp(expected_removed_part, removed_part) == 0, "failed while asserting removed part");
  free(stemmed_word);
  free(removed_part);
  return NULL;
}

char *test_remove_complex_prefix_rule9() 
{
  return test_remove_complex_prefix("teterbang", "terbang", "te",  remove_complex_prefix_rule9);
}

char *test_remove_complex_prefix_rule10_l() 
{
  return test_remove_complex_prefix("melalu", "lalu", "me",  remove_complex_prefix_rule10);
}

char *test_remove_complex_prefix_rule10_r() 
{
  return test_remove_complex_prefix("meracun", "racun", "me",  remove_complex_prefix_rule10);
}

char *test_remove_complex_prefix_rule10_w() 
{
  return test_remove_complex_prefix("mewarna", "warna", "me",  remove_complex_prefix_rule10);
}

char *test_remove_complex_prefix_rule10_y() 
{
  return test_remove_complex_prefix("meyakin", "yakin", "me",  remove_complex_prefix_rule10);
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
  mu_run_test(test_remove_complex_prefix_rule4);
  mu_run_test(test_remove_complex_prefix_rule5);
  mu_run_test(test_remove_complex_prefix_rule6a);
  mu_run_test(test_remove_complex_prefix_rule6b);
  mu_run_test(test_remove_complex_prefix_rule7);
  mu_run_test(test_remove_complex_prefix_rule8);
  mu_run_test(test_remove_complex_prefix_rule9);
  mu_run_test(test_remove_complex_prefix_rule10_l);
  mu_run_test(test_remove_complex_prefix_rule10_r);
  mu_run_test(test_remove_complex_prefix_rule10_w);
  mu_run_test(test_remove_complex_prefix_rule10_y);

  return NULL;
}

RUN_TESTS(all_tests);
