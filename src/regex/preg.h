#ifndef _preg_replace_h
#define _preg_replace_h

char *preg_replace(char *pattern, char *replacement, char *subject);

int preg_match(char *pattern, char *subject, char **matches[]);

void free_matches(int matches_count, char **matches[]);
#endif
