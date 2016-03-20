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

  AFFIX_REMOVAL *removals;
  int removal_count;

  int rc = remove_prefixes(stemmer, "mewarnai", &stemmed_word, &removal_count, &removals);

  debug("word: mewarnai, expected stemmed word: warnai, actual stemmed word: %s", stemmed_word);
  mu_assert(rc == PARTIALLY_STEMMED, "it should be PARTIALLY_STEMMED");
  mu_assert(strcmp("warnai", stemmed_word) == 0, "failed while asserting stemmed word");
  mu_assert(removal_count == 1, "one prefix removed");
  mu_assert(strcmp(removals[0].original_word, "mewarnai") == 0, "returns the original word");
  mu_assert(strcmp(removals[0].removed_part, "me") == 0, "returns the removed portion");
  mu_assert(strcmp(removals[0].result, "warnai") == 0, "returns the original_word after stemming");

  free(stemmed_word);
  return NULL;
}

char *test_remove_prefixes_runs_3_times() 
{
  char *stemmed_word;

  AFFIX_REMOVAL *removals;
  int removal_count;

  // diberberlari is a fake work, but we need it as a test, can't think of a valid word
  int rc = remove_prefixes(stemmer, "diberberlari", &stemmed_word, &removal_count, &removals);
  debug("word: diberberlari, expected stemmed word: lari, actual stemmed word: %s", stemmed_word);
  mu_assert(rc == FULLY_STEMMED, "it is fully stemmed");
  mu_assert(strcmp("lari", stemmed_word) == 0, "it stems to the correct root word");
  mu_assert(removal_count == 3, "three prefixes removed");

  debug("Removal 1 expected => original_word: diberberlari, removed_part: di, result: berberlari |" 
                   "actual => original_word: %s, removed_part: %s, result: %s", 
                   removals[0].original_word, removals[0].removed_part, removals[0].result);

  mu_assert(strcmp(removals[0].original_word, "diberberlari") == 0, "returns the original word before the first removal");
  mu_assert(strcmp(removals[0].removed_part, "di") == 0, "returns the first removal removed portion");
  mu_assert(strcmp(removals[0].result, "berberlari") == 0, "returns the word after stemming");

  debug("Removal 2 expected => original_word: berberlari, removed_part: ber, result: berlari |"
                   "actual => original_word: %s, removed_part: %s, result: %s",
      removals[1].original_word, removals[1].removed_part, removals[1].result);
  mu_assert(strcmp(removals[1].original_word, "berberlari") == 0, "returns the original word");
  mu_assert(strcmp(removals[1].removed_part, "ber") == 0, "returns the removed portion");
  mu_assert(strcmp(removals[1].result, "berlari") == 0, "returns the word after stemming");

  debug("Removal 3 expected => original_word: berlari, removed_part: ber, result: lari |"
      "actual => original_word: %s, removed_part: %s, result: %s", 
      removals[2].original_word, removals[2].removed_part, removals[2].result);
  mu_assert(strcmp(removals[2].original_word, "berlari") == 0, "returns the original word");
  mu_assert(strcmp(removals[2].removed_part, "ber") == 0, "returns the removed portion");
  mu_assert(strcmp(removals[2].result, "lari") == 0, "returns the word after stemming");

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
