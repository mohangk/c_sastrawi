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

char *test_remove_complex_prefix(char *stemable_word, char *expected_stemmed_word, char *expected_removed_part, int expected_response_code, PREFIX_REMOVER fn)
{  
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = fn(stemable_word, &stemmed_word, &removed_part);
  debug("word: %s, expected_response_code: %d, actual_response_code: %d, expected stemmed word: %s, actual stemmed word: %s, expected removed part: %s, actual removed part: %s", stemable_word, expected_response_code, rc, expected_stemmed_word, stemmed_word, expected_removed_part, removed_part);
  mu_assert(rc == expected_response_code, "failed while asserting expected_response_code");
  mu_assert(strcmp(expected_stemmed_word, stemmed_word) == 0, "failed while asserting stemmed word");
  mu_assert(strcmp(expected_removed_part, removed_part) == 0, "failed while asserting removed part");

  if(rc != NOT_STEMMED) {
    free(stemmed_word);
    free(removed_part);
  }

  return NULL;
}

char *test_remove_plain_prefix_returns_0_if_word_notin_dictionary() 
{
  return test_remove_complex_prefix("dipertikai", "pertikai", "di", PARTIALLY_STEMMED, remove_plain_prefix);
}

char *test_remove_plain_prefix_di() 
{
  return test_remove_complex_prefix("dicinta", "cinta", "di", FULLY_STEMMED, remove_plain_prefix);
}

char *test_remove_plain_prefix_ke() 
{
  return test_remove_complex_prefix("kesana", "sana", "ke", FULLY_STEMMED, remove_plain_prefix);
}

char *test_remove_plain_prefix_se() 
{
  return test_remove_complex_prefix("sejenis", "jenis", "se", FULLY_STEMMED, remove_plain_prefix);
}

char *test_remove_complex_prefix_rule1_a() 
{
  return test_remove_complex_prefix("beria", "ia", "ber", FULLY_STEMMED, remove_complex_prefix_rule1);
}

char *test_remove_complex_prefix_rule1_b() 
{

  return test_remove_complex_prefix("berakit", "rakit", "be", FULLY_STEMMED, remove_complex_prefix_rule1);
}

char *test_remove_complex_prefix_rule2() 
{
  return test_remove_complex_prefix("berlari", "lari", "ber", FULLY_STEMMED,remove_complex_prefix_rule2);
}

char *test_remove_complex_prefix_rule2_excludes_er() 
{
  return test_remove_complex_prefix("berdaerah", "berdaerah", "", NOT_STEMMED, remove_complex_prefix_rule2);

}

char *test_remove_complex_prefix_rule2_returns_stemmed_word_although_not_in_dict() 
{
  return test_remove_complex_prefix("berlarian", "larian", "ber", PARTIALLY_STEMMED, remove_complex_prefix_rule2);
}

char *test_remove_complex_prefix_rule3_only_includes_er() 
{
  return test_remove_complex_prefix("berdaerah", "daerah", "ber", FULLY_STEMMED, remove_complex_prefix_rule3);
}

char *test_remove_complex_prefix_rule3_only_includes_er_not_stemmed()
{
  return test_remove_complex_prefix("bertabur", "bertabur", "", NOT_STEMMED, remove_complex_prefix_rule3);
}


char *test_remove_complex_prefix_rule4() 
{
  return test_remove_complex_prefix("belajar", "ajar", "bel", FULLY_STEMMED,remove_complex_prefix_rule4);
}

char *test_remove_complex_prefix_rule4_not_stemmed() 
{
  return test_remove_complex_prefix("bertabur", "bertabur", "", NOT_STEMMED, remove_complex_prefix_rule4);
}

char *test_remove_complex_prefix_rule5() 
{
  return test_remove_complex_prefix("bekerja", "kerja", "be", FULLY_STEMMED, remove_complex_prefix_rule5);
}

char *test_remove_complex_prefix_rule5_not_stemmed() 
{
  return test_remove_complex_prefix("berlari", "berlari", "", NOT_STEMMED, remove_complex_prefix_rule5);
}

char *test_remove_complex_prefix_rule6a() 
{
  return test_remove_complex_prefix("terancam", "ancam", "ter", FULLY_STEMMED, remove_complex_prefix_rule6);
}

char *test_remove_complex_prefix_rule6a_not_stemmed() 
{
  return test_remove_complex_prefix("terbalik", "terbalik", "", NOT_STEMMED, remove_complex_prefix_rule6);
}

char *test_remove_complex_prefix_rule6b() 
{
  return test_remove_complex_prefix("teracun", "racun", "te", FULLY_STEMMED, remove_complex_prefix_rule6);
}

