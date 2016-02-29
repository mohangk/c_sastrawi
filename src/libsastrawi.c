#include "sastrawi/features.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libsastrawi.h"
#include "sastrawi/stem_plural.h"
#include "sastrawi/stem_singular.h"

sastrawi_err sastrawi_stemmer_new(sastrawi_stemmer **ppStemmer)
{
  void *dummy = malloc(16);
  if (!dummy) {
    return SASTRAWI_E_MEMORY;
  }
  *ppStemmer = ((sastrawi_stemmer *)dummy);
  return SASTRAWI_E_OK;
}
sastrawi_err sastrawi_stemmer_free(sastrawi_stemmer *pStemmer)
{
  free(pStemmer);
  return SASTRAWI_E_OK;
}
