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

char *all_tests()
{
  mu_suite_start();
  mu_run_test(test_is_plural);
  
  return NULL;
}

RUN_TESTS(all_tests);
