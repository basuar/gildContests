#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>

#define BUFFER_SZ (4096 * 8)
#define ORIG_SUBNET_ID_FLAG (1 << ((sizeof(unsigned int) * 8) - 1))
#define SUBNET_ID_MASK (~ORIG_SUBNET_ID_FLAG)

#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

unsigned int *nodeInfoBase;

unsigned int getSubNetId(register unsigned int i) {
	if ((nodeInfoBase[i] & SUBNET_ID_MASK) == i)
		return i;
	else 
		return nodeInfoBase[i] = getSubNetId((nodeInfoBase[i] & SUBNET_ID_MASK));
}

inline int strtol_space(const char *nptr, char **endptr) {
	register int acc = 0;
	do {
		acc *= 10;
		acc += *nptr++ - '0';
	} while (*nptr != ' ');
	*endptr = (char*) nptr;
	return acc;
}
		
inline int strtol_newline(const char *nptr, char **endptr) {
	register int acc = 0;
	do {
		acc *= 10;
		acc += *nptr++ - '0';
	} while (*nptr != '\n');
	*endptr = (char*) nptr;
	return acc;
}

int main(int z,char** v) {
	char rdBuf[BUFFER_SZ + 1], *endPtr = rdBuf;
	int fd = open(v[1], O_RDONLY), rdBytes = read(fd, rdBuf, BUFFER_SZ);
	char *rdPtr;
	register int y=0, n=0;
	const int nNodes = strtol_newline(rdBuf, &rdPtr);
	unsigned int nodeInfo[nNodes + 1];

	bzero(nodeInfo, (nNodes + 1) * sizeof(unsigned int));
	nodeInfoBase = nodeInfo;
	__builtin_prefetch(nodeInfo);

	++rdPtr;
	do {
		endPtr += rdBytes;
		*endPtr = 0;
		const char* const lastLF = strrchr(((rdBuf < (endPtr - 24)) ? (endPtr - 24) : rdBuf), '\n');
		while (likely(rdPtr < lastLF)) {
			int isConnData = (*rdPtr++ == 'c');
			register const int n1 = strtol_space(++rdPtr, &rdPtr);
			register const int n2 = strtol_newline(++rdPtr, &rdPtr);
			++rdPtr;
			if (likely(isConnData))
				if (likely(nodeInfo[n1] && nodeInfo[n2])) {
					const unsigned int v1 = getSubNetId(n1);
					const unsigned int v2 = getSubNetId(n2);
					if (v1 != v2) {
						nodeInfo[n2] = v1;
						nodeInfo[v2] = v1;
					}
				}
				else if (nodeInfo[n1] || nodeInfo[n2])
					if (nodeInfo[n1])
						nodeInfo[n2] = getSubNetId(n1);
					else
						nodeInfo[n1] = getSubNetId(n2);
				else {
					nodeInfo[n2] = n1;
					nodeInfo[n1] = n1 | ORIG_SUBNET_ID_FLAG;
				}
			else if ((nodeInfo[n1] && nodeInfo[n2]) && (getSubNetId(n1) == getSubNetId(n2)))
				++y;
			else
				++n;
		}
		memcpy(rdBuf, rdPtr, endPtr - rdPtr);
		endPtr = rdBuf + (endPtr - rdPtr);
		rdBytes = rdPtr - rdBuf;
		rdPtr = rdBuf;
	} while (likely(rdBytes = read(fd, endPtr, rdBytes)));

	write(1, rdBuf, sprintf(rdBuf, "%d,%d\n", y, n));
	_exit(0);
}
