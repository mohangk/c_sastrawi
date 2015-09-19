#include "minunit.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../sastrawi.h"
#include "../dbg.h"

char *test_is_plural()
{

  check(is_plural("hati-ku") == 0, "hati-ku is not plural");
  check(is_plural("test2") == 0, "test2 is not plural");
  check(is_plural("hati-hati") == 1, "hati-hati is plural");

  return NULL;
error:
  return 0;

}


char *test_plural_parts() {
  char **parts = NULL;
  int rc;

  rc = plural_parts("beli", &parts);
  check(rc == 1, "beli has 1 part");
  check(strcmp("beli", parts[0]) == 0, "beli is returned in the parts");

  rc = plural_parts("beli-beli", &parts);
  check(rc == 2, "beli-beli has 2 parts");
  check(strcmp("beli", parts[0]) == 0, "beli-beli has 2 parts");
  check(strcmp("beli", parts[1]) == 0, "beli-beli has 2 parts");

  rc = plural_parts("beli-beli-ku", &parts);
  check(rc == 2, "beli-beli-ku has 2 parts");
  check(strcmp("beli", parts[0]) == 0, "For beli-beli-ku, first part should be beli");
  check(strcmp("beli-ku", parts[1]) == 0, "For beli-beli-ku, second part should be beli-ku");

  return NULL;
error:
  return 0;

}

char *all_tests()
{
  mu_suite_start();
  mu_run_test(test_is_plural);
  mu_run_test(test_plural_parts);
  
  return NULL;
}

RUN_TESTS(all_tests);
