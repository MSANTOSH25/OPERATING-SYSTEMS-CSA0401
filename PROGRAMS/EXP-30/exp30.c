/*
 * Experiment 30: Demonstrate thread related concepts:
 * (i) create (ii) join (iii) equal (iv) exit
 */
#include <stdio.h>
#include <pthread.h>

void *threadFunction(void *arg) {
    int id = *((int *)arg);
    printf("Thread %d started. Thread ID (self): %lu\n", id, (unsigned long)pthread_self());

    if (id == 1) {
        printf("Thread %d exiting via pthread_exit().\n", id);
        pthread_exit(NULL);
    }

    printf("Thread %d finishing normally.\n", id);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;

    // (i) create
    pthread_create(&t1, NULL, threadFunction, &id1);
    pthread_create(&t2, NULL, threadFunction, &id2);

    // (iii) equal
    if (pthread_equal(t1, t2))
        printf("Thread 1 and Thread 2 are the same thread.\n");
    else
        printf("Thread 1 and Thread 2 are different threads.\n");

    // (ii) join
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Both threads have completed.\n");

    // (iv) exit - main thread exits, letting other threads (already joined) finish
    pthread_exit(NULL);
}
