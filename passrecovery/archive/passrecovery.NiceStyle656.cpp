#include <stdio.h>
#include <string.h>
#include <unistd.h>

char wordBuffer[8];
int wordBufferIdx;
char cryptResult[16];
char wordSet[2048];
int numWords;
const int range[6][2] = {{3,6}, {2,5}, {1,4}, {1,3}, {1,2}, {1,1}};

inline void tryToCrackPassword()
{
	register const int startRange = range[wordBufferIdx - 1][0];
	register const int endRange = range[wordBufferIdx - 1][1];
	register char* wordPtr = wordSet;
	register int currWordNum = 0;
	char buffer[9];

	// Check for 5,6,7 & 8 letter passwords.
	while (currWordNum < numWords)
	{
		register const int pairWordLen = *wordPtr;
		if ((pairWordLen >= startRange) && (pairWordLen <= endRange))
		{
			memcpy(buffer, wordBuffer, wordBufferIdx);
			memcpy(&buffer[wordBufferIdx + 1], (wordPtr + 1), pairWordLen);
			buffer[wordBufferIdx + 1 + pairWordLen] = '\0';
			if (((buffer[wordBufferIdx] = '0'), (!memcmp(cryptResult, crypt(buffer, cryptResult), 13))) ||
				((buffer[wordBufferIdx] = '2'), (!memcmp(cryptResult, crypt(buffer, cryptResult), 13))) ||
				((buffer[wordBufferIdx] = '4'), (!memcmp(cryptResult, crypt(buffer, cryptResult), 13))) ||
				((buffer[wordBufferIdx] = '8'), (!memcmp(cryptResult, crypt(buffer, cryptResult), 13))))
			{
				printf("%s\n", buffer);
				fflush(stdout);
				_exit(1);
			}
			memcpy(buffer, (wordPtr + 1), pairWordLen);
			memcpy(&buffer[pairWordLen + 1], wordBuffer, wordBufferIdx);
			if (((buffer[pairWordLen] = '0'), (!memcmp(cryptResult, crypt(buffer, cryptResult), 13))) ||
				((buffer[pairWordLen] = '2'), (!memcmp(cryptResult, crypt(buffer, cryptResult), 13))) ||
				((buffer[pairWordLen] = '4'), (!memcmp(cryptResult, crypt(buffer, cryptResult), 13))) ||
				((buffer[pairWordLen] = '8'), (!memcmp(cryptResult, crypt(buffer, cryptResult), 13))))
			{
				printf("%s\n", buffer);
				fflush(stdout);
				_exit(1);
			}
		}
		++currWordNum;
		wordPtr += (pairWordLen + 1);
	}
}

inline void processWord()
{
	if (wordBufferIdx && (wordBufferIdx < 7))
	{
		register char* wordPtr = wordSet;
		register int currWordNum = 0;
		while (currWordNum < numWords)
		{
			if ((*wordPtr == wordBufferIdx) && (!memcmp((wordPtr+1), wordBuffer, wordBufferIdx)))
				break;
			wordPtr += (*wordPtr + 1);
			++currWordNum;
		}
		if (currWordNum == numWords)
		{
			tryToCrackPassword();
			*wordPtr = (char) wordBufferIdx;
			memcpy(++wordPtr, wordBuffer, wordBufferIdx);
			++numWords;
		}
	}
}

int main(int argc, char** argv)
{
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
		processWord();
		wordBufferIdx = 0;
	}
	processWord();
	return 0;
}
