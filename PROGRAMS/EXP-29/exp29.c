/*
 * Experiment 29: Simulate the solution of the Classical Process
 * Synchronization (Bounded Buffer) Problem using semaphores and mutex.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define TOTAL_ITEMS 8

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty_slots, full_slots;
pthread_mutex_t mutex;

void *producer(void *arg) {
    for (int i = 1; i <= TOTAL_ITEMS; i++) {
        sem_wait(&empty_slots);
        pthread_mutex_lock(&mutex);

        buffer[in] = i * 10;
        printf("Producer produced item: %d at slot %d\n", buffer[in], in);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full_slots);
        usleep(300000);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 1; i <= TOTAL_ITEMS; i++) {
        sem_wait(&full_slots);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        printf("Consumer consumed item: %d from slot %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty_slots);
        usleep(500000);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty_slots, 0, BUFFER_SIZE);
    sem_init(&full_slots, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);
    pthread_mutex_destroy(&mutex);

    return 0;
}
