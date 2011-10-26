#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>

#define BUFFER_SZ (4096 * 64)
#define ORIG_SUBNET_ID_FLAG (1 << ((sizeof(unsigned int) * 8) - 1))
#define SUBNET_ID_MASK (~ORIG_SUBNET_ID_FLAG)

#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

unsigned int *nodeInfoBase;

unsigned int getSubNetId(register unsigned int i) {
	return ((nodeInfoBase[i] & SUBNET_ID_MASK) != i) ? (nodeInfoBase[i] = getSubNetId((nodeInfoBase[i] & SUBNET_ID_MASK))) : i;
}

inline unsigned int strtoul_space(const char *&nptr) {
	register unsigned int acc = 0;
	do {
		acc *= 10;
		acc += *nptr++ - '0';
	} while (*nptr != ' ');
	return acc;
}
		
inline unsigned int strtoul_newline(const char *&nptr) {
	register unsigned int acc = 0;
	do {
		acc *= 10;
		acc += *nptr++ - '0';
	} while (*nptr != '\n');
	return acc;
}

int main(int z, char** v) {
	char rdBuf[BUFFER_SZ + 1] __attribute__ ((aligned (__BIGGEST_ALIGNMENT__))), *endPtr = rdBuf;
	int fd = open(v[1], O_RDONLY);
	posix_fadvise(fd, 0, 0, POSIX_FADV_SEQUENTIAL);
	register const char *rdPtr = rdBuf;
	int rdBytes = read(fd, rdBuf, BUFFER_SZ);
	register unsigned int y = 0, n = 0;
	const int nNodes = strtoul_newline(rdPtr);
	unsigned int nodeInfo[nNodes + 1] __attribute__ ((aligned (__BIGGEST_ALIGNMENT__)));

	nodeInfoBase = nodeInfo;
	{
		register unsigned int *tmpPtr = nodeInfo;
		for (int i = nNodes; i; --i)
			__builtin_prefetch(++tmpPtr, 1, 3);
	}
	bzero(nodeInfo, (nNodes + 1) * sizeof(unsigned int));

	do {
		endPtr += rdBytes;
		*endPtr = 0;
		const char* const lastLF = strrchr(endPtr - 16, '\n');
		while (++rdPtr < lastLF) {
			int isConnData = (*rdPtr++ == 'c');
			register const unsigned int n1 = strtoul_space(++rdPtr);
			register const unsigned int n2 = strtoul_newline(++rdPtr);
			if (likely(isConnData))
				if (likely(nodeInfo[n1] && nodeInfo[n2])) {
					const unsigned int v1 = getSubNetId(n1);
					const unsigned int v2 = getSubNetId(n2);
					if (v1 != v2) {
						nodeInfo[n2] = v1;
						nodeInfo[v2] = v1; } }
				else if (likely(nodeInfo[n1] | nodeInfo[n2]))
					if (nodeInfo[n1])
						nodeInfo[n2] = getSubNetId(n1);
					else
						nodeInfo[n1] = getSubNetId(n2);
				else {
					nodeInfo[n2] = n1;
					nodeInfo[n1] = n1 | ORIG_SUBNET_ID_FLAG; }
			else if (unlikely(nodeInfo[n1] && (getSubNetId(n1) == getSubNetId(n2))))
				++y;
			else
				++n; }
		memcpy(rdBuf, rdPtr, endPtr - rdPtr);
		endPtr = rdBuf + (endPtr - rdPtr);
		rdBytes = rdPtr - rdBuf;
		rdPtr = rdBuf - 1;
	} while (rdBytes = read(fd, endPtr, rdBytes));

	write(1, rdBuf, sprintf(rdBuf, "%d,%d\n", y, n));
	_exit(0);
}