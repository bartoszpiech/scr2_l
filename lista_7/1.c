#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void*
function(void* id) {
    int tid = (int) id;
    //sleep(1);
    printf("Hello SCR. Written by thread ID: %d\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[5];
    int iret[5];
    for (int i = 0; i < 5; i++) {
	printf("%d\n", i);
	iret[i] = pthread_create(&threads[i], NULL, function, (void *)i);
	//sleep(1);
    }
    pthread_exit(NULL);
    return 0;
}
