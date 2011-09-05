#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char* wordSet[6];
int numWords[8];
char cryptResult[16];
char wordBuffer[8];
int wordBufferIdx = 0;

inline void tryToCrackPassword()
{
	int startRange, endRange;
	char buffer[9];

	// Check for 5,6,7 & 8 letter passwords.
	switch (wordBufferIdx)
	{
		case 1:
		{
			// Check with 3, 4, 5 & 6 letter words.
			startRange = 3;
			endRange = 6;
		}
		break;

		case 2:
		{
			// Check with 2, 3, 4 & 5 letter words.
			startRange = 2;
			endRange = 5;
		}
		break;

		case 3:
		{
			// Check with 1, 2, 3 & 4 letter words.
			startRange = 1;
			endRange = 4;
		}
		break;

		case 4:
		{
			// Check with 1, 2 & 3 letter words.
			startRange = 1;
			endRange = 3;
		}
		break;

		case 5:
		{
			// Check with 1 & 2 letter words.
			startRange = 1;
			endRange = 2;
		}
		break;

		case 6:
		{
			// Check with 1 letter words.
			startRange = 1;
			endRange = 1;
		}
		break;
	}

	memcpy(buffer, wordBuffer, wordBufferIdx);

	// Check with 3, 4, 5 & 6 letter words.
	for (int pairWordLen = startRange; pairWordLen <= endRange; ++pairWordLen)
	{
		buffer[wordBufferIdx + 1 + pairWordLen] = '\0';

		for (int i = numWords[pairWordLen - 1] - 1; i != -1; --i)
		{
			memcpy(&buffer[wordBufferIdx + 1], &wordSet[pairWordLen - 1][i * pairWordLen], pairWordLen);

			buffer[wordBufferIdx] = '0';
			if (!memcmp(&cryptResult[1], &crypt(buffer, cryptResult)[1], 12) ||
				((buffer[wordBufferIdx] = '2') && (!memcmp(&cryptResult[1], &crypt(buffer, cryptResult)[1], 12))) ||
				((buffer[wordBufferIdx] = '4') && (!memcmp(&cryptResult[1], &crypt(buffer, cryptResult)[1], 12))) ||
				((buffer[wordBufferIdx] = '8') && (!memcmp(&cryptResult[1], &crypt(buffer, cryptResult)[1], 12))))
			{
				printf("%s\n", buffer);
				fflush(stdout);
				_exit(1);
			}
		}
	}

	for (int pairWordLen = startRange; pairWordLen <= endRange; ++pairWordLen)
	{
		memcpy(&buffer[pairWordLen + 1], wordBuffer, wordBufferIdx);
		buffer[wordBufferIdx + 1 + pairWordLen] = '\0';

		for (int i = numWords[pairWordLen - 1] - 1; i != -1; --i)
		{
			memcpy(buffer, &wordSet[pairWordLen - 1][i * pairWordLen], pairWordLen);

			buffer[pairWordLen] = '0';
			if (!memcmp(&cryptResult[1], &crypt(buffer, cryptResult)[1], 12) ||
				((buffer[pairWordLen] = '2') && (!memcmp(&cryptResult[1], &crypt(buffer, cryptResult)[1], 12))) ||
				((buffer[pairWordLen] = '4') && (!memcmp(&cryptResult[1], &crypt(buffer, cryptResult)[1], 12))) ||
				((buffer[pairWordLen] = '8') && (!memcmp(&cryptResult[1], &crypt(buffer, cryptResult)[1], 12))))
			{
				printf("%s\n", buffer);
				fflush(stdout);
				_exit(1);
			}
		}
	}
}

int main(int argc, char** argv)
{
	for (int i = 0; i < 6; ++i)
		wordSet[i] = (char*) malloc((i+1) * 128);

	FILE* fp = fopen(argv[1], "r");
	fgets(cryptResult, sizeof(cryptResult), fp);

	register int singleChar;
	while ((singleChar = getc(fp)) != EOF)
	{
		if (singleChar <= 'Z')
			singleChar += 'a' - 'A';

		if ((singleChar >= 'a') && (singleChar <= 'z'))
		{
			if (++wordBufferIdx < 7)
				wordBuffer[wordBufferIdx - 1] = (char) singleChar;

			continue;
		}

		if (wordBufferIdx && (wordBufferIdx < 7))
		{
			int i = numWords[wordBufferIdx - 1] - 1;
			for (; i != -1; --i)
				if (!memcmp(&wordSet[wordBufferIdx - 1][i * wordBufferIdx], wordBuffer, wordBufferIdx))
					break;
			if (i == -1)
			{
				tryToCrackPassword();
				memcpy(&wordSet[wordBufferIdx - 1][numWords[wordBufferIdx - 1]++ * wordBufferIdx], wordBuffer, wordBufferIdx);
			}
		}

		wordBufferIdx = 0;
	}

	if (wordBufferIdx && (wordBufferIdx < 7))
	{
		int i = numWords[wordBufferIdx - 1] - 1;
		for (; i != -1; --i)
			if (!memcmp(&wordSet[wordBufferIdx - 1][i * wordBufferIdx], wordBuffer, wordBufferIdx))
				break;
		if (i == -1)
		{
			tryToCrackPassword();
			memcpy(&wordSet[wordBufferIdx - 1][numWords[wordBufferIdx - 1]++ * wordBufferIdx], wordBuffer, wordBufferIdx);
		}
	}

	return 0;
}
