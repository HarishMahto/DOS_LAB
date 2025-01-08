#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_COUNT 10

sem_t sem_countdown; // Semaphore for countdown thread
sem_t sem_countup;   // Semaphore for countup thread

void* countdown(void* arg) {
    for (int i = MAX_COUNT; i > 0; i--) {
        sem_wait(&sem_countdown); // Wait for countdown semaphore
        printf("Countdown: %d\n", i);
        sem_post(&sem_countup);    // Signal countup semaphore
    }
    return NULL;
}

void* countup(void* arg) {
    for (int i = 1; i <= MAX_COUNT; i++) {
        sem_wait(&sem_countup); // Wait for countup semaphore
        printf("Countup: %d\n", i);
        sem_post(&sem_countdown); // Signal countdown semaphore
    }
    return NULL;
}

int main() {
    pthread_t thread_countdown, thread_countup;

    // Initialize semaphores
    sem_init(&sem_countdown, 0, 1); // Start with countdown semaphore available
    sem_init(&sem_countup, 0, 0);   // Countup semaphore is not available initially

    // Create threads
    pthread_create(&thread_countdown, NULL, countdown, NULL);
    pthread_create(&thread_countup, NULL, countup, NULL);

    // Wait for threads to finish
    pthread_join(thread_countdown, NULL);
    pthread_join(thread_countup, NULL);

    // Clean up
    sem_destroy(&sem_countdown);
    sem_destroy(&sem_countup);

    return 0;
}
