#ifdef __linux
  #define _GNU_SOURCE 
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../uthash/uthash.h"
#include "dictionary.h"
#include "../dbg.h"


struct dict_entry {
  char *word;
  UT_hash_handle hh;
};

struct dict_entry *dict;

void remove_newline(char **word, int length) {
  if((*word)[length-1] == '\n') {
    (*word)[length-1] = '\0';
  }
}

int dictionary_load(char *dict_path)
{
  FILE *dict_file = NULL;
  char *word = NULL;
  size_t linecap =  0;
  ssize_t linelen;

  dict_file = fopen(dict_path, "rb");
  check(dict_file, "Failed to open %s", dict_path);

  while((linelen = getline(&word, &linecap, dict_file)) > 0) {
    remove_newline(&word, linelen);
    dictionary_add(word);
    free(word);
    word = NULL;
  }

  fclose(dict_file);

  return 1;
error:
  if(dict_file) fclose(dict_file);
  if(word) free(word);
  return 0;
}

int dictionary_add(char *word)
{
  struct dict_entry *dict_word = NULL;
  dict_word = malloc(sizeof(struct dict_entry));
  check_mem(dict_word);

  dict_word->word = strndup(word, strlen(word));
  HASH_ADD_KEYPTR(hh, dict, dict_word->word, strlen(dict_word->word), dict_word);
  return 1;

error:
  log_err("Failed to  allocate memory for dictionary entry");
  exit(1);
}

int dictionary_contains(char *word)
{
  struct dict_entry *dict_word = NULL;

  HASH_FIND_STR(dict, word, dict_word);

  if(dict_word == NULL) 
    return 0;
  else
    return 1;
}
