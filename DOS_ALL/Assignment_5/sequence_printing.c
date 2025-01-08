#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_COUNT 20

sem_t semA, semB, semC;

void* printA(void* arg) {
    for (int i = 1; i <= MAX_COUNT; i += 3) {
        sem_wait(&semA);
        printf("A%d\n", i);
        sem_post(&semB);
    }
    return NULL;
}

void* printB(void* arg) {
    for (int i = 2; i <= MAX_COUNT; i += 3) {
        sem_wait(&semB);
        printf("B%d\n", i);
        sem_post(&semC);
    }
    return NULL;
}

void* printC(void* arg) {
    for (int i = 3; i <= MAX_COUNT; i += 3) {
        sem_wait(&semC);
        printf("C%d\n", i);
        sem_post(&semA);
    }
    return NULL;
}

int main() {
    pthread_t threadA, threadB, threadC;

    // Initialize semaphores
    sem_init(&semA, 0, 1); // Start with A's turn
    sem_init(&semB, 0, 0); // B waits
    sem_init(&semC, 0, 0); // C waits

    // Create threads
    pthread_create(&threadA, NULL, printA, NULL);
    pthread_create(&threadB, NULL, printB, NULL);
    pthread_create(&threadC, NULL, printC, NULL);

    // Wait for threads to finish
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    // Destroy semaphores
    sem_destroy(&semA);
    sem_destroy(&semB);
    sem_destroy(&semC);

    return 0;
}