#include "sastrawi/features.h"
#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libsastrawi.h"
#include "sastrawi/suffix_removers.h"
#include "sastrawi/remove_suffixes.h"
#include "sastrawi/dictionary.h"
#include "dbg.h"

sastrawi_stemmer *stemmer;

char *test_remove_suffixes() 
{
  char *word = "bajumukah";
  char *stemmed_word = NULL;
  remove_suffixes(stemmer, word, &stemmed_word);
  debug("stem word: %s, expected: baju, actual: %s", word, stemmed_word);
  mu_assert(strcmp("baju", stemmed_word) == 0, "it stems to baju");
  free(stemmed_word);

  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  sastrawi_stemmer_new(&stemmer);

  dictionary_load(dictionary_fullpath("data/kata-dasar.txt"));

  mu_run_test(test_remove_suffixes);

  return NULL;
}

RUN_TESTS(all_tests);
