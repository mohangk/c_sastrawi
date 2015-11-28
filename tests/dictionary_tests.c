#ifdef __linux
  #define _GNU_SOURCE 
#endif
#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libsastrawi.h"
#include "dbg.h"
#include "dictionary_tests.h"

char *test_dictionary_load() 
{
  int rc;

  rc = dictionary_load(dictionary_fullpath("tests/test_dict.txt"));
  mu_assert(rc, "when test_dict exists return truthy");

  rc = dictionary_load(dictionary_fullpath("tests/test_not_exists.txt"));
  mu_assert(!rc, "when the dict file does not exist it should return falsy");

  return NULL;
}

char *test_dictionary_contains() 
{
  dictionary_load(dictionary_fullpath("tests/test_dict.txt"));
  mu_assert(dictionary_contains("aba"), "test dict contains aba");
  mu_assert(!dictionary_contains("non-existent"), "test dict does not contain non-existent");

  return NULL;
}

char *test_dictionary_add() 
{
  dictionary_add("nonexistent");

  mu_assert(dictionary_contains("nonexistent"), "dict should contain nonexistent");
  mu_assert(!dictionary_contains("nonexistent2"), "dict should not contain nonexistent2");

  int count = dictionary_count();
  dictionary_add("bola");
  int new_count = dictionary_count();
  mu_assert(count == new_count, "dictionary_add ensures that entries are unique");

  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  dictionary_load(dictionary_fullpath("data/kata-dasar.txt"));

  mu_run_test(test_dictionary_load);
  mu_run_test(test_dictionary_add);
  mu_run_test(test_dictionary_contains);

  return NULL;
}

RUN_TESTS(all_tests);
