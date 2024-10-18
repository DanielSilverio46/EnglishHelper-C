#ifndef WORD_H
#define WORD_H

#include <stdbool.h>

extern char **words;

__declspec(dllexport) extern bool loadWordFile(void);
__declspec(dllexport) extern void closeWordFile(void);

__declspec(dllexport) extern char *getSpecificWord(unsigned int index);
__declspec(dllexport) extern void randomWord(char *store);
__declspec(dllexport) extern void divideTuple(char *__restrict__ tuple, char **__restrict__ pEnglish, char **__restrict__ pPortuguese);

__declspec(dllexport) extern char *FileContent(void);
__declspec(dllexport) extern unsigned int totalTuples(void);

__declspec(dllexport) extern void updateWordFile(const char *Words);

#endif