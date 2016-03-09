#include "sastrawi/features.h"
#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libsastrawi.h"
#include "sastrawi/suffix_removers.h"
#include "sastrawi/dictionary.h"
#include "dbg.h"

sastrawi_stemmer *stemmer;

char *test_remove_inflectional_particle_with_dash() 
{
  char *stemmed_word = NULL; 
  char *removed_part = NULL;

  int rc = remove_inflectional_particle(stemmer, "penting-kah", &stemmed_word, &removed_part);
  mu_assert(rc, "successfully stems");
  mu_assert(strcmp("penting", stemmed_word) == 0, "we expect 'penting' as the stemmed word");
  mu_assert(strcmp("kah", removed_part) == 0, "we expect 'kah' as the removed part");

  return NULL;
}

char *test_remove_inflectional_particle_without_dash() 
{
  char *stemmed_word = NULL; 
  char *removed_part = NULL;

  int rc = remove_inflectional_particle(stemmer, "pentingkah", &stemmed_word, &removed_part);
  mu_assert(rc, "successfully stems");
  mu_assert(strcmp("penting", stemmed_word) == 0, "we expect 'penting' as the stemmed word");
  mu_assert(strcmp("kah", removed_part) == 0, "we expect 'kah' as the removed part");

  return NULL;
}

char *test_remove_inflectional_particle_no_match() 
{
  char *stemmed_word = NULL; 
  char *removed_part = NULL;

  int rc = remove_inflectional_particle(stemmer, "penting", &stemmed_word, &removed_part);
  mu_assert(!rc, "fails stem");
  mu_assert(strcmp("penting", stemmed_word) == 0, "we expect no change in the word passed in");
  mu_assert(strcmp("", removed_part) == 0, "we expect empty string in the removed_part");

  return NULL;
}

char *test_remove_possessive_pronoun_with_dash() 
{
  char *stemmed_word = NULL; 
  char *removed_part = NULL;

  int rc = remove_possessive_pronoun(stemmer, "cinta-ku", &stemmed_word, &removed_part);

  mu_assert(rc, "successfully stems");
  mu_assert(strcmp("cinta", stemmed_word) == 0, "we expect 'cinta' as the stemmed word");
  mu_assert(strcmp("ku", removed_part) == 0, "we expect 'ku' as the removed part");

  return NULL;
}

char *test_remove_possessive_pronoun_without_dash() 
{
  char *stemmed_word = NULL; 
  char *removed_part = NULL;

  int rc = remove_possessive_pronoun(stemmer, "cintaku", &stemmed_word, &removed_part);
  mu_assert(rc, "successfully stems");
  mu_assert(strcmp("cinta", stemmed_word) == 0, "we expect 'cinta' as the stemmed word");
  mu_assert(strcmp("ku", removed_part) == 0, "we expect 'ku' as the removed part");

  return NULL;
}

char *test_remove_derivational_suffix_with_dash() 
{
  char *stemmed_word = NULL; 
  char *removed_part = NULL;

  int rc = remove_derivational_suffix(stemmer, "cinta-kan", &stemmed_word, &removed_part);

  mu_assert(rc, "successfully stems");
  mu_assert(strcmp("cinta", stemmed_word) == 0, "we expect 'cinta' as the stemmed word");
  mu_assert(strcmp("kan", removed_part) == 0, "we expect 'kan' as the removed part");

  return NULL;
}

char *test_remove_derivational_suffix_without_dash() 
{
  char *stemmed_word = NULL; 
  char *removed_part = NULL;

  int rc = remove_derivational_suffix(stemmer, "cintakan", &stemmed_word, &removed_part);
  mu_assert(rc, "successfully stems");
  mu_assert(strcmp("cinta", stemmed_word) == 0, "we expect 'cinta' as the stemmed word");
  mu_assert(strcmp("kan", removed_part) == 0, "we expect 'kan' as the removed part");

  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  sastrawi_stemmer_new(&stemmer);

  char *path = dictionary_fullpath("data/kata-dasar.txt");
  dictionary_load(path);
  free(path);

  mu_run_test(test_remove_inflectional_particle_with_dash);
  mu_run_test(test_remove_inflectional_particle_without_dash);
  mu_run_test(test_remove_inflectional_particle_no_match);

  mu_run_test(test_remove_possessive_pronoun_with_dash);
  mu_run_test(test_remove_possessive_pronoun_without_dash);

  mu_run_test(test_remove_derivational_suffix_with_dash);
  mu_run_test(test_remove_derivational_suffix_without_dash);

  return NULL;
}

RUN_TESTS(all_tests);
