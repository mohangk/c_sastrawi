#ifndef SASTRAWI_STEM_PLURAL_H_INCLUDED
#define SASTRAWI_STEM_PLURAL_H_INCLUDED
//Sastrawi\Stemmer::isPlural
int is_plural(sastrawi_stemmer *stemmer, char *word);

int plural_parts(sastrawi_stemmer *stemmer, char *word, char **parts[]);

//Sastrawi\Stemmer::stemPluralWord
int stem_plural_word(sastrawi_stemmer *stemmer, char *word, char **stemmed_word);
#endif
