#ifdef __linux
  #define _GNU_SOURCE 
#endif
#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sastrawi.h"
#include "../dbg.h"

void free_parts(int parts_count, char **parts[])
{
  for (int i = 0; i < parts_count; i++)
  {
    free((*parts)[i]);
  }
  free(*parts);
}


char *test_is_plural()
{

  mu_assert(!is_plural("hati-ku"), "hati-ku is not plural");
  mu_assert(!is_plural("test2"), "test2 is not plural");
  mu_assert(is_plural("hati-hati"), "hati-hati is plural");

  return NULL;
}

char *test_plural_parts() {
  char **parts = NULL;
  int rc;

  rc = plural_parts("beli", &parts);
  mu_assert(rc == 1, "beli has 1 part");
  mu_assert(strcmp("beli", parts[0]) == 0, "beli is returned in the parts");

  free_parts(rc, &parts);

  rc = plural_parts("beli-beli", &parts);
  mu_assert(rc == 2, "beli-beli has 2 parts");
  mu_assert(strcmp("beli", parts[0]) == 0, "beli-beli has 2 parts");
  mu_assert(strcmp("beli", parts[1]) == 0, "beli-beli has 2 parts");

  free_parts(rc, &parts);

  rc = plural_parts("beli-beli-ku", &parts);
  mu_assert(rc == 2, "beli-beli-ku has 2 parts");
  mu_assert(strcmp("beli", parts[0]) == 0, "For beli-beli-ku, first part should be beli");
  mu_assert(strcmp("beli-ku", parts[1]) == 0, "For beli-beli-ku, second part should be beli-ku");

  free_parts(rc, &parts);

  return NULL;
}

char *test_stem_plural_word_when_both_words_are_root_words_and_the_same() 
{
  char *word = "malaikat-malaikat";
  char *stemmed_word = NULL;
  int rc = stem_plural_word(word, &stemmed_word);
  mu_assert(strcmp("malaikat", stemmed_word) == 0, "it stems to malaikat");
  free(stemmed_word);



  /* char *word3 = "berlari-lari"; */
  /* char *stemmed_word3 = NULL; */
  /* rc = stem_plural_word(word3, &stemmed_word3); */
  /* debug("stem %s => %s, expected %s", word3, stemmed_word3, "lari"); */
  /* mu_assert(strcmp("lari", stemmed_word3) == 0, "it stems to lari"); */
  /* free(stemmed_word3); */

  return NULL;
}

char *test_stem_plural_word_when_one_word_has_suffixes() 
{
  char *word = "malaikat-malaikatnya";
  char *stemmed_word = NULL;
  int rc = stem_plural_word(word, &stemmed_word);
  mu_assert(strcmp("malaikat", stemmed_word) == 0, "it stems to malaikat");
  free(stemmed_word);

  return NULL;
}



char *test_stem_singular_word() 
{
  char *word = "bola";
  char *stemmed_word = NULL;
  int rc = stem_singular_word(word, &stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("bola", stemmed_word) == 0, "if the word exists in the dictionary, just return it");
  free(stemmed_word);
  return NULL;
}


char *test_remove_inflectional_particle_with_dash() 
{
  char *stemmed_word = NULL; 
  char *removed_part = NULL;

  int rc = remove_inflectional_particle("penting-kah", &stemmed_word, &removed_part);
  mu_assert(rc, "successfully stems");
  mu_assert(strcmp("penting", stemmed_word) == 0, "we expect 'penting' as the stemmed word");
  mu_assert(strcmp("kah", removed_part) == 0, "we expect 'kah' as the removed part");

  return NULL;
}



char *test_remove_inflectional_particle_without_dash() 
{
  char *stemmed_word = NULL; 
  char *removed_part = NULL;

  int rc = remove_inflectional_particle("pentingkah", &stemmed_word, &removed_part);
  mu_assert(rc, "successfully stems");
  mu_assert(strcmp("penting", stemmed_word) == 0, "we expect 'penting' as the stemmed word");
  mu_assert(strcmp("kah", removed_part) == 0, "we expect 'kah' as the removed part");

  return NULL;
}

