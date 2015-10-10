#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *dictionary_fullpath(char *relative_path);
int dictionary_load(char *path_to_dict);
int dictionary_contains(char *word);
int dictionary_add(char *word);
int dictionary_count();
