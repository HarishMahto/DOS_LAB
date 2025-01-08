#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define PRODUCE_COUNT 20

int buffer[BUFFER_SIZE];
int in = 0; // Index for the next produced item
int out = 0; // Index for the next consumed item

sem_t empty; // Semaphore to count empty slots
sem_t full;  // Semaphore to count full slots
pthread_mutex_t mutex; // Mutex for critical section

void* producer(void* arg) {
    for (int i = 1; i <= PRODUCE_COUNT; i++) {
        int item = i; // Produce an item (1 to 20)
        
        // Wait for an empty slot
        sem_wait(&empty);
        
        // Lock the mutex to access the buffer
        pthread_mutex_lock(&mutex);
        
        // Produce the item
        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE; // Circular buffer
        
        // Unlock the mutex
        pthread_mutex_unlock(&mutex);
        
        // Signal that a new item is available
        sem_post(&full);
        
        // Simulate some processing time
        usleep(rand() % 100000);
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < PRODUCE_COUNT; i++) {
        // Wait for a full slot
        sem_wait(&full);
        
        // Lock the mutex to access the buffer
        pthread_mutex_lock(&mutex);
        
        // Consume the item
        int item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE; // Circular buffer
        
        // Unlock the mutex
        pthread_mutex_unlock(&mutex);
        
        // Signal that an empty slot is available
        sem_post(&empty);
        
        // Simulate some processing time
        usleep(rand() % 100000);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE); // All slots are empty initially
    sem_init(&full, 0, 0); // No slots are full initially
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for both threads to finish
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Clean up
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
