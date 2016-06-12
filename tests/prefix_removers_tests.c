#include "sastrawi/features.h"
#include "minunit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libsastrawi.h"
#include "sastrawi/dictionary.h"
#include "sastrawi/prefix_removers.h"
#include "sastrawi/remove_prefixes.h"
#include "dbg.h"

sastrawi_stemmer *stemmer;

char *test_remove_complex_prefix(char *stemable_word, char *expected_stemmed_word, char *expected_removed_part, int expected_response_code, PREFIX_REMOVER fn)
{  
  char *stemmed_word = NULL;
  char *removed_part = NULL;

  int rc = fn(stemmer, stemable_word, &stemmed_word, &removed_part);
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

char *test_remove_complex_prefix_rule1_a_partially_stemmed() 
{
  return test_remove_complex_prefix("berakhirlah", "akhirlah", "ber", PARTIALLY_STEMMED, remove_complex_prefix_rule1);
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

char *test_remove_complex_prefix_rule2_partially_stemmed() 
{
  return test_remove_complex_prefix("berlarian", "larian", "ber", PARTIALLY_STEMMED, remove_complex_prefix_rule2);
}

char *test_remove_complex_prefix_rule3_only_includes_er() 
{
  return test_remove_complex_prefix("berdaerah", "daerah", "ber", FULLY_STEMMED, remove_complex_prefix_rule3);
}

char *test_remove_complex_prefix_rule3_only_includes_er_partially_stemmed() 
{
  return test_remove_complex_prefix("berdaerahlah", "daerahlah", "ber", PARTIALLY_STEMMED, remove_complex_prefix_rule3);
}

char *test_remove_complex_prefix_rule3_only_includes_er_not_stemmed()
{
  return test_remove_complex_prefix("bertabur", "bertabur", "", NOT_STEMMED, remove_complex_prefix_rule3);
}


char *test_remove_complex_prefix_rule4() 
{
  return test_remove_complex_prefix("belajar", "ajar", "bel", FULLY_STEMMED,remove_complex_prefix_rule4);
}

char *test_remove_complex_prefix_rule4_partially_stemmed() 
{
  return test_remove_complex_prefix("belajarlah", "ajarlah", "bel", PARTIALLY_STEMMED,remove_complex_prefix_rule4);
}

char *test_remove_complex_prefix_rule4_not_stemmed() 
{
  return test_remove_complex_prefix("bertabur", "bertabur", "", NOT_STEMMED, remove_complex_prefix_rule4);
}

char *test_remove_complex_prefix_rule5() 
{
  return test_remove_complex_prefix("bekerja", "kerja", "be", FULLY_STEMMED, remove_complex_prefix_rule5);
}

char *test_remove_complex_prefix_rule5_partially_stemmed() 
{
  return test_remove_complex_prefix("bekerjalah", "kerjalah", "be", PARTIALLY_STEMMED, remove_complex_prefix_rule5);
}

char *test_remove_complex_prefix_rule5_not_stemmed() 
{
  return test_remove_complex_prefix("berlari", "berlari", "", NOT_STEMMED, remove_complex_prefix_rule5);
}

char *test_remove_complex_prefix_rule6a() 
{
  return test_remove_complex_prefix("terancam", "ancam", "ter", FULLY_STEMMED, remove_complex_prefix_rule6);
}

char *test_remove_complex_prefix_rule6a_partially_stemmed() 
{
  return test_remove_complex_prefix("terancamlah", "ancamlah", "ter", PARTIALLY_STEMMED, remove_complex_prefix_rule6);
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


char *test_remove_complex_prefix_rule7_partially_stemmed() 
{
  return test_remove_complex_prefix("terperuklah", "peruklah", "ter", PARTIALLY_STEMMED, remove_complex_prefix_rule7);
}

char *test_remove_complex_prefix_rule8() 
{
  return test_remove_complex_prefix("tertangkap", "tangkap", "ter", FULLY_STEMMED, remove_complex_prefix_rule8);
}

char *test_remove_complex_prefix_rule8_partially_stemmed() 
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

char *test_remove_complex_prefix_rule9_partially_stemmed() 
{
  return test_remove_complex_prefix("teterbangan", "terbangan", "te", PARTIALLY_STEMMED, remove_complex_prefix_rule9);
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

char *test_remove_complex_prefix_rule10_partially_stemmed() 
{
  return test_remove_complex_prefix("meyakinkan", "yakinkan", "me", PARTIALLY_STEMMED, remove_complex_prefix_rule10);
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

char *test_remove_complex_prefix_rule11_partially_stemmed() 
{
  return test_remove_complex_prefix("memvoniskan", "voniskan", "mem", PARTIALLY_STEMMED, remove_complex_prefix_rule11);
}

char *test_remove_complex_prefix_rule11_unstemmable() 
{
  return test_remove_complex_prefix("terbalik", "terbalik", "", NOT_STEMMED, remove_complex_prefix_rule11);
}

char *test_remove_complex_prefix_rule12() 
{
  return test_remove_complex_prefix("mempengaruh", "pengaruh", "mem", FULLY_STEMMED, remove_complex_prefix_rule12);
}

char *test_remove_complex_prefix_rule12_partially_stemmed() 
{
  return test_remove_complex_prefix("mempengaruhi", "pengaruhi", "mem", PARTIALLY_STEMMED, remove_complex_prefix_rule12);
}

char *test_remove_complex_prefix_rule13a() 
{
  return test_remove_complex_prefix("memasuk", "masuk", "me", FULLY_STEMMED, remove_complex_prefix_rule13);
}

char *test_remove_complex_prefix_rule13a_partially_stemmed() 
{
  return test_remove_complex_prefix("memasukan", "masukan", "me", PARTIALLY_STEMMED, remove_complex_prefix_rule13);
}

char *test_remove_complex_prefix_rule13b() 
{
  return test_remove_complex_prefix("memakai", "pakai", "me", FULLY_STEMMED, remove_complex_prefix_rule13);
}

char *test_remove_complex_prefix_rule14_partially_stemmed() 
{
  return test_remove_complex_prefix("mencantumkan", "cantumkan", "men", PARTIALLY_STEMMED, remove_complex_prefix_rule14);
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


char *test_remove_complex_prefix_rule15_partially_stemmed() 
{
  return test_remove_complex_prefix("menikmati", "nikmati", "me", PARTIALLY_STEMMED, remove_complex_prefix_rule15);
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

char *test_remove_complex_prefix_rule16_partially_stemmed() 
{
  return test_remove_complex_prefix("mengkritikan", "kritikan", "meng", PARTIALLY_STEMMED, remove_complex_prefix_rule16);
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

char *test_remove_complex_prefix_rule17_partially_stemmed() 
{
  return test_remove_complex_prefix("mengeratkan", "eratkan", "meng", PARTIALLY_STEMMED, remove_complex_prefix_rule17);
}

char *test_remove_complex_prefix_rule18a() 
{
  return test_remove_complex_prefix("menyala", "nyala", "me", FULLY_STEMMED, remove_complex_prefix_rule18);
}

char *test_remove_complex_prefix_rule18b() 
{
  return test_remove_complex_prefix("menyapu", "sapu", "meny", FULLY_STEMMED, remove_complex_prefix_rule18);
}

char *test_remove_complex_prefix_rule18_partially_stemmed() 
{
  return test_remove_complex_prefix("menyalakan", "nyalakan", "me", PARTIALLY_STEMMED, remove_complex_prefix_rule18);
}

char *test_remove_complex_prefix_rule19_1() 
{
  return test_remove_complex_prefix("memproteksi", "proteksi", "mem", FULLY_STEMMED, remove_complex_prefix_rule19);
}

char *test_remove_complex_prefix_rule19_2() 
{
  return test_remove_complex_prefix("mempatroli", "patroli", "mem", FULLY_STEMMED, remove_complex_prefix_rule19);
}

char *test_remove_complex_prefix_rule19_partially_stemmed() 
{
  return test_remove_complex_prefix("mempatrolikan", "patrolikan", "mem", PARTIALLY_STEMMED, remove_complex_prefix_rule19);
}

char *test_remove_complex_prefix_rule20_1() 
{
  return test_remove_complex_prefix("pewarna", "warna", "pe", FULLY_STEMMED, remove_complex_prefix_rule20);
}

char *test_remove_complex_prefix_rule20_2() 
{
  return test_remove_complex_prefix("peyoga", "yoga", "pe", FULLY_STEMMED, remove_complex_prefix_rule20);
}

char *test_remove_complex_prefix_rule20_partially_stemmed()
{
  return test_remove_complex_prefix("pewarnaan", "warnaan", "pe", PARTIALLY_STEMMED, remove_complex_prefix_rule20);
}


char *test_remove_complex_prefix_rule21a_partially_stemmed()
{
  return test_remove_complex_prefix("peradilan", "adilan", "per", PARTIALLY_STEMMED, remove_complex_prefix_rule21);
}

char *test_remove_complex_prefix_rule21b_fully_stemmed() 
{
  return test_remove_complex_prefix("peramping", "ramping", "pe", FULLY_STEMMED, remove_complex_prefix_rule21);
}

char *test_remove_complex_prefix_rule21_not_stemmed() 
{
  return test_remove_complex_prefix("perjudikan", "perjudikan", "", NOT_STEMMED, remove_complex_prefix_rule21);
}

char *test_remove_complex_prefix_rule23_fully_stemmed() 
{
  return test_remove_complex_prefix("pertahan", "tahan", "per", FULLY_STEMMED, remove_complex_prefix_rule23);
}

char *test_remove_complex_prefix_rule23_not_stemmed() 
{
  return test_remove_complex_prefix("perdaerah", "perdaerah", "", NOT_STEMMED, remove_complex_prefix_rule23);
}

char *test_remove_complex_prefix_rule24_fully_stemmed() 
{
  return test_remove_complex_prefix("perdaerah", "daerah", "per", FULLY_STEMMED, remove_complex_prefix_rule24);
}

char *test_remove_complex_prefix_rule25_fully_stemmed_b() 
{
  return test_remove_complex_prefix("pembaruan", "baruan", "pem", PARTIALLY_STEMMED, remove_complex_prefix_rule25);
}

char *test_remove_complex_prefix_rule25_fully_stemmed_f() 
{
  return test_remove_complex_prefix("pemfokus", "fokus", "pem", FULLY_STEMMED, remove_complex_prefix_rule25);
}

char *test_remove_complex_prefix_rule25_fully_stemmed_v() 
{
  return test_remove_complex_prefix("pemvaksinan", "vaksinan", "pem", PARTIALLY_STEMMED, remove_complex_prefix_rule25);
}

char *all_tests()
{
  mu_suite_start();

  sastrawi_stemmer_new(&stemmer);

  char *path = dictionary_fullpath("data/kata-dasar.txt");
  dictionary_load(path);
  free(path);

  mu_run_test(test_remove_plain_prefix_returns_0_if_word_notin_dictionary)
  mu_run_test(test_remove_plain_prefix_di);
  mu_run_test(test_remove_plain_prefix_ke);
  mu_run_test(test_remove_plain_prefix_se);
  mu_run_test(test_remove_complex_prefix_rule1_a);
  mu_run_test(test_remove_complex_prefix_rule1_b);
  mu_run_test(test_remove_complex_prefix_rule1_a_partially_stemmed);
  mu_run_test(test_remove_complex_prefix_rule2);
  mu_run_test(test_remove_complex_prefix_rule2_excludes_er);
  mu_run_test(test_remove_complex_prefix_rule2_partially_stemmed);
  mu_run_test(test_remove_complex_prefix_rule3_only_includes_er);
  mu_run_test(test_remove_complex_prefix_rule3_only_includes_er_partially_stemmed);
  mu_run_test(test_remove_complex_prefix_rule3_only_includes_er_not_stemmed);
  mu_run_test(test_remove_complex_prefix_rule4);
  mu_run_test(test_remove_complex_prefix_rule4_partially_stemmed);
  mu_run_test(test_remove_complex_prefix_rule4_not_stemmed);
  mu_run_test(test_remove_complex_prefix_rule5);
  mu_run_test(test_remove_complex_prefix_rule5_partially_stemmed);
  mu_run_test(test_remove_complex_prefix_rule5_not_stemmed);
  mu_run_test(test_remove_complex_prefix_rule6a);
  mu_run_test(test_remove_complex_prefix_rule6a_partially_stemmed);
  mu_run_test(test_remove_complex_prefix_rule6a_not_stemmed);
  mu_run_test(test_remove_complex_prefix_rule6b);
  mu_run_test(test_remove_complex_prefix_rule6b_not_stemmed);
  mu_run_test(test_remove_complex_prefix_rule7);
  mu_run_test(test_remove_complex_prefix_rule7_partially_stemmed);
  mu_run_test(test_remove_complex_prefix_rule8);
  mu_run_test(test_remove_complex_prefix_rule8_excludes_er);
  mu_run_test(test_remove_complex_prefix_rule8_partially_stemmed);
  mu_run_test(test_remove_complex_prefix_rule9);
  mu_run_test(test_remove_complex_prefix_rule9_partially_stemmed);
  mu_run_test(test_remove_complex_prefix_rule10_l);
  mu_run_test(test_remove_complex_prefix_rule10_r);
  mu_run_test(test_remove_complex_prefix_rule10_w);
  mu_run_test(test_remove_complex_prefix_rule10_y);
  mu_run_test(test_remove_complex_prefix_rule10_partially_stemmed);
  mu_run_test(test_remove_complex_prefix_rule11_f);
  mu_run_test(test_remove_complex_prefix_rule11_b);
  mu_run_test(test_remove_complex_prefix_rule11_v);
  mu_run_test(test_remove_complex_prefix_rule11_partially_stemmed);
  mu_run_test(test_remove_complex_prefix_rule11_unstemmable);
  mu_run_test(test_remove_complex_prefix_rule12);
  mu_run_test(test_remove_complex_prefix_rule12_partially_stemmed);
  mu_run_test(test_remove_complex_prefix_rule13a);
  mu_run_test(test_remove_complex_prefix_rule13a_partially_stemmed);
  mu_run_test(test_remove_complex_prefix_rule13b);
  mu_run_test(test_remove_complex_prefix_rule14_c);
  mu_run_test(test_remove_complex_prefix_rule14_d);
  mu_run_test(test_remove_complex_prefix_rule14_j);
  mu_run_test(test_remove_complex_prefix_rule14_s);
  mu_run_test(test_remove_complex_prefix_rule14_t);
  mu_run_test(test_remove_complex_prefix_rule14_z);
  mu_run_test(test_remove_complex_prefix_rule14_partially_stemmed);
  mu_run_test(test_remove_complex_prefix_rule15a);
  mu_run_test(test_remove_complex_prefix_rule15b);
  mu_run_test(test_remove_complex_prefix_rule15_partially_stemmed);
  mu_run_test(test_remove_complex_prefix_rule16_g);
  mu_run_test(test_remove_complex_prefix_rule16_h);
  mu_run_test(test_remove_complex_prefix_rule16_q);
  mu_run_test(test_remove_complex_prefix_rule16_k);
  mu_run_test(test_remove_complex_prefix_rule16_partially_stemmed);
  mu_run_test(test_remove_complex_prefix_rule17a);
  mu_run_test(test_remove_complex_prefix_rule17b);
  mu_run_test(test_remove_complex_prefix_rule17c);
  mu_run_test(test_remove_complex_prefix_rule17d);
  mu_run_test(test_remove_complex_prefix_rule17_partially_stemmed);
  mu_run_test(test_remove_complex_prefix_rule18a);
  mu_run_test(test_remove_complex_prefix_rule18b);
  mu_run_test(test_remove_complex_prefix_rule18_partially_stemmed);
  mu_run_test(test_remove_complex_prefix_rule19_1);
  mu_run_test(test_remove_complex_prefix_rule19_2);
  mu_run_test(test_remove_complex_prefix_rule19_partially_stemmed);
  mu_run_test(test_remove_complex_prefix_rule20_1);
  mu_run_test(test_remove_complex_prefix_rule20_2);
  mu_run_test(test_remove_complex_prefix_rule20_partially_stemmed);
  mu_run_test(test_remove_complex_prefix_rule21a_partially_stemmed);
  mu_run_test(test_remove_complex_prefix_rule21b_fully_stemmed);
  mu_run_test(test_remove_complex_prefix_rule21_not_stemmed);
  mu_run_test(test_remove_complex_prefix_rule23_fully_stemmed);
  mu_run_test(test_remove_complex_prefix_rule23_not_stemmed);
  mu_run_test(test_remove_complex_prefix_rule24_fully_stemmed);
  mu_run_test(test_remove_complex_prefix_rule25_fully_stemmed_b);
  mu_run_test(test_remove_complex_prefix_rule25_fully_stemmed_f);
  mu_run_test(test_remove_complex_prefix_rule25_fully_stemmed_v);
  return NULL;
}

RUN_TESTS(all_tests);
