#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <ucontext.h>

int i = 0;
int j = 0;

void sig_handler(int sig, siginfo_t *si, ucontext_t *con) {
	if (sig == 14) { // SIGALRM
		printf("Odebrany SIGALRM");
		exit(14);
	} else if (sig == 15) { // SIGTERM
		printf("Odebrany SIGTERM");
	} else if (sig == 10) { // SIGUSR1
		sigignore(SIGALRM);
		j = 1;
	}
	/*
	else if (sig == 12) { // SIGUSR2
	}
	*/
}

int main() {
	struct timespec tv;
	tv.tv_sec = (time_t) 1;
	tv.tv_nsec = 100 * 1000000L;

	sigset_t signal_set;
	sigemptyset(&signal_set);
	sigaddset(&signal_set, SIGALRM);
	sigaddset(&signal_set, SIGTERM);
	sigaddset(&signal_set, SIGUSR1);
	sigaddset(&signal_set, SIGUSR2);

	sigprocmask(SIG_UNBLOCK, &signal_set, NULL);

	struct sigaction act;
	act.sa_handler = sig_handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGALRM, &act, 0);
	sigaction(SIGTERM, &act, 0);
	sigaction(SIGUSR1, &act, 0);
	sigignore(SIGUSR2); // ignoruje SIGUSR2

	printf("%d\n", getpid());
	while(1) {
		i++;
		nanosleep(&tv, (struct timespec*) NULL);
		if (j == 1) {
			sigignore(SIGALRM);
			for (int k = 0; k < 10; k++) {
				printf("%d\n", k); // debug
				i++;
				nanosleep(&tv, (struct timespec*) NULL);
			}
			sigaction(SIGALRM, &act, 0);
			j = 0;
		}
	}
	return 0;
}

