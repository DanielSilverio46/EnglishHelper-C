#ifndef WORD_H
#define WORD_H
#include <stdio.h>

extern FILE *wordFile;

void loadWordFile(void);

void closeWordFile(void);

int totalTuples(void);

void randomWord(char *store, size_t lengthStore);

void divideTuple(char *tuple, char **english, char **portuguese);

#endif