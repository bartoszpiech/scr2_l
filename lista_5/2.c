#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 10

int main(int argc, char **argv) {
    if (argc < 2) { // error
	return 1;
    }
    //printf("%s\n", argv[1]);
    int fd_tab[2];
    if (pipe(fd_tab) == -1) { // error
	return 2;
    }
    int pid = fork();
    if (pid < 0) { // error
	return 3;
    } else if (pid > 0) { // parent
	char buf[BUFSIZE];
	int fd_plik = open(argv[1], O_RDONLY);
	close(fd_tab[0]); // close reading from pipe
	while (read(fd_plik, buf, BUFSIZE) > 0) {
	    write(fd_tab[1], buf, BUFSIZE);
	}
	//sleep(10); // proces potomny zaczyna wyswietlac img dopiero po zamknieciu potoku przez proces nadrzedny
	close(fd_tab[1]);
	return 0;
    } else { // child
	close(fd_tab[1]);
	close(0); // zamkniecie standard input
	dup2(fd_tab[0], 0); // zduplikowanie deskryptora potoku jako standard input
	execlp("/usr/bin/display", "display", NULL);
	close(fd_tab[0]);
	exit(0);
    }
}
