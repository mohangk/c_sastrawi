#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "regex/preg.h"
#include "sastrawi/stem_plural.h"
#include "sastrawi/stem_singular.h"
#include "sastrawi/dictionary.h"


typedef struct sastrawi_stemmer sastrawi_stemmer;
typedef int32_t sastrawi_err;

sastrawi_err sastrawi_stemmer_new(sastrawi_stemmer **);
sastrawi_err sastrawi_stemmer_free(sastrawi_stemmer *);

#define SASTRAWI_E_OK 0
#define SASTRAWI_E_UNKNOWN 1
#define SASTRAWI_E_MEMORY 2

#define SASTRAWI_FAILED(c) ((c) != SASTRAWI_E_OK)

typedef struct affix_removal AFFIX_REMOVAL;
struct affix_removal {
  enum {DP, DS, PP, P} type;
  char *removed_part;
  char *original_word;
};
