#ifndef WORD_H
#define WORD_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

__declspec(dllexport) extern void createWordFile(void);

__declspec(dllexport) extern bool loadWordFile(void);
__declspec(dllexport) extern void closeWordFile(void);

__declspec(dllexport) int getAllWords(char *restrict, size_t length);
__declspec(dllexport) extern void getRandomTuple(char *store, unsigned int lengthStore);

__declspec(dllexport) void splitTuple(char *restrict tuple, char **lang1, char **lang2);
__declspec(dllexport) extern int totalTuples(void);

__declspec(dllexport) extern void updateWordFile(const char *Words, size_t Total_Letters);

typedef struct tuple
{
    char tuple[0xff];

	char *str1;
	char *str2;

	char sep;
	unsigned int isep;
} Tuple;

__declspec(dllexport) void InitTuple(Tuple *tuple);

__declspec(dllexport) inline void SetStrs(Tuple *tuple, char *str1, char *str2);

__declspec(dllexport) inline void SetSep(Tuple *tuple, char sep);

__declspec(dllexport) inline void SetIsep(Tuple *tuple, unsigned int i);

__declspec(dllexport) void FreeTuple(Tuple *tuple);
#endif