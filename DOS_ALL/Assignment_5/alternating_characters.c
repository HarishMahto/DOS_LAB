#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_COUNT 20

sem_t sem_A; // Semaphore for thread A
sem_t sem_B; // Semaphore for thread B

void* print_A(void* arg) {
    for (int i = 0; i < MAX_COUNT; i++) {
        sem_wait(&sem_A); // Wait for semaphore A
        printf("A");
        sem_post(&sem_B); // Signal semaphore B
    }
    return NULL;
}

void* print_B(void* arg) {
    for (int i = 0; i < MAX_COUNT; i++) {
        sem_wait(&sem_B); // Wait for semaphore B
        printf("B");
        sem_post(&sem_A); // Signal semaphore A
    }
    return NULL;
}

int main() {
    pthread_t thread_A, thread_B;

    // Initialize semaphores
    sem_init(&sem_A, 0, 1); // Start with A's semaphore available
    sem_init(&sem_B, 0, 0); // B's semaphore is not available initially

    // Create threads
    pthread_create(&thread_A, NULL, print_A, NULL);
    pthread_create(&thread_B, NULL, print_B, NULL);

    // Wait for threads to finish
    pthread_join(thread_A, NULL);
    pthread_join(thread_B, NULL);

    // Clean up
    sem_destroy(&sem_A);
    sem_destroy(&sem_B);

    printf("\n"); // New line after completion
    return 0;
}
