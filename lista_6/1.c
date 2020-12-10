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
	fd = open(file_name, O_RDONLY); // otworzenie pliku
	if (fd == -1) {
	    return 1;
	}
	memfd = open("shared_memory", O_RDWR | O_CREAT, MODE);	// otworzenie pliku "pamieci", na ktory zostanie
	if (memfd == -1) {					// przeslana tresc pliku otwartego wczesniej
	    return 2;
	}
	if ((stat(file_name, &info)) == -1) {			// pobranie danych pliku (size itp...)
	    return 3;
	}
	printf("Rozmiar: %lld bajtow\n", (long long)info.st_size);
	ftruncate(memfd, info.st_size);				// obciecie / wyczysczenie pliku "pamieci" 
	segm = mmap(NULL, info.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, memfd, 0); // zmapowanie obszaru do pamieci
	read(fd, segm, info.st_size);		// wypelnienie "pamieci" danymi z pliku
	msync(segm, info.st_size, MS_SYNC);	// synchronizacja segmentu pamieci
	close(fd);
	close(memfd);
    }
    munmap(segm, info.st_size);			// zwolnienie wczesniejszego obszaru
    return 0;
}
