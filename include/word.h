#ifndef WORD_H
#define WORD_H

#define dll __declspec(dllexport)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef struct tuple
{
    char tuple[0xff];
	char buff[0xff];

	char *str1;
	char *str2;

	char sep;
	unsigned int isep;
} Tuple;

// Tuple Manipulation

#define GetTuple(Tuple) (Tuple->tuple)

#define GetStr1(Tuple) (Tuple->str1)
#define GetStr2(Tuple) (Tuple->str2)

#define GetTupleSeparator(Tuple) (Tuple->sep)

#define SetTupleSeparator(Tuple, Char) (Tuple->sep = Char)

dll extern void InitTuple(Tuple **restrict tuple);
dll extern void FreeTuple(Tuple *tuple);

dll extern void SplitTuple(Tuple *tuple);

// Words Manipulation

dll extern void createWordFile(void);

dll extern bool loadWordFile(void);
dll extern void closeWordFile(void);

dll extern int getAllWords(char *string, size_t length);
dll extern void getRandomTuple(char *store, unsigned int lengthStore);

dll extern int totalTuples(void);

dll extern void updateWordFile(const char *Words, size_t Total_Letters);

#endif