char *test_remove_complex_prefix_rule6b_not_stemmed() 
{
  return test_remove_complex_prefix("terbalik", "terbalik", "", NOT_STEMMED, remove_complex_prefix_rule6);
}

char *test_remove_complex_prefix_rule7() 
{
  return test_remove_complex_prefix("terperuk", "peruk", "ter", FULLY_STEMMED, remove_complex_prefix_rule7);
}

char *test_remove_complex_prefix_rule8() 
{
  return test_remove_complex_prefix("tertangkap", "tangkap", "ter", FULLY_STEMMED, remove_complex_prefix_rule8);
}

char *test_remove_complex_prefix_rule8_when_partially_stemmed() 
{
  return test_remove_complex_prefix("tertangkaplah", "tangkaplah", "ter", PARTIALLY_STEMMED, remove_complex_prefix_rule8);
}

char *test_remove_complex_prefix_rule8_excludes_er() 
{
  return test_remove_complex_prefix("terterbang", "terterbang", "", NOT_STEMMED, remove_complex_prefix_rule8);
}

char *test_remove_complex_prefix_rule9() 
{
  return test_remove_complex_prefix("teterbang", "terbang", "te", FULLY_STEMMED, remove_complex_prefix_rule9);
}

char *test_remove_complex_prefix_rule10_l() 
{
  return test_remove_complex_prefix("melalu", "lalu", "me", FULLY_STEMMED, remove_complex_prefix_rule10);
}

char *test_remove_complex_prefix_rule10_r() 
{
  return test_remove_complex_prefix("meracun", "racun", "me", FULLY_STEMMED, remove_complex_prefix_rule10);
}

char *test_remove_complex_prefix_rule10_w() 
{
  return test_remove_complex_prefix("mewarna", "warna", "me", FULLY_STEMMED, remove_complex_prefix_rule10);
}

char *test_remove_complex_prefix_rule10_y() 
{
  return test_remove_complex_prefix("meyakin", "yakin", "me", FULLY_STEMMED, remove_complex_prefix_rule10);
}

char *test_remove_complex_prefix_rule11_f() 
{
  return test_remove_complex_prefix("memfasilitas", "fasilitas", "mem", FULLY_STEMMED, remove_complex_prefix_rule11);
}

char *test_remove_complex_prefix_rule11_b() 
{
  return test_remove_complex_prefix("membantu", "bantu", "mem", FULLY_STEMMED, remove_complex_prefix_rule11);
}

char *test_remove_complex_prefix_rule11_v() 
{
  return test_remove_complex_prefix("memvonis", "vonis", "mem", FULLY_STEMMED, remove_complex_prefix_rule11);
}

char *test_remove_complex_prefix_rule11_unstemmable() 
{
  return test_remove_complex_prefix("terbalik", "terbalik", "", NOT_STEMMED, remove_complex_prefix_rule11);
}

char *test_remove_complex_prefix_rule12() 
{
  return test_remove_complex_prefix("mempengaruh", "pengaruh", "mem", FULLY_STEMMED, remove_complex_prefix_rule12);
}

char *test_remove_complex_prefix_rule13a() 
{
  return test_remove_complex_prefix("memasuk", "masuk", "me", FULLY_STEMMED, remove_complex_prefix_rule13);
}

char *test_remove_complex_prefix_rule13b() 
{
  return test_remove_complex_prefix("memakai", "pakai", "me", FULLY_STEMMED, remove_complex_prefix_rule13);
}

char *test_remove_complex_prefix_rule14_c() 
{
  return test_remove_complex_prefix("mencantum", "cantum", "men", FULLY_STEMMED, remove_complex_prefix_rule14);
}

char *test_remove_complex_prefix_rule14_d() 
{
  return test_remove_complex_prefix("menduduk", "duduk", "men", FULLY_STEMMED, remove_complex_prefix_rule14);
}

char *test_remove_complex_prefix_rule14_j() 
{
  return test_remove_complex_prefix("menjemput", "jemput", "men", FULLY_STEMMED, remove_complex_prefix_rule14);
}

char *test_remove_complex_prefix_rule14_s() 
{
  return test_remove_complex_prefix("mensyukur", "syukur", "men", FULLY_STEMMED, remove_complex_prefix_rule14);
}

char *test_remove_complex_prefix_rule14_t() 
{
  return test_remove_complex_prefix("mentaat", "taat", "men", FULLY_STEMMED, remove_complex_prefix_rule14);
}

