#include "sastrawi/features.h"
#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libsastrawi.h"
#include "dbg.h"

void set_affix_removal(AFFIX_REMOVAL *affix_removals) {
  affix_removals[1].removed_part = "blah";
  affix_removals[1].result = "result1";
}

char *test_affix_removal() 
{
  AFFIX_REMOVAL affix_removals[3];

  affix_removals[0].removed_part = "kan";
  affix_removals[0].original_word = "belikan";
  affix_removals[0].result = "result0";

  set_affix_removal(affix_removals);

  mu_assert(strcmp(affix_removals[0].original_word,"belikan") == 0, "returns the original word");
  mu_assert(strcmp(affix_removals[0].result,"result0") == 0, "returns the word after stemming");
  mu_assert(strcmp(affix_removals[1].removed_part,"blah") == 0, "returns the original word");
  mu_assert(strcmp(affix_removals[1].result, "result1") == 0, "returns the word after stemming");

  return NULL;
}



char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_affix_removal);

  return NULL;
}

RUN_TESTS(all_tests);
