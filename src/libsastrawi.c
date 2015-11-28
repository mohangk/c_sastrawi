#ifdef __linux
  #define _GNU_SOURCE 
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libsastrawi.h"
#include "sastrawi/stem_plural.h"
#include "sastrawi/stem_singular.h"

void print_my_name() 
{
  printf("mohan");
}
