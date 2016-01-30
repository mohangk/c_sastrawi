#ifdef __linux
  #define _GNU_SOURCE 
#endif
#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libsastrawi.h"
#include "sastrawi/remove_prefixes.h"
#include "dbg.h"

char *test_remove_complex_prefix(char *stemable_word, char *expected_stemmed_word, char *expected_removed_part, PREFIX_REMOVER fn)
{  
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = fn(stemable_word, &stemmed_word, &removed_part);
  debug("word: %s, expected stemmed word: %s, actual stemmed word: %s, expected removed part: %s, actual removed part: %s", stemable_word, expected_stemmed_word, stemmed_word, expected_removed_part, removed_part);
  mu_assert(rc == 1, "failed to stem");
  mu_assert(strcmp(expected_stemmed_word, stemmed_word) == 0, "failed while asserting stemmed word");
  mu_assert(strcmp(expected_removed_part, removed_part) == 0, "failed while asserting removed part");
  free(stemmed_word);
  free(removed_part);
  return NULL;
}

char *test_remove_plain_prefix_returns_0_if_word_notin_dictionary() 
{
  char *stemmed_word = NULL; 
  char *removed_part = NULL;

  int rc = remove_plain_prefix("dipertikai", &stemmed_word, &removed_part);

  mu_assert(rc == 0, "successfully stems but not in dictionary");
  mu_assert(strcmp("pertikai", stemmed_word) == 0, "we expect 'pertikai' as the stemmed word");
  mu_assert(strcmp("di", removed_part) == 0, "we expect 'di' as the removed part");

  free(stemmed_word);
  free(removed_part);

  return NULL;
}

char *test_remove_plain_prefix_di() 
{
  return test_remove_complex_prefix("dicinta", "cinta", "di",  remove_plain_prefix);
}

char *test_remove_plain_prefix_ke() 
{
  return test_remove_complex_prefix("kesana", "sana", "ke",  remove_plain_prefix);
}

char *test_remove_plain_prefix_se() 
{
  return test_remove_complex_prefix("sejenis", "jenis", "se",  remove_plain_prefix);
}

