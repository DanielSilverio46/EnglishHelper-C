#ifndef WORD_H
#define WORD_H
#define dll __declspec(dllexport)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

dll extern void createWordFile(void);

dll extern bool loadWordFile(void);
dll extern void closeWordFile(void);

dll extern int getAllWords(char *restrict, size_t length);
dll extern void getRandomTuple(char *store, unsigned int lengthStore);

dll extern int totalTuples(void);

dll extern void updateWordFile(const char *Words, size_t Total_Letters);

typedef struct tuple
{
    char tuple[0xff];
	char buff[0xff];

	char *str1;
	char *str2;

	char sep;
	unsigned int isep;
} Tuple;

dll extern void InitTuple(Tuple **restrict tuple);
dll extern void FreeTuple(Tuple *tuple);

dll extern inline char *Str1(Tuple *tuple);
dll extern inline char *Str2(Tuple *tuple);

dll extern void SplitTuple(Tuple *tuple);
#endif