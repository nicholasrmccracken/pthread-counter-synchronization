#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sharedCounter = 0;
int num_iterations;

void *thread(void *vargp)
{
    for (int i = 0; i < num_iterations; i++) {
        sharedCounter++;
    }
} 

int main(int agrc, char *argv[]) {
    if (agrc != 3) {
        printf("Usage: %s <#_iteration> <#_thread>\n", argv[0]);
        exit(1);
    }

    num_iterations = atoi(argv[1]);
    int num_threads = atoi(argv[2]);

    if (num_threads > 10) {
        printf("Maximal number of threads is 10\n");
        exit(1);
    }

    pthread_t tids[num_threads];
    
    for (int i = 0; i < num_threads; i++) {
        pthread_create(&tids[i], NULL, thread, NULL);
    }
    for (int i = 0; i < num_threads; i++) {
        pthread_join(tids[i], NULL);
    }
    
    printf("Threads: %d, Expected Iterations: %d, Actual Iterations: %d\n", 
    num_threads, num_iterations * num_threads, sharedCounter);
    exit(0); 
}
