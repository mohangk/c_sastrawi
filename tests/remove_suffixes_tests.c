#include "sastrawi/features.h"
#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libsastrawi.h"
#include "sastrawi/suffix_removers.h"
#include "sastrawi/remove_suffixes.h"
#include "sastrawi/remove_prefixes.h"
#include "sastrawi/dictionary.h"
#include "dbg.h"

sastrawi_stemmer *stemmer;

char *test_remove_suffixes_when_fully_stemmed() 
{
  char *word = "bajumukah";
  char *stemmed_word = NULL;

  AFFIX_REMOVAL *removals;
  int removal_count;
  
  int rc = remove_suffixes(stemmer, word, &stemmed_word, &removal_count, &removals);
  debug("stem word: %s, expected: baju, actual: %s", word, stemmed_word);

  mu_assert(rc == FULLY_STEMMED, "it is fully stemmed");
  mu_assert(strcmp("baju", stemmed_word) == 0, "it stems to baju");
  mu_assert(removal_count == 2, "two suffixes removed");

  debug("Removal 1 expected => original_word: bajumukah, removed_part: kah | actual => original_word: %s, removed_part: %s", removals[0].original_word, removals[0].removed_part);
  mu_assert(strcmp(removals[0].original_word, "bajumukah") == 0, "returns the original word");
  mu_assert(strcmp(removals[0].removed_part, "kah") == 0, "returns the removed portion");

  debug("Removal 2 expected => original_word: bajumu, removed_part: mu | actual => original_word: %s, removed_part: %s", removals[1].original_word, removals[1].removed_part);
  mu_assert(strcmp(removals[1].original_word, "bajumu") == 0, "returns the original word");
  mu_assert(strcmp(removals[1].removed_part, "mu") == 0, "returns the removed portion");
  free(stemmed_word);

  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  sastrawi_stemmer_new(&stemmer);

  dictionary_load(dictionary_fullpath("data/kata-dasar.txt"));

  mu_run_test(test_remove_suffixes_when_fully_stemmed);

  return NULL;
}

RUN_TESTS(all_tests);
