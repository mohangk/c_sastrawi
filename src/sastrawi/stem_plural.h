#ifndef SASTRAWI_STEM_PLURAL_H_INCLUDED
#define SASTRAWI_STEM_PLURAL_H_INCLUDED
//Sastrawi\Stemmer::isPlural
int is_plural(char *word);

int plural_parts(char *word, char **parts[]);

//Sastrawi\Stemmer::stemPluralWord
int stem_plural_word(char *word, char **stemmed_word);
#endif
