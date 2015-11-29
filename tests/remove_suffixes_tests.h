#ifdef __linux
  #define _GNU_SOURCE 
#endif
#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sastrawi/remove_suffixes.h"
#include "../dbg.h"

char *test_remove_inflectional_particle_with_dash();
char *test_remove_inflectional_particle_without_dash();
char *test_remove_inflectional_particle_no_match();
char *test_remove_possessive_pronoun_with_dash();
char *test_remove_possessive_pronoun_without_dash();
char *test_remove_derivational_suffix_with_dash();
char *test_remove_derivational_suffix_without_dash();
char *test_remove_suffixes();
