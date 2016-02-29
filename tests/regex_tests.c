#include "minunit.h"
#include "regex/preg.h"
#include <string.h>
#include <stdlib.h>

char *test_regex_substitute_large() 
{
  void *c = NULL;
  char *replace = preg_replace(&c, "1", "12345678901234567890", "1");
  mu_assert(strcmp(replace, "12345678901234567890") == 0, "can replace with large string");
  free(replace);
  return NULL;
}
char *all_tests()
{
  mu_suite_start();
  mu_run_test(test_regex_substitute_large);

  return NULL;
}
RUN_TESTS(all_tests)
