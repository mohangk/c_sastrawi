#include "minunit.h"
#include "libsastrawi.h"
#include "dbg.h"

char *test_new_and_free_stemmer() 
{
  sastrawi_stemmer *stem;
  sastrawi_err rc = sastrawi_stemmer_new(&stem);
  mu_assert(rc == 0, "can create stemmer");
  rc = sastrawi_stemmer_free(stem);
  mu_assert(rc == 0, "can free stemmer");
  return NULL;
}

char *all_tests()
{
  mu_suite_start();
  mu_run_test(test_new_and_free_stemmer);
  return NULL;
}

RUN_TESTS(all_tests);
