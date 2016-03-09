#ifndef SASTRAWI_LIBSASTRAWI_H_INCLUDED
#define SASTRAWI_LIBSASTRAWI_H_INCLUDED

#include <stdint.h>

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
  char *removed_part;
  char *original_word;
};

#endif