char *test_remove_complex_prefix_rule14_z() 
{
  return test_remove_complex_prefix("menziarah", "ziarah", "men", FULLY_STEMMED, remove_complex_prefix_rule14);
}

char *test_remove_complex_prefix_rule15a() 
{
  return test_remove_complex_prefix("menikmat", "nikmat", "me", FULLY_STEMMED, remove_complex_prefix_rule15);
}

char *test_remove_complex_prefix_rule15b() 
{
  return test_remove_complex_prefix("menulis", "tulis", "me", FULLY_STEMMED, remove_complex_prefix_rule15);
}

char *test_remove_complex_prefix_rule16_g() 
{
  return test_remove_complex_prefix("mengguna", "guna", "meng", FULLY_STEMMED, remove_complex_prefix_rule16);
}

char *test_remove_complex_prefix_rule16_h() 
{
  return test_remove_complex_prefix("menghambat", "hambat", "meng", FULLY_STEMMED, remove_complex_prefix_rule16);
}

char *test_remove_complex_prefix_rule16_q() 
{
  return test_remove_complex_prefix("mengqasar", "qasar", "meng", FULLY_STEMMED, remove_complex_prefix_rule16);
}

char *test_remove_complex_prefix_rule16_k() 
{
  return test_remove_complex_prefix("mengkritik", "kritik", "meng", FULLY_STEMMED, remove_complex_prefix_rule16);
}

char *test_remove_complex_prefix_rule17a() 
{
  return test_remove_complex_prefix("mengerat", "erat", "meng", FULLY_STEMMED, remove_complex_prefix_rule17);
}

char *test_remove_complex_prefix_rule17b() 
{
  return test_remove_complex_prefix("mengecil", "kecil", "meng", FULLY_STEMMED, remove_complex_prefix_rule17);
}

char *test_remove_complex_prefix_rule17c() 
{
  return test_remove_complex_prefix("mengecat", "cat", "menge", FULLY_STEMMED, remove_complex_prefix_rule17);
}

char *test_remove_complex_prefix_rule17d() 
{
  return test_remove_complex_prefix("mengiang", "ngiang", "me", FULLY_STEMMED, remove_complex_prefix_rule17);
}

char *test_remove_complex_prefix_rule18a() 
{
  return test_remove_complex_prefix("menyala", "nyala", "me", FULLY_STEMMED, remove_complex_prefix_rule18);
}

char *test_remove_complex_prefix_rule18b() 
{
  return test_remove_complex_prefix("menyapu", "sapu", "meny", FULLY_STEMMED, remove_complex_prefix_rule18);
}

char *test_remove_complex_prefix_rule19_1() 
{
  return test_remove_complex_prefix("memproteksi", "proteksi", "mem", FULLY_STEMMED, remove_complex_prefix_rule19);
}

char *test_remove_complex_prefix_rule19_2() 
{
  return test_remove_complex_prefix("mempatroli", "patroli", "mem", FULLY_STEMMED, remove_complex_prefix_rule19);
}

char *test_remove_complex_prefix_rule20_1() 
{
  return test_remove_complex_prefix("pewarna", "warna", "pe", FULLY_STEMMED, remove_complex_prefix_rule20);
}

char *test_remove_complex_prefix_rule20_2() 
{
  return test_remove_complex_prefix("peyoga", "yoga", "pe", FULLY_STEMMED, remove_complex_prefix_rule20);
}

char *test_remove_prefixes_when_partially_stemmed()
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
  mu_run_test(test_remove_complex_prefix_rule3_only_includes_er_not_stemmed);
  mu_run_test(test_remove_complex_prefix_rule4);
  mu_run_test(test_remove_complex_prefix_rule4_not_stemmed);
  mu_run_test(test_remove_complex_prefix_rule5);
  mu_run_test(test_remove_complex_prefix_rule5_not_stemmed);
  mu_run_test(test_remove_complex_prefix_rule6a);
  mu_run_test(test_remove_complex_prefix_rule6a_not_stemmed);
  mu_run_test(test_remove_complex_prefix_rule6b);
  mu_run_test(test_remove_complex_prefix_rule6b_not_stemmed);
  mu_run_test(test_remove_complex_prefix_rule7);
  mu_run_test(test_remove_complex_prefix_rule8);
  mu_run_test(test_remove_complex_prefix_rule8_excludes_er);
  mu_run_test(test_remove_complex_prefix_rule8_when_partially_stemmed);
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
  mu_run_test(test_remove_prefixes_when_partially_stemmed);
  mu_run_test(test_remove_prefixes_runs_3_times);
  return NULL;
}

RUN_TESTS(all_tests);
