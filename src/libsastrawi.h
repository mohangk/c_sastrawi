#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "regex/preg.h"
#include "sastrawi/stem_plural.h"
#include "sastrawi/stem_singular.h"
#include "sastrawi/dictionary.h"

void print_my_name();

typedef struct affix_removal AFFIX_REMOVAL;
struct affix_removal {
  enum {DP, DS, PP, P} type;
  char *removed_part;
  char *original_word;
};
