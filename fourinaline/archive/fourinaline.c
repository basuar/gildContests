#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define likely(x) __builtin_expect((x), 1)
#define unlikely(x) __builtin_expect((x), 0)
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define BUFFER_SZ (4096 * 1)
 
static const char * const resultString[] = { 0, "1\n", "2\n", "draw\n", "play\n" };
int main(int z, char **v)
{
	char rdBuf[BUFFER_SZ + 1], returnCode = 3;
	int fd = open(v[1], O_RDONLY);
	posix_fadvise(fd, 0, 0, POSIX_FADV_NOREUSE);
	struct stat fstatData; fstat(fd, &fstatData);
	unsigned int numReadCycles = fstatData.st_size / BUFFER_SZ;
	register off_t readOffset = fstatData.st_size;
	unsigned int rdBytes = pread(fd, rdBuf, min(BUFFER_SZ, readOffset), readOffset - min(BUFFER_SZ, readOffset)); readOffset -= min(BUFFER_SZ, readOffset);
	register char *rdPtr = strchr(rdBuf, '\n');
	register unsigned int cols = (strchr(rdPtr + 1, '\n') - rdPtr) / 2;
	register unsigned int currentRowIdx = 1;
	unsigned char ew[cols + 1], sn[cols + 1], swne[cols + 1], senw[2][cols + 1];
	register unsigned char *_ew, *_sn, *_senw, *_swne; swne[0]= 0;
	
	// Read upto BUFFER_SZ bytes in cycles
	do {
		rdPtr = rdBuf + rdBytes;
		while (rdPtr > rdBuf) {
			currentRowIdx = !currentRowIdx;
			_ew = &ew[cols]; _sn = &sn[cols]; _swne = &swne[cols]; _senw = &senw[currentRowIdx][cols];
			*_ew = *_sn = *_swne = *_senw = (*rdPtr - '0');
			for (register int i = cols - 1; i; --i) {
				--_ew; --_sn; --_swne; --_senw; rdPtr -= 2;
				const register unsigned char value = *rdPtr - '0';
				if (value) {
					*_ew = ((*(_ew + 1)) << 2) | value;
					*_sn = (*_sn << 2) | value;
					*_swne = (*(_swne - 1) << 2) | value;
					*_senw = (senw[!currentRowIdx][i + 1] << 2) | value;
					if ((*_ew == 0x55) | (*_ew == 0xaa) | (*_sn == 0x55) | (*_sn == 0xaa) | (*_swne == 0x55) | (*_swne == 0xaa) | (*_senw == 0x55) | (*_senw == 0xaa)) { write(1, resultString[value], 2); _exit(0); }
				} else { *_ew = *_sn = *_swne = *_senw = 0; returnCode =  4; }
			}
			rdPtr -= 2;
		}
		readOffset -= min(BUFFER_SZ, readOffset);
		rdBytes = pread(fd, rdBuf, min(BUFFER_SZ, readOffset), readOffset);
	} while (numReadCycles--);
	write(1, resultString[returnCode], 5); _exit(0);
}
