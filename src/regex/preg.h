#ifndef _preg_replace_h
#define _preg_replace_h

char *preg_replace(void **cache, char *pattern, char *replacement, char *subject);

int preg_match(void **cache, char *pattern, char *subject, char **matches[]);

void free_matches(int matches_count, char **matches[]);
#endif
