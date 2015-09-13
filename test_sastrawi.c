#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sastrawi.h"
#include "dbg.h"


int main(int argc, char **argv)
{

  debug("is hati-ku plural: %d \n", is_plural("hati-ku"));
  //printf("is hati-hati plural: %d \n", is_plural("hati-hati"));
  debug("is test2 plural: %d", is_plural("test2"));
  debug("is test3 plural: %d", is_plural("test3"));
  //printf("is test4 plural: %d", is_plural("test4"));
  //printf("is test5 plural: %d", is_plural("test5"));
  debug("is hati-hati plural: %d", is_plural("hati-hati"));

  return 0;
}
