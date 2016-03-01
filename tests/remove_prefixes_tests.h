#include "sastrawi/features.h"
#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sastrawi.h"
#include "../dbg.h"

char *test_remove_plain_prefix_di();
char *test_remove_plain_prefix_ke(); 
char *test_remove_plain_prefix_se();
char *test_remove_complex_prefix_rule1_a();
char *test_remove_complex_prefix_rule1_b();
char *test_remove_complex_prefix_rule2();
char *test_remove_complex_prefix_rule2_excludes_er();
char *test_remove_complex_prefix_rule3_only_includes_er();
char *test_remove_plain_prefix_returns_0_if_word_notin_dictionary();
