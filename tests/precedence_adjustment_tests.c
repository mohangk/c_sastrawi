#ifdef __linux
  #define _GNU_SOURCE 
#endif
#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sastrawi/precedence_adjustment.h"
#include "dbg.h"

char *test_precedence_adjustment_satisfied_be_lah()
{
  char *word_to_stem = "belilah";
  int rc = is_precedence_adjustment_satisfied(word_to_stem);
  debug("word: %s", word_to_stem);
  mu_assert(rc == 1, "should be satisfied");
  return NULL;
}

char *test_precedence_adjustment_satisfied_be_an()
{
  char *word_to_stem = "belaan";
  int rc = is_precedence_adjustment_satisfied(word_to_stem);
  debug("word: %s", word_to_stem);
  mu_assert(rc == 1, "should be satisfied");
  return NULL;
}

char *test_precedence_adjustment_satisfied_me_i()
{
  char *word_to_stem = "merangkumi";
  int rc = is_precedence_adjustment_satisfied(word_to_stem);
  debug("word: %s", word_to_stem);
  mu_assert(rc == 1, "should be satisfied");
  return NULL;
}

char *test_precedence_adjustment_satisfied_di_i()
{
  char *word_to_stem = "dikahwini";
  int rc = is_precedence_adjustment_satisfied(word_to_stem);
  debug("word: %s", word_to_stem);
  mu_assert(rc == 1, "should be satisfied");
  return NULL;
}

char *test_precedence_adjustment_satisfied_pe_i()
{
  char *word_to_stem = "penyanyi";
  int rc = is_precedence_adjustment_satisfied(word_to_stem);
  debug("word: %s", word_to_stem);
  mu_assert(rc == 1, "should be satisfied");
  return NULL;
}

char *test_precedence_adjustment_satisfied_ter_i()
{
  char *word_to_stem = "terkini";
  int rc = is_precedence_adjustment_satisfied(word_to_stem);
  debug("word: %s", word_to_stem);
  mu_assert(rc == 1, "should be satisfied");
  return NULL;
}

char *test_precedence_adjustment_not_satisfied()
{
  char *word_to_stem = "terjunam";
  int rc = is_precedence_adjustment_satisfied(word_to_stem);
  debug("word: %s", word_to_stem);
  mu_assert(rc == 0, "should not be satisfied");
  return NULL;
}

char *all_tests()
{
  mu_suite_start();
  mu_run_test(test_precedence_adjustment_satisfied_be_lah);
  mu_run_test(test_precedence_adjustment_satisfied_be_an);
  mu_run_test(test_precedence_adjustment_satisfied_me_i);
  mu_run_test(test_precedence_adjustment_satisfied_di_i);
  mu_run_test(test_precedence_adjustment_satisfied_pe_i);
  mu_run_test(test_precedence_adjustment_satisfied_ter_i);
  mu_run_test(test_precedence_adjustment_not_satisfied);
  return NULL;
}

RUN_TESTS(all_tests);
