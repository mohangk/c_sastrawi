#ifdef __linux
  #define _GNU_SOURCE 
#endif
#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sastrawi.h"
#include "../dbg.h"
#include "test_dictionary.h"
#include "test_stem_plural.h"

void free_parts(int parts_count, char **parts[])
{
  for (int i = 0; i < parts_count; i++)
  {
    free((*parts)[i]);
  }
  free(*parts);
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

char *test_remove_complex_prefix_rule1_a() 
{
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = remove_complex_prefix_rule1("beria", &stemmed_word, &removed_part);
  debug("stem word: beria, expected: ia, actual: %s", stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("ia", stemmed_word) == 0, "it stems to ia");
  mu_assert(strcmp("ber", removed_part) == 0, "remove part should be ber");
  free(stemmed_word);
  free(removed_part);

  return NULL;
}

char *test_remove_complex_prefix_rule1_b() 
{
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = remove_complex_prefix_rule1("berakit", &stemmed_word, &removed_part);
  debug("stem word: berakit, expected: rakit, actual: %s", stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("rakit", stemmed_word) == 0, "it stems to rakit");
  mu_assert(strcmp("be", removed_part) == 0, "remove part should be be");
  free(stemmed_word);
  free(removed_part);

  return NULL;
}

char *test_remove_complex_prefix_rule2() 
{
  char *word = "berkop";
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = remove_complex_prefix_rule2(word, &stemmed_word, &removed_part);
  debug("stem word: %s, expected: kop, actual: %s", word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("kop", stemmed_word) == 0, "it stems to kop");
  mu_assert(strcmp("ber", removed_part) == 0, "remove part should be ber");
  free(stemmed_word);
  free(removed_part);

  return NULL;
}

char *test_remove_complex_prefix_rule2_excludes_er() 
{
  char *word = "berdaerah";
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = remove_complex_prefix_rule2(word, &stemmed_word, &removed_part);
  debug("stem word: %s, expected: berdaerah, actual: %s", word, stemmed_word);
  mu_assert(rc == 0, "does not stem");
  mu_assert(strcmp("berdaerah", stemmed_word) == 0, "it does not stem it");
  free(stemmed_word);
  free(removed_part);

  return NULL;
}

char *test_remove_complex_prefix_rule3_only_includes_er() 
{
  char *stemable_word = "berdaerah";
  char *nonstemable_word = "bertabur";
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = remove_complex_prefix_rule3(stemable_word, &stemmed_word, &removed_part);
  debug("stem word: %s, expected: daerah, actual: %s", stemable_word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("daerah", stemmed_word) == 0, "it stems to daerah");
  mu_assert(strcmp("ber", removed_part) == 0, "remove part should be ber");
  free(stemmed_word);
  free(removed_part);
 
  rc = remove_complex_prefix_rule3(nonstemable_word, &stemmed_word, &removed_part);
  mu_assert(rc == 0, "cannot stem");
  free(stemmed_word);
  free(removed_part);

  return NULL;
}

char *test_stem_singular_word_removes_complex_prefixes_1() 
{
  char *word = "beria";
  char *stemmed_word = NULL;
  int rc = stem_singular_word(word, &stemmed_word);
  debug("stem word: %s, expected: ia, actual: %s", word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("ia", stemmed_word) == 0, "it stems to ia");
  free(stemmed_word);

  return NULL;
}


char *test_stem_singular_word_removes_complex_prefixes_2() 
{
  char *word = "bertabur";
  char *stemmed_word = NULL;
  int rc = stem_singular_word(word, &stemmed_word);
  debug("stem word: %s, expected: tabur, actual: %s", word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("tabur", stemmed_word) == 0, "it stems to tabur");
  free(stemmed_word);

  return NULL;
}

char *test_stem_singular_word_removes_complex_prefixes_3() 
{
  char *word = "berdaerah";
  char *stemmed_word = NULL;
  int rc = stem_singular_word(word, &stemmed_word);
  debug("stem word: %s, expected: daerah, actual: %s", word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("daerah", stemmed_word) == 0, "it stems to daerah");
  free(stemmed_word);

  return NULL;
}
//TODO - create a test with berlarikah, to test return suffix

char *all_tests()
{
  mu_suite_start();

  dictionary_load(dictionary_fullpath("data/kata-dasar.txt"));

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

  mu_run_test(test_remove_complex_prefix_rule1_a);
  mu_run_test(test_remove_complex_prefix_rule1_b);
  mu_run_test(test_remove_complex_prefix_rule2);
  mu_run_test(test_remove_complex_prefix_rule2_excludes_er);
  mu_run_test(test_remove_complex_prefix_rule3_only_includes_er);

  mu_run_test(test_stem_singular_word_removes_plain_prefixes);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_1);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_2);
  mu_run_test(test_stem_singular_word_removes_complex_prefixes_3);
  mu_run_test(test_dictionary_load);
  mu_run_test(test_dictionary_add);
  mu_run_test(test_dictionary_contains);

  return NULL;
}

RUN_TESTS(all_tests);