char *test_remove_inflectional_particle_no_match() 
{
  char *stemmed_word = NULL; 
  char *removed_part = NULL;

  int rc = remove_inflectional_particle("penting", &stemmed_word, &removed_part);
  mu_assert(!rc, "fails stem");
  mu_assert(strcmp("penting", stemmed_word) == 0, "we expect no change in the word passed in");
  mu_assert(strcmp("", removed_part) == 0, "we expect empty string in the removed_part");

  return NULL;
}

char *test_remove_possessive_pronoun_with_dash() 
{
  char *stemmed_word = NULL; 
  char *removed_part = NULL;

  int rc = remove_possessive_pronoun("cinta-ku", &stemmed_word, &removed_part);

  mu_assert(rc, "successfully stems");
  mu_assert(strcmp("cinta", stemmed_word) == 0, "we expect 'cinta' as the stemmed word");
  mu_assert(strcmp("ku", removed_part) == 0, "we expect 'ku' as the removed part");

  return NULL;
}

char *test_remove_possessive_pronoun_without_dash() 
{
  char *stemmed_word = NULL; 
  char *removed_part = NULL;

  int rc = remove_possessive_pronoun("cintaku", &stemmed_word, &removed_part);
  mu_assert(rc, "successfully stems");
  mu_assert(strcmp("cinta", stemmed_word) == 0, "we expect 'cinta' as the stemmed word");
  mu_assert(strcmp("ku", removed_part) == 0, "we expect 'ku' as the removed part");

  return NULL;
}

char *test_remove_derivational_suffix_with_dash() 
{
  char *stemmed_word = NULL; 
  char *removed_part = NULL;

  int rc = remove_derivational_suffix("cinta-kan", &stemmed_word, &removed_part);

  mu_assert(rc, "successfully stems");
  mu_assert(strcmp("cinta", stemmed_word) == 0, "we expect 'cinta' as the stemmed word");
  mu_assert(strcmp("kan", removed_part) == 0, "we expect 'kan' as the removed part");

  return NULL;
}

char *test_remove_derivational_suffix_without_dash() 
{
  char *stemmed_word = NULL; 
  char *removed_part = NULL;

  int rc = remove_derivational_suffix("cintakan", &stemmed_word, &removed_part);
  mu_assert(rc, "successfully stems");
  mu_assert(strcmp("cinta", stemmed_word) == 0, "we expect 'cinta' as the stemmed word");
  mu_assert(strcmp("kan", removed_part) == 0, "we expect 'kan' as the removed part");

  return NULL;
}



char *test_remove_suffixes() 
{
  char *word = "bajumukah";
  char *stemmed_word = NULL;
  remove_suffixes(word, &stemmed_word);
  debug("stem word: %s, expected: baju, actual: %s", word, stemmed_word);
  mu_assert(strcmp("baju", stemmed_word) == 0, "it stems to baju");
  free(stemmed_word);

  return NULL;
}

char *test_remove_plain_prefix_di() 
{
  char *stemmed_word = NULL; 
  char *removed_part = NULL;

  int rc = remove_plain_prefix("dicinta", &stemmed_word, &removed_part);

  mu_assert(rc, "successfully stems");
  mu_assert(strcmp("cinta", stemmed_word) == 0, "we expect 'cinta' as the stemmed word");
  mu_assert(strcmp("di", removed_part) == 0, "we expect 'di' as the removed part");

  return NULL;
}

char *test_remove_plain_prefix_ke() 
{
  char *stemmed_word = NULL; 
  char *removed_part = NULL;

  int rc = remove_plain_prefix("kesana", &stemmed_word, &removed_part);

  mu_assert(rc, "successfully stems");
  mu_assert(strcmp("sana", stemmed_word) == 0, "we expect 'sana' as the stemmed word");
  mu_assert(strcmp("ke", removed_part) == 0, "we expect 'ke' as the removed part");

  return NULL;
}

char *test_remove_plain_prefix_se() 
{
  char *stemmed_word = NULL; 
  char *removed_part = NULL;

  int rc = remove_plain_prefix("sejenis", &stemmed_word, &removed_part);

  mu_assert(rc, "successfully stems");
  mu_assert(strcmp("jenis", stemmed_word) == 0, "we expect 'jenis' as the stemmed word");
  mu_assert(strcmp("se", removed_part) == 0, "we expect 'se' as the removed part");

  return NULL;
}

char *test_stem_singular_word_removes_suffixes() 
{
  char *word = "bajumukah";
  char *stemmed_word = NULL;
  int rc = stem_singular_word(word, &stemmed_word);
  debug("stem word: %s, expected: baju, actual: %s", word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("baju", stemmed_word) == 0, "it stems to baju");
  free(stemmed_word);

  return NULL;
}

char *test_stem_singular_word_removes_plain_prefixes() 
{
  char *word = "kerajinannya";
  char *stemmed_word = NULL;
  int rc = stem_singular_word(word, &stemmed_word);
  debug("stem word: %s, expected: rajin, actual: %s", word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("rajin", stemmed_word) == 0, "it stems to rajin");
  free(stemmed_word);

  return NULL;
}

char *test_dictionary_load() 
{
  int rc;

  rc = dictionary_load(dictionary_fullpath("tests/test_dict.txt"));
  mu_assert(rc, "when test_dict exists return truthy");

  rc = dictionary_load(dictionary_fullpath("tests/test_not_exists.txt"));
  mu_assert(!rc, "when the dict file does not exist it should return falsy");

  return NULL;
}

char *test_dictionary_contains() 
{
  dictionary_load(dictionary_fullpath("tests/test_dict.txt"));
  mu_assert(dictionary_contains("aba"), "test dict contains aba");
  mu_assert(!dictionary_contains("non-existent"), "test dict does not contain non-existent");

  return NULL;
}

char *test_dictionary_add() 
{
  dictionary_add("nonexistent");

  mu_assert(dictionary_contains("nonexistent"), "dict should contain nonexistent");
  mu_assert(!dictionary_contains("nonexistent2"), "dict should not contain nonexistent2");

  int count = dictionary_count();
  dictionary_add("bola");
  int new_count = dictionary_count();
  mu_assert(count == new_count, "dictionary_add ensures that entries are unique");

  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_is_plural);
  mu_run_test(test_plural_parts);
  mu_run_test(test_stem_plural_word_when_both_words_are_root_words_and_the_same);
  mu_run_test(test_stem_plural_word_when_one_word_has_suffixes);

  mu_run_test(test_remove_inflectional_particle_with_dash);
  mu_run_test(test_remove_inflectional_particle_without_dash);
  mu_run_test(test_remove_inflectional_particle_no_match);

  mu_run_test(test_remove_possessive_pronoun_with_dash);
  mu_run_test(test_remove_possessive_pronoun_without_dash);

  mu_run_test(test_remove_derivational_suffix_with_dash);
  mu_run_test(test_remove_derivational_suffix_without_dash);

  mu_run_test(test_remove_suffixes);

  mu_run_test(test_remove_plain_prefix_di);
  mu_run_test(test_remove_plain_prefix_ke);
  mu_run_test(test_remove_plain_prefix_se);

  mu_run_test(test_stem_singular_word);
  mu_run_test(test_stem_singular_word_removes_suffixes);
  mu_run_test(test_stem_singular_word_removes_plain_prefixes);

  mu_run_test(test_dictionary_load);
  mu_run_test(test_dictionary_add);
  mu_run_test(test_dictionary_contains);
  
  return NULL;
}

RUN_TESTS(all_tests);
