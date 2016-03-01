#ifndef _preg_replace_h
#define _preg_replace_h

int preg_match(void **cache, char *pattern, char *subject, char **matches[]);

void free_matches(int matches_count, char **matches[]);
#endif
