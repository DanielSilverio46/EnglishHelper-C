#include "word.h"
#include <windows.h>

#include <stdio.h>

/* Tuple Manipulation */

dll void InitTuple(Tuple **restrict tuple)
{
	(*tuple) = malloc(sizeof(Tuple));

	(*tuple)->str1 = NULL;
	(*tuple)-> str2 = NULL;

	(*tuple)->sep = ':';
	(*tuple)->isep = 0x00;
}

dll void FreeTuple(Tuple *tuple)
{
	free(tuple);
}

dll void SplitTuple(Tuple *tuple)
{
	strcpy(tuple->buff, tuple->tuple);

	size_t buff_len = strlen(tuple->buff);
	unsigned int i = 0x00;

	while(i != buff_len)
	{
		if (tuple->buff[i] == tuple->sep){
			tuple->isep = i;
			tuple->buff[i] = '\0';
		}
		if (tuple->buff[i] == '\n') tuple->buff[i] = '\0';
		i++;
	}

	tuple->str1 = tuple->buff;
	tuple->str2 = tuple->buff + tuple->isep + 0x01;
}

/* File Manipulation */

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

	if (wordFile != NULL) closeWordFile();

	wordFile = fopen("words.txt", "w");
	fwrite(Words, sizeof(char), Total_Letters, wordFile);
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