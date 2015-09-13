# cSastrawi

## Introduction

Bahasa Indonesia is one of the most spoken language in the world.
[Stemming](https://en.wikipedia.org/wiki/Stemming) is important for many fields of computer science, from text search to machine learning.
This is an attempt at porting the high quality [PHP based Bahasa Indonesian stemmer - Sastrawi](http://github.com/sastrawi/sastrawi) by [Andy Librian](https://github.com/andylibrian) to the C programming language.

## Why a port to C?

- Because it will allow for a more direct integration with PostgreSQL via its full text search dictionary support.
- We would be able to write bindings for most languages that provide ways to wrap C libraries
- Because we can :)
