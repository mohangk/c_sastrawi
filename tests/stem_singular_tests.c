#ifdef __linux
  #define _GNU_SOURCE 
#endif
#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libsastrawi.h"
#include "dbg.h"

char *test_stem_singular_word_for(char *word, char *expected_stem_word) 
{
  char *stemmed_word = NULL;
  int rc = stem_singular_word(word, &stemmed_word);
  debug("stem word: %s, expected: %s, actual: %s", word, expected_stem_word, stemmed_word);
  mu_assert(rc == 1, "failed to stem");
  mu_assert(strcmp(expected_stem_word, stemmed_word) == 0, "failed to stem correctly");
  free(stemmed_word);

  return NULL;
}

char *test_stem_singular_word_does_not_need_stemming() 
{
  return test_stem_singular_word_for("bola", "bola");
}

char *test_stem_singular_word_returns_original_word_when_cannot_stem()
{

  char *stemmed_word;
  char *word = "beblahblahan";
  char *expected_stem_word = "beblahblahan";
  int rc = stem_singular_word(word, &stemmed_word);
  debug("stem word: %s, expected: %s, actual: %s", word, expected_stem_word, stemmed_word);
  mu_assert(rc == 0, "did not fail to stem");
  mu_assert(strcmp(expected_stem_word, stemmed_word) == 0, "should not change the word");
  free(stemmed_word);
  return NULL;
}

char *test_stem_singular_word_removes_plain_prefixes() 
{
  return test_stem_singular_word_for("kerajinannya", "rajin");
}

char *test_stem_singular_word_removes_suffixes() 
{
  return test_stem_singular_word_for("bajumukah", "baju");
}

char *test_stem_singular_word_removes_complex_prefixes_1() 
{
  return test_stem_singular_word_for("beria", "ia");
}

char *test_stem_singular_word_removes_complex_prefixes_2() 
{
  return test_stem_singular_word_for("bertabur", "tabur");
}

char *test_stem_singular_word_removes_complex_prefixes_3() 
{
  return test_stem_singular_word_for("berdaerah", "daerah");
}

char *test_stem_singular_word_removes_complex_prefixes_4() 
{
  return test_stem_singular_word_for("belajar", "ajar");
}

char *test_stem_singular_word_removes_complex_prefixes_5() 
{
  return test_stem_singular_word_for("bekerja", "kerja");
}

char *test_stem_singular_word_removes_complex_prefixes_6() 
{
  return test_stem_singular_word_for("teracun", "racun");
}

char *test_stem_singular_word_removes_complex_prefixes_7() 
{
  return test_stem_singular_word_for("terperuk", "peruk");
}

char *test_stem_singular_word_removes_complex_prefixes_8() 
{
  return test_stem_singular_word_for("tertangkap", "tangkap");
}

char *test_stem_singular_word_removes_complex_prefixes_9() 
{
  return test_stem_singular_word_for("teterbang", "terbang");
}

char *test_stem_singular_word_removes_complex_prefixes_10() 
{
  return test_stem_singular_word_for("mewarnai", "warna");
}

char *test_stem_singular_word_removes_complex_prefixes_11() 
{
  return test_stem_singular_word_for("memfasilitasi", "fasilitas");
}

char *test_stem_singular_word_removes_complex_prefixes_12() 
{
  return test_stem_singular_word_for("mempengaruhi", "pengaruh");
}

char *test_stem_singular_word_removes_complex_prefixes_13() 
{
  return test_stem_singular_word_for("memasuki", "masuk");
}

char *test_stem_singular_word_removes_complex_prefixes_14() 
{
  return test_stem_singular_word_for("mentaati", "taat");
}

char *test_stem_singular_word_removes_complex_prefixes_15() 
{
  return test_stem_singular_word_for("menikmati", "nikmat");
}

char *test_stem_singular_word_removes_complex_prefixes_16() 
{
  return test_stem_singular_word_for("mengqasar", "qasar");
}

char *test_stem_singular_word_removes_complex_prefixes_17() 
{
  return test_stem_singular_word_for("mengecil", "kecil");
}

char *test_stem_singular_word_removes_complex_prefixes_18() 
{
  return test_stem_singular_word_for("menyapu", "sapu");
}

char *test_stem_singular_word_removes_complex_prefixes_19() 
{
  return test_stem_singular_word_for("memprotes", "protes");
}

char *test_stem_singular_word_removes_complex_prefixes_20() 
{
  return test_stem_singular_word_for("peyoga", "yoga");
}

char *test_stem_singular_word_uses_precedence_adjustment()
{
  return test_stem_singular_word_for("memakai","pakai");
}

char *test_stem_singular_word_uses_precedence_adjustment_2()
{
  return test_stem_singular_word_for("didiamkan","diam");
}


char *all_tests()
{
  mu_suite_start();

  char *path = dictionary_fullpath("data/kata-dasar.txt");
  dictionary_load(path);
  free(path);

  mu_run_test(test_stem_singular_word_does_not_need_stemming);
  mu_run_test(test_stem_singular_word_returns_original_word_when_cannot_stem);
  mu_run_test(test_stem_singular_word_removes_suffixes);

  mu_run_test(test_stem_singular_word_removes_plain_prefixes);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_1);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_2);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_3);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_4);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_5);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_6);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_7);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_8);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_9);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_10);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_11);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_12);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_13);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_14);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_15);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_16);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_17);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_18);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_19);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_20);
  mu_run_test(test_stem_singular_word_uses_precedence_adjustment);
  mu_run_test(test_stem_singular_word_uses_precedence_adjustment_2);
  return NULL;
}

RUN_TESTS(all_tests);
