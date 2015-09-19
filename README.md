# cSastrawi

## Introduction

Bahasa Indonesia is one of the most spoken language in the world.
[Stemming](https://en.wikipedia.org/wiki/Stemming) is important for many fields of computer science, from text search to machine learning.
This is an attempt at porting the high quality [PHP based Bahasa Indonesian stemmer - Sastrawi](http://github.com/sastrawi/sastrawi) by [Andy Librian](https://github.com/andylibrian) to the C programming language.

## Why a port to C?

- Because it will allow for a more direct integration with PostgreSQL via its full text search dictionary support.
- We would be able to write bindings for most languages that provide ways to wrap C libraries
- Because we can :)

## Caveat emptor

- This is still super early code. Pretty much useless for anyone who actually wants something to use today. For that please look at PHP Sastrawi instead. I am putting this out here so that people who are interested/smarter then me can get involved early if they are so inclined.
- I am learning C as I go along so apologies for the crappy code and lack of proper setup.

## Run tests

1. For now just run `make` <br/>
```
		± |master ✓| → make
		gcc -O3 -Wall -g -I/usr/local/include -c tests/test_sastrawi.c  -o tests/test_sastrawi.o
		gcc -O3 -Wall -g -I/usr/local/include -c sastrawi.c  -o sastrawi.o
		gcc -O3 -Wall -g -I/usr/local/include -c regex/preg.c  -o regex/preg.o
		gcc -O3 -Wall -g -I/usr/local/include -o test_sastrawi tests/test_sastrawi.o sastrawi.o regex/preg.o -L/usr/local/lib -lpcre2-8
		test_sastrawi compiled!
```
2. A file called `test_sastrawi` will be created in the same folder. When you run it you should see something like <br>
```
		DEBUG tests/test_sastrawi.c:55: ----- RUNNING: ./test_sastrawi
		-----
		 RUNNING: ./test_sastrawi
		DEBUG tests/test_sastrawi.c:49:
		------ test_is_plural
		DEBUG tests/test_sastrawi.c:50:
		------ test_plural_parts
		ALL TESTS PASSED
		Tests run: 2
```


