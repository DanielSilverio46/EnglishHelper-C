#include "headers\word.h"

FILE *wordFile = NULL;

__declspec(dllexport) void InitTuple(Tuple *tuple)
{
	tuple = malloc(sizeof(Tuple));

	tuple->str1 = NULL;
	tuple-> str2 = NULL;

	tuple->sep = ':';
	tuple->isep = 0x00;
}

__declspec(dllexport) inline void SetStrs(Tuple *tuple, char *str1, char *str2)
{
	tuple->str1 = str1;
	tuple->str2 = str2;
}

__declspec(dllexport) inline void SetSep(Tuple *tuple, char sep)
{
	tuple->sep = sep;
}

__declspec(dllexport) inline void SetIsep(Tuple *tuple, unsigned int i)
{
	tuple->isep = i;
}

__declspec(dllexport) void FreeTuple(Tuple *tuple)
{
	tuple->str1 = NULL;
	tuple->str2 = NULL;
	tuple->sep = '\0';
	tuple->isep = 0x00;

	free(tuple);
}


__declspec(dllexport) void createWordFile(void)
{
	wordFile = fopen("words.txt", "w");

	if (wordFile != NULL) {
		fwrite("gato:cat", sizeof(char), 8, wordFile);
		closeWordFile();

		loadWordFile();
	}
}

__declspec(dllexport) bool loadWordFile(void)
{
	wordFile = fopen("words.txt", "r");

	if (wordFile == NULL) return false;
	else return true;
}

__declspec(dllexport) void closeWordFile(void)
{
	if (wordFile != NULL) fclose(wordFile);
}

__declspec(dllexport) void updateWordFile(const char *Words, size_t Total_Letters)
{
	if (Words == NULL) return;

	if (wordFile != NULL) closeWordFile();

	wordFile = fopen("words.txt", "w");
	fwrite(Words, sizeof(char), Total_Letters, wordFile);
	fclose(wordFile);

	loadWordFile();
}

__declspec(dllexport) int totalTuples(void)
{
	if (wordFile == NULL) return -0x01;
	
	int i = 0x00;
	char buff[0xff];

	for (; fgets(buff, sizeof(buff), wordFile) != NULL; ++i);

	fseek(wordFile, 0x00, SEEK_SET);

	return i;
}

__declspec(dllexport) void getRandomTuple(char *store, unsigned int lengthStore)
{
	if (wordFile == NULL) return;
	
	srand(time(NULL));

	int randWord = 0x00;
	int t = totalTuples();
	
	if (t == -0x01) return;
	
	while (randWord == 0x00) randWord = rand() % (t + 0x01);

	for (int i=0x00; i != randWord; ++i) fgets(store, lengthStore, wordFile);

	fseek(wordFile, 0x00, SEEK_SET);
}

__declspec(dllexport) void splitTuple(char *restrict tuple, char **lang1, char **lang2)
{
	unsigned int i = 0x00;

	*lang1 = tuple;

	while(tuple[i] != ':') ++i;
	tuple[i] = '\0';

	*lang2 = tuple + i + 0x01;
}

__declspec(dllexport) int getAllWords(char *string, size_t length)
{
	if (wordFile == NULL) return -1;

	int c, i = 0x00;

	while((c = fgetc(wordFile)) != EOF)
	{
		if (i > length - 1) break;

		string[i] = (char)c;
		i++;
	}

	string[i] = '\0';

	fseek(wordFile, 0x00, SEEK_SET);

	return 0x01;
}