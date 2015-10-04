#ifdef __linux
  #define _GNU_SOURCE 
#endif
#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../sastrawi.h"
#include "../dbg.h"

void free_parts(int parts_count, char **parts[])
{
  for (int i = 0; i < parts_count; i++)
  {
    free((*parts)[i]);
  }
  free(*parts);
}

char *dict_fullpath(char *relative_path) 
{
  char *cwd = NULL;
  char *full_path = NULL;

  int rc = asprintf(&full_path, "%s/%s", getcwd(cwd,0), relative_path);
  check(rc != -1, "Cannot allocate memory");

  return full_path;
error:
  exit(1);
}

char *test_is_plural()
{

  mu_assert(!is_plural("hati-ku"), "hati-ku is not plural");
  mu_assert(!is_plural("test2"), "test2 is not plural");
  mu_assert(is_plural("hati-hati"), "hati-hati is plural");

  return NULL;
}

char *test_plural_parts() {
  char **parts = NULL;
  int rc;

  rc = plural_parts("beli", &parts);
  mu_assert(rc == 1, "beli has 1 part");
  mu_assert(strcmp("beli", parts[0]) == 0, "beli is returned in the parts");

  free_parts(rc, &parts);

  rc = plural_parts("beli-beli", &parts);
  mu_assert(rc == 2, "beli-beli has 2 parts");
  mu_assert(strcmp("beli", parts[0]) == 0, "beli-beli has 2 parts");
  mu_assert(strcmp("beli", parts[1]) == 0, "beli-beli has 2 parts");

  free_parts(rc, &parts);

  rc = plural_parts("beli-beli-ku", &parts);
  mu_assert(rc == 2, "beli-beli-ku has 2 parts");
  mu_assert(strcmp("beli", parts[0]) == 0, "For beli-beli-ku, first part should be beli");
  mu_assert(strcmp("beli-ku", parts[1]) == 0, "For beli-beli-ku, second part should be beli-ku");

  free_parts(rc, &parts);

  return NULL;
}

char *test_dictionary_load() 
{
  int rc;

  rc = dictionary_load(dict_fullpath("tests/test_dict.txt"));
  mu_assert(rc, "when test_dict exists return truthy");

  rc = dictionary_load(dict_fullpath("tests/test_not_exists.txt"));
  mu_assert(!rc, "when the dict file does not exist it should return falsy");

  return NULL;
}

char *test_dictionary_add() 
{
  dictionary_add("bola");
  mu_assert(dictionary_contains("bola"), "dict should contain bola");
  mu_assert(!dictionary_contains("bela"), "dict should not contain bela");
}

char *test_dictionary_contains() {

  dictionary_load(dict_fullpath("tests/test_dict.txt"));
  mu_assert(dictionary_contains("aba"), "test dict contains aba");
  mu_assert(!dictionary_contains("bela"), "test dict does not contain bela");

  return NULL;
}

char *all_tests()
{
  mu_suite_start();
  mu_run_test(test_is_plural);
  mu_run_test(test_plural_parts);
  mu_run_test(test_dictionary_load);
  mu_run_test(test_dictionary_add);
  mu_run_test(test_dictionary_contains);
  
  return NULL;
}

RUN_TESTS(all_tests);
