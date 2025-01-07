#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_NUM 20

sem_t sem_odd;  // Semaphore for odd numbers
sem_t sem_even; // Semaphore for even numbers

void* print_odd(void* arg) {
    for (int i = 1; i <= MAX_NUM; i += 2) {
        sem_wait(&sem_odd); // Wait for the odd semaphore
        printf("%d\n", i);  // Print odd number
        sem_post(&sem_even); // Signal the even semaphore
    }
    return NULL;
}

void* print_even(void* arg) {
    for (int i = 2; i <= MAX_NUM; i += 2) {
        sem_wait(&sem_even); // Wait for the even semaphore
        printf("%d\n", i);   // Print even number
        sem_post(&sem_odd);  // Signal the odd semaphore
    }
    return NULL;
}

int main() {
    pthread_t thread_odd, thread_even;

    // Initialize semaphores
    sem_init(&sem_odd, 0, 1);  // Start with odd semaphore available
    sem_init(&sem_even, 0, 0); // Even semaphore is not available initially

    // Create threads
    pthread_create(&thread_odd, NULL, print_odd, NULL);
    pthread_create(&thread_even, NULL, print_even, NULL);

    // Wait for threads to finish
    pthread_join(thread_odd, NULL);
    pthread_join(thread_even, NULL);

    // Clean up
    sem_destroy(&sem_odd);
    sem_destroy(&sem_even);

    return 0;
}
