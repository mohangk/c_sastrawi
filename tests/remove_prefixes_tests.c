#include "sastrawi/features.h"
#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libsastrawi.h"
#include "sastrawi/dictionary.h"
#include "sastrawi/remove_prefixes.h"
#include "dbg.h"

sastrawi_stemmer *stemmer;

char *test_remove_prefixes_when_partially_stemmed()
{
  char *stemmed_word;

  int rc = remove_prefixes(stemmer, "mewarnai", &stemmed_word);

  debug("word: mewarnai, expected stemmed word: warnai, actual stemmed word: %s", stemmed_word);
  mu_assert(rc == PARTIALLY_STEMMED, "it should be PARTIALLY_STEMMED");
  mu_assert(strcmp("warnai", stemmed_word) == 0, "failed while asserting stemmed word");
  free(stemmed_word);
  return NULL;
}

char *test_remove_prefixes_runs_3_times() 
{
  char *stemmed_word;

  // diberberlari is a fake work, but we need it as a test, can't think of a valid word
  int rc = remove_prefixes(stemmer, "diberberlari", &stemmed_word);
  debug("word: diberberlari, expected stemmed word: lari, actual stemmed word: %s", stemmed_word);
  mu_assert(rc == FULLY_STEMMED, "it is fully stemmed");
  mu_assert(strcmp("lari", stemmed_word) == 0, "failed while asserting stemmed word");
  free(stemmed_word);
  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  sastrawi_stemmer_new(&stemmer);

  char *path = dictionary_fullpath("data/kata-dasar.txt");
  dictionary_load(path);
  free(path);

  mu_run_test(test_remove_prefixes_when_partially_stemmed);
  mu_run_test(test_remove_prefixes_runs_3_times);
  return NULL;
}

RUN_TESTS(all_tests);
