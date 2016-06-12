#include "sastrawi/features.h"
#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libsastrawi.h"
#include "sastrawi/remove_prefixes.h"
#include "sastrawi/stem_singular.h"
#include "sastrawi/dictionary.h"
#include "dbg.h"

sastrawi_stemmer *stemmer;

char *test_stem_singular_word_for(char *word, char *expected_stem_word) 
{
  char *stemmed_word = NULL;
  int rc = stem_singular_word(stemmer, word, &stemmed_word);
  debug("stem word: %s, expected: %s, actual: %s", word, expected_stem_word, stemmed_word);
  mu_assert(rc == FULLY_STEMMED, "failed to stem");
  mu_assert(strcmp(expected_stem_word, stemmed_word) == 0, "failed to stem correctly");
  free(stemmed_word);

  return NULL;
}

char *test_stem_singular_word_does_not_need_stemming() 
{
  char *stemmed_word;
  char *word = "bola";
  char *expected_stem_word = "bola";
  int rc = stem_singular_word(stemmer, word, &stemmed_word);
  debug("stem word: %s, expected: %s, actual: %s, expexted_rc %d, actual_rc %d", word, expected_stem_word, stemmed_word, NOT_STEMMED, rc);
  mu_assert(rc == FULLY_STEMMED, "word that does not need stemming is returned as FULLY_STEMMED");
  mu_assert(strcmp(expected_stem_word, stemmed_word) == 0, "should not change the word");
  free(stemmed_word);
  return NULL;
}

char *test_stem_singular_word_returns_original_word_when_cannot_stem()
{

  char *stemmed_word;
  char *word = "beblahblahan";
  char *expected_stem_word = "beblahblahan";
  int rc = stem_singular_word(stemmer, word, &stemmed_word);
  debug("stem word: %s, expected: %s, actual: %s", word, expected_stem_word, stemmed_word);
  mu_assert(rc == NOT_STEMMED, "did not fail to stem");
  mu_assert(strcmp(expected_stem_word, stemmed_word) == 0, "should not change the word");
  free(stemmed_word);
  return NULL;
}

char *test_stem_singular_word_removes_plain_prefixes() 
{
  return test_stem_singular_word_for("kerajinannya", "rajin");
}

char *test_stem_singular_word_removes_suffixes1() 
{
  return test_stem_singular_word_for("bajumukah", "baju");
}

char *test_stem_singular_word_removes_suffixes2() 
{
  return test_stem_singular_word_for("malaikatnya", "malaikat");
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

char *test_stem_singular_word_removes_complex_prefixes_21a() 
{
  return test_stem_singular_word_for("perundikan", "undi");
}

char *test_stem_singular_word_removes_complex_prefixes_21b() 
{
  return test_stem_singular_word_for("perampingan", "ramping");
}

char *test_stem_singular_word_uses_precedence_adjustment()
{
  return test_stem_singular_word_for("memakai","pakai");
}

char *test_stem_singular_word_uses_precedence_adjustment_2()
{
  return test_stem_singular_word_for("didiamkan","diam");
}


char *test_stem_singular_word_uses_suffix_returning_loop()
{
  return test_stem_singular_word_for("bersembunyi","sembunyi");
}

char *test_suffix_returning_loop_when_cannot_stem() 
{
  char *post_remove;
  int rc = suffix_returning_loop(stemmer, "unstemmable", &post_remove);
  mu_assert(rc == NOT_STEMMED, "should return NOT_STEMMED");

  return NULL;
}


/* char *test_suffix_returning_loop_when_no_suffixes_removed()  */
/* {} */

char *test_suffix_returning_loop_when_original_word_berdesakan() 
{
  char *stemmed_word;
  char *word = "berdesakan";
  int rc = suffix_returning_loop(stemmer, word, &stemmed_word);

  debug("stem word: %s, expected: desak, actual: %s", word, stemmed_word);
  mu_assert(rc == FULLY_STEMMED, "should be FULLY_STEMMED");
  mu_assert(strcmp(stemmed_word, "desak") == 0, "stems to desak");

  return NULL;
}

char *test_suffix_returning_loop_when_original_word_bermakan() 
{
  char *stemmed_word;
  char *word = "bermakan";
  int rc = suffix_returning_loop(stemmer, word, &stemmed_word);

  debug("stem word: %s, expected: makan, actual: %s", word, stemmed_word);
  mu_assert(rc == FULLY_STEMMED, "should be FULLY_STEMMED");
  mu_assert(strcmp(stemmed_word, "makan") == 0, "stems to makan");

  return NULL;
}

char *test_suffix_returning_loop_when_original_word_bersembunyi() 
{
  char *stemmed_word;
  char *word = "bersembunyi";
  int rc = suffix_returning_loop(stemmer, word, &stemmed_word);

  debug("stem word: %s, expected: sembunyi, actual: %s", word, stemmed_word);
  mu_assert(rc == FULLY_STEMMED, "should be FULLY_STEMMED");
  mu_assert(strcmp(stemmed_word, "sembunyi") == 0, "stems to sembunyi");

  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  sastrawi_stemmer_new(&stemmer);

  char *path = dictionary_fullpath("data/kata-dasar.txt");
  dictionary_load(path);
  free(path);


  mu_run_test(test_stem_singular_word_does_not_need_stemming);
  mu_run_test(test_stem_singular_word_returns_original_word_when_cannot_stem);
  mu_run_test(test_stem_singular_word_removes_suffixes1);
  mu_run_test(test_stem_singular_word_removes_suffixes2);

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
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_21a);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_21b);
  mu_run_test(test_stem_singular_word_uses_precedence_adjustment);
  mu_run_test(test_stem_singular_word_uses_precedence_adjustment_2);

  mu_run_test(test_suffix_returning_loop_when_cannot_stem);
  mu_run_test(test_suffix_returning_loop_when_original_word_berdesakan);
  mu_run_test(test_suffix_returning_loop_when_original_word_bermakan);
  mu_run_test(test_suffix_returning_loop_when_original_word_bersembunyi);

  mu_run_test(test_stem_singular_word_uses_suffix_returning_loop);
  return NULL;
}

RUN_TESTS(all_tests);
