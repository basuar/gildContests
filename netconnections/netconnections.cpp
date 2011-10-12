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
	return ((nodeInfoBase[i] & SUBNET_ID_MASK) == i) ? i : nodeInfoBase[i] = getSubNetId((nodeInfoBase[i] & SUBNET_ID_MASK));
}

inline unsigned int strtoul_space(const char *nptr, char **endptr) {
	register unsigned int acc = 0;
	do {
		acc *= 10;
		acc += *nptr++ - '0';
	} while (*nptr != ' ');
	*endptr = (char*) nptr;
	return acc;
}
		
inline unsigned int strtoul_newline(const char *nptr, char **endptr) {
	register unsigned int acc = 0;
	do {
		acc *= 10;
		acc += *nptr++ - '0';
	} while (*nptr != '\n');
	*endptr = (char*) nptr;
	return acc;
}

int main(int z,char** v) {
	char rdBuf[BUFFER_SZ + 1], *endPtr = rdBuf;
	int fd = open(v[1], O_RDONLY);
	posix_fadvise(fd, 0, 0, POSIX_FADV_SEQUENTIAL);
	int rdBytes = read(fd, rdBuf, BUFFER_SZ);
	register char *rdPtr;
	register int y=0, n=0;
	const unsigned int nNodes = strtoul_newline(rdBuf, &rdPtr);
	unsigned int nodeInfo[nNodes + 1];
	nodeInfoBase = nodeInfo;
	__builtin_prefetch(nodeInfo);
	bzero(nodeInfo, (nNodes + 1) * sizeof(unsigned int));

	do {
		endPtr += rdBytes;
		*endPtr = 0;
		const char* const lastLF = strrchr(((rdBuf < (endPtr - 24)) ? (endPtr - 24) : rdBuf), '\n');
		while (++rdPtr < lastLF) {
			int isConnData = (*rdPtr++ == 'c');
			const register unsigned int n1 = strtoul_space(++rdPtr, &rdPtr);
			const register unsigned int n2 = strtoul_newline(++rdPtr, &rdPtr);
			if (likely(isConnData))
				if (likely(!!nodeInfo[n1] & !!nodeInfo[n2])) {
					const register unsigned int v1 = getSubNetId(n1);
					const register unsigned int v2 = getSubNetId(n2);
					if (v1 != v2) {
						nodeInfo[n2] = v1;
						nodeInfo[v2] = v1;
					}
				}
				else if (!!nodeInfo[n1] | !!nodeInfo[n2])
					if (nodeInfo[n1])
						nodeInfo[n2] = getSubNetId(n1);
					else
						nodeInfo[n1] = getSubNetId(n2);
				else {
					nodeInfo[n2] = n1;
					nodeInfo[n1] = n1 | ORIG_SUBNET_ID_FLAG;
				}
			else {
				const register bool yIncrement = ((!!nodeInfo[n1] & !!nodeInfo[n2]) && (getSubNetId(n1) == getSubNetId(n2)));
				y += yIncrement;
				n += !yIncrement;
			}
		}
		memcpy(rdBuf, rdPtr, endPtr - rdPtr);
		endPtr = rdBuf + (endPtr - rdPtr);
		rdBytes = rdPtr - rdBuf;
		rdPtr = rdBuf - 1;
	} while (rdBytes = read(fd, endPtr, rdBytes));

	write(1, rdBuf, sprintf(rdBuf, "%d,%d\n", y, n));
	_exit(0);
}
