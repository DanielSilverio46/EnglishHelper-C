#include <windows.h>
#include "word.h"

#pragma region Tuple Manipulation

dll void InitTuple(Tuple **restrict tuple)
{
	(*tuple) = malloc(sizeof(Tuple));

	SetStr1((*tuple), NULL);
	SetStr2((*tuple), NULL);

	SetTupleSeparator((*tuple), ':');

	SetIndexSeparator((*tuple), 0x00);
}

dll void SplitTuple(Tuple *tuple)
{
	strcpy(tuple->buff, tuple->tuple);

	size_t buff_len = strlen(tuple->buff);
	unsigned int i = 0x00;

	for(unsigned int i; i != buff_len; ++i)
	{
		if (tuple->buff[i] == tuple->sep){
			SetIndexSeparator(tuple, i);
			tuple->buff[i] = '\0';
		}

		if (tuple->buff[i] == '\n') tuple->buff[i] = '\0';
	}

	SetStr1(tuple, tuple->buff);
	SetStr2(tuple, tuple->buff + tuple->isep + 0x01);
}

dll inline void SetStr1(Tuple *tuple, char *string)
{
	tuple->str1 = string;
}

dll inline void SetStr2(Tuple *tuple, char *string)
{
	tuple->str2 = string;
}

#pragma endregion

#pragma region Word Manipulation

FILE *wordFile = NULL;

dll void createWordFile(void)
{
	wordFile = fopen("words.txt", "w");

	if (wordFile != NULL) {
		fwrite("gato:cat", sizeof(char), 8, wordFile);
		closeWordFile();

		loadWordFile();
	}
}

dll bool loadWordFile(void)
{
	wordFile = fopen("words.txt", "r");

	if (wordFile == NULL) return false;
	else return true;
}

dll void closeWordFile(void)
{
	if (wordFile != NULL) fclose(wordFile);
}

dll void updateWordFile(const char *Words, size_t Total_Letters)
{
	if (Words == NULL) return;

	closeWordFile();

	wordFile = fopen("words.txt", "w");

	fprintf(wordFile, "%s", Words);
	fclose(wordFile);

	loadWordFile();
}

dll int totalTuples(void)
{
	if (wordFile == NULL) return -0x01;
	
	int i = 0x00;
	char buff[0xff];

	for (; fgets(buff, sizeof(buff), wordFile) != NULL; ++i);

	fseek(wordFile, 0x00, SEEK_SET);

	return i;
}

dll void getRandomTuple(char *store, unsigned int lengthStore)
{
	if (wordFile == NULL) return;
	
	srand(time(NULL));

	int randWord = 0x00;
	int t = totalTuples();
	
	if (t == -0x01) return;
	
	do { randWord = rand() % (t + 0x01); } while (randWord == 0x00);
	for (int i=0x00; i != randWord; ++i) fgets(store, lengthStore, wordFile);

	size_t store_len = strlen(store);

	fseek(wordFile, 0x00, SEEK_SET);
}

dll int getAllWords(char *string, size_t length)
{
	if (wordFile == NULL) return -0x01;

	int c, i = 0x00;

	while((c = fgetc(wordFile)) != EOF)
	{
		if (i > length - 0x01) break;

		string[i] = (char)c;
		i++;
	}

	string[i] = '\0';

	fseek(wordFile, 0x00, SEEK_SET);

	return 0x01;
}

#pragma endregion