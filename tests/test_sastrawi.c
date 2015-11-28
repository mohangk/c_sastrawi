#ifdef __linux
  #define _GNU_SOURCE 
#endif
#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sastrawi.h"
#include "../dbg.h"
#include "test_dictionary.h"
#include "test_stem_plural.h"
#include "test_stem_singular.h"
#include "test_remove_suffixes.h"
#include "test_remove_prefixes.h"

void free_parts(int parts_count, char **parts[])
{
  for (int i = 0; i < parts_count; i++)
  {
    free((*parts)[i]);
  }
  free(*parts);
}


//TODO - create a test with berlarikah, to test return suffix
char *all_tests()
{
  mu_suite_start();

  dictionary_load(dictionary_fullpath("data/kata-dasar.txt"));

  /* mu_run_test(test_is_plural); */
  /* mu_run_test(test_plural_parts); */
  /* mu_run_test(test_stem_plural_word_when_both_words_are_root_words_and_the_same); */
  /* mu_run_test(test_stem_plural_word_when_one_word_has_suffixes); */

  mu_run_test(test_remove_inflectional_particle_with_dash);
  mu_run_test(test_remove_inflectional_particle_without_dash);
  mu_run_test(test_remove_inflectional_particle_no_match);

  mu_run_test(test_remove_possessive_pronoun_with_dash);
  mu_run_test(test_remove_possessive_pronoun_without_dash);

  mu_run_test(test_remove_derivational_suffix_with_dash);
  mu_run_test(test_remove_derivational_suffix_without_dash);

  mu_run_test(test_remove_suffixes);

  mu_run_test(test_remove_plain_prefix_returns_0_if_word_notin_dictionary)
  mu_run_test(test_remove_plain_prefix_di);
  mu_run_test(test_remove_plain_prefix_ke);
  mu_run_test(test_remove_plain_prefix_se);

  /* mu_run_test(test_stem_singular_word); */
  /* mu_run_test(test_stem_singular_word_removes_suffixes); */

  mu_run_test(test_remove_complex_prefix_rule1_a);
  mu_run_test(test_remove_complex_prefix_rule1_b);
  mu_run_test(test_remove_complex_prefix_rule2);
  mu_run_test(test_remove_complex_prefix_rule2_excludes_er);
  mu_run_test(test_remove_complex_prefix_rule3_only_includes_er);

  /* mu_run_test(test_stem_singular_word_removes_plain_prefixes); */
  /* mu_run_test(test_stem_singular_word_removes_complex_prefixes_1); */
  /* mu_run_test(test_stem_singular_word_removes_complex_prefixes_2); */
  /* mu_run_test(test_stem_singular_word_removes_complex_prefixes_3); */
  /* mu_run_test(test_dictionary_load); */
  /* mu_run_test(test_dictionary_add); */
  /* mu_run_test(test_dictionary_contains); */

  return NULL;
}

RUN_TESTS(all_tests);