char *test_remove_complex_prefix_rule1_a() 
{
  return test_remove_complex_prefix("beria", "ia", "ber",  remove_complex_prefix_rule1);
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
  return test_remove_complex_prefix("berlari", "lari", "ber", remove_complex_prefix_rule2);
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

char *test_remove_complex_prefix_rule2_returns_stemmed_word_although_not_in_dict() 
{
  char *word = "berlarian";
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = remove_complex_prefix_rule2(word, &stemmed_word, &removed_part);
  debug("stem word: %s, expected: larian, actual: %s", word, stemmed_word);
  mu_assert(rc == 0, "larian not in dictionary");
  mu_assert(strcmp("larian", stemmed_word) == 0, "the ber is removed");
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

char *test_remove_complex_prefix_rule4() 
{
  char *stemable_word = "belajar";
  char *nonstemable_word = "bertabur";
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = remove_complex_prefix_rule4(stemable_word, &stemmed_word, &removed_part);
  debug("stem word: %s, expected: ajar, actual: %s", stemable_word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("ajar", stemmed_word) == 0, "it stems to ajar");
  mu_assert(strcmp("bel", removed_part) == 0, "remove part should be bel");
  free(stemmed_word);
  free(removed_part);
 
  rc = remove_complex_prefix_rule4(nonstemable_word, &stemmed_word, &removed_part);
  mu_assert(rc == 0, "cannot stem");
  free(stemmed_word);
  free(removed_part);

  return NULL;
}

char *test_remove_complex_prefix_rule5() 
{
  char *stemable_word = "bekerja";
  char *nonstemable_word = "berlari";
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = remove_complex_prefix_rule5(stemable_word, &stemmed_word, &removed_part);
  debug("stem word: %s, expected: kerja, actual: %s", stemable_word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("kerja", stemmed_word) == 0, "it stems to kerja");
  mu_assert(strcmp("be", removed_part) == 0, "remove part should be be");
  free(stemmed_word);
  free(removed_part);
 
  rc = remove_complex_prefix_rule5(nonstemable_word, &stemmed_word, &removed_part);
  mu_assert(rc == 0, "cannot stem");
  free(stemmed_word);
  free(removed_part);

  return NULL;
}

char *test_remove_complex_prefix_rule6a() 
{
  char *stemable_word = "terancam";
  char *nonstemable_word = "terbalik";
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = remove_complex_prefix_rule6(stemable_word, &stemmed_word, &removed_part);
  debug("stem word: %s, expected: ancam, actual: %s", stemable_word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("ancam", stemmed_word) == 0, "it stems to ancam");
  mu_assert(strcmp("ter", removed_part) == 0, "remove part should be be");
  free(stemmed_word);
  free(removed_part);
 
  rc = remove_complex_prefix_rule6(nonstemable_word, &stemmed_word, &removed_part);
  mu_assert(rc == 0, "cannot stem");
  free(stemmed_word);
  free(removed_part);

  return NULL;
}

char *test_remove_complex_prefix_rule6b() 
{
  char *stemable_word = "teracun";
  char *nonstemable_word = "terbalik";
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = remove_complex_prefix_rule6(stemable_word, &stemmed_word, &removed_part);
  debug("stem word: %s, expected: racun, actual: %s", stemable_word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("racun", stemmed_word) == 0, "it stems to racun");
  mu_assert(strcmp("te", removed_part) == 0, "remove part should be te");
  free(stemmed_word);
  free(removed_part);
 
  rc = remove_complex_prefix_rule6(nonstemable_word, &stemmed_word, &removed_part);
  mu_assert(rc == 0, "cannot stem");
  free(stemmed_word);
  free(removed_part);

  return NULL;
}

char *test_remove_complex_prefix_rule7() 
{
  char *stemable_word = "terperuk";
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = remove_complex_prefix_rule7(stemable_word, &stemmed_word, &removed_part);
  debug("stem word: %s, expected: peruk, actual: %s", stemable_word, stemmed_word);
  mu_assert(rc == 1, "sucessfully stemmed");
  mu_assert(strcmp("peruk", stemmed_word) == 0, "it stems to peruk");
  mu_assert(strcmp("ter", removed_part) == 0, "remove part should be ter");
  free(stemmed_word);
  free(removed_part);
  return NULL;
}

char *test_remove_complex_prefix_rule8() 
{
  return test_remove_complex_prefix("tertangkap", "tangkap", "ter",  remove_complex_prefix_rule8);
}

char *test_remove_complex_prefix_rule8_still_stems_when_not_in_dict() 
{
  char *stemable_word = "tertangkaplah";
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = remove_complex_prefix_rule8(stemable_word, &stemmed_word, &removed_part);
  debug("stem word: %s, expected: tangkaplah, actual: %s", stemable_word, stemmed_word);
  mu_assert(rc == 0, "not in dict");
  mu_assert(strcmp("tangkaplah", stemmed_word) == 0, "it stems to tangkaplah");
  mu_assert(strcmp("ter", removed_part) == 0, "remove part should be ter");
  free(stemmed_word);
  free(removed_part);
  return NULL;
}

char *test_remove_complex_prefix_rule8_excludes_er() 
{
  char *word = "terterbang";
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = remove_complex_prefix_rule8(word, &stemmed_word, &removed_part);
  debug("stem word: %s, expected: terterbang, actual: %s", word, stemmed_word);
  mu_assert(rc == 0, "does not stem");
  mu_assert(strcmp("terterbang", stemmed_word) == 0, "it does not stem it");
  free(stemmed_word);
  free(removed_part);

  return NULL;
}

char *test_remove_complex_prefix_rule9() 
{
  return test_remove_complex_prefix("teterbang", "terbang", "te",  remove_complex_prefix_rule9);
}

char *test_remove_complex_prefix_rule10_l() 
{
  return test_remove_complex_prefix("melalu", "lalu", "me",  remove_complex_prefix_rule10);
}

char *test_remove_complex_prefix_rule10_r() 
{
  return test_remove_complex_prefix("meracun", "racun", "me",  remove_complex_prefix_rule10);
}

char *test_remove_complex_prefix_rule10_w() 
{
  return test_remove_complex_prefix("mewarna", "warna", "me",  remove_complex_prefix_rule10);
}

char *test_remove_complex_prefix_rule10_y() 
{
  return test_remove_complex_prefix("meyakin", "yakin", "me",  remove_complex_prefix_rule10);
}

char *test_remove_complex_prefix_rule11_f() 
{
  return test_remove_complex_prefix("memfasilitas", "fasilitas", "mem",  remove_complex_prefix_rule11);
}

char *test_remove_complex_prefix_rule11_b() 
{
  return test_remove_complex_prefix("membantu", "bantu", "mem",  remove_complex_prefix_rule11);
}

char *test_remove_complex_prefix_rule11_v() 
{
  return test_remove_complex_prefix("memvonis", "vonis", "mem",  remove_complex_prefix_rule11);
}

char *test_remove_complex_prefix_rule11_unstemmable() 
{
  char *word = "terbalik";
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = remove_complex_prefix_rule11(word, &stemmed_word, &removed_part);
  debug("word: %s, expected: %s, actual: %s, expected removed: %s, actual removed : %s",
      word, word, 
      stemmed_word, "", 
      removed_part);

  mu_assert(rc == 0, "should not stem");
  mu_assert(strcmp(word, stemmed_word) == 0, "it returns the original word");
  mu_assert(strcmp("", removed_part) == 0, "it returns an empty string as the removed part");
  free(stemmed_word);
  free(removed_part);

  return NULL;
}

char *test_remove_complex_prefix_rule12() 
{
  return test_remove_complex_prefix("mempengaruh", "pengaruh", "mem",  remove_complex_prefix_rule12);
}

char *test_remove_complex_prefix_rule13a() 
{
  return test_remove_complex_prefix("memasuk", "masuk", "me",  remove_complex_prefix_rule13);
}

char *test_remove_complex_prefix_rule13b() 
{
  return test_remove_complex_prefix("memakai", "pakai", "me",  remove_complex_prefix_rule13);
}

char *test_remove_complex_prefix_rule14_c() 
{
  return test_remove_complex_prefix("mencantum", "cantum", "men",  remove_complex_prefix_rule14);
}

char *test_remove_complex_prefix_rule14_d() 
{
  return test_remove_complex_prefix("menduduk", "duduk", "men",  remove_complex_prefix_rule14);
}

char *test_remove_complex_prefix_rule14_j() 
{
  return test_remove_complex_prefix("menjemput", "jemput", "men",  remove_complex_prefix_rule14);
}

char *test_remove_complex_prefix_rule14_s() 
{
  return test_remove_complex_prefix("mensyukur", "syukur", "men",  remove_complex_prefix_rule14);
}

char *test_remove_complex_prefix_rule14_t() 
{
  return test_remove_complex_prefix("mentaat", "taat", "men",  remove_complex_prefix_rule14);
}

char *test_remove_complex_prefix_rule14_z() 
{
  return test_remove_complex_prefix("menziarah", "ziarah", "men",  remove_complex_prefix_rule14);
}

char *test_remove_complex_prefix_rule15a() 
{
  return test_remove_complex_prefix("menikmat", "nikmat", "me",  remove_complex_prefix_rule15);
}

char *test_remove_complex_prefix_rule15b() 
{
  return test_remove_complex_prefix("menulis", "tulis", "me",  remove_complex_prefix_rule15);
}

char *test_remove_complex_prefix_rule16_g() 
{
  return test_remove_complex_prefix("mengguna", "guna", "meng",  remove_complex_prefix_rule16);
}

char *test_remove_complex_prefix_rule16_h() 
{
  return test_remove_complex_prefix("menghambat", "hambat", "meng",  remove_complex_prefix_rule16);
}

char *test_remove_complex_prefix_rule16_q() 
{
  return test_remove_complex_prefix("mengqasar", "qasar", "meng",  remove_complex_prefix_rule16);
}

char *test_remove_complex_prefix_rule16_k() 
{
  return test_remove_complex_prefix("mengkritik", "kritik", "meng",  remove_complex_prefix_rule16);
}

char *test_remove_complex_prefix_rule17a() 
{
  return test_remove_complex_prefix("mengerat", "erat", "meng",  remove_complex_prefix_rule17);
}

char *test_remove_complex_prefix_rule17b() 
{
  return test_remove_complex_prefix("mengecil", "kecil", "meng",  remove_complex_prefix_rule17);
}

char *test_remove_complex_prefix_rule17c() 
{
  return test_remove_complex_prefix("mengecat", "cat", "menge",  remove_complex_prefix_rule17);
}

char *test_remove_complex_prefix_rule17d() 
{
  return test_remove_complex_prefix("mengiang", "ngiang", "me",  remove_complex_prefix_rule17);
}

char *test_remove_complex_prefix_rule18a() 
{
  return test_remove_complex_prefix("menyala", "nyala", "me",  remove_complex_prefix_rule18);
}

char *test_remove_complex_prefix_rule18b() 
{
  return test_remove_complex_prefix("menyapu", "sapu", "meny",  remove_complex_prefix_rule18);
}

char *test_remove_complex_prefix_rule19_1() 
{
  return test_remove_complex_prefix("memproteksi", "proteksi", "mem",  remove_complex_prefix_rule19);
}

char *test_remove_complex_prefix_rule19_2() 
{
  return test_remove_complex_prefix("mempatroli", "patroli", "mem",  remove_complex_prefix_rule19);
}

char *test_remove_complex_prefix_rule20_1() 
{
  return test_remove_complex_prefix("pewarna", "warna", "pe",  remove_complex_prefix_rule20);
}

char *test_remove_complex_prefix_rule20_2() 
{
  return test_remove_complex_prefix("peyoga", "yoga", "pe",  remove_complex_prefix_rule20);
}

char *test_remove_prefixes_when_cannot_stem_to_word_in_dict()
{
  char *stemmed_word;

  int rc = remove_prefixes("mewarnai", &stemmed_word);
  debug("word: mewarnai, expected stemmed word: warnai, actual stemmed word: %s", stemmed_word);
  mu_assert(rc == 0, "it changes the word, but its not done");
  mu_assert(strcmp("warnai", stemmed_word) == 0, "failed while asserting stemmed word");
  free(stemmed_word);
  return NULL;
}

char *test_remove_prefixes_runs_3_times() 
{
  char *stemmed_word;

  // diberberlari is a fake work, but we need it as a test, can't think of a valid word
  int rc = remove_prefixes("diberberlari", &stemmed_word);
  debug("word: diberberlari, expected stemmed word: lari, actual stemmed word: %s", stemmed_word);
  mu_assert(rc == 1, "it is fully stemmed");
  mu_assert(strcmp("lari", stemmed_word) == 0, "failed while asserting stemmed word");
  free(stemmed_word);
  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  char *path = dictionary_fullpath("data/kata-dasar.txt");
  dictionary_load(path);
  free(path);


  mu_run_test(test_remove_plain_prefix_returns_0_if_word_notin_dictionary)
  mu_run_test(test_remove_plain_prefix_di);
  mu_run_test(test_remove_plain_prefix_ke);
  mu_run_test(test_remove_plain_prefix_se);
  mu_run_test(test_remove_complex_prefix_rule1_a);
  mu_run_test(test_remove_complex_prefix_rule1_b);
  mu_run_test(test_remove_complex_prefix_rule2);
  mu_run_test(test_remove_complex_prefix_rule2_excludes_er);
  mu_run_test(test_remove_complex_prefix_rule2_returns_stemmed_word_although_not_in_dict);
  mu_run_test(test_remove_complex_prefix_rule3_only_includes_er);
  mu_run_test(test_remove_complex_prefix_rule4);
  mu_run_test(test_remove_complex_prefix_rule5);
  mu_run_test(test_remove_complex_prefix_rule6a);
  mu_run_test(test_remove_complex_prefix_rule6b);
  mu_run_test(test_remove_complex_prefix_rule7);
  mu_run_test(test_remove_complex_prefix_rule8);
  mu_run_test(test_remove_complex_prefix_rule8_excludes_er);
  mu_run_test(test_remove_complex_prefix_rule8_still_stems_when_not_in_dict);
  mu_run_test(test_remove_complex_prefix_rule9);
  mu_run_test(test_remove_complex_prefix_rule10_l);
  mu_run_test(test_remove_complex_prefix_rule10_r);
  mu_run_test(test_remove_complex_prefix_rule10_w);
  mu_run_test(test_remove_complex_prefix_rule10_y);
  mu_run_test(test_remove_complex_prefix_rule11_f);
  mu_run_test(test_remove_complex_prefix_rule11_b);
  mu_run_test(test_remove_complex_prefix_rule11_v);
  mu_run_test(test_remove_complex_prefix_rule11_unstemmable);
  mu_run_test(test_remove_complex_prefix_rule12);
  mu_run_test(test_remove_complex_prefix_rule13a);
  mu_run_test(test_remove_complex_prefix_rule13b);
  mu_run_test(test_remove_complex_prefix_rule14_c);
  mu_run_test(test_remove_complex_prefix_rule14_d);
  mu_run_test(test_remove_complex_prefix_rule14_j);
  mu_run_test(test_remove_complex_prefix_rule14_s);
  mu_run_test(test_remove_complex_prefix_rule14_t);
  mu_run_test(test_remove_complex_prefix_rule14_z);
  mu_run_test(test_remove_complex_prefix_rule15a);
  mu_run_test(test_remove_complex_prefix_rule15b);
  mu_run_test(test_remove_complex_prefix_rule16_g);
  mu_run_test(test_remove_complex_prefix_rule16_h);
  mu_run_test(test_remove_complex_prefix_rule16_q);
  mu_run_test(test_remove_complex_prefix_rule16_k);
  mu_run_test(test_remove_complex_prefix_rule17a);
  mu_run_test(test_remove_complex_prefix_rule17b);
  mu_run_test(test_remove_complex_prefix_rule17c);
  mu_run_test(test_remove_complex_prefix_rule17d);
  mu_run_test(test_remove_complex_prefix_rule18a);
  mu_run_test(test_remove_complex_prefix_rule18b);
  mu_run_test(test_remove_complex_prefix_rule19_1);
  mu_run_test(test_remove_complex_prefix_rule19_2);
  mu_run_test(test_remove_complex_prefix_rule20_1);
  mu_run_test(test_remove_complex_prefix_rule20_2);
  mu_run_test(test_remove_prefixes_when_cannot_stem_to_word_in_dict);
  mu_run_test(test_remove_prefixes_runs_3_times);
  return NULL;
}

RUN_TESTS(all_tests);
