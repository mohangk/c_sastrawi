#include "sastrawi/features.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sastrawi/sastrawi_internal.h"
#include "libsastrawi.h"

sastrawi_err sastrawi_stemmer_new(sastrawi_stemmer **ppStemmer)
{
  sastrawi_stemmer *pStemmer = malloc(sizeof(struct sastrawi_stemmer));
  if (!pStemmer) {
    *ppStemmer = NULL;
    return SASTRAWI_E_MEMORY;
  }

  pStemmer->regex_cache = NULL;

  *ppStemmer = pStemmer;
  return SASTRAWI_E_OK;
}
sastrawi_err sastrawi_stemmer_free(sastrawi_stemmer *pStemmer)
{
  free(pStemmer);
  return SASTRAWI_E_OK;
}
