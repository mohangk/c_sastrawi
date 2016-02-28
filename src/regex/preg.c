#define _XOPEN_SOURCE 500
// for strdup
#include <stdio.h>
#include <string.h>
#define PCRE2_STATIC
#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>
#include "../uthash/uthash.h"
#include "preg.h"
#include "../dbg.h"

/**
 * TODO: 
 * - Do we need memory management for the cached regex ?
 */

struct re_cache {
  char *re;
  pcre2_code *compiled_re;
  UT_hash_handle hh;
};

struct re_cache *active_re_cache;

pcre2_code *compile(char *pattern) {

  PCRE2_SPTR pcre2_pattern = (PCRE2_SPTR)pattern;

  pcre2_code *re;
  int errornumber;
  PCRE2_SIZE erroroffset;

  re = pcre2_compile(
    pcre2_pattern,               /* the pattern */
    PCRE2_ZERO_TERMINATED, /* indicates pattern is zero-terminated */
    0,                     /* default options */
    &errornumber,          /* for error number */
    &erroroffset,          /* for error offset */
    NULL);                 /* use default compile context */

  pcre2_jit_compile(re, PCRE2_JIT_COMPLETE);

  if (re == NULL) {
    PCRE2_UCHAR buffer[256];
    pcre2_get_error_message(errornumber, buffer, sizeof(buffer));
    printf("PCRE2 compilation failed at offset %d: %s\n for pattern: %s", (int)erroroffset,
      buffer, pattern);
    exit(1);
  }

  return re;
}

pcre2_code *get_compiled_re(char *re)
{
  struct re_cache *re_cache_item = NULL;
  HASH_FIND_STR(active_re_cache, re, re_cache_item);
  if(re_cache_item == NULL) {

    re_cache_item = malloc(sizeof(struct re_cache));
    check_mem(re_cache_item);

    re_cache_item->re = strdup(re);
    re_cache_item->compiled_re = compile(re_cache_item->re);
    HASH_ADD_KEYPTR(hh, active_re_cache, re_cache_item->re, strlen(re_cache_item->re), re_cache_item);
  } 

  return re_cache_item->compiled_re;

error:
  log_err("Failed to  allocate memory for regex cache");
  exit(1);
}


int preg_match(char *pattern, char *subject, char **matches[]) {

  int rc;
  PCRE2_SIZE *ovector;

  pcre2_code *compiled_re = get_compiled_re(pattern);

  PCRE2_SPTR pcre2_subject = (PCRE2_SPTR)subject;
  size_t subject_length = strlen((char *)subject);

  pcre2_match_data *match_data;

  match_data = pcre2_match_data_create_from_pattern(compiled_re, NULL);

  rc = pcre2_match(
              compiled_re,
              pcre2_subject,
              subject_length,
              0,
              0,
              match_data,
              NULL);


  if (rc > 1) {
    *matches = malloc(rc * sizeof(char*));
    ovector = pcre2_get_ovector_pointer(match_data);

    check_mem(matches);

    for (int i = 0; i < rc; i++)
    {
      PCRE2_SPTR substring_start = pcre2_subject + ovector[2*i];
      size_t substring_length = ovector[2*i+1] - ovector[2*i];
      char *substring_copy = malloc(substring_length + 1);
      strncpy(substring_copy, (char *)substring_start, substring_length);
      substring_copy[substring_length] = 0;
      (*matches)[i] = substring_copy;
    }
  }

  pcre2_match_data_free(match_data);
  return rc;
error:
  log_err("Failed to allocate memory for matches");
  exit(1);
}

void free_matches(int matches_count, char **matches[])
{
  for (int i = 0; i < matches_count; i++)
  {
    free((*matches)[i]);
  }
  free(*matches);
}


