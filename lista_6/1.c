#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MODE 0644

int main() {
    int fd, memfd;
    char  file_name[128];
    void *segm; // segment, nazwa pliku
    struct stat info; // info nt. rozmiaru pliku
    while (1) {
	printf("Podaj nazwe pliku: ");
	scanf("%s", file_name);
	fd = open(file_name, O_RDONLY);
	if (fd == -1) {
	    return 1;
	}
	memfd = open("shared_memory", O_RDWR | O_CREAT, MODE);
	if (memfd == -1) {
	    return 2;
	}
	if ((stat(file_name, &info)) == -1) {
	    return 3;
	}
	printf("Rozmiar: %lld bajtow\n", (long long)info.st_size);
	ftruncate(memfd, info.st_size);
	segm = mmap(NULL, info.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, memfd, 0);
	read(fd, segm, info.st_size);
	msync(segm, info.st_size, MS_SYNC);
	close(fd);
	close(memfd);
    }
    munmap(segm, info.st_size);
    return 0;
}
