#include "features.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "precedence_adjustment.h"
#include "../dbg.h"


int is_precedence_adjustment_satisfied(char *original_word)
{
  int len = strlen(original_word);

  if(strncmp(original_word, "be", 2) == 0) {
    if(len > 4 && strcmp(&original_word[len-3], "lah") == 0) {
      return 1;
    }

    if(len > 3 && strcmp(&original_word[len-2], "an") == 0) {
      return 1;
    }

  } else if(strncmp(original_word, "me", 2) == 0 ||
      strncmp(original_word, "di", 2) == 0 ||
      strncmp(original_word, "pe", 2) == 0 ||
      strncmp(original_word, "ter", 3) == 0) {

    if(len > 2 && strcmp(&original_word[len-1], "i") == 0) {
      return 1;
    }

  }

  return 0;

}
