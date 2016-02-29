#ifdef __linux
  #define _GNU_SOURCE 
#endif
#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libsastrawi.h"
#include "sastrawi/stem_plural.h"
#include "sastrawi/dictionary.h"
#include "dbg.h"
#include "test_helper.h"

static sastrawi_stemmer *stemmer;


char *test_is_plural()
{

  mu_assert(!is_plural(stemmer, "hati-ku"), "hati-ku is not plural");
  mu_assert(!is_plural(stemmer, "test2"), "test2 is not plural");
  mu_assert(is_plural(stemmer, "hati-hati"), "hati-hati is plural");

  return NULL;
}

char *test_plural_parts() {
  char **parts = NULL;
  int rc;

  rc = plural_parts(stemmer, "beli", &parts);
  mu_assert(rc == 1, "beli has 1 part");
  mu_assert(strcmp("beli", parts[0]) == 0, "beli is returned in the parts");

  free_parts(rc, &parts);

  rc = plural_parts(stemmer, "beli-beli", &parts);
  mu_assert(rc == 2, "beli-beli has 2 parts");
  mu_assert(strcmp("beli", parts[0]) == 0, "beli-beli has 2 parts");
  mu_assert(strcmp("beli", parts[1]) == 0, "beli-beli has 2 parts");

  free_parts(rc, &parts);

  rc = plural_parts(stemmer, "beli-beli-ku", &parts);
  mu_assert(rc == 2, "beli-beli-ku has 2 parts");
  mu_assert(strcmp("beli", parts[0]) == 0, "For beli-beli-ku, first part should be beli");
  mu_assert(strcmp("beli-ku", parts[1]) == 0, "For beli-beli-ku, second part should be beli-ku");

  free_parts(rc, &parts);

  return NULL;
}

char *test_stem_plural_word_when_both_words_are_root_words_and_the_same() 
{
  char *word = "malaikat-malaikat";
  char *stemmed_word = NULL;
  stem_plural_word(stemmer, word, &stemmed_word);
  mu_assert(strcmp("malaikat", stemmed_word) == 0, "it stems to malaikat");
  free(stemmed_word);



  /* char *word3 = "berlari-lari"; */
  /* char *stemmed_word3 = NULL; */
  /* rc = stem_plural_word(word3, &stemmed_word3); */
  /* debug("stem %s => %s, expected %s", word3, stemmed_word3, "lari"); */
  /* mu_assert(strcmp("lari", stemmed_word3) == 0, "it stems to lari"); */
  /* free(stemmed_word3); */

  return NULL;
}

char *test_stem_plural_word_when_one_word_has_suffixes() 
{
  char *word = "malaikat-malaikatnya";
  char *stemmed_word = NULL;
  char *expected_stemmed_word = "malaikat";
  stem_plural_word(stemmer, word, &stemmed_word);

  debug("stem word: %s, expected: %s, actual: %s", word, expected_stemmed_word, stemmed_word);
  mu_assert(strcmp("malaikat", stemmed_word) == 0, "it stems to malaikat");
  free(stemmed_word);

  return NULL;
}


//TODO - create a test with berlarikah, to test return suffix
char *all_tests()
{

  sastrawi_stemmer_new(&stemmer);
  mu_suite_start();

  dictionary_load(dictionary_fullpath("data/kata-dasar.txt"));

  mu_run_test(test_is_plural);
  mu_run_test(test_plural_parts);
  mu_run_test(test_stem_plural_word_when_both_words_are_root_words_and_the_same);
  mu_run_test(test_stem_plural_word_when_one_word_has_suffixes);

  return NULL;
}

RUN_TESTS(all_tests);
