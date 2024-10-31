#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FILE *wordFile;

__declspec(dllexport) void loadWordFile(void)
{
	wordFile = fopen("./words.txt", "r");

	if (wordFile == NULL)
	{
		char _word[] = "cat:gato\n";
	
		wordFile = fopen("./words.txt", "a");
		fwrite(_word, sizeof(char), sizeof(_word) / sizeof(char), wordFile);
		fseek(wordFile, 0, SEEK_SET);
	}
}

__declspec(dllexport) void closeWordFile(void)
{
	if (wordFile != NULL) fclose(wordFile);
}

__declspec(dllexport) void updateWordFile(const char *Words, size_t Total_Letters)
{
	if (Words == NULL && wordFile == NULL) return;

	fwrite(Words, sizeof(char), Total_Letters, wordFile);
}
__declspec(dllexport) int totalTuples(void)
{
	if (wordFile == NULL) return -1;
	
	int i = 0;
	char buff[255];

	for (; fgets(buff, sizeof(buff), wordFile) != NULL; ++i);

	fseek(wordFile, 0, SEEK_SET);

	return i;
}

__declspec(dllexport) void randomWord(char *store, unsigned int lengthStore)
{
	if (wordFile == NULL) return;

	int randWord = 0x00;

	do {
		srand(time(NULL));
		int t = totalTuples();
		if (t == -1) return;

		randWord = rand() % (t + 0x01);
	} while (randWord == 0);

	for (int i=0x00; i != randWord; ++i) fgets(store, lengthStore, wordFile);

	fseek(wordFile, 0x00, SEEK_SET);
}

__declspec(dllexport) void splitTuple(char *tuple, char **english, char **portuguese)
{
	int i = 0;

	*english = tuple;

	while(tuple[i]!=':') ++i;
	tuple[i] = '\0';

	*portuguese = &tuple[i+1];
}