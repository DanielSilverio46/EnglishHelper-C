#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FILE *wordFile;

__declspec(dllexport) int totalTuples(void)
{
	int i = 0;
	char trash[255];

	for (; fgets(trash, sizeof(trash), wordFile) != NULL; ++i);

	fseek(wordFile, 0, SEEK_SET);

	return i;
}

__declspec(dllexport) void loadWordFile(void)
{
	wordFile = fopen("words.txt", "r");
}

__declspec(dllexport) void closeWordFile(void)
{
	fclose(wordFile);
}

__declspec(dllexport) void randomWord(char *store, size_t lengthStore)
{
	int randWord = 0;
	do {
		srand(time(NULL));
		randWord = rand() % (totalTuples() + 1);
	} while (randWord == 0);

	for (int i=0; i != randWord; ++i)
		fgets(store, lengthStore, wordFile);

	fseek(wordFile, 0, SEEK_SET);
}

__declspec(dllexport) void divideTuple(char *tuple, char **english, char **portuguese)
{
	int i = 0;

	*english = tuple;

	while(tuple[i] != ':') ++i;
	tuple[i] = '\0';

	*portuguese = &tuple[i+1];

